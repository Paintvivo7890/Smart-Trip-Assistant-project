// main_GUI.cpp — Smart Trip Assistant  [CYBERPUNK TECH EDITION]
// Compile: g++ main_GUI.cpp input.cpp recommendation.cpp dataENG.cpp -o test.exe -mwindows -lcomctl32 -lgdi32
//
// UI Design: Dark cyberpunk terminal x Modern SaaS Dashboard
//   - Full custom GDI painting (no default Windows widget look)
//   - Neon glow buttons with hover animation
//   - Animated scan-line + pulse header
//   - Card-based panel layout
//   - Color palette: #0a0e1a (bg) / #00d4ff (cyan) / #39ff14 (green) / #ff6b35 (orange)

#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "recommendation.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdi32.lib")

// ═══════════════════════════════════════════════════════
//  COLOR PALETTE
// ═══════════════════════════════════════════════════════
#define C_BG        RGB(10,  14,  26)
#define C_PANEL     RGB(16,  22,  40)
#define C_ACCENT1   RGB(0,  212, 255)   // cyan
#define C_ACCENT2   RGB(57, 255,  20)   // electric green
#define C_ACCENT3   RGB(255,107,  53)   // neon orange
#define C_TEXT      RGB(220, 240, 255)
#define C_TEXTDIM   RGB(100, 140, 180)
#define C_HOVER     RGB(0,   50,  80)
#define C_INPUT_BG  RGB(8,   16,  32)

// ═══════════════════════════════════════════════════════
//  CONTROL IDs
// ═══════════════════════════════════════════════════════
#define ID_BTN_PLAN      101
#define ID_BTN_EAT       102
#define ID_BTN_EXIT      103
#define ID_TIMER_ANIM    200

#define ID_E_PEOPLE      201
#define ID_E_BUDGET      202
#define ID_E_DAYS        203
#define ID_CB_PROVINCE   205
#define ID_CB_STYLE      206
#define ID_BTN_SEARCH    207
#define ID_LIST_RESULT   208
#define ID_BTN_CLOSE     209

#define ID_E_CUSTOMER    301
#define ID_CB_CATEGORY   302
#define ID_BTN_GO        303
#define ID_LIST_EAT      304
#define ID_BTN_CLOSE_EAT 305

// ═══════════════════════════════════════════════════════
//  GLOBALS
// ═══════════════════════════════════════════════════════
HINSTANCE g_hInst     = NULL;
HWND      g_hMain     = NULL;
HBRUSH    g_darkBrush  = NULL;
HBRUSH    g_panelBrush = NULL;
HBRUSH    g_inputBrush = NULL;

static int  g_scanY    = 0;
static int  g_pulse    = 0;
static bool g_pulseFwd = true;
static int  g_hoverBtn = -1;

// ═══════════════════════════════════════════════════════
//  UTILITY
// ═══════════════════════════════════════════════════════
static std::string GetDlgStr(HWND h, int id) {
    char buf[512]={};
    GetDlgItemTextA(h, id, buf, 512);
    return buf;
}
static int GetDlgInt(HWND h, int id) {
    try { return std::stoi(GetDlgStr(h,id)); } catch(...){ return 0; }
}
static void LB_Add(HWND h, const std::string& s) {
    SendMessageA(h, LB_ADDSTRING, 0, (LPARAM)s.c_str());
}
static void CB_AddA(HWND h, const char* s) {
    SendMessageA(h, CB_ADDSTRING, 0, (LPARAM)s);
}

// ═══════════════════════════════════════════════════════
//  DATA
// ═══════════════════════════════════════════════════════
static const char* PROVINCES[] = {
    "Chiang Mai","Chiang Rai","Mae Hong Son","Lamphun","Lampang",
    "Phayao","Phrae","Nan","Uttaradit","Tak",
    "Sukhothai","Phitsanulok","Kamphaeng Phet","Phetchabun","Phichit",
    "Nakhon Sawan","Uthai Thani"
};
static const char* STYLES[] = {
    "Culture","Adventure","Natural","Photo","Cafe","Random"
};

static std::vector<Place> SearchPlaces(int pvSel, int stSel) {
    vector<int> pv = { pvSel + 1 };
    vector<int> st = { stSel + 1 };
    vector<Place> f = Screening_province(allplace, pv);
    if (stSel == 5) return f;
    return Recommendation_place(f, st);
}

// ═══════════════════════════════════════════════════════
//  GDI HELPERS
// ═══════════════════════════════════════════════════════
static HFONT MakeFont(int size, bool bold, bool mono) {
    LOGFONTA lf={};
    lf.lfHeight  = -size;
    lf.lfWeight  = bold ? FW_BOLD : FW_NORMAL;
    lf.lfCharSet = DEFAULT_CHARSET;
    strcpy_s(lf.lfFaceName, mono ? "Consolas" : "Segoe UI");
    return CreateFontIndirectA(&lf);
}

static void FillRR(HDC hdc, RECT r, COLORREF fill, COLORREF border, int rad=6) {
    HBRUSH br = CreateSolidBrush(fill);
    HPEN   pn = CreatePen(PS_SOLID, 1, border);
    SelectObject(hdc, br); SelectObject(hdc, pn);
    RoundRect(hdc, r.left, r.top, r.right, r.bottom, rad, rad);
    DeleteObject(br); DeleteObject(pn);
}

static void GlowRect(HDC hdc, RECT r, COLORREF col, int glow=2) {
    for (int i=glow; i>=1; i--) {
        COLORREF dim = RGB(GetRValue(col)/(i*2+1),
                          GetGValue(col)/(i*2+1),
                          GetBValue(col)/(i*2+1));
        HPEN p = CreatePen(PS_SOLID,1,dim);
        HPEN op=(HPEN)SelectObject(hdc,p);
        SelectObject(hdc,GetStockObject(NULL_BRUSH));
        RECT gr={r.left-i,r.top-i,r.right+i,r.bottom+i};
        RoundRect(hdc,gr.left,gr.top,gr.right,gr.bottom,6,6);
        SelectObject(hdc,op); DeleteObject(p);
    }
    HPEN p=CreatePen(PS_SOLID,1,col);
    HPEN op=(HPEN)SelectObject(hdc,p);
    SelectObject(hdc,GetStockObject(NULL_BRUSH));
    RoundRect(hdc,r.left,r.top,r.right,r.bottom,6,6);
    SelectObject(hdc,op); DeleteObject(p);
}

static void TxtC(HDC hdc, const char* t, RECT r, COLORREF c, int sz=12, bool b=false, bool m=false) {
    HFONT f=MakeFont(sz,b,m), of=(HFONT)SelectObject(hdc,f);
    SetTextColor(hdc,c); SetBkMode(hdc,TRANSPARENT);
    DrawTextA(hdc,t,-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    SelectObject(hdc,of); DeleteObject(f);
}
static void TxtL(HDC hdc, const char* t, int x, int y, COLORREF c, int sz=11, bool b=false, bool m=false) {
    HFONT f=MakeFont(sz,b,m), of=(HFONT)SelectObject(hdc,f);
    SetTextColor(hdc,c); SetBkMode(hdc,TRANSPARENT);
    TextOutA(hdc,x,y,t,(int)strlen(t));
    SelectObject(hdc,of); DeleteObject(f);
}

// ═══════════════════════════════════════════════════════
//  CUSTOM BUTTON PAINT
// ═══════════════════════════════════════════════════════
static void PaintNeonBtn(HDC hdc, RECT rc, const char* label, COLORREF accent, bool hover, bool press) {
    COLORREF bg = press ? RGB(0,80,120) : hover ? C_HOVER : C_PANEL;
    FillRR(hdc, rc, bg, accent, 8);

    if (hover || press) {
        // top highlight stripe
        HPEN hp=CreatePen(PS_SOLID,1,accent);
        HPEN op=(HPEN)SelectObject(hdc,hp);
        MoveToEx(hdc,rc.left+12,rc.top+1,NULL); LineTo(hdc,rc.right-12,rc.top+1);
        SelectObject(hdc,op); DeleteObject(hp);
        // bottom dim line
        COLORREF dim=RGB(GetRValue(accent)/3,GetGValue(accent)/3,GetBValue(accent)/3);
        HPEN hp2=CreatePen(PS_SOLID,1,dim);
        op=(HPEN)SelectObject(hdc,hp2);
        MoveToEx(hdc,rc.left+12,rc.bottom-2,NULL); LineTo(hdc,rc.right-12,rc.bottom-2);
        SelectObject(hdc,op); DeleteObject(hp2);
    }

    GlowRect(hdc, rc, accent, hover ? 3 : 1);
    COLORREF txtC = hover ? RGB(255,255,255) : accent;
    TxtC(hdc, label, rc, txtC, 11, true, true);
}

// ═══════════════════════════════════════════════════════
//  MAIN WINDOW PAINT
// ═══════════════════════════════════════════════════════
static void PaintMain(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    RECT cl; GetClientRect(hWnd, &cl);
    int W=cl.right, H=cl.bottom;

    // double-buffer
    HDC mem=CreateCompatibleDC(hdc);
    HBITMAP bmp=CreateCompatibleBitmap(hdc,W,H);
    HBITMAP ob=(HBITMAP)SelectObject(mem,bmp);

    // background gradient
    for (int y=0;y<H;y++) {
        HPEN p=CreatePen(PS_SOLID,1,RGB(10+y*3/H, 14+y*5/H, 26+y*18/H));
        HPEN op=(HPEN)SelectObject(mem,p);
        MoveToEx(mem,0,y,NULL); LineTo(mem,W,y);
        SelectObject(mem,op); DeleteObject(p);
    }

    // grid dots
    for (int gx=25;gx<W;gx+=30)
    for (int gy=25;gy<H;gy+=30)
        SetPixel(mem,gx,gy,RGB(0,40,65));

    // scan line
    {
        HPEN sp=CreatePen(PS_SOLID,1,RGB(0,55,75));
        HPEN op=(HPEN)SelectObject(mem,sp);
        MoveToEx(mem,0,g_scanY,NULL); LineTo(mem,W,g_scanY);
        SelectObject(mem,op); DeleteObject(sp);
    }

    // top gradient bar (cyan → green)
    for (int x=0;x<W;x++) {
        float t=(float)x/W;
        SetPixel(mem,x,0,RGB((int)(t*57),(int)(212+t*43),(int)(255-t*235)));
        SetPixel(mem,x,1,RGB((int)(t*20),(int)(80+t*20),(int)(80-t*60)));
    }

    // corner brackets
    auto corner=[&](int x,int y,int sx,int sy){
        HPEN cp=CreatePen(PS_SOLID,2,C_ACCENT2);
        HPEN op=(HPEN)SelectObject(mem,cp);
        MoveToEx(mem,x,y+sy*12,NULL); LineTo(mem,x,y); LineTo(mem,x+sx*12,y);
        SelectObject(mem,op); DeleteObject(cp);
    };
    corner(22,22, 1, 1); corner(W-22,22,-1, 1);
    corner(22,H-22,1,-1); corner(W-22,H-22,-1,-1);

    // version tag
    TxtL(mem,"v2.0  //  NORTHERN THAILAND  //  920 LOCATIONS",24,14,C_TEXTDIM,8,false,true);

    // main title
    RECT tr={0,38,W,72};
    TxtC(mem,"SMART TRIP ASSISTANT",tr,C_ACCENT1,20,true,false);

    // animated subtitle
    int brite=80+(int)(g_pulse*1.7f); if(brite>255)brite=255;
    COLORREF subC=RGB(0,(int)(brite*0.83f),(int)(brite*1.0f));
    RECT sr={0,74,W,94};
    TxtC(mem,"[ PLAN  //  DISCOVER  //  EAT ]",sr,subC,9,false,true);

    // divider
    {
        HPEN lp=CreatePen(PS_SOLID,1,RGB(0,60,90));
        HPEN op=(HPEN)SelectObject(mem,lp);
        MoveToEx(mem,44,104,NULL); LineTo(mem,W-44,104);
        SelectObject(mem,op); DeleteObject(lp);
        // accent dots on divider
        SetPixel(mem,44,104,C_ACCENT1); SetPixel(mem,W-44,104,C_ACCENT1);
    }

    // status bar
    {
        RECT sb={0,H-26,W,H};
        FillRR(mem,sb,RGB(6,10,20),C_PANEL,0);
        // blinking dot
        COLORREF dot=g_pulseFwd ? C_ACCENT2 : RGB(0,80,0);
        HBRUSH db=CreateSolidBrush(dot);
        HBRUSH ob2=(HBRUSH)SelectObject(mem,db);
        SelectObject(mem,GetStockObject(NULL_PEN));
        Ellipse(mem,14,H-19,22,H-11);
        SelectObject(mem,ob2); DeleteObject(db);
        TxtL(mem,"SYSTEM READY  |  17 PROVINCES  |  920 LOCATIONS  |  5 STYLES",30,H-21,C_TEXTDIM,8,false,true);
    }

    BitBlt(hdc,0,0,W,H,mem,0,0,SRCCOPY);
    SelectObject(mem,ob); DeleteObject(bmp); DeleteDC(mem);
    EndPaint(hWnd,&ps);
}

// ═══════════════════════════════════════════════════════
//  DARK THEME for Dialogs
// ═══════════════════════════════════════════════════════
static INT_PTR DarkTheme(HWND hDlg, UINT msg, WPARAM wParam, LPARAM) {
    switch(msg) {
    case WM_CTLCOLORDLG:
        return (INT_PTR)g_panelBrush;
    case WM_CTLCOLORSTATIC: {
        HDC h=(HDC)wParam; SetTextColor(h,C_TEXT); SetBkColor(h,C_PANEL);
        return (INT_PTR)g_panelBrush;
    }
    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORLISTBOX: {
        HDC h=(HDC)wParam; SetTextColor(h,C_ACCENT2); SetBkColor(h,C_INPUT_BG);
        return (INT_PTR)g_inputBrush;
    }
    case WM_CTLCOLORBTN: {
        HDC h=(HDC)wParam; SetTextColor(h,C_ACCENT1); SetBkColor(h,C_PANEL);
        return (INT_PTR)g_panelBrush;
    }
    }
    return 0;
}

// ═══════════════════════════════════════════════════════
//  PLAN TRIP DIALOG
// ═══════════════════════════════════════════════════════
INT_PTR CALLBACK PlanDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    INT_PTR dt=DarkTheme(hDlg,msg,wParam,lParam);
    if(dt) return dt;

    switch(msg) {
    case WM_INITDIALOG: {
        HWND hPv=GetDlgItem(hDlg,ID_CB_PROVINCE);
        for(auto& p:PROVINCES) CB_AddA(hPv,p);
        SendMessage(hPv,CB_SETCURSEL,0,0);

        HWND hSt=GetDlgItem(hDlg,ID_CB_STYLE);
        for(auto& s:STYLES) CB_AddA(hSt,s);
        SendMessage(hSt,CB_SETCURSEL,0,0);

        HFONT f=MakeFont(11,false,true);
        SendMessage(GetDlgItem(hDlg,ID_LIST_RESULT),WM_SETFONT,(WPARAM)f,TRUE);
        return TRUE;
    }
    case WM_COMMAND: {
        int wID=LOWORD(wParam);
        if(wID==ID_BTN_SEARCH) {
            int people=GetDlgInt(hDlg,ID_E_PEOPLE);
            int budget=GetDlgInt(hDlg,ID_E_BUDGET);
            int days  =GetDlgInt(hDlg,ID_E_DAYS);
            int pvSel =(int)SendMessage(GetDlgItem(hDlg,ID_CB_PROVINCE),CB_GETCURSEL,0,0);
            int stSel =(int)SendMessage(GetDlgItem(hDlg,ID_CB_STYLE),   CB_GETCURSEL,0,0);
            HWND hList=GetDlgItem(hDlg,ID_LIST_RESULT);

            if(people<=0||days<=0){
                MessageBoxA(hDlg,"People and Days must be > 0","Input Error",MB_OK|MB_ICONWARNING);
                return TRUE;
            }

            auto results=SearchPlaces(pvSel,stSel);
            SendMessage(hList,LB_RESETCONTENT,0,0);

            LB_Add(hList,"  +------------------------------------------+");
            LB_Add(hList,"  |  SEARCH RESULTS                          |");
            LB_Add(hList,"  |  Province  : "+std::string(PROVINCES[pvSel])+"        ");
            LB_Add(hList,"  |  Style     : "+std::string(STYLES[stSel])+"           ");
            LB_Add(hList,"  |  Travelers : "+std::to_string(people)+" person(s)       ");
            LB_Add(hList,"  |  Days      : "+std::to_string(days)+"                 ");
            LB_Add(hList,"  +------------------------------------------+");
            LB_Add(hList,"");

            if(results.empty()){
                LB_Add(hList,"  >> NO RESULTS FOUND <<");
            } else {
                int no=1,total=0;
                for(auto& p:results){
                    std::string n2=(no<10?"  0":"  ")+std::to_string(no++);
                    LB_Add(hList,"  -----------------------------------------");
                    LB_Add(hList,n2+"  "+p.name);
                    LB_Add(hList,"      District : "+p.district);
                    LB_Add(hList,"      Fee      : "+(p.price==0?std::string("FREE"):std::to_string(p.price)+" THB/person"));
                    total+=p.price*people;
                }
                LB_Add(hList,"  =========================================");
                LB_Add(hList,"  TOTAL ENTRANCE  :  "+std::to_string(total)+" THB");
                if(budget>0)
                    LB_Add(hList,"  REMAINING       :  "+std::to_string(budget-total)+" THB");
                LB_Add(hList,"");
                LB_Add(hList,"  [ "+std::to_string(results.size())+" LOCATIONS FOUND ]");
            }
            return TRUE;
        }
        if(wID==ID_BTN_CLOSE||wID==IDCANCEL){EndDialog(hDlg,0);return TRUE;}
        break;
    }
    case WM_CLOSE: EndDialog(hDlg,0); return TRUE;
    }
    return FALSE;
}

// ═══════════════════════════════════════════════════════
//  EAT DIALOG
// ═══════════════════════════════════════════════════════
INT_PTR CALLBACK EatDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    INT_PTR dt=DarkTheme(hDlg,msg,wParam,lParam);
    if(dt) return dt;

    static const char* NL[]={"Pad Thai","Boat Noodles","Tom Yum Noodles","Khao Soi","Bamee Moo Daeng"};
    static const char* RI[]={"Khao Pad","Khao Man Gai","Khao Moo Daeng","Khao Na Ped","Khao Kha Moo"};
    static const char* AL[]={"Pad Thai","Boat Noodles","Khao Soi","Khao Pad","Khao Man Gai",
                              "Som Tum","Larb","Massaman Curry","Green Curry","Mango Sticky Rice"};
    switch(msg){
    case WM_INITDIALOG:{
        HWND hC=GetDlgItem(hDlg,ID_CB_CATEGORY);
        CB_AddA(hC,"Noodles"); CB_AddA(hC,"Rice"); CB_AddA(hC,"Surprise me!");
        SendMessage(hC,CB_SETCURSEL,0,0);
        HFONT f=MakeFont(11,false,true);
        SendMessage(GetDlgItem(hDlg,ID_LIST_EAT),WM_SETFONT,(WPARAM)f,TRUE);
        return TRUE;
    }
    case WM_COMMAND:{
        int wID=LOWORD(wParam);
        if(wID==ID_BTN_GO){
            int ctm=(int)GetDlgInt(hDlg,ID_E_CUSTOMER);
            int cat=(int)SendMessage(GetDlgItem(hDlg,ID_CB_CATEGORY),CB_GETCURSEL,0,0);
            HWND hList=GetDlgItem(hDlg,ID_LIST_EAT);

            if(ctm<=0){MessageBoxA(hDlg,"People > 0","Error",MB_OK|MB_ICONWARNING);return TRUE;}

            SendMessage(hList,LB_RESETCONTENT,0,0);
            LB_Add(hList,"  +------------------------------------------+");
            LB_Add(hList,"  |  MEAL RECOMMENDATION ENGINE              |");
            LB_Add(hList,"  |  Generating for "+std::to_string(ctm)+" person(s)...    ");
            LB_Add(hList,"  +------------------------------------------+");
            LB_Add(hList,"");

            srand((unsigned)GetTickCount());
            for(int i=1;i<=ctm;i++){
                std::string meal;
                if(cat==0)      meal=NL[rand()%5];
                else if(cat==1) meal=RI[rand()%5];
                else            meal=AL[rand()%10];
                LB_Add(hList,"  PERSON #"+std::to_string(i));
                LB_Add(hList,"  ----------------------------------------");
                LB_Add(hList,"  >>  "+meal);
                LB_Add(hList,"");
            }
            LB_Add(hList,"  [ ENJOY YOUR MEAL! ]");
            return TRUE;
        }
        if(wID==ID_BTN_CLOSE_EAT||wID==IDCANCEL){EndDialog(hDlg,0);return TRUE;}
        break;
    }
    case WM_CLOSE: EndDialog(hDlg,0); return TRUE;
    }
    return FALSE;
}

// ═══════════════════════════════════════════════════════
//  DIALOG BUILDER
// ═══════════════════════════════════════════════════════
struct DB {
    BYTE buf[8192]; int pos=0;
    void align4(){pos=(pos+3)&~3;}
    void w(WORD v){*(WORD*)(buf+pos)=v;pos+=2;}
    void dw(DWORD v){*(DWORD*)(buf+pos)=v;pos+=4;}
    void ws(const wchar_t* s){while(*s)w((WORD)*s++);w(0);}
    void ctrl(DWORD st,short x,short y,short wd,short ht,
              WORD id,const wchar_t* cls,const wchar_t* txt){
        align4(); dw(st|WS_CHILD|WS_VISIBLE); dw(0);
        w((WORD)x);w((WORD)y);w((WORD)wd);w((WORD)ht);w(id);
        ws(cls); ws(txt); w(0);
    }
};

static void ShowPlanDialog(HWND hP) {
    DB b;
    DLGTEMPLATE* d=(DLGTEMPLATE*)b.buf;
    d->style=DS_SETFONT|DS_MODALFRAME|DS_CENTER|WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME;
    d->dwExtendedStyle=0; d->cdit=0; d->x=0;d->y=0;d->cx=440;d->cy=400;
    b.pos=sizeof(DLGTEMPLATE);
    b.w(0);b.w(0); b.ws(L"[ SMART TRIP ]  Plan Your Journey");
    b.w(10); b.ws(L"Consolas");
    short n=0;
    auto a=[&](DWORD st,short x,short y,short w,short h,WORD id,const wchar_t* c,const wchar_t* t){b.ctrl(st,x,y,w,h,id,c,t);n++;};

    a(SS_LEFT,            8,  8,100,12, 0,               L"STATIC", L"Travelers :");
    a(WS_BORDER|ES_NUMBER,110, 6, 50,14,ID_E_PEOPLE,     L"EDIT",   L"1");
    a(SS_LEFT,           170,  8, 90,12, 0,               L"STATIC", L"Budget (0=skip) :");
    a(WS_BORDER|ES_NUMBER,265, 6, 60,14,ID_E_BUDGET,     L"EDIT",   L"0");
    a(SS_LEFT,           336,  8, 50,12, 0,               L"STATIC", L"Days :");
    a(WS_BORDER|ES_NUMBER,386, 6, 46,14,ID_E_DAYS,       L"EDIT",   L"1");

    a(SS_LEFT,            8, 28,100,12, 0,               L"STATIC", L"Province :");
    a(CBS_DROPDOWNLIST|WS_VSCROLL,110,26,150,160,ID_CB_PROVINCE,L"COMBOBOX",L"");
    a(SS_LEFT,           270, 28, 70,12, 0,               L"STATIC", L"Style :");
    a(CBS_DROPDOWNLIST|WS_VSCROLL,345,26,130,120,ID_CB_STYLE,L"COMBOBOX",L"");

    a(BS_PUSHBUTTON,      8, 50,130,18, ID_BTN_SEARCH,   L"BUTTON", L">> SEARCH <<");
    a(SS_LEFT,            8, 74,200,12, 0,               L"STATIC", L"RESULTS :");
    a(WS_BORDER|WS_VSCROLL|LBS_NOTIFY|LBS_NOINTEGRALHEIGHT,
                          8, 88,424,282,ID_LIST_RESULT,  L"LISTBOX",L"");
    a(BS_PUSHBUTTON,     372,378, 60,16,ID_BTN_CLOSE,    L"BUTTON", L"[ CLOSE ]");

    d->cdit=n;
    DialogBoxIndirectParamA(g_hInst,(DLGTEMPLATE*)b.buf,hP,PlanDlgProc,0);
}

static void ShowEatDialog(HWND hP) {
    DB b;
    DLGTEMPLATE* d=(DLGTEMPLATE*)b.buf;
    d->style=DS_SETFONT|DS_MODALFRAME|DS_CENTER|WS_POPUP|WS_CAPTION|WS_SYSMENU;
    d->dwExtendedStyle=0; d->cdit=0; d->x=0;d->y=0;d->cx=350;d->cy=350;
    b.pos=sizeof(DLGTEMPLATE);
    b.w(0);b.w(0); b.ws(L"[ SMART TRIP ]  What to Eat Today?");
    b.w(10); b.ws(L"Consolas");
    short n=0;
    auto a=[&](DWORD st,short x,short y,short w,short h,WORD id,const wchar_t* c,const wchar_t* t){b.ctrl(st,x,y,w,h,id,c,t);n++;};

    a(SS_LEFT,            8,  8,100,12, 0,               L"STATIC",  L"People :");
    a(WS_BORDER|ES_NUMBER,100, 6, 50,14,ID_E_CUSTOMER,   L"EDIT",    L"1");
    a(SS_LEFT,           160,  8, 80,12, 0,               L"STATIC",  L"Dish Type :");
    a(CBS_DROPDOWNLIST|WS_VSCROLL,248,6,96,80,ID_CB_CATEGORY,L"COMBOBOX",L"");
    a(BS_PUSHBUTTON,      8, 26,150,18, ID_BTN_GO,        L"BUTTON",  L">> GENERATE <<");
    a(SS_LEFT,            8, 50,200,12, 0,               L"STATIC",  L"RESULTS :");
    a(WS_BORDER|WS_VSCROLL|LBS_NOTIFY|LBS_NOINTEGRALHEIGHT,
                          8, 64,334,260,ID_LIST_EAT,     L"LISTBOX", L"");
    a(BS_PUSHBUTTON,     284,330, 60,14,ID_BTN_CLOSE_EAT,L"BUTTON",  L"[ CLOSE ]");

    d->cdit=n;
    DialogBoxIndirectParamA(g_hInst,(DLGTEMPLATE*)b.buf,hP,EatDlgProc,0);
}

// ═══════════════════════════════════════════════════════
//  MAIN WINDOW PROC
// ═══════════════════════════════════════════════════════
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
    case WM_CREATE: {
        g_darkBrush  = CreateSolidBrush(C_BG);
        g_panelBrush = CreateSolidBrush(C_PANEL);
        g_inputBrush = CreateSolidBrush(C_INPUT_BG);

        // Owner-draw buttons
        CreateWindowA("BUTTON","",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,
            80,128,240,44,hWnd,(HMENU)ID_BTN_PLAN,g_hInst,NULL);
        CreateWindowA("BUTTON","",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,
            80,186,240,44,hWnd,(HMENU)ID_BTN_EAT,g_hInst,NULL);
        CreateWindowA("BUTTON","",WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,
            80,244,240,44,hWnd,(HMENU)ID_BTN_EXIT,g_hInst,NULL);

        SetTimer(hWnd,ID_TIMER_ANIM,50,NULL);
        return 0;
    }
    case WM_TIMER: {
        RECT rc; GetClientRect(hWnd,&rc);
        g_scanY=(g_scanY+2)%rc.bottom;
        if(g_pulseFwd){g_pulse+=3;if(g_pulse>=100)g_pulseFwd=false;}
        else           {g_pulse-=3;if(g_pulse<=0)  g_pulseFwd=true;}
        InvalidateRect(hWnd,NULL,FALSE);
        return 0;
    }
    case WM_PAINT:    PaintMain(hWnd); return 0;
    case WM_ERASEBKGND: return 1;

    case WM_DRAWITEM: {
        DRAWITEMSTRUCT* di=(DRAWITEMSTRUCT*)lParam;
        if(di->CtlType!=ODT_BUTTON) break;
        bool hov=(g_hoverBtn==(int)di->CtlID);
        bool press=(di->itemState&ODS_SELECTED)!=0;
        const char* lbl=""; COLORREF acc=C_ACCENT1;
        if(di->CtlID==ID_BTN_PLAN) {lbl="[ 1 ]   PLAN TRIP";          acc=C_ACCENT1;}
        if(di->CtlID==ID_BTN_EAT)  {lbl="[ 2 ]   WHAT TO EAT TODAY?"; acc=C_ACCENT2;}
        if(di->CtlID==ID_BTN_EXIT) {lbl="[ 3 ]   EXIT SYSTEM";         acc=C_ACCENT3;}
        PaintNeonBtn(di->hDC,di->rcItem,lbl,acc,hov,press);
        return TRUE;
    }

    case WM_MOUSEMOVE: {
        POINT pt={LOWORD(lParam),(short)HIWORD(lParam)};
        int prev=g_hoverBtn; g_hoverBtn=-1;
        HWND btns[]={GetDlgItem(hWnd,ID_BTN_PLAN),GetDlgItem(hWnd,ID_BTN_EAT),GetDlgItem(hWnd,ID_BTN_EXIT)};
        int ids[]={ID_BTN_PLAN,ID_BTN_EAT,ID_BTN_EXIT};
        for(int i=0;i<3;i++){
            RECT r; GetWindowRect(btns[i],&r);
            MapWindowPoints(NULL,hWnd,(POINT*)&r,2);
            if(PtInRect(&r,pt)){g_hoverBtn=ids[i];break;}
        }
        if(g_hoverBtn!=prev)
            for(auto& b:btns) InvalidateRect(b,NULL,TRUE);
        return 0;
    }

    case WM_COMMAND:
        switch(LOWORD(wParam)){
        case ID_BTN_PLAN:  ShowPlanDialog(hWnd); break;
        case ID_BTN_EAT:   ShowEatDialog(hWnd);  break;
        case ID_BTN_EXIT:  DestroyWindow(hWnd);  break;
        }
        return 0;

    case WM_DESTROY:
        KillTimer(hWnd,ID_TIMER_ANIM);
        DeleteObject(g_darkBrush);
        DeleteObject(g_panelBrush);
        DeleteObject(g_inputBrush);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hWnd,msg,wParam,lParam);
}

// ═══════════════════════════════════════════════════════
//  WINMAIN
// ═══════════════════════════════════════════════════════
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nShow) {
    g_hInst=hInst;
    srand((unsigned)time(0));
    InitCommonControls();

    WNDCLASSEXA wc={};
    wc.cbSize=sizeof(wc);
    wc.style=CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
    wc.lpfnWndProc=MainWndProc;
    wc.hInstance=hInst;
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground=CreateSolidBrush(C_BG);
    wc.lpszClassName="SmartTripCyberpunk";
    wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    RegisterClassExA(&wc);

    int sw=GetSystemMetrics(SM_CXSCREEN);
    int sh=GetSystemMetrics(SM_CYSCREEN);
    int ww=400, wh=330;

    g_hMain=CreateWindowExA(
        WS_EX_LAYERED,
        "SmartTripCyberpunk",
        "Smart Trip Assistant  |  v2.0  CYBERPUNK",
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
        (sw-ww)/2,(sh-wh)/2,ww,wh,
        NULL,NULL,hInst,NULL);

    // slight transparency
    SetLayeredWindowAttributes(g_hMain,0,242,LWA_ALPHA);

    ShowWindow(g_hMain,nShow);
    UpdateWindow(g_hMain);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
