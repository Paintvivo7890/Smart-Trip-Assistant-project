// #include "input.h"
// #include "recommendation.h"


// using namespace std;


// void displayBanner(){
//     cout << endl<<"===================================="<<endl;
//     cout << endl<< "    SMART PLAN TRIP ASSITANT       "<<endl;
//     cout << endl<<"===================================="<<endl;
// }

// void select_mode(){

//     int select = 0; // 0 คือ สถานะยังไม่ได้เลือก
//     string input = "";
//     do {
//         cout<<"[ 1 ] : Plan trip \n";
//         cout<<"[ 2 ] : What to Eat Today ? \n";
//         cout<<"[ 3 ] : Exit \n";
//         cout<<"Select :  ";
        
//         cin >> input;
//         clearInputBuffer(); //ไม่มีก็ได้ แต่เผื่อเพิ่ม input ที่เป็น int

//         if (input == "1") select = 1;
//         else if (input == "2") select = 2;
//         else if (input == "3") select = 3;
//         else {
//             Error();
//             select = 0;
//         }

//         if(select != 1 && select != 2 && select != 3) Error();

        
//     } while (select != 1 && select != 2 && select != 3);

//     if(select == 1){
//         //Feature 1 plan trip
//         getUserInput_1(); // [**1**]

//     }else if(select == 2){
//         //Feature 2 restaurant
//         getUserInput_2(); // [**2**]

//     }else if(select == 3){
//         //exit
        
//     }
// }

// // Enter 1 plan trip [**1**]
// TravelPreference getUserInput_1(){

//     TravelPreference pref;
//     int day = 1;
//     int place,type_trip,people,budget;
//     char again = 'n';

//     line();
//     cout<<"=====>>> Smart Trip Assistant <<<=====" << endl;
//     cout<<"Please enter your travel information below.\n"<<endl;
//     line();
    
//     //1.ไปกี่คน
//     pref.people = getValid_Integer("Number of travelers : ");
//     people = pref.people;

//     //2.งบประมาณ เลือก 1.บอก 2.ให้โปรแกรมคิดให้
//     pref.budget = getValid_Integer("Total budget (THB) [Enter 0 if not specified] : ");
//     budget = pref.budget;
//     //long time กี่วัน
//     pref.days = getValid_Integer("How many days will you be staying? : ");
//     day = pref.days;
    
//     for(int i = 1 ; i <= day ; i++){
//         line();
//         cout<< "[ Day "<< i <<" ] "<<endl;
//         //วันที่ i ไปกี่ที่
//         pref.num_place = getValid_Integer("How many places would you like to visit per day? : ");
//         place = pref.num_place;

//         for(int j = 1 ; j <= place ; j++){
//             //1.เลือกจังหวัด
//             show_pv();
//             line();
//             cout<< "[ place "<< j <<" ] "<<endl;
//             // pref.province = getValid_Integer("Which province would you like to visit? : ");
//             // pv = pref.province;
//             pref.Province.push_back(getValid_Integer("Which province would you like to visit? : "));
//             line();
//             //2.เลือกสไตล์
//             show_style();
//             // pref.tripStyle = getValid_Integer("Enter 1-6 : ");
//             // ts =  pref.tripStyle;
//             pref.tripStyle.push_back(getValid_Integer("Enter 1-5 : "));
//             vector<Place> p1 = Screening_province(allplace, pref.Province);
//             vector<Place> p2 = Recommendation_place(p1,pref.tripStyle);
//             Show_Place(p2);
//         }
       
//     }

//     return pref;
// }

// // Enter 2 Feature food
// Restaurant getUserInput_2(){
//     Restaurant rest;
//     int ctm , ctgr ,btf , ml;

//     cout<<"========== Restaurant ==========";
    
//     //ถามจำนวนคน
//     rest.customer = getValid_Integer("How many people are dining ? : ");
//     ctm = rest.customer;
    

//     for (int i = 0; i < ctm; i++){
//         cout<<"People[ "<<i+1<<" ]"<<endl;
//         Person p;
        
//         p.meals = getValid_Integer("How many meals would you like ?\nEnter number: ");
//         ml = p.meals;

//         for(int j = 0 ; j < ml ; j ++){
//             Meal m;

//             cout<<"Meals[ "<<j+1<<" ]"<<endl;
//             //เลือกเส้น หรือ ข้าว
//             m.category = getValid_Integer("Select your preferred dish type:\n1. Noodles\n2. Rice\n3. Surprise me\nEnter your choice (1-3): ");
//             ctgr = m.category;

//             if(ctgr == 3){
//                 cout<<"Random";
//                 //random
//                 break;
//             }
//         }
//     }
//     return rest;
// }



// //เคลียร์บัฟเฟอร์
// void clearInputBuffer(){
//     cin.clear();
//     cin.ignore(numeric_limits<streamsize>::max(),'\n');//reset error state ลบทุกอย่างจนกว่าจะเจอ newline
// }

// int getValid_Integer(const string &prompt){
//     int value;

//     while(1){
//         cout << prompt;
//         //check ว่าเป็น Number มั้ย
//         if(cin >> value && value > 0){
//             clearInputBuffer(); //ล้างสิ่งที่ผู้ใช้ป้อนค้างไว้ใน Buffer
//             return value;
//         }
//         cout << "Error : Please enter a valid number or number more than zero. \n" ;
//         clearInputBuffer(); //clear for next input
//     }
// }

// // input type Yes/No แปลงเป็น Boolean
// bool getYes_No_Input(const string &prompt){
//     string input_YN;

//     while(1){
//         cout << prompt << "[Yes / No] : ";
//         getline(cin,input_YN);

//         for(char &text : input_YN){
//             text = toupper(text);
//         }
        
//         if(input_YN == "YES" || input_YN == "Y"){
//             return true;
//         }else if(input_YN == "NO" || input_YN == "N"){
//             return false;
//         }else {
//             cout << "Error: Please enter 'yes' or 'no'.\n";
//         }
//     }

// }

// //input type string
// string getString_Input(const string& prompt){
//     string str;

//     while(1){
//         cout << prompt;
//         getline(cin,str);
//         line(); //เส้นกั้น

//         if(!str.empty()) return str;
//         else cout << "Error : Input can't be empty"<<endl;

//     }
// }

// // Error message helper
// void Error(){
//     cout<<"Error: Invalid input. Please try again."<<endl;
// }

// void line(){
//     cout<<"------------------------------------------------------"<<endl;
// }


// //โขว์ข้อมูลจังงหวัด
// void show_pv(){
//     cout << left
//          << setw(20) << "[1] Chiang Mai"
//          << setw(20) << "[2] Chiang Rai"
//          << setw(20) << "[3] Mae Hong Son"
//          << setw(20) << "[4] Lamphun"
//          << setw(20) << "[5] Lampang" << endl

//          << setw(20) << "[6] Phayao"
//          << setw(20) << "[7] Phrae"
//          << setw(20) << "[8] Nan"
//          << setw(20) << "[9] Uttaradit"
//          << setw(20) << "[10] Tak" << endl

//          << setw(20) << "[11] Sukhothai"
//          << setw(20) << "[12] Phitsanulok"
//          << setw(20) << "[13] Kamphaeng Phet"
//          << setw(20) << "[14] Phetchabun"
//          << setw(20) << "[15] Phichit" << endl

//          << setw(20) << "[16] Nakhon Sawan"
//          << setw(20) << "[17] Uthai Thani" << endl;
// }

// void show_style(){
//     line();
//     cout<<"Select your preferred dish type:"<<endl;
//     line();
//     cout<<left
//         << setw(25) << "[ 1 ] Culture"
//         << setw(25) << "[ 2 ] Adventure" << endl
//         << setw(25) << "[ 3 ] Natural"
//         << setw(25) << "[ 4 ] Photo" << endl

//         << setw(25) << "[ 5 ] Cafe" 
//         << setw(25) << "[ 6 ] Random" << endl;
// }


// void show_place(){
//     cout<<"Place----------wait logic recomendation"<<endl;
// }
#include "input.h"
#include "recommendation.h"

using namespace std;

// ===== ANSI Color Codes =====
#define RESET       "\033[0m"
#define BOLD        "\033[1m"

// Text Colors
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Bright Colors
#define BRIGHT_RED      "\033[91m"
#define BRIGHT_GREEN    "\033[92m"
#define BRIGHT_YELLOW   "\033[93m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_MAGENTA  "\033[95m"
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_WHITE    "\033[97m"

// Background Colors
#define BG_BLUE     "\033[44m"
#define BG_CYAN     "\033[46m"


void displayBanner(){
    cout << endl;
    cout << BOLD BRIGHT_CYAN  "====================================" RESET << endl;
    cout << BOLD BRIGHT_YELLOW "    SMART PLAN TRIP ASSISTANT      " RESET << endl;
    cout << BOLD BRIGHT_CYAN  "====================================" RESET << endl;
    cout << endl;
}

void select_mode(){

    int select = 0;
    string input = "";

    do {
        cout << BOLD BRIGHT_GREEN  "[ 1 ]" RESET " : " BRIGHT_WHITE "Plan trip"          RESET "\n";
        cout << BOLD BRIGHT_YELLOW "[ 2 ]" RESET " : " BRIGHT_WHITE "What to Eat Today?" RESET "\n";
        cout << BOLD BRIGHT_RED    "[ 3 ]" RESET " : " BRIGHT_WHITE "Exit"               RESET "\n";
        cout << BOLD CYAN "Select : " RESET;

        cin >> input;
        clearInputBuffer();

        if      (input == "1") select = 1;
        else if (input == "2") select = 2;
        else if (input == "3") select = 3;
        else {
            Error();
            select = 0;
        }

        if(select != 1 && select != 2 && select != 3) Error();

    } while (select != 1 && select != 2 && select != 3);

    if(select == 1){
        getUserInput_1();
    } else if(select == 2){
        getUserInput_2();
    } else if(select == 3){
        cout << BOLD BRIGHT_RED "\nGoodbye! Safe travels!\n" RESET << endl;
    }
}

// Enter 1 plan trip
TravelPreference getUserInput_1(){

    TravelPreference pref;
    int day = 1;
    int place, type_trip, people, budget;

    line();
    cout << BOLD BG_CYAN "   ===>>> Smart Trip Assistant <<<===   " RESET << endl;
    cout << BRIGHT_WHITE "Please enter your travel information below.\n" RESET << endl;
    line();

    // 1. จำนวนคน
    pref.people = getValid_Integer(BOLD BRIGHT_GREEN "Number of travelers : " RESET);
    people = pref.people;

    // 2. งบประมาณ
    pref.budget = getValid_Integer(BOLD BRIGHT_YELLOW "Total budget (THB) [Enter 0 if not specified] : " RESET);
    budget = pref.budget;

    // 3. จำนวนวัน
    pref.days = getValid_Integer(BOLD BRIGHT_CYAN "How many days will you be staying? : " RESET);
    day = pref.days;

    for(int i = 1; i <= day; i++){
        line();
        cout << BOLD BRIGHT_MAGENTA "[ Day " << i << " ]" RESET << endl;

        pref.num_place = getValid_Integer(BOLD BRIGHT_CYAN "How many places would you like to visit per day? : " RESET);
        place = pref.num_place;

        for(int j = 1; j <= place; j++){
            show_pv();
            line();
            cout << BOLD BRIGHT_BLUE "[ Place " << j << " ]" RESET << endl;

            pref.Province.push_back(getValid_Integer(BOLD YELLOW "Which province would you like to visit? : " RESET));
            line();

            show_style();
            pref.tripStyle.push_back(getValid_Integer(BOLD YELLOW "Enter 1-5 : " RESET));

            vector<Place> p1 = Screening_province(allplace, pref.Province);
            vector<Place> p2 = Recommendation_place(p1, pref.tripStyle);
            Show_Place(p2);
        }
    }

    return pref;
}

// Enter 2 Feature food
Restaurant getUserInput_2(){
    Restaurant rest;
    int ctm, ctgr, btf, ml;

    cout << endl;
    cout << BOLD BRIGHT_YELLOW "========== [ Restaurant ] ==========" RESET << endl;

    rest.customer = getValid_Integer(BOLD BRIGHT_GREEN "How many people are dining? : " RESET);
    ctm = rest.customer;

    for(int i = 0; i < ctm; i++){
        cout << BOLD BRIGHT_CYAN "\nPeople[ " << i+1 << " ]" RESET << endl;
        Person p;

        p.meals = getValid_Integer(BOLD YELLOW "How many meals would you like?\nEnter number: " RESET);
        ml = p.meals;

        for(int j = 0; j < ml; j++){
            Meal m;

            cout << BOLD BRIGHT_MAGENTA "Meals[ " << j+1 << " ]" RESET << endl;

            m.category = getValid_Integer(
                BOLD "Select your preferred dish type:\n"
                BRIGHT_GREEN  "  1. Noodles\n" RESET
                BRIGHT_YELLOW "  2. Rice\n"    RESET
                BRIGHT_CYAN   "  3. Surprise me\n" RESET
                BOLD CYAN "Enter your choice (1-3): " RESET
            );
            ctgr = m.category;

            if(ctgr == 3){
                cout << BOLD BRIGHT_MAGENTA ">> Random!" RESET << endl;
                break;
            }
        }
    }
    return rest;
}


// เคลียร์บัฟเฟอร์
void clearInputBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValid_Integer(const string &prompt){
    int value;

    while(1){
        cout << prompt;
        if(cin >> value && value > 0){
            clearInputBuffer();
            return value;
        }
        cout << BOLD BRIGHT_RED "[!] Error : Please enter a valid number greater than zero.\n" RESET;
        clearInputBuffer();
    }
}

// input type Yes/No
bool getYes_No_Input(const string &prompt){
    string input_YN;

    while(1){
        cout << prompt << BOLD CYAN "[Yes / No] : " RESET;
        getline(cin, input_YN);

        for(char &text : input_YN) text = toupper(text);

        if(input_YN == "YES" || input_YN == "Y"){
            return true;
        } else if(input_YN == "NO" || input_YN == "N"){
            return false;
        } else {
            cout << BOLD BRIGHT_RED "[!] Error: Please enter 'yes' or 'no'.\n" RESET;
        }
    }
}

// input type string
string getString_Input(const string& prompt){
    string str;

    while(1){
        cout << prompt;
        getline(cin, str);
        line();

        if(!str.empty()) return str;
        else cout << BOLD BRIGHT_RED "[!] Error : Input can't be empty\n" RESET;
    }
}

// Error message
void Error(){
    cout << BOLD BRIGHT_RED "[!] Error: Invalid input. Please try again.\n" RESET;
}

void line(){
    cout << BRIGHT_BLUE "------------------------------------------------------" RESET << endl;
}


// โชว์จังหวัด
void show_pv(){
    cout << endl << BOLD BRIGHT_CYAN ">> Select Province:" RESET << endl;
    cout << left
         << BRIGHT_GREEN  << setw(20) << "[1] Chiang Mai"
         << BRIGHT_YELLOW << setw(20) << "[2] Chiang Rai"
         << BRIGHT_CYAN   << setw(20) << "[3] Mae Hong Son"
         << BRIGHT_GREEN  << setw(20) << "[4] Lamphun"
         << BRIGHT_YELLOW << setw(20) << "[5] Lampang"   << RESET << endl

         << BRIGHT_CYAN   << setw(20) << "[6] Phayao"
         << BRIGHT_GREEN  << setw(20) << "[7] Phrae"
         << BRIGHT_YELLOW << setw(20) << "[8] Nan"
         << BRIGHT_CYAN   << setw(20) << "[9] Uttaradit"
         << BRIGHT_GREEN  << setw(20) << "[10] Tak"      << RESET << endl

         << BRIGHT_YELLOW << setw(20) << "[11] Sukhothai"
         << BRIGHT_CYAN   << setw(20) << "[12] Phitsanulok"
         << BRIGHT_GREEN  << setw(20) << "[13] Kamphaeng Phet"
         << BRIGHT_YELLOW << setw(20) << "[14] Phetchabun"
         << BRIGHT_CYAN   << setw(20) << "[15] Phichit"  << RESET << endl

         << BRIGHT_GREEN  << setw(20) << "[16] Nakhon Sawan"
         << BRIGHT_YELLOW << setw(20) << "[17] Uthai Thani" << RESET << endl;
}

void show_style(){
    line();
    cout << BOLD BRIGHT_CYAN ">> Select your travel style:" RESET << endl;
    line();
    cout << left
         << BOLD BRIGHT_GREEN  << setw(25) << "[ 1 ] Culture"
         << BOLD BRIGHT_RED    << setw(25) << "[ 2 ] Adventure"  << RESET << endl
         << BOLD BRIGHT_GREEN  << setw(25) << "[ 3 ] Natural"
         << BOLD BRIGHT_YELLOW << setw(25) << "[ 4 ] Photo"      << RESET << endl
         << BOLD BRIGHT_CYAN   << setw(25) << "[ 5 ] Cafe"
         << BOLD BRIGHT_MAGENTA<< setw(25) << "[ 6 ] Random"     << RESET << endl;
}

void Show_place(vector<Place>& places) {
    if (places.empty()) {
        cout << BOLD BRIGHT_RED "  [!] No places found for this selection.\n" RESET;
        return;
    }

    // --- Column widths ---
    const int W_NO   = 4;
    const int W_NAME = 38;
    const int W_DIST = 20;
    const int W_FEE  = 14;

    // --- Border helpers (UTF-8 box-drawing) ---
    //  ถ้าเครื่องรองรับ UTF-8 ใช้อันนี้
    //  ถ้าไม่รองรับ ให้เปลี่ยน top/mid/bot/row เป็นเส้น ASCII ด้านล่าง

    auto repeat = [](const string& s, int n) {
        string r;
        for (int i = 0; i < n; i++) r += s;
        return r;
    };

    // UTF-8 box
    string H   = "\u2500"; // ─
    string VT  = "\u2502"; // │
    string TL  = "\u250C"; // ┌
    string TR  = "\u2510"; // ┐
    string BL  = "\u2514"; // └
    string BR  = "\u2518"; // ┘
    string ML  = "\u251C"; // ├
    string MR  = "\u2524"; // ┤
    string TM  = "\u252C"; // ┬
    string BM  = "\u2534"; // ┴
    string CR  = "\u253C"; // ┼

    // ASCII fallback  (uncomment เพื่อใช้แทน)
    // string H="-", VT="|", TL="+", TR="+", BL="+", BR="+";
    // string ML="+", MR="+", TM="+", BM="+", CR="+";

    auto top = [&]() {
        cout << BRIGHT_CYAN
             << TL << repeat(H, W_NO+2)
             << TM << repeat(H, W_NAME+2)
             << TM << repeat(H, W_DIST+2)
             << TM << repeat(H, W_FEE+2)
             << TR << RESET << "\n";
    };
    auto mid = [&]() {
        cout << BRIGHT_CYAN
             << ML << repeat(H, W_NO+2)
             << CR << repeat(H, W_NAME+2)
             << CR << repeat(H, W_DIST+2)
             << CR << repeat(H, W_FEE+2)
             << MR << RESET << "\n";
    };
    auto bot = [&]() {
        cout << BRIGHT_CYAN
             << BL << repeat(H, W_NO+2)
             << BM << repeat(H, W_NAME+2)
             << BM << repeat(H, W_DIST+2)
             << BM << repeat(H, W_FEE+2)
             << BR << RESET << "\n";
    };
    auto row = [&](const string& no, const string& name,
                   const string& dist, const string& fee,
                   const char* c_no, const char* c_name,
                   const char* c_dist, const char* c_fee) {
        cout << BRIGHT_CYAN << VT << RESET
             << " " << c_no   << left << setw(W_NO)   << no   << RESET
             << " " << BRIGHT_CYAN << VT << RESET
             << " " << c_name << left << setw(W_NAME)  << name << RESET
             << " " << BRIGHT_CYAN << VT << RESET
             << " " << c_dist << left << setw(W_DIST)  << dist << RESET
             << " " << BRIGHT_CYAN << VT << RESET
             << " " << c_fee  << right<< setw(W_FEE)   << fee  << RESET
             << " " << BRIGHT_CYAN << VT << RESET << "\n";
    };

    // --- Header ---
    top();
    row(" No", "Place Name", "District", "Fee (THB)",
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW,
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW);
    mid();

    // --- Rows ---
    for (int i = 0; i < (int)places.size(); i++) {
        string fee_str = (places[i].price == 0)
                         ? "Free"
                         : to_string(places[i].price);

        // สลับสีแถวคู่/คี่
        const char* c_row  = (i % 2 == 0) ? BRIGHT_WHITE : BRIGHT_GREEN;
        const char* c_fee  = (places[i].price == 0)
                             ? BRIGHT_GREEN : BRIGHT_YELLOW;

        row(" " + to_string(i+1),
            places[i].name,
            places[i].district,
            fee_str,
            BRIGHT_CYAN, c_row, c_row, c_fee);

        if (i < (int)places.size() - 1) mid();
    }

    bot();
    cout << BRIGHT_CYAN " Total : " RESET
         << BOLD BRIGHT_YELLOW << places.size() << " place(s) found\n" RESET;
    line();
}