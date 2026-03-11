// ╔══════════════════════════════════════════════════════════════════════════╗
//  SMART TRIP ASSISTANT v8 — Win32 API | ULTRA Dark Neon Edition
//  ✨ Feature 1 : Plan Trip      — เลือกสถานที่ท่องเที่ยว (Wizard 3 ขั้น)
//  🍜 Feature 2 : What to Eat   — แนะนำร้านอาหาร (Wizard 4 ขั้น)
//  🤖 Feature 3 : AI Advisor    — AI แนะนำทริปอัจฉริยะ
//  💾 Feature 4 : View Saved    — เปิดไฟล์สรุปทริปที่บันทึก
// ╚══════════════════════════════════════════════════════════════════════════╝
//
//  วิธีคอมไพล์ (MinGW g++ 64-bit):
//
//  g++ main_pro_GUI_v8.cpp dataENG.cpp -o SmartTrip.exe ^
//      -lgdi32 -luser32 -lshell32 -lcomctl32 -mwindows -std=c++17 -O2
//
// ══════════════════════════════════════════════════════════════════════════
//  ★ = จุดที่แก้ไขง่าย  |  ทุกค่าสีและขนาดอยู่ใน Section 1-2
// ══════════════════════════════════════════════════════════════════════════

//g++ main_GUI.cpp dataENG.cpp input.cpp recommendation.cpp calculation.cpp receipt.cpp -o TripGUI.exe -lgdi32 -luser32 -lshell32 -mwindows -std=c++17 -O2
//g++ main_GUI.cpp dataENG.cpp-o TripGUI.exe -lgdi32 -luser32 -lshell32 -mwindows -std=c++17 -O2
//-lwinhttp
// #include <winhttp.h>
// #pragma comment(lib, "winhttp.lib")
// std::string CallClaude(std::string prompt) {
//     // เปิด connection ไป api.anthropic.com
//     HINTERNET hSession = WinHttpOpen(L"SmartTrip", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, 0, 0, 0);
//     HINTERNET hConnect = WinHttpConnect(hSession, L"api.anthropic.com", 443, 0);
//     HINTERNET hReq    = WinHttpOpenRequest(hConnect, L"POST", L"/v1/messages",
//                             0, 0, 0, WINHTTP_FLAG_SECURE);

//     // Header
//     WinHttpAddRequestHeaders(hReq, L"x-api-key: YOUR_API_KEY", -1, 0);
//     WinHttpAddRequestHeaders(hReq, L"anthropic-version: 2023-06-01", -1, 0);
//     WinHttpAddRequestHeaders(hReq, L"content-type: application/json", -1, 0);

//     // Body JSON
//     std::string body = R"({"model":"claude-sonnet-4-20250514","max_tokens":1024,"messages":[{"role":"user","content":")" + prompt + R"("}]})";

//     // Send
//     WinHttpSendRequest(hReq, 0, 0, (LPVOID)body.c_str(), body.size(), body.size(), 0);
//     WinHttpReceiveResponse(hReq, 0);

//     // อ่าน response
//     std::string response;
//     DWORD size = 0;
//     do {
//         WinHttpQueryDataAvailable(hReq, &size);
//         std::string buf(size, 0);
//         DWORD downloaded = 0;
//         WinHttpReadData(hReq, &buf[0], size, &downloaded);
//         response += buf;
//     } while (size > 0);

//     return response; // เป็น JSON ดิบ ต้อง parse ต่อ
// }

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")

// clang-format off
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
// clang-format on
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "dataENG.h"

// ══════════════════════════════════════════════════════════════════════════
// SECTION 1 ★ — Palette (Dark Neon Cyber)
// ══════════════════════════════════════════════════════════════════════════

// พื้นหลัง
#define BG_BASE    RGB(8,  10, 22)    // ★ พื้นหลังหลัก (เข้มมาก)
#define BG_DEEP    RGB(5,   6, 16)    // พื้นหลังลึก (gradient ล่างสุด)
#define BG_PANEL   RGB(14, 18, 38)    // พาเนล / การ์ด
#define BG_CARD    RGB(18, 24, 46)    // การ์ดย่อย
#define BG_GLASS   RGB(22, 28, 54)    // Glass-morphism layer
#define BG_ROW_A   RGB(16, 20, 42)    // แถวตาราง สีคู่
#define BG_ROW_B   RGB(20, 26, 50)    // แถวตาราง สีคี่
#define BG_ROW_S   RGB(30, 80,170)    // แถวที่เลือก
#define BG_HEADER  RGB(12, 16, 32)    // Header / Footer
#define BG_TBL_H   RGB(10, 28, 70)    // หัวตาราง
#define BG_SURF    RGB(20, 24, 48)    // Surface ผิวบาง

// Accent — Neon
#define AC_CYAN    RGB(0,  230, 200)  // ★ หลัก: Cyan นีออน
#define AC_BLUE    RGB(50, 140, 255)  // ฟ้าสด
#define AC_BL      RGB(80, 160, 255)  // ฟ้าอ่อน
#define AC_BD      RGB(20,  60, 155)  // ฟ้าเข้ม
#define AC_PUR     RGB(160, 80, 255)  // ม่วงนีออน
#define AC_PD      RGB( 80, 35, 140)  // ม่วงเข้ม
#define AC_GRN     RGB(30,  220, 120) // ★ เขียวนีออน
#define AC_GD      RGB(12,  100,  50) // เขียวเข้ม
#define AC_ORG     RGB(255, 160,  40) // ส้มนีออน
#define AC_RED     RGB(255,  60,  80) // แดงนีออน
#define AC_GOLD    RGB(255, 210,  60) // ทอง AI
#define AC_PINK    RGB(255,  80, 180) // ชมพูนีออน

// ข้อความ
#define TXT_HI     RGB(230, 242, 255) // สว่างสุด
#define TXT_M      RGB(130, 148, 195) // กลาง
#define TXT_D      RGB( 60,  72, 115) // หมอง

// ขอบ
#define BRD_N      RGB( 30,  36,  72) // ปกติ
#define BRD_H      RGB( 50,  90, 175) // Hover
#define BRD_G      RGB(  0, 200, 170) // Glow (cyan)

// ปุ่ม
#define BTN_N      RGB(18, 22, 48)
#define BTN_RN     RGB(55, 15, 20)
#define BTN_RH     RGB(200, 40, 55)
#define BTN_GN     RGB(12, 38, 24)
#define BTN_SN     RGB(20, 30, 65)
#define BTN_SH     RGB(40, 60,120)
#define BTN_YN     RGB(50, 42,  8)
#define BTN_YH     RGB(200,160, 20)

// ══════════════════════════════════════════════════════════════════════════
// SECTION 2 ★ — ขนาดหน้าต่าง / ID
// ══════════════════════════════════════════════════════════════════════════

#define MW   1060   // ★ ความกว้างหน้าต่างหลัก (px)
#define MH    700   // ★ ความสูงหน้าต่างหลัก (px)
#define WW    860   // Wizard popup กว้าง
#define WH    640   // Wizard popup สูง
#define RW    960   // Result popup กว้าง
#define RH2   700   // Result popup สูง
#define AW    820   // AI popup กว้าง
#define AH    580   // AI popup สูง

// IDs
#define ID_NEXT   201
#define ID_BACK   202
#define ID_QUIT   203
#define ID_DONE   204
#define ID_SAVE   301
#define ID_CLEAR  302
#define ID_CLOSE  303
#define ID_ASKAI  401
#define ID_LIST   501
#define ID_TANIM  601
#define ID_TSCAN  602
#define ID_TPART  603   // Timer particle
#define ID_TTYPE  604   // Timer typewriter (AI)

// ══════════════════════════════════════════════════════════════════════════
// SECTION 3 — Struct & Global
// ══════════════════════════════════════════════════════════════════════════

// Struct ปุ่ม (custom animated)
struct CBtn {
  RECT rc;
  std::wstring lbl, ico;
  int id;
  COLORREF cN, cH, cP;
  bool hov = false, dn = false;
  float an = 0.f;   // 0→1 animation progress
  float pulse = 0.f;// pulse glow
};

// Struct ข้อมูลที่ user เลือก
struct Pick {
  std::wstring name, cat, province;
  int cost;
  bool isFood;
  Pick() : cost(0), isFood(false) {}
  Pick(std::wstring n, std::wstring c, std::wstring p, int co, bool f)
    : name(n), cat(c), province(p), cost(co), isFood(f) {}
};

// Struct Particle สำหรับ background
struct Particle {
  float x, y, vx, vy, size, alpha, life, maxLife;
  COLORREF col;
};

// Helper: narrow → wide
std::wstring S2W(const std::string &s) {
  return std::wstring(s.begin(), s.end());
}

// ── Global State ──────────────────────────────────────────────────────────
HINSTANCE g_hI      = nullptr;
HWND      g_hMain   = nullptr;
HWND      g_hWiz    = nullptr;
HWND      g_hRes    = nullptr;
HWND      g_hAI     = nullptr;
HWND      g_hList   = nullptr;

int   g_wizMode   = 0;   // 0=Place, 1=Food
int   g_step      = 0;
int   g_selProv   = 0;
int   g_selStyle  = 0;
int   g_selDist   = 0;
int   g_selType   = 0;

std::vector<Place>      g_filtPlaces;
std::vector<restaurant> g_filtRests;
std::vector<Pick>       g_picks;

// ── Animation State ───────────────────────────────────────────────────────
int   g_tick      = 0;
float g_sinT      = 0.f;
float g_cosT      = 0.f;
int   g_scanY     = 0;
bool  g_glowP     = false;
float g_bgShift   = 0.f;    // background aurora shift
float g_starBlink = 0.f;    // star blink phase

// Particles
std::vector<Particle> g_particles;
std::mt19937 g_rng(42);

// AI Typewriter
std::wstring g_aiText;        // ข้อความเต็ม
std::wstring g_aiDisplay;     // ข้อความที่แสดงแล้ว
int          g_aiIdx  = 0;    // ตำแหน่งปัจจุบัน
bool         g_aiDone = false;
int          g_aiCursor = 0;  // cursor blink

// ── Filter data ───────────────────────────────────────────────────────────
std::vector<std::string> g_styles  = {"Culture","Adventure","Natural","Photo","Cafe","Random"};
std::vector<std::string> g_ftypes  = {"Noodle","Rice","Surprise"};

// ══════════════════════════════════════════════════════════════════════════
// SECTION 4 — Forward Declarations
// ══════════════════════════════════════════════════════════════════════════
LRESULT CALLBACK MainProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WizProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ResProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK AIProc(HWND,UINT,WPARAM,LPARAM);
void OpenWizard(HWND,int);
void OpenResult(HWND);
void OpenAI(HWND);
void DoFilter();
void RefreshList();

// ══════════════════════════════════════════════════════════════════════════
// SECTION 5 — Data Helpers
// ══════════════════════════════════════════════════════════════════════════

std::vector<std::string> UniqProvPlace() {
  std::vector<std::string> v;
  for (auto &p : allplace)
    if (std::find(v.begin(),v.end(),p.province)==v.end())
      v.push_back(p.province);
  return v;
}
std::vector<std::string> UniqProvRest() {
  std::vector<std::string> v;
  for (auto &r : allrestaurant)
    if (std::find(v.begin(),v.end(),r.province)==v.end())
      v.push_back(r.province);
  return v;
}
std::vector<std::string> UniqDist(const std::string &prov) {
  std::vector<std::string> v;
  for (auto &r : allrestaurant)
    if (r.province==prov && std::find(v.begin(),v.end(),r.district)==v.end())
      v.push_back(r.district);
  return v;
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 6 — GDI Drawing Toolkit (ปรับปรุง v8)
// ══════════════════════════════════════════════════════════════════════════

HFONT MkF(int pt, bool bold=false, bool italic=false, LPCWSTR face=L"Segoe UI") {
  HDC dc=GetDC(nullptr);
  int px=-MulDiv(pt,GetDeviceCaps(dc,LOGPIXELSY),72);
  ReleaseDC(nullptr,dc);
  return CreateFont(px,0,0,0,bold?FW_BOLD:FW_NORMAL,italic,FALSE,FALSE,
    DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
    CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,face);
}

// Gradient แนวตั้ง
void GradV(HDC dc,RECT r,COLORREF top,COLORREF bot) {
  int h=r.bottom-r.top; if(h<=0)return;
  for(int y=0;y<h;y++){
    float f=(float)y/h;
    COLORREF c=RGB(
      (BYTE)(GetRValue(top)+f*(GetRValue(bot)-GetRValue(top))),
      (BYTE)(GetGValue(top)+f*(GetGValue(bot)-GetGValue(top))),
      (BYTE)(GetBValue(top)+f*(GetBValue(bot)-GetBValue(top))));
    HPEN p=CreatePen(PS_SOLID,1,c);
    HPEN op=(HPEN)SelectObject(dc,p);
    MoveToEx(dc,r.left,r.top+y,nullptr); LineTo(dc,r.right,r.top+y);
    SelectObject(dc,op); DeleteObject(p);
  }
}

// Gradient วงกลม (radial approximate) — ใช้สำหรับ glow spot
void RadialGlow(HDC dc,int cx,int cy,int radius,COLORREF col,float alpha) {
  int steps=radius/3; if(steps<1)steps=1;
  for(int i=steps;i>=1;i--){
    float t=(float)i/steps;
    float a=alpha*(1.f-t*t);
    BYTE r2=(BYTE)(GetRValue(col)*a);
    BYTE g2=(BYTE)(GetGValue(col)*a);
    BYTE b2=(BYTE)(GetBValue(col)*a);
    HPEN pn=CreatePen(PS_SOLID,3,RGB(r2,g2,b2));
    HPEN op=(HPEN)SelectObject(dc,pn);
    HBRUSH nb=(HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH ob2=(HBRUSH)SelectObject(dc,nb);
    int rr=i*3;
    Ellipse(dc,cx-rr,cy-rr,cx+rr,cy+rr);
    SelectObject(dc,op); SelectObject(dc,ob2);
    DeleteObject(pn);
  }
}

// สี่เหลี่ยมมนมีพื้น
void RndFill(HDC dc,RECT r,int rad,COLORREF fill,COLORREF bord,int bw=1){
  HBRUSH br=CreateSolidBrush(fill);
  HPEN   pn=CreatePen(PS_SOLID,bw,bord);
  auto ob=(HBRUSH)SelectObject(dc,br);
  auto op=(HPEN)SelectObject(dc,pn);
  RoundRect(dc,r.left,r.top,r.right,r.bottom,rad,rad);
  SelectObject(dc,ob); SelectObject(dc,op);
  DeleteObject(br); DeleteObject(pn);
}

// สี่เหลี่ยมมนแค่เส้นขอบ
void RndBord(HDC dc,RECT r,int rad,COLORREF bord,int bw=1){
  HBRUSH nb=(HBRUSH)GetStockObject(NULL_BRUSH);
  HPEN   pn=CreatePen(PS_SOLID,bw,bord);
  auto ob=(HBRUSH)SelectObject(dc,nb);
  auto op=(HPEN)SelectObject(dc,pn);
  RoundRect(dc,r.left,r.top,r.right,r.bottom,rad,rad);
  SelectObject(dc,ob); SelectObject(dc,op);
  DeleteObject(pn);
}

// Glow border (วาดหลายชั้น)
void GlowBord(HDC dc,RECT r,int rad,COLORREF col,float intensity=1.f){
  for(int i=6;i>=1;i--){
    RECT gr={r.left-i,r.top-i,r.right+i,r.bottom+i};
    float a=intensity*0.12f*(7-i);
    COLORREF gc=RGB((BYTE)(GetRValue(col)*a),(BYTE)(GetGValue(col)*a),(BYTE)(GetBValue(col)*a));
    HPEN pn=CreatePen(PS_SOLID,1,gc);
    HBRUSH nb=(HBRUSH)GetStockObject(NULL_BRUSH);
    auto op=(HPEN)SelectObject(dc,pn);
    auto ob=(HBRUSH)SelectObject(dc,nb);
    RoundRect(dc,gr.left,gr.top,gr.right,gr.bottom,rad+i,rad+i);
    SelectObject(dc,op); SelectObject(dc,ob);
    DeleteObject(pn);
  }
  RndBord(dc,r,rad,col,2);
}

// ข้อความกึ่งกลาง / ซ้าย / ขวา
void TC(HDC dc,const std::wstring &s,RECT r,COLORREF c,HFONT f){
  SetBkMode(dc,TRANSPARENT); SetTextColor(dc,c);
  auto of=(HFONT)SelectObject(dc,f);
  DrawText(dc,s.c_str(),-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  SelectObject(dc,of);
}
void TL(HDC dc,const std::wstring &s,RECT r,COLORREF c,HFONT f,int pad=10){
  r.left+=pad;
  SetBkMode(dc,TRANSPARENT); SetTextColor(dc,c);
  auto of=(HFONT)SelectObject(dc,f);
  DrawText(dc,s.c_str(),-1,&r,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  SelectObject(dc,of);
}
void TR(HDC dc,const std::wstring &s,RECT r,COLORREF c,HFONT f,int pad=10){
  r.right-=pad;
  SetBkMode(dc,TRANSPARENT); SetTextColor(dc,c);
  auto of=(HFONT)SelectObject(dc,f);
  DrawText(dc,s.c_str(),-1,&r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
  SelectObject(dc,of);
}
// ข้อความหลายบรรทัด (ซ้าย, top-aligned)
void TML(HDC dc,const std::wstring &s,RECT r,COLORREF c,HFONT f,int pad=10){
  r.left+=pad; r.top+=6;
  SetBkMode(dc,TRANSPARENT); SetTextColor(dc,c);
  auto of=(HFONT)SelectObject(dc,f);
  DrawText(dc,s.c_str(),-1,&r,DT_LEFT|DT_TOP|DT_WORDBREAK|DT_NOPREFIX);
  SelectObject(dc,of);
}

void HLine(HDC dc,int x1,int x2,int y,COLORREF c,int w=1){
  HPEN p=CreatePen(PS_SOLID,w,c);
  HPEN op=(HPEN)SelectObject(dc,p);
  MoveToEx(dc,x1,y,nullptr); LineTo(dc,x2,y);
  SelectObject(dc,op); DeleteObject(p);
}
void VLine(HDC dc,int x,int y1,int y2,COLORREF c){
  HPEN p=CreatePen(PS_SOLID,1,c);
  HPEN op=(HPEN)SelectObject(dc,p);
  MoveToEx(dc,x,y1,nullptr); LineTo(dc,x,y2);
  SelectObject(dc,op); DeleteObject(p);
}
void Fill(HDC dc,RECT r,COLORREF c){
  HBRUSH b=CreateSolidBrush(c);
  FillRect(dc,&r,b); DeleteObject(b);
}

// Lerp สี
COLORREF Lerp(COLORREF a,COLORREF b,float t){
  t=std::max(0.f,std::min(1.f,t));
  return RGB((BYTE)(GetRValue(a)+t*(GetRValue(b)-GetRValue(a))),
             (BYTE)(GetGValue(a)+t*(GetGValue(b)-GetGValue(a))),
             (BYTE)(GetBValue(a)+t*(GetBValue(b)-GetBValue(a))));
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 7 — Particle System (v8 ใหม่)
// ══════════════════════════════════════════════════════════════════════════

void InitParticles(int W,int H){
  g_particles.clear();
  std::uniform_real_distribution<float> rx(0,(float)W);
  std::uniform_real_distribution<float> ry(0,(float)H);
  std::uniform_real_distribution<float> rv(-0.3f,0.3f);
  std::uniform_real_distribution<float> rs(0.8f,2.5f);
  std::uniform_real_distribution<float> rl(80.f,200.f);
  std::uniform_int_distribution<int> rc(0,3);
  COLORREF cols[]={AC_CYAN,AC_BLUE,AC_PUR,AC_GRN};
  for(int i=0;i<55;i++){
    Particle p;
    p.x=rx(g_rng); p.y=ry(g_rng);
    p.vx=rv(g_rng); p.vy=-0.15f-std::uniform_real_distribution<float>(0.f,0.2f)(g_rng);
    p.size=rs(g_rng);
    p.life=rl(g_rng); p.maxLife=p.life;
    p.alpha=std::uniform_real_distribution<float>(0.3f,0.9f)(g_rng);
    p.col=cols[rc(g_rng)];
    g_particles.push_back(p);
  }
}

void TickParticles(int W,int H){
  std::uniform_real_distribution<float> rx(0,(float)W);
  std::uniform_real_distribution<float> rv(-0.3f,0.3f);
  std::uniform_real_distribution<float> rs(0.8f,2.5f);
  std::uniform_real_distribution<float> rl(80.f,200.f);
  std::uniform_int_distribution<int> rc(0,3);
  COLORREF cols[]={AC_CYAN,AC_BLUE,AC_PUR,AC_GRN};
  for(auto &p:g_particles){
    p.x+=p.vx; p.y+=p.vy; p.life-=1.f;
    if(p.x<0)p.x=(float)W; if(p.x>W)p.x=0;
    if(p.life<=0||p.y<-10){
      p.x=rx(g_rng); p.y=(float)H+5;
      p.vx=rv(g_rng); p.vy=-0.15f-std::uniform_real_distribution<float>(0.f,0.2f)(g_rng);
      p.size=rs(g_rng);
      p.life=rl(g_rng); p.maxLife=p.life;
      p.col=cols[rc(g_rng)];
    }
  }
}

void DrawParticles(HDC dc){
  for(auto &p:g_particles){
    float fade=std::min(1.f,p.life/20.f)*std::min(1.f,(p.maxLife-p.life)/20.f);
    float a=p.alpha*fade;
    BYTE r2=(BYTE)(GetRValue(p.col)*a);
    BYTE g2=(BYTE)(GetGValue(p.col)*a);
    BYTE b2=(BYTE)(GetBValue(p.col)*a);
    HBRUSH br=CreateSolidBrush(RGB(r2,g2,b2));
    HPEN   pn=CreatePen(PS_SOLID,1,RGB(r2,g2,b2));
    auto ob=(HBRUSH)SelectObject(dc,br);
    auto op=(HPEN)SelectObject(dc,pn);
    int sz=(int)p.size;
    Ellipse(dc,(int)p.x-sz,(int)p.y-sz,(int)p.x+sz,(int)p.y+sz);
    SelectObject(dc,ob); SelectObject(dc,op);
    DeleteObject(br); DeleteObject(pn);
  }
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 8 — Button System (Smooth Easing v8)
// ══════════════════════════════════════════════════════════════════════════

// วาดปุ่ม Neon style พร้อม glow + highlight bar
void DrawBtn(HDC dc,CBtn &b,HFONT f){
  float t=b.dn?0.7f:b.an;
  COLORREF col=Lerp(b.cN,b.cH,t);

  // Outer glow (หลายชั้น)
  if(t>0.04f){
    GlowBord(dc,b.rc,12,b.cH,t*0.8f);
  }

  // ตัวปุ่ม (gradient เล็กน้อย)
  RECT inner=b.rc;
  RndFill(dc,inner,12,col,t>0.04f?b.cH:BRD_N,t>0.04f?2:1);

  // Highlight bar ด้านบน
  if(t>0.04f){
    RECT sh={b.rc.left+8,b.rc.top+2,b.rc.right-8,b.rc.top+5};
    RndFill(dc,sh,2,Lerp(col,RGB(255,255,255),0.3f*t),Lerp(col,RGB(255,255,255),0.3f*t));
  }

  // Shimmer line (เส้นแสงวิ่ง)
  if(t>0.5f){
    int sx=(int)((b.rc.right-b.rc.left)*b.pulse)+b.rc.left;
    if(sx>b.rc.left && sx<b.rc.right){
      HPEN sp=CreatePen(PS_SOLID,1,Lerp(col,RGB(255,255,255),0.4f));
      HPEN op2=(HPEN)SelectObject(dc,sp);
      MoveToEx(dc,sx,b.rc.top+3,nullptr); LineTo(dc,sx,b.rc.bottom-3);
      SelectObject(dc,op2); DeleteObject(sp);
    }
  }

  // ข้อความ + ไอคอน
  std::wstring txt=b.ico.empty()?b.lbl:b.ico+L"  "+b.lbl;
  TC(dc,txt,b.rc,t>0.04f?TXT_HI:TXT_M,f);
}

// อัปเดต animation (easing)
bool TickBtns(std::vector<CBtn>&v){
  bool dirty=false;
  for(auto &b:v){
    float tgt=b.hov?1.f:0.f;
    float d=tgt-b.an;
    if(fabsf(d)>0.003f){
      // Ease-out cubic
      b.an+=d*(b.hov?0.18f:0.12f);
      dirty=true;
    }
    // Pulse shimmer เมื่อ hover
    if(b.hov){
      b.pulse+=0.025f;
      if(b.pulse>1.2f)b.pulse=0.f;
    }
  }
  return dirty;
}
void HitBtns(std::vector<CBtn>&v,POINT pt,HWND hw){
  for(auto &b:v){
    bool was=b.hov;
    b.hov=!!PtInRect(&b.rc,pt);
    if(b.hov!=was)InvalidateRect(hw,nullptr,FALSE);
  }
}
int ClickBtns(std::vector<CBtn>&v,POINT pt){
  int id=-1;
  for(auto &b:v){
    if(b.dn&&PtInRect(&b.rc,pt))id=b.id;
    b.dn=false;
  }
  return id;
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 9 — Background FX
// ══════════════════════════════════════════════════════════════════════════

// วาด Grid dots
void DrawGrid(HDC dc,int W,int H){
  for(int x=32;x<W;x+=32)
    for(int y=32;y<H;y+=32){
      BYTE v=(BYTE)(12+4*sinf((x+g_tick*0.3f)*0.05f)*cosf((y+g_tick*0.2f)*0.04f));
      SetPixel(dc,x,y,RGB(v,v,v+8));
    }
}

// Scanline เรืองแสง
void DrawScan(HDC dc,int W,int H,int sY){
  if(sY<0||sY>=H)return;
  for(int y=sY;y<std::min(H,sY+4);y++){
    float a=1.f-(float)(y-sY)/4.f;
    HPEN p=CreatePen(PS_SOLID,1,
      RGB((BYTE)(0),(BYTE)(28*a),(BYTE)(50*a)));
    HPEN op=(HPEN)SelectObject(dc,p);
    MoveToEx(dc,0,y,nullptr); LineTo(dc,W,y);
    SelectObject(dc,op); DeleteObject(p);
  }
}

// Aurora (แสง gradient หลอก ด้านบน)
void DrawAurora(HDC dc,int W,float phase){
  int bands=4;
  COLORREF aColors[]={AC_CYAN,AC_PUR,AC_BLUE,AC_GRN};
  for(int i=0;i<bands;i++){
    float px=(float)i/bands;
    float cx=W*(px+0.1f*sinf(phase+i*1.3f));
    int r2=(int)(GetRValue(aColors[i])*0.06f);
    int g2=(int)(GetGValue(aColors[i])*0.06f);
    int b2=(int)(GetBValue(aColors[i])*0.06f);
    RadialGlow(dc,(int)cx,0,180,RGB(r2,g2,b2),0.5f);
  }
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 10 — AI Advisor Engine
// ══════════════════════════════════════════════════════════════════════════

// สร้างข้อความแนะนำทริปแบบ AI (rule-based ที่ดูฉลาด)
std::wstring GenerateAIAdvice() {
  if(g_picks.empty()){
    return L"[ AI Trip Advisor ]\n\n"
           L"ยังไม่มีรายการในแผนทริปของคุณ\n\n"
           L"คำแนะนำ:\n"
           L"  1. กด 'Plan Trip' เพื่อเลือกสถานที่ท่องเที่ยว\n"
           L"  2. กด 'What to Eat' เพื่อเลือกร้านอาหาร\n"
           L"  3. กลับมากด 'AI Advisor' อีกครั้ง\n\n"
           L"AI จะวิเคราะห์แผนทริปของคุณโดยอัตโนมัติ!";
  }

  // วิเคราะห์ข้อมูล
  std::map<std::wstring,int> provCount;
  std::map<std::wstring,int> catCount;
  int totalCost=0, foodCost=0, placeCost=0;
  int foodCnt=0, placeCnt=0;
  for(auto &p:g_picks){
    provCount[p.province]++;
    catCount[p.cat]++;
    totalCost+=p.cost;
    if(p.isFood){ foodCost+=p.cost; foodCnt++; }
    else { placeCost+=p.cost; placeCnt++; }
  }

  // จังหวัดหลัก
  std::wstring mainProv;
  int maxP=0;
  for(auto &kv:provCount) if(kv.second>maxP){maxP=kv.second;mainProv=kv.first;}

  // หมวดที่ชอบ
  std::wstring favCat;
  int maxC=0;
  for(auto &kv:catCount) if(kv.second>maxC){maxC=kv.second;favCat=kv.first;}

  std::wstring advice=L"[ 🤖 AI Trip Advisor — Smart Analysis ]\n\n";
  advice+=L"📊 สรุปแผนทริปของคุณ:\n";
  advice+=L"  • สถานที่ท่องเที่ยว: "+std::to_wstring(placeCnt)+L" แห่ง\n";
  advice+=L"  • ร้านอาหาร: "+std::to_wstring(foodCnt)+L" ร้าน\n";
  advice+=L"  • ค่าใช้จ่ายรวม: "+std::to_wstring(totalCost)+L" บาท\n\n";

  if(!mainProv.empty()){
    advice+=L"📍 จังหวัดหลักในทริป: "+mainProv+L"\n";
  }
  if(!favCat.empty()){
    advice+=L"🎨 หมวดที่คุณชอบ: "+favCat+L"\n\n";
  }

  // คำแนะนำตามงบ
  advice+=L"💡 คำแนะนำจาก AI:\n";
  if(totalCost==0){
    advice+=L"  ✅ แผนทริปของคุณฟรีทั้งหมด! ยอดเยี่ยม\n";
  } else if(totalCost<500){
    advice+=L"  ✅ งบประมาณน้อยมาก — ประหยัดมาก\n";
    advice+=L"  💡 ลองเพิ่มร้านอาหารดีๆ สักร้านได้\n";
  } else if(totalCost<1500){
    advice+=L"  ✅ งบประมาณพอดี — เหมาะสำหรับ 1 วัน\n";
  } else if(totalCost<3000){
    advice+=L"  ⚠️ งบค่อนข้างสูง — ควรวางแผน 2-3 วัน\n";
    advice+=L"  💡 แนะนำให้แยกเดินทางหลายรอบ\n";
  } else {
    advice+=L"  ⚠️ งบสูงมาก — แนะนำทริปแบบ Package\n";
    advice+=L"  💡 ลองติดต่อทัวร์ท้องถิ่นเพื่อประหยัด\n";
  }

  // แนะนำตามสัดส่วน food/place
  advice+=L"\n🍜 สัดส่วนอาหาร vs สถานที่:\n";
  if(foodCnt==0){
    advice+=L"  ⚠️ ยังไม่มีร้านอาหาร! กด 'What to Eat' เพิ่มได้\n";
  } else if(placeCnt==0){
    advice+=L"  ⚠️ มีแต่ร้านอาหาร ลองเพิ่มสถานที่ท่องเที่ยวด้วย\n";
  } else {
    float ratio=(float)foodCnt/(foodCnt+placeCnt);
    if(ratio>0.6f) advice+=L"  💡 อาหารเยอะกว่าสถานที่ — Food Trip นะนี่!\n";
    else if(ratio<0.3f) advice+=L"  💡 สถานที่เยอะ อาหารน้อย — อย่าลืมกินข้าวด้วยนะ\n";
    else advice+=L"  ✅ สัดส่วนอาหาร:สถานที่สมดุลดี!\n";
  }

  // แนะนำจังหวัด
  if(provCount.size()>2){
    advice+=L"\n🗺️ คุณเลือกหลายจังหวัด ("+std::to_wstring(provCount.size())+L" จังหวัด)\n";
    advice+=L"  💡 แนะนำให้เรียงลำดับตามเส้นทาง\n";
    advice+=L"  เพื่อประหยัดเวลาและค่าเดินทาง\n";
  }

  advice+=L"\n✨ ขอให้เดินทางปลอดภัยและสนุกกับทริป!";
  return advice;
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 11 — Save System (ปรับปรุง v8)
// ══════════════════════════════════════════════════════════════════════════

void DoSave(HWND owner){
  std::ofstream f("trip_results.txt",std::ios::app);
  if(!f){ MessageBox(owner,L"ไม่สามารถบันทึกไฟล์ได้!",L"Error",MB_ICONERROR); return; }

  time_t t=time(0); char ts[64]; ctime_s(ts,sizeof(ts),&t);
  // ลบ newline ท้าย timestamp
  int tlen=(int)strlen(ts);
  if(tlen>0&&ts[tlen-1]=='\n')ts[tlen-1]='\0';

  auto W=[](const std::wstring&w){
    std::string s; for(wchar_t c:w)s+=(c<128?(char)c:'?'); return s;
  };

  f<<"╔══════════════════════════════════════════════╗\n";
  f<<"║  SMART TRIP ASSISTANT v8 — Trip Summary      ║\n";
  f<<"╚══════════════════════════════════════════════╝\n";
  f<<"  Saved: "<<ts<<"\n";
  f<<"────────────────────────────────────────────────\n\n";

  int total=0,n=1,foodCost=0,placeCost=0;
  f<<"  PLACES (สถานที่ท่องเที่ยว)\n";
  f<<"  ─────────────────────────\n";
  bool hasPlace=false;
  for(auto &p:g_picks){
    if(!p.isFood){
      f<<"  "<<n++<<". "<<W(p.name)<<" ["<<W(p.cat)<<"]\n";
      f<<"     "<<W(p.province)<<"  → "<<p.cost<<" THB\n";
      placeCost+=p.cost; total+=p.cost; hasPlace=true;
    }
  }
  if(!hasPlace) f<<"  (ไม่มีสถานที่)\n";

  f<<"\n  RESTAURANTS (ร้านอาหาร)\n";
  f<<"  ─────────────────────────\n";
  bool hasFood=false;
  for(auto &p:g_picks){
    if(p.isFood){
      f<<"  "<<n++<<". "<<W(p.name)<<" ["<<W(p.cat)<<"]\n";
      f<<"     "<<W(p.province)<<"  → "<<p.cost<<" THB\n";
      foodCost+=p.cost; total+=p.cost; hasFood=true;
    }
  }
  if(!hasFood) f<<"  (ไม่มีร้านอาหาร)\n";

  f<<"\n────────────────────────────────────────────────\n";
  f<<"  ค่าสถานที่รวม : "<<placeCost<<" THB\n";
  f<<"  ค่าอาหารรวม  : "<<foodCost<<" THB\n";
  f<<"  TOTAL         : "<<total<<" THB\n";
  f<<"╚══════════════════════════════════════════════╝\n\n";
  f.close();

  MessageBox(owner,L"บันทึกสำเร็จ!\nบันทึกลงไฟล์ trip_results.txt แล้ว",
             L"\u2705  Saved!",MB_ICONINFORMATION);
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 12 — Wizard Logic
// ══════════════════════════════════════════════════════════════════════════

int MaxStep(){ return (g_wizMode==0)?2:3; }

std::wstring StepTitle(int s){
  if(g_wizMode==0){
    if(s==0) return L"\U0001F30F  Step 1 — เลือกจังหวัด";
    if(s==1) return L"\U0001F3A8  Step 2 — เลือกสไตล์การท่องเที่ยว";
    if(s==2) return L"\U0001F4CD  Step 3 — เลือกสถานที่ที่ชอบ!";
  } else {
    if(s==0) return L"\U0001F30F  Step 1 — เลือกจังหวัด";
    if(s==1) return L"\U0001F3D8  Step 2 — เลือกอำเภอ";
    if(s==2) return L"\U0001F35C  Step 3 — เลือกประเภทอาหาร";
    if(s==3) return L"\U0001F374  Step 4 — เลือกร้านอาหาร!";
  }
  return L"";
}

std::wstring StepDesc(int s){
  if(g_wizMode==0){
    if(s==0) return L"ต้องการไปเที่ยวที่จังหวัดไหน? เลือกได้เลย";
    if(s==1) return L"ชอบสไตล์การท่องเที่ยวแบบไหน?";
    if(s==2) return L"คลิกรายการ แล้วกด Next / Add to Plan เพื่อเพิ่มเข้าทริป";
  } else {
    if(s==0) return L"ต้องการกินอาหารที่จังหวัดไหน?";
    if(s==1) return L"เลือกอำเภอที่ต้องการ";
    if(s==2) return L"ชอบกินอาหารประเภทไหน?";
    if(s==3) return L"คลิกร้านอาหาร แล้วกด Next / Add to Plan";
  }
  return L"";
}

std::vector<std::wstring> StepItems(int s){
  std::vector<std::wstring> r;
  if(g_wizMode==0){
    if(s==0){ for(auto&p:UniqProvPlace()) r.push_back(L"   \U0001F4CD  "+S2W(p)); }
    else if(s==1){
      std::vector<std::pair<std::wstring,std::wstring>> styleInfo={
        {L"Culture",L"\U0001F3DB  Culture — วัฒนธรรม / วัด / ประวัติศาสตร์"},
        {L"Adventure",L"\u26F0  Adventure — ผจญภัย / ธรรมชาติ"},
        {L"Natural",L"\U0001F333  Natural — ธรรมชาติ / ภูเขา / น้ำตก"},
        {L"Photo",L"\U0001F4F8  Photo — จุดถ่ายภาพ / วิวสวย"},
        {L"Cafe",L"\u2615  Cafe — คาเฟ่ / ร้านกาแฟ"},
        {L"Random",L"\U0001F3B2  Random — สุ่มทุกประเภท"}
      };
      for(auto&st:styleInfo) r.push_back(L"   "+st.second);
    }
    else if(s==2){
      for(auto&p:g_filtPlaces)
        r.push_back(L"   "+S2W(p.name)+L"   ("+std::to_wstring(p.price)+L" THB)");
      if(r.empty()) r.push_back(L"   (ไม่พบสถานที่ตามเงื่อนไข)");
    }
  } else {
    if(s==0){ for(auto&p:UniqProvRest()) r.push_back(L"   \U0001F4CD  "+S2W(p)); }
    else if(s==1){
      auto pv=UniqProvRest();
      std::string sp=(g_selProv<(int)pv.size())?pv[g_selProv]:"";
      auto v=UniqDist(sp);
      v.insert(v.begin(),"(All Districts)");
      for(auto&d:v) r.push_back(L"   \U0001F3D8  "+S2W(d));
    }
    else if(s==2){
      std::vector<std::pair<std::wstring,std::wstring>> typeInfo={
        {L"Noodle",L"\U0001F35C  Noodle — ก๋วยเตี๋ยว / บะหมี่ / เส้น"},
        {L"Rice",  L"\U0001F35A  Rice — ข้าวหน้าต่างๆ / ข้าวผัด"},
        {L"Surprise",L"\U0001F3B2  Surprise — สุ่มร้านแนะนำ"}
      };
      for(auto&t:typeInfo) r.push_back(L"   "+t.second);
    }
    else if(s==3){
      for(auto&rs:g_filtRests)
        r.push_back(L"   \U0001F374  "+S2W(rs.name)+L"  ["+S2W(rs.type)+L"]  "+
                    std::to_wstring(rs.price)+L" THB");
      if(r.empty()) r.push_back(L"   (ไม่พบร้านอาหารตามเงื่อนไข)");
    }
  }
  return r;
}

void DoFilter(){
  if(g_wizMode==0){
    g_filtPlaces.clear();
    auto pv=UniqProvPlace();
    std::string sp=(g_selProv<(int)pv.size())?pv[g_selProv]:"";
    std::string ss=(g_selStyle<(int)g_styles.size())?g_styles[g_selStyle]:"";
    for(auto&p:allplace)
      if(p.province==sp&&(ss=="Random"||p.type==ss))
        g_filtPlaces.push_back(p);
  } else {
    g_filtRests.clear();
    auto pv=UniqProvRest();
    std::string sp=(g_selProv<(int)pv.size())?pv[g_selProv]:"";
    auto dists=UniqDist(sp);
    dists.insert(dists.begin(),"ทุกอำเภอ (All Districts)");
    std::string sd=(g_selDist<(int)dists.size())?dists[g_selDist]:"ทุกอำเภอ (All Districts)";
    std::string ft=(g_selType<(int)g_ftypes.size())?g_ftypes[g_selType]:"Surprise";
    for(auto&r:allrestaurant){
      bool mP=(r.province==sp);
      bool mD=(sd=="ทุกอำเภอ (All Districts)"||r.district==sd);
      bool mT=(ft=="Surprise"||r.type==ft);
      if(mP&&mD&&mT) g_filtRests.push_back(r);
    }
    // Surprise = สุ่ม 5 ร้าน
    if(ft=="Surprise"&&g_filtRests.size()>5){
      std::shuffle(g_filtRests.begin(),g_filtRests.end(),g_rng);
      g_filtRests.resize(5);
    }
  }
}

WNDPROC g_oldListProc=nullptr;
LRESULT CALLBACK ListSubProc(HWND h,UINT m,WPARAM w,LPARAM l){
  if(m==WM_ERASEBKGND){
    HDC d=(HDC)w; RECT r; GetClientRect(h,&r);
    Fill(d,r,BG_CARD); return 1;
  }
  return CallWindowProc(g_oldListProc,h,m,w,l);
}

void RefreshList(){
  if(!g_hList)return;
  SendMessage(g_hList,LB_RESETCONTENT,0,0);
  auto items=StepItems(g_step);
  for(auto&it:items) SendMessage(g_hList,LB_ADDSTRING,0,(LPARAM)it.c_str());
  SendMessage(g_hList,LB_SETCURSEL,0,0);
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 13 — Main Menu Window
// ══════════════════════════════════════════════════════════════════════════

static std::vector<CBtn> g_menuBtns;
static bool g_menuInited=false;

void InitMenuBtns(){
  if(g_menuInited)return;
  g_menuInited=true;
  int bw=340,bh=58;
  int bx=(MW-bw)/2;

  // ปุ่ม 1: Plan Trip
  g_menuBtns.push_back({{bx,248,bx+bw,248+bh},
    L"Plan Trip",L"\U0001F30F",1,BTN_N,AC_BLUE,AC_BD});
  // ปุ่ม 2: What to Eat
  g_menuBtns.push_back({{bx,320,bx+bw,320+bh},
    L"What to Eat",L"\U0001F35C",2,BTN_N,AC_PUR,AC_PD});
  // ปุ่ม 3: AI Advisor
  g_menuBtns.push_back({{bx,392,bx+bw,392+bh},
    L"AI Trip Advisor",L"\U0001F916",3,BTN_YN,AC_GOLD,RGB(120,90,10)});
  // ปุ่ม 4: View Saved
  g_menuBtns.push_back({{bx,464,bx+bw,464+bh},
    L"View Saved Trips",L"\U0001F4CB",4,BTN_GN,AC_GRN,AC_GD});
  // ปุ่ม 5: Exit
  g_menuBtns.push_back({{bx,540,bx+bw,540+bh},
    L"Exit",L"\u2715",5,BTN_RN,AC_RED,RGB(120,20,30)});
}

LRESULT CALLBACK MainProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp){
  switch(msg){

  case WM_CREATE:
    SetTimer(hw,ID_TANIM,16,nullptr);   // 60fps
    SetTimer(hw,ID_TSCAN,28,nullptr);   // scanline
    SetTimer(hw,ID_TPART,50,nullptr);   // particles
    InitParticles(MW,MH);
    return 0;

  case WM_TIMER:
    g_tick++;
    g_sinT=sinf(g_tick*0.035f);
    g_cosT=cosf(g_tick*0.028f);
    g_bgShift+=0.008f;
    g_starBlink+=0.06f;
    if(g_tick%22==0) g_glowP=!g_glowP;
    if(wp==ID_TSCAN) g_scanY=(g_scanY+3)%MH;
    if(wp==ID_TPART){ TickParticles(MW,MH); }
    InitMenuBtns();
    TickBtns(g_menuBtns);
    InvalidateRect(hw,nullptr,FALSE);
    return 0;

  case WM_PAINT:{
    PAINTSTRUCT ps; HDC hdc=BeginPaint(hw,&ps);
    RECT rc; GetClientRect(hw,&rc);

    // Double-buffer
    HDC mem=CreateCompatibleDC(hdc);
    HBITMAP bm=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
    HBITMAP ob=(HBITMAP)SelectObject(mem,bm);

    // ── พื้นหลัง gradient ──
    GradV(mem,rc,BG_BASE,BG_DEEP);
    DrawGrid(mem,MW,MH);

    // ── Aurora ──
    DrawAurora(mem,MW,g_bgShift);

    // ── Particles ──
    DrawParticles(mem);

    // ── Scanline ──
    DrawScan(mem,MW,MH,g_scanY);

    // ── Top accent bar ──
    COLORREF topCol=Lerp(AC_CYAN,AC_PUR,(g_sinT+1.f)*0.5f);
    Fill(mem,{0,0,MW,3},topCol);
    Fill(mem,{0,3,MW,5},BG_HEADER);

    // ── การ์ดหลัก (Glassmorphism) ──
    RECT card={MW/2-300,45,MW/2+300,610};
    {
      RECT sh=card; OffsetRect(&sh,8,10);
      RndFill(mem,sh,24,RGB(2,3,8),RGB(2,3,8));
    }
    GradV(mem,card,BG_PANEL,BG_GLASS);
    GlowBord(mem,card,24,Lerp(AC_CYAN,AC_PUR,(g_sinT+1.f)*0.5f),0.6f);

    // ── Top glow line บนการ์ด ──
    COLORREF gc=Lerp(AC_CYAN,AC_BLUE,(g_sinT+1.f)*0.5f);
    Fill(mem,{card.left+30,card.top,card.right-30,card.top+2},gc);

    // ── Logo area ──
    // ไอคอนเครื่องบิน พร้อม glow
    {
      int icx=MW/2, icy=95;
      // Glow behind icon
      RadialGlow(mem,icx,icy,45,AC_CYAN,0.35f);
      HFONT fi=MkF(46); BYTE bc=(BYTE)(170+60*g_sinT);
      TC(mem,L"\u2708",{icx-55,icy-36,icx+55,icy+36},RGB(bc,bc+20,255),fi);
      DeleteObject(fi);
    }

    // ── ชื่อโปรแกรม ──
    {
      HFONT ft=MkF(28,true,false,L"Segoe UI");
      COLORREF nc=g_glowP?AC_CYAN:TXT_HI;
      TC(mem,L"Smart Trip Assistant",{MW/2-300,132,MW/2+300,174},nc,ft);
      DeleteObject(ft);
    }
    // Version badge
    {
      RECT vr={MW/2+130,128,MW/2+210,138};
      RndFill(mem,vr,8,AC_BD,AC_BLUE);
      HFONT fv=MkF(7,true); TC(mem,L"version 8.0",vr,AC_CYAN,fv); DeleteObject(fv);
    }

    // ── Subtitle ──
    {
      HFONT fs=MkF(10,false,true);
      TC(mem,L"Northern Thailand  \u2022  Places & Restaurants  \u2022  AI Advisor",
         {MW/2-320,175,MW/2+320,195},TXT_D,fs);
      DeleteObject(fs);
    }

    // ── Divider MAIN MENU ──
    int dy=232;
    HLine(mem,MW/2-220,MW/2-70,dy,BRD_N);
    HLine(mem,MW/2+70,MW/2+220,dy,BRD_N);
    {
      RECT lr={MW/2-70,dy-12,MW/2+70,dy+12};
      RndFill(mem,lr,5,BG_SURF,BRD_N);
      HFONT fl=MkF(8); TC(mem,L"MAIN MENU",lr,TXT_D,fl); DeleteObject(fl);
    }

    // ── Buttons ──
    InitMenuBtns();
    HFONT fb=MkF(13,true);
    for(auto &b:g_menuBtns) DrawBtn(mem,b,fb);
    DeleteObject(fb);

    // ── Plan Badge (จำนวน items) ──
    if(!g_picks.empty()){
      RECT br={MW/2+165,232,MW/2+296,254};
      RndFill(mem,br,10,RGB(8,40,20),AC_GRN,2);
      HFONT fbg=MkF(8,true);
      std::wstring badge=L"\U0001F4E6 "+std::to_wstring(g_picks.size())+L" รายการ";
      TC(mem,badge,br,AC_GRN,fbg); DeleteObject(fbg);
    }

    // ── Footer ──
    Fill(mem,{0,MH-30,MW,MH},BG_HEADER);
    HLine(mem,0,MW,MH-30,BRD_N);
    {
      HFONT fv=MkF(9);
      TL(mem,L"  Smart Trip v8  |  Win32 API  |  Pro Dark Neon",
         {0,MH-30,MW/2,MH},TXT_D,fv,6);
      TR(mem,g_glowP?L"READY  \u25cf  ":L"READY  \u25cb  ",
         {0,MH-30,MW,MH},g_glowP?AC_GRN:TXT_D,fv,6);
      DeleteObject(fv);
    }

    BitBlt(hdc,0,0,rc.right,rc.bottom,mem,0,0,SRCCOPY);
    SelectObject(mem,ob); DeleteObject(bm); DeleteDC(mem);
    EndPaint(hw,&ps); return 0;
  }

  case WM_MOUSEMOVE:
    HitBtns(g_menuBtns,{GET_X_LPARAM(lp),GET_Y_LPARAM(lp)},hw);
    return 0;
  case WM_LBUTTONDOWN:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    for(auto&b:g_menuBtns) if(PtInRect(&b.rc,pt))b.dn=true;
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_LBUTTONUP:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    int id=ClickBtns(g_menuBtns,pt);
    if(id==1){ g_step=0; OpenWizard(hw,0); }
    else if(id==2){ g_step=0; OpenWizard(hw,1); }
    else if(id==3){ OpenAI(hw); }
    else if(id==4){
      auto r=ShellExecute(nullptr,L"open",L"notepad.exe",
                          L"trip_results.txt",nullptr,SW_SHOW);
      if(r<=(HINSTANCE)32)
        MessageBox(hw,L"ยังไม่มีทริปที่บันทึก\nเพิ่มรายการแล้วกด Save ใน Summary",
                   L"Info",MB_ICONINFORMATION);
    }
    else if(id==5) PostQuitMessage(0);
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_ERASEBKGND: return 1;
  case WM_DESTROY:
    KillTimer(hw,ID_TANIM); KillTimer(hw,ID_TSCAN); KillTimer(hw,ID_TPART);
    PostQuitMessage(0); return 0;
  }
  return DefWindowProc(hw,msg,wp,lp);
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 14 — Wizard Window
// ══════════════════════════════════════════════════════════════════════════

static std::vector<CBtn> g_wizBtns;

void OpenWizard(HWND parent,int mode){
  g_wizMode=mode;
  g_selProv=g_selStyle=g_selDist=g_selType=0;
  if(g_hWiz){ DestroyWindow(g_hWiz); g_hWiz=nullptr; }

  int sx=(GetSystemMetrics(SM_CXSCREEN)-WW)/2;
  int sy=(GetSystemMetrics(SM_CYSCREEN)-WH)/2;

  g_hWiz=CreateWindowEx(WS_EX_DLGMODALFRAME|WS_EX_TOPMOST,L"TripApp_Wiz",
    mode==0?L"\U0001F30F  Plan Trip Wizard":L"\U0001F35C  Restaurant Wizard",
    WS_POPUP|WS_CAPTION|WS_SYSMENU,sx,sy,WW,WH,parent,nullptr,g_hI,nullptr);

  g_hList=CreateWindowEx(0,L"LISTBOX",nullptr,
    WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWFIXED|LBS_HASSTRINGS,
    30,188,WW-60,320,g_hWiz,(HMENU)ID_LIST,g_hI,nullptr);
  SendMessage(g_hList,LB_SETITEMHEIGHT,0,48);
  g_oldListProc=(WNDPROC)SetWindowLongPtr(g_hList,GWLP_WNDPROC,(LONG_PTR)ListSubProc);

  g_wizBtns.clear();
  int by=WH-74,bh=48;
  g_wizBtns.push_back({{30,by,180,by+bh},L"Back",L"\u25c4",ID_BACK,BTN_SN,BTN_SH,RGB(18,30,65)});
  g_wizBtns.push_back({{WW/2-80,by,WW/2+80,by+bh},L"Done / Close",L"\u2714",ID_DONE,BTN_GN,AC_GRN,AC_GD});
  g_wizBtns.push_back({{WW-30-190,by,WW-30,by+bh},L"Next",L"\u25ba",ID_NEXT,AC_BD,AC_BLUE,AC_BD});

  RefreshList();
  ShowWindow(g_hWiz,SW_SHOW);
  UpdateWindow(g_hWiz);
}

LRESULT CALLBACK WizProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp){
  switch(msg){
  case WM_CREATE:
    SetTimer(hw,ID_TANIM,16,nullptr);
    return 0;
  case WM_TIMER:
    if(TickBtns(g_wizBtns))InvalidateRect(hw,nullptr,FALSE);
    return 0;

  case WM_PAINT:{
    PAINTSTRUCT ps; HDC hdc=BeginPaint(hw,&ps);
    RECT rc; GetClientRect(hw,&rc);
    HDC mem=CreateCompatibleDC(hdc);
    HBITMAP bm=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
    HBITMAP ob=(HBITMAP)SelectObject(mem,bm);

    GradV(mem,rc,BG_BASE,BG_DEEP);
    DrawGrid(mem,WW,WH);

    // Header
    Fill(mem,{0,0,WW,62},BG_HEADER);
    COLORREF acc=(g_wizMode==0)?AC_BLUE:AC_PUR;
    HLine(mem,0,WW,62,acc,2);

    // Progress bar
    int ms=MaxStep()+1, sw2=64, gap=10;
    int sx2=(WW-(ms*(sw2+gap)-gap))/2;
    for(int i=0;i<ms;i++){
      RECT dr={sx2+i*(sw2+gap),22,sx2+i*(sw2+gap)+sw2,32};
      COLORREF dc2=(i<g_step)?AC_GRN:((i==g_step)?acc:BRD_N);
      RndFill(mem,dr,5,dc2,dc2);
      if(i==g_step){
        // แสงกะพริบบน progress ปัจจุบัน
        COLORREF pc=Lerp(acc,RGB(255,255,255),(g_sinT+1.f)*0.15f);
        RndFill(mem,dr,5,pc,pc);
      }
    }

    // ชื่อ Step
    {HFONT ft=MkF(16,true); TC(mem,StepTitle(g_step),{0,68,WW,102},TXT_HI,ft); DeleteObject(ft);}
    // คำอธิบาย Step
    {HFONT fd=MkF(11,false,true); TC(mem,StepDesc(g_step),{0,102,WW,124},TXT_D,fd); DeleteObject(fd);}

    // ป้าย "SELECT"
    {
      HFONT fc=MkF(8);
      RECT cr={30,142,WW-30,162};
      RndFill(mem,cr,4,BG_SURF,BRD_N);
      HLine(mem,30,WW-30,142,BRD_N);
      TL(mem,L"  \u2193  เลือกรายการด้านล่าง",cr,AC_CYAN,fc,6);
      HLine(mem,30,WW-30,162,BRD_N);
      DeleteObject(fc);
    }

    // ขอบ ListBox
    GlowBord(mem,{28,185,WW-28,510},5,(g_wizMode==0)?AC_BLUE:AC_PUR,0.7f);

    // Bottom bar
    Fill(mem,{0,WH-86,WW,WH},BG_HEADER);
    HLine(mem,0,WW,WH-86,BRD_N,1);

    // Pick counter badge
    if(!g_picks.empty()){
      RECT br2={WW-200,WH-116,WW-20,WH-90};
      RndFill(mem,br2,5,RGB(8,36,20),AC_GRN,2);
      HFONT fb2=MkF(9,true);
      std::wstring btxt=L"\U0001F4E6 "+std::to_wstring(g_picks.size())+L" ในแผน";
      TC(mem,btxt,br2,AC_GRN,fb2); DeleteObject(fb2);
    }

    {
      HFONT fb=MkF(12,true);
      for(auto&b:g_wizBtns){
        if(b.id==ID_NEXT){
          b.lbl=(g_step==MaxStep())?L"Add to Plan":L"Next";
          b.ico=(g_step==MaxStep())?L"\u2795":L"\u25ba";
          b.cN=(g_step==MaxStep())?BTN_YN:AC_BD;
          b.cH=(g_step==MaxStep())?AC_GOLD:AC_BLUE;
        }
        DrawBtn(mem,b,fb);
      }
      DeleteObject(fb);
    }

    BitBlt(hdc,0,0,rc.right,rc.bottom,mem,0,0,SRCCOPY);
    SelectObject(mem,ob); DeleteObject(bm); DeleteDC(mem);
    EndPaint(hw,&ps); return 0;
  }

  case WM_DRAWITEM:{
    auto*d=(DRAWITEMSTRUCT*)lp;
    if(d->CtlID!=ID_LIST||d->itemID==(UINT)-1)break;
    bool sel=!!(d->itemState&ODS_SELECTED);

    // พื้นแถว
    Fill(d->hDC,d->rcItem,sel?BG_ROW_S:((d->itemID%2==0)?BG_ROW_A:BG_ROW_B));
    HLine(d->hDC,d->rcItem.left,d->rcItem.right,d->rcItem.bottom-1,BRD_N);

    if(sel){
      // เส้นแถบสีซ้าย
      RECT vr={d->rcItem.left,d->rcItem.top,d->rcItem.left+4,d->rcItem.bottom};
      Fill(d->hDC,vr,(g_wizMode==0)?AC_BLUE:AC_PUR);
      // Glow overlay เล็กน้อย
      Fill(d->hDC,{d->rcItem.left+4,d->rcItem.top,d->rcItem.right,d->rcItem.bottom},
           Lerp(BG_ROW_S,RGB(0,0,0),0.1f));
      // Arrow
      HFONT fa=MkF(11,true); RECT ar=d->rcItem; ar.right-=10;
      TR(d->hDC,L"\u276F",ar,TXT_HI,fa,8); DeleteObject(fa);
    }

    wchar_t buf[400]={};
    SendMessage(g_hList,LB_GETTEXT,d->itemID,(LPARAM)buf);
    HFONT fi=MkF(12,sel);
    SetBkMode(d->hDC,TRANSPARENT);
    SetTextColor(d->hDC,sel?TXT_HI:TXT_M);
    auto of=(HFONT)SelectObject(d->hDC,fi);
    RECT tr2=d->rcItem; tr2.left+=(sel?22:10);
    DrawText(d->hDC,buf,-1,&tr2,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
    SelectObject(d->hDC,of); DeleteObject(fi);
    return TRUE;
  }
  case WM_MEASUREITEM:
    ((MEASUREITEMSTRUCT*)lp)->itemHeight=48; return TRUE;

  case WM_MOUSEMOVE:
    HitBtns(g_wizBtns,{GET_X_LPARAM(lp),GET_Y_LPARAM(lp)},hw); return 0;
  case WM_LBUTTONDOWN:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    for(auto&b:g_wizBtns) if(PtInRect(&b.rc,pt))b.dn=true;
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_LBUTTONUP:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    int id=ClickBtns(g_wizBtns,pt);

    if(id==ID_DONE){
      DestroyWindow(hw); g_hWiz=nullptr;
      OpenResult(g_hMain); return 0;
    }
    if(id==ID_BACK&&g_step>0){
      g_step--; RefreshList(); InvalidateRect(hw,nullptr,TRUE); return 0;
    }
    if(id==ID_NEXT){
      int sel=(int)SendMessage(g_hList,LB_GETCURSEL,0,0);
      if(sel<0)sel=0;
      bool isLast=(g_step==MaxStep());
      if(isLast){
        if(g_wizMode==0&&sel<(int)g_filtPlaces.size()){
          auto&p=g_filtPlaces[sel];
          g_picks.push_back({S2W(p.name),S2W(p.type),S2W(p.province),p.price,false});
          MessageBox(hw,(L"\u2728 เพิ่มสถานที่: "+S2W(p.name)).c_str(),
                     L"Added!",MB_ICONINFORMATION);
        } else if(g_wizMode==1&&sel<(int)g_filtRests.size()){
          auto&r=g_filtRests[sel];
          g_picks.push_back({S2W(r.name),S2W(r.type),S2W(r.province),r.price,true});
          MessageBox(hw,(L"\U0001F35C เพิ่มร้านอาหาร: "+S2W(r.name)).c_str(),
                     L"Added!",MB_ICONINFORMATION);
        }
        InvalidateRect(hw,nullptr,FALSE);
        if(g_hMain)InvalidateRect(g_hMain,nullptr,FALSE);
        return 0;
      }
      if(g_wizMode==0){
        if(g_step==0) g_selProv=sel;
        if(g_step==1){ g_selStyle=sel; DoFilter(); }
      } else {
        if(g_step==0) g_selProv=sel;
        if(g_step==1) g_selDist=sel;
        if(g_step==2){ g_selType=sel; DoFilter(); }
      }
      g_step++; RefreshList(); InvalidateRect(hw,nullptr,TRUE); return 0;
    }
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_ERASEBKGND: return 1;
  case WM_DESTROY: g_hWiz=nullptr; KillTimer(hw,ID_TANIM); return 0;
  }
  return DefWindowProc(hw,msg,wp,lp);
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 15 — Result Summary Window
// ══════════════════════════════════════════════════════════════════════════

static std::vector<CBtn> g_resBtns;

void OpenResult(HWND par){
  if(g_hRes){ DestroyWindow(g_hRes); g_hRes=nullptr; }
  int sx=(GetSystemMetrics(SM_CXSCREEN)-RW)/2;
  int sy=(GetSystemMetrics(SM_CYSCREEN)-RH2)/2;
  g_hRes=CreateWindowEx(WS_EX_DLGMODALFRAME|WS_EX_TOPMOST,L"TripApp_Res",
    L"\U0001F4CB  Your Trip Plan Summary",
    WS_POPUP|WS_CAPTION|WS_SYSMENU,sx,sy,RW,RH2,par,nullptr,g_hI,nullptr);

  g_resBtns.clear();
  int by=RH2-72,bh=48;
  g_resBtns.push_back({{RW/2-95,by,RW/2+95,by+bh},L"Save to File",L"\U0001F4BE",ID_SAVE,BTN_GN,AC_GRN,AC_GD});
  g_resBtns.push_back({{28,by,210,by+bh},L"Clear Plan",L"\U0001F5D1",ID_CLEAR,BTN_RN,AC_RED,RGB(120,20,30)});
  g_resBtns.push_back({{RW-28-160,by,RW-28,by+bh},L"Close",L"\u2715",ID_CLOSE,BTN_SN,BTN_SH,RGB(18,30,65)});

  ShowWindow(g_hRes,SW_SHOW); UpdateWindow(g_hRes);
}

LRESULT CALLBACK ResProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp){
  switch(msg){
  case WM_CREATE: SetTimer(hw,ID_TANIM,16,nullptr); return 0;
  case WM_TIMER:  if(TickBtns(g_resBtns))InvalidateRect(hw,nullptr,FALSE); return 0;

  case WM_PAINT:{
    PAINTSTRUCT ps; HDC hdc=BeginPaint(hw,&ps);
    RECT rc; GetClientRect(hw,&rc);
    HDC mem=CreateCompatibleDC(hdc);
    HBITMAP bm=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
    HBITMAP ob=(HBITMAP)SelectObject(mem,bm);

    GradV(mem,rc,BG_BASE,BG_DEEP);
    DrawGrid(mem,RW,RH2);

    // Header
    Fill(mem,{0,0,RW,58},BG_HEADER);
    HLine(mem,0,RW,58,AC_CYAN,2);
    {HFONT fh=MkF(17,true); TC(mem,L"\U0001F4CB  YOUR TRIP PLAN",{0,10,RW,52},TXT_HI,fh); DeleteObject(fh);}

    // ตาราง
    int TT=70,TLx=20,TRx=RW-20,RHt=40;
    int c0=TLx,c1=TLx+38,c2=TLx+370,c3=TLx+540,c4=TRx;

    // หัวตาราง
    GradV(mem,{TLx,TT,TRx,TT+RHt},BG_TBL_H,BG_PANEL);
    HLine(mem,TLx,TRx,TT,BRD_H,1); HLine(mem,TLx,TRx,TT+RHt,BRD_H,1);
    {
      HFONT fh2=MkF(10,true);
      auto th=[&](int x1,int x2,const std::wstring&t){TL(mem,t,{x1,TT,x2,TT+RHt},AC_CYAN,fh2,8);};
      th(c0,c1,L"#"); th(c1,c2,L"Place / Restaurant"); th(c2,c3,L"Category"); th(c3,c4,L"Province + Cost");
      DeleteObject(fh2);
    }

    // แถวข้อมูล
    int maxR=(int)std::min(g_picks.size(),(size_t)13);
    HFONT fr=MkF(11); int totalC=0,pCost=0,fCost=0;

    if(g_picks.empty()){
      RECT nr={TLx,TT+RHt,TRx,TT+RHt*3};
      Fill(mem,nr,BG_ROW_A);
      TC(mem,L"ยังไม่มีรายการ \u2014 กด Plan Trip หรือ What to Eat เพื่อเพิ่มรายการ",nr,TXT_D,fr);
    }
    for(int i=0;i<maxR;i++){
      auto&p=g_picks[i]; totalC+=p.cost;
      if(p.isFood)fCost+=p.cost; else pCost+=p.cost;
      int ry=TT+RHt*(i+1);
      COLORREF rowBg=(i%2==0)?BG_ROW_A:BG_ROW_B;
      Fill(mem,{TLx,ry,TRx,ry+RHt},rowBg);
      HLine(mem,TLx,TRx,ry+RHt-1,BRD_N);

      // ไอคอน food/place
      {
        RECT ir={c0,ry,c1,ry+RHt};
        HFONT fi2=MkF(11); TC(mem,p.isFood?L"\U0001F35C":L"\U0001F4CD",ir,TXT_M,fi2); DeleteObject(fi2);
      }
      auto cl=[&](int x1,int x2,const std::wstring&t,COLORREF c){TL(mem,t,{x1,ry,x2,ry+RHt},c,fr,8);};
      cl(c1,c2,p.name,TXT_HI);
      cl(c2,c3,p.cat,p.isFood?AC_ORG:AC_BL);
      std::wstring rCol=p.province+L"  ("+(p.cost==0?L"FREE":std::to_wstring(p.cost)+L" THB")+L")";
      cl(c3,c4,rCol,AC_CYAN);
    }

    // "... และอีก N รายการ"
    if(g_picks.size()>(size_t)maxR){
      int ry=TT+RHt*(maxR+1);
      for(size_t i=maxR;i<g_picks.size();i++){totalC+=g_picks[i].cost;if(g_picks[i].isFood)fCost+=g_picks[i].cost;else pCost+=g_picks[i].cost;}
      TC(mem,L"... และอีก "+std::to_wstring(g_picks.size()-maxR)+L" รายการ",
         {TLx,ry,TRx,ry+RHt},TXT_M,fr);
    }
    DeleteObject(fr);

    // แถวสรุปยอด
    if(!g_picks.empty()){
      int ry=TT+RHt*(maxR+(g_picks.size()>13?2:1));
      // สรุปแต่ละประเภท
      RECT sumR={TLx,ry,TRx,ry+48};
      GradV(mem,sumR,RGB(10,30,20),RGB(8,24,16));
      HLine(mem,TLx,TRx,ry,AC_GRN,1); HLine(mem,TLx,TRx,ry+48,AC_GRN,1);
      HFONT fB=MkF(11,true);
      TL(mem,L"  \U0001F4CD สถานที่: "+std::to_wstring(pCost)+L" THB   \U0001F35C อาหาร: "+std::to_wstring(fCost)+L" THB",
         {TLx,ry,TRx/2,ry+48},TXT_M,fB,8);
      TR(mem,L"รวมทั้งหมด:  "+std::to_wstring(totalC)+L" THB  ",
         {TLx,ry,TRx,ry+48},AC_GRN,fB,8);
      DeleteObject(fB);
    }

    // Bottom bar
    Fill(mem,{0,RH2-82,RW,RH2},BG_HEADER);
    HLine(mem,0,RW,RH2-82,BRD_N);
    HFONT fb=MkF(12,true);
    for(auto&b:g_resBtns) DrawBtn(mem,b,fb);
    DeleteObject(fb);

    BitBlt(hdc,0,0,rc.right,rc.bottom,mem,0,0,SRCCOPY);
    SelectObject(mem,ob); DeleteObject(bm); DeleteDC(mem);
    EndPaint(hw,&ps); return 0;
  }

  case WM_MOUSEMOVE: HitBtns(g_resBtns,{GET_X_LPARAM(lp),GET_Y_LPARAM(lp)},hw); return 0;
  case WM_LBUTTONDOWN:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    for(auto&b:g_resBtns) if(PtInRect(&b.rc,pt))b.dn=true;
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_LBUTTONUP:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    int id=ClickBtns(g_resBtns,pt);
    if(id==ID_SAVE) DoSave(hw);
    if(id==ID_CLOSE){ DestroyWindow(hw); g_hRes=nullptr; }
    if(id==ID_CLEAR){
      if(MessageBox(hw,L"ลบรายการทั้งหมดในแผนทริป?",L"Clear Plan",
                    MB_YESNO|MB_ICONQUESTION)==IDYES){
        g_picks.clear();
        InvalidateRect(hw,nullptr,FALSE);
        if(g_hMain)InvalidateRect(g_hMain,nullptr,FALSE);
      }
    }
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_ERASEBKGND: return 1;
  case WM_DESTROY: g_hRes=nullptr; KillTimer(hw,ID_TANIM); return 0;
  }
  return DefWindowProc(hw,msg,wp,lp);
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 16 — AI Advisor Window (v8 ใหม่!)
// ══════════════════════════════════════════════════════════════════════════

static std::vector<CBtn> g_aiBtns;

void OpenAI(HWND par){
  if(g_hAI){ DestroyWindow(g_hAI); g_hAI=nullptr; }

  // สร้างข้อความ AI
  g_aiText=GenerateAIAdvice();
  g_aiDisplay=L"";
  g_aiIdx=0;
  g_aiDone=false;
  g_aiCursor=0;

  int sx=(GetSystemMetrics(SM_CXSCREEN)-AW)/2;
  int sy=(GetSystemMetrics(SM_CYSCREEN)-AH)/2;
  g_hAI=CreateWindowEx(WS_EX_DLGMODALFRAME|WS_EX_TOPMOST,L"TripApp_AI",
    L"\U0001F916  AI Trip Advisor",
    WS_POPUP|WS_CAPTION|WS_SYSMENU,sx,sy,AW,AH,par,nullptr,g_hI,nullptr);

  g_aiBtns.clear();
  int by=AH-68,bh=46;
  g_aiBtns.push_back({{AW/2-80,by,AW/2+80,by+bh},L"Close",L"\u2715",ID_CLOSE,BTN_SN,BTN_SH,RGB(18,30,65)});
  g_aiBtns.push_back({{AW-28-180,by,AW-28,by+bh},L"Regenerate",L"\U0001F504",ID_ASKAI,BTN_YN,AC_GOLD,RGB(80,60,8)});

  ShowWindow(g_hAI,SW_SHOW); UpdateWindow(g_hAI);
}

LRESULT CALLBACK AIProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp){
  switch(msg){
  case WM_CREATE:
    SetTimer(hw,ID_TANIM,16,nullptr);
    SetTimer(hw,ID_TTYPE,18,nullptr); // Typewriter speed
    return 0;

  case WM_TIMER:
    if(wp==ID_TTYPE){
      // Typewriter effect: เพิ่มทีละ 2-3 ตัวอักษร
      if(!g_aiDone&&g_aiIdx<(int)g_aiText.size()){
        int add=std::min(3,(int)g_aiText.size()-g_aiIdx);
        g_aiDisplay+=g_aiText.substr(g_aiIdx,add);
        g_aiIdx+=add;
        if(g_aiIdx>=(int)g_aiText.size()) g_aiDone=true;
        InvalidateRect(hw,nullptr,FALSE);
      }
    }
    if(wp==ID_TANIM){
      g_aiCursor=(g_aiCursor+1)%30; // cursor blink
      TickBtns(g_aiBtns);
      InvalidateRect(hw,nullptr,FALSE);
    }
    return 0;

  case WM_PAINT:{
    PAINTSTRUCT ps; HDC hdc=BeginPaint(hw,&ps);
    RECT rc; GetClientRect(hw,&rc);
    HDC mem=CreateCompatibleDC(hdc);
    HBITMAP bm=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
    HBITMAP ob=(HBITMAP)SelectObject(mem,bm);

    GradV(mem,rc,BG_BASE,BG_DEEP);
    DrawGrid(mem,AW,AH);

    // Header
    Fill(mem,{0,0,AW,58},BG_HEADER);
    HLine(mem,0,AW,58,AC_GOLD,2);
    // AI icon glow
    RadialGlow(mem,50,29,30,AC_GOLD,0.3f);
    {
      HFONT fh=MkF(17,true);
      TL(mem,L"  \U0001F916  AI Trip Advisor",{0,10,AW-20,52},AC_GOLD,fh,4);
      DeleteObject(fh);
    }
    // Status indicator
    {
      HFONT fs2=MkF(9);
      std::wstring stat=g_aiDone?L"\u25cf DONE":L"\u25cf THINKING...";
      COLORREF sc=g_aiDone?AC_GRN:Lerp(AC_GOLD,AC_ORG,(g_sinT+1.f)*0.5f);
      TR(mem,stat,{0,10,AW-10,52},sc,fs2,6);
      DeleteObject(fs2);
    }

    // กล่อง text area
    RECT ta={20,64,AW-20,AH-82};
    RndFill(mem,ta,8,BG_CARD,BRD_N);
    GlowBord(mem,ta,8,AC_GOLD,0.4f);

    // ข้อความ AI + cursor
    std::wstring disp=g_aiDisplay;
    if(!g_aiDone&&g_aiCursor<15) disp+=L"\u2588"; // block cursor กะพริบ

    {
      HFONT ft=MkF(11,false,false,L"Consolas");
      TML(mem,disp,ta,g_aiDone?AC_GRN:Lerp(AC_GOLD,TXT_HI,0.6f),ft,14);
      DeleteObject(ft);
    }

    // ถ้าพิมพ์เสร็จ → แสดง glow เส้นขอบ
    if(g_aiDone) GlowBord(mem,ta,8,AC_GRN,0.7f);

    // Bottom bar
    Fill(mem,{0,AH-78,AW,AH},BG_HEADER);
    HLine(mem,0,AW,AH-78,BRD_N);
    HFONT fb=MkF(12,true);
    for(auto&b:g_aiBtns) DrawBtn(mem,b,fb);
    DeleteObject(fb);

    // Tip ด้านล่าง
    {
      HFONT ft2=MkF(9,false,true);
      TL(mem,L"  AI วิเคราะห์จากข้อมูลในแผนทริปของคุณ",
         {0,AH-78,AW/2,AH},TXT_D,ft2,4);
      DeleteObject(ft2);
    }

    BitBlt(hdc,0,0,rc.right,rc.bottom,mem,0,0,SRCCOPY);
    SelectObject(mem,ob); DeleteObject(bm); DeleteDC(mem);
    EndPaint(hw,&ps); return 0;
  }

  case WM_MOUSEMOVE: HitBtns(g_aiBtns,{GET_X_LPARAM(lp),GET_Y_LPARAM(lp)},hw); return 0;
  case WM_LBUTTONDOWN:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    for(auto&b:g_aiBtns) if(PtInRect(&b.rc,pt))b.dn=true;
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_LBUTTONUP:{
    POINT pt={GET_X_LPARAM(lp),GET_Y_LPARAM(lp)};
    int id=ClickBtns(g_aiBtns,pt);
    if(id==ID_CLOSE){ DestroyWindow(hw); g_hAI=nullptr; }
    if(id==ID_ASKAI){
      // Regenerate: รีเซ็ต typewriter
      g_aiText=GenerateAIAdvice();
      g_aiDisplay=L""; g_aiIdx=0; g_aiDone=false;
      InvalidateRect(hw,nullptr,FALSE);
    }
    InvalidateRect(hw,nullptr,FALSE); return 0;
  }
  case WM_ERASEBKGND: return 1;
  case WM_DESTROY:
    g_hAI=nullptr;
    KillTimer(hw,ID_TANIM); KillTimer(hw,ID_TTYPE);
    return 0;
  }
  return DefWindowProc(hw,msg,wp,lp);
}

// ══════════════════════════════════════════════════════════════════════════
// SECTION 17 — WinMain
// ══════════════════════════════════════════════════════════════════════════

int WINAPI WinMain(HINSTANCE hI,HINSTANCE,LPSTR,int nShow){
  g_hI=hI;

  auto Reg=[&](LPCWSTR cn,WNDPROC proc,COLORREF bg){
    WNDCLASSEX w={sizeof(WNDCLASSEX)};
    w.lpfnWndProc=proc; w.hInstance=hI;
    w.hbrBackground=CreateSolidBrush(bg);
    w.hCursor=LoadCursor(nullptr,IDC_ARROW);
    w.lpszClassName=cn;
    w.style=CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    RegisterClassEx(&w);
  };

  Reg(L"TripApp_Main", MainProc, BG_BASE);
  Reg(L"TripApp_Wiz",  WizProc,  BG_PANEL);
  Reg(L"TripApp_Res",  ResProc,  BG_PANEL);
  Reg(L"TripApp_AI",   AIProc,   BG_BASE);

  int sx=(GetSystemMetrics(SM_CXSCREEN)-MW)/2;
  int sy=(GetSystemMetrics(SM_CYSCREEN)-MH)/2;

  g_hMain=CreateWindowEx(
    WS_EX_APPWINDOW,L"TripApp_Main",
    L"\u2708  Smart Trip Assistant v8  |  Pro Dark Neon",
    WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MAXIMIZEBOX,
    sx,sy,MW,MH,nullptr,nullptr,hI,nullptr);

  ShowWindow(g_hMain,nShow);
  UpdateWindow(g_hMain);

  MSG msg={};
  while(GetMessage(&msg,nullptr,0,0)){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int)msg.wParam;
}