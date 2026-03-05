#include "recommendation.h"

// ===== ANSI Color Codes =====
#define RESET           "\033[0m"
#define BOLD            "\033[1m"
#define BRIGHT_RED      "\033[91m"
#define BRIGHT_GREEN    "\033[92m"
#define BRIGHT_YELLOW   "\033[93m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_MAGENTA  "\033[95m"
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_WHITE    "\033[97m"

// pv คือ เลขที่ผู้ใช้เลือกจังหวัด
vector<Place> Screening_province(vector<Place> &ap, vector<int> Pro){
    vector<Place> province_accordingto_condition;
    
    int pv = Pro[Pro.size() - 1];
    string PV;
    if(pv == 1)  PV = "Chiang Mai";
    if(pv == 2)  PV = "Chiang Rai";
    if(pv == 3)  PV = "Mae Hong Son";
    if(pv == 4)  PV = "Lamphun";
    if(pv == 5)  PV = "Lampang";
    if(pv == 6)  PV = "Phayao";
    if(pv == 7)  PV = "Phrae";
    if(pv == 8)  PV = "Nan";
    if(pv == 9)  PV = "Uttaradit";
    if(pv == 10) PV = "Tak";
    if(pv == 11) PV = "Sukhothai";
    if(pv == 12) PV = "Phitsanulok";
    if(pv == 13) PV = "Kamphaeng Phet";
    if(pv == 14) PV = "Phetchabun";
    if(pv == 15) PV = "Phichit";
    if(pv == 16) PV = "Nakhon Sawan";
    if(pv == 17) PV = "Uthai Thani";

    for(int i = 0; i < (int)ap.size(); i++){
        if(PV == ap[i].Province){
            province_accordingto_condition.push_back(ap[i]);
        }
    }
    return province_accordingto_condition;
}

// ts คือ เลขที่ผู้ใช้เลือก type สถานที่
vector<Place> Recommendation_place(vector<Place> &pac, vector<int> T){
    vector<Place> Place_accordingto_condition;
    int ts = T[T.size() - 1];
    string TS;
    if(ts == 1) TS = "Culture";
    if(ts == 2) TS = "Adventure";
    if(ts == 3) TS = "Natural";
    if(ts == 4) TS = "Photo";
    if(ts == 5) TS = "Cafe";

    for(int i = 0; i < (int)pac.size(); i++){
        if(TS == pac[i].type){
            Place_accordingto_condition.push_back(pac[i]);
        }
    }
    return Place_accordingto_condition;
}

// โชว์สถานที่แบบตารางสีสัน
void Show_Place(vector<Place> &P){
    if(P.empty()){
        cout << BOLD BRIGHT_RED "[!] No places found for this selection.\n" RESET;
        return;
    }

    // --- Column widths ---
    const int W_NO   = 4;
    const int W_NAME = 38;
    const int W_DIST = 22;
    const int W_FEE  = 12;

    auto repeat = [](const string& s, int n){
        string r; for(int i = 0; i < n; i++) r += s; return r;
    };

    // ASCII box
    string H="-", VT="|", TL="+", TR="+", BL="+", BR="+";
    string ML="+", MR="+", TM="+", BM="+", CR="+";

    auto top = [&](){
        cout << BRIGHT_CYAN
             << TL << repeat(H, W_NO+2)
             << TM << repeat(H, W_NAME+2)
             << TM << repeat(H, W_DIST+2)
             << TM << repeat(H, W_FEE+2)
             << TR << RESET << "\n";
    };
    auto mid = [&](){
        cout << BRIGHT_CYAN
             << ML << repeat(H, W_NO+2)
             << CR << repeat(H, W_NAME+2)
             << CR << repeat(H, W_DIST+2)
             << CR << repeat(H, W_FEE+2)
             << MR << RESET << "\n";
    };
    auto bot = [&](){
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
                   const char* c_dist, const char* c_fee){
        cout << BRIGHT_CYAN << VT << RESET
             << " " << c_no   << left  << setw(W_NO)   << no   << RESET
             << " " << BRIGHT_CYAN << VT << RESET
             << " " << c_name << left  << setw(W_NAME)  << name << RESET
             << " " << BRIGHT_CYAN << VT << RESET
             << " " << c_dist << left  << setw(W_DIST)  << dist << RESET
             << " " << BRIGHT_CYAN << VT << RESET
             << " " << c_fee  << right << setw(W_FEE)   << fee  << RESET
             << " " << BRIGHT_CYAN << VT << RESET << "\n";
    };

    // Header
    top();
    row(" No", "Place Name", "District", "Fee (THB)",
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW,
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW);
    mid();

    // Data rows
    for(int i = 0; i < (int)P.size(); i++){
        string fee_str = (P[i].price == 0) ? "Free" : to_string(P[i].price);
        const char* c_row = (i % 2 == 0) ? BRIGHT_WHITE : BRIGHT_GREEN;
        const char* c_fee = (P[i].price == 0) ? BRIGHT_GREEN : BRIGHT_YELLOW;

        row(" " + to_string(i+1),
            P[i].name,
            P[i].district,
            fee_str,
            BRIGHT_CYAN, c_row, c_row, c_fee);

        if(i < (int)P.size() - 1) mid();
    }

    bot();
    cout << BRIGHT_CYAN " Total : " RESET
         << BOLD BRIGHT_YELLOW << P.size() << " place(s) found\n" RESET;
}

// รับเวคเตอร์จาก trip
vector<string> getDistrictList(vector<Place> tripPlaces){
    vector<string> result;
    for(int i = 0; i < (int)tripPlaces.size(); i++){
        string currentDistrict = tripPlaces[i].district;
        bool isDuplicate = false;
        for(int j = 0; j < (int)result.size(); j++){
            if(result[j] == currentDistrict){ isDuplicate = true; break; }
        }
        if(!isDuplicate) result.push_back(currentDistrict);
    }
    return result;
}

// รับ result ของ getDistrictList
vector<Restaurant> filterRestaurantsByDistricts(vector<string> districtList, vector<Restaurant> allRestaurants){
    vector<Restaurant> filteredResult;
    for(int i = 0; i < (int)allRestaurants.size(); i++){
        for(int j = 0; j < (int)districtList.size(); j++){
            if(allRestaurants[i].district == districtList[j]){
                filteredResult.push_back(allRestaurants[i]);
                break;
            }
        }
    }
    return filteredResult;
}

// รับ filteredResult เพื่อนำมาแยกประเภท
vector<Restaurant> Recommendation_place(vector<Restaurant> &pac, int ts){
    vector<Restaurant> Restaurant_accordingto_condition;
    string TS = "";
    if(ts == 1) TS = "Noodle";
    else if(ts == 2) TS = "Rice";

    for(int i = 0; i < (int)pac.size(); i++){
        if(pac[i].type == TS)
            Restaurant_accordingto_condition.push_back(pac[i]);
    }
    return Restaurant_accordingto_condition;
}

void Show_Restaurant(vector<Restaurant> &P){
    if(P.empty()){
        cout << BOLD BRIGHT_RED "[!] No restaurants found!\n" RESET;
        return;
    }

    const int W_NO   = 4;
    const int W_NAME = 30;
    const int W_DIST = 22;
    const int W_TYPE = 10;
    const int W_PRICE = 12;

    auto repeat = [](const string& s, int n){
        string r; for(int i = 0; i < n; i++) r += s; return r;
    };

    string H="-", VT="|", TL="+", TR="+", BL="+", BR="+";
    string ML="+", MR="+", TM="+", BM="+", CR="+";

    auto top = [&](){
        cout << BRIGHT_MAGENTA
             << TL << repeat(H, W_NO+2)   << TM << repeat(H, W_NAME+2)
             << TM << repeat(H, W_DIST+2) << TM << repeat(H, W_TYPE+2)
             << TM << repeat(H, W_PRICE+2) << TR << RESET << "\n";
    };
    auto mid = [&](){
        cout << BRIGHT_MAGENTA
             << ML << repeat(H, W_NO+2)   << CR << repeat(H, W_NAME+2)
             << CR << repeat(H, W_DIST+2) << CR << repeat(H, W_TYPE+2)
             << CR << repeat(H, W_PRICE+2) << MR << RESET << "\n";
    };
    auto bot = [&](){
        cout << BRIGHT_MAGENTA
             << BL << repeat(H, W_NO+2)   << BM << repeat(H, W_NAME+2)
             << BM << repeat(H, W_DIST+2) << BM << repeat(H, W_TYPE+2)
             << BM << repeat(H, W_PRICE+2) << BR << RESET << "\n";
    };
    auto row = [&](const string& no, const string& name, const string& dist,
                   const string& type, const string& price,
                   const char* cn, const char* cname, const char* cd,
                   const char* ct, const char* cp){
        cout << BRIGHT_MAGENTA << VT << RESET
             << " " << cn    << left  << setw(W_NO)    << no    << RESET
             << " " << BRIGHT_MAGENTA << VT << RESET
             << " " << cname << left  << setw(W_NAME)  << name  << RESET
             << " " << BRIGHT_MAGENTA << VT << RESET
             << " " << cd    << left  << setw(W_DIST)  << dist  << RESET
             << " " << BRIGHT_MAGENTA << VT << RESET
             << " " << ct    << left  << setw(W_TYPE)  << type  << RESET
             << " " << BRIGHT_MAGENTA << VT << RESET
             << " " << cp    << right << setw(W_PRICE) << price << RESET
             << " " << BRIGHT_MAGENTA << VT << RESET << "\n";
    };

    cout << "\n" << BOLD BRIGHT_MAGENTA "===== RECOMMENDED RESTAURANTS =====" RESET "\n";
    top();
    row(" No","Name","District","Type","Price (THB)",
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW,
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW);
    mid();

    for(int i = 0; i < (int)P.size(); i++){
        const char* c_row = (i % 2 == 0) ? BRIGHT_WHITE : BRIGHT_GREEN;
        row(" " + to_string(i+1),
            P[i].name, P[i].district, P[i].type,
            to_string(P[i].price) + " THB",
            BRIGHT_MAGENTA, c_row, c_row, c_row, BRIGHT_YELLOW);
        if(i < (int)P.size() - 1) mid();
    }
    bot();
    cout << BRIGHT_MAGENTA " Total : " RESET
         << BOLD BRIGHT_YELLOW << P.size() << " restaurant(s) found\n" RESET;
}

vector<Restaurant> selectresRestaurant(vector<Restaurant> &P){
    vector<Restaurant> select;
    int noForselect;
    cout << BOLD BRIGHT_CYAN "Select by number (0 to finish) : " RESET;
    do{
        cin >> noForselect;
        if(noForselect > 0 && noForselect <= (int)P.size()){
            select.push_back(P[noForselect - 1]);
            cout << BRIGHT_GREEN "Added : " RESET << P[noForselect-1].name << "\n";
            cout << BOLD BRIGHT_CYAN "Select by number (0 to finish) : " RESET;
        } else if(noForselect != 0){
            cout << BOLD BRIGHT_RED "[!] Invalid selection!\n" RESET;
        }
    } while(noForselect != 0);
    return select;
}

void Show_Restaurantsellect(vector<Restaurant> &P){
    if(P.empty()){
        cout << BOLD BRIGHT_RED "[!] You have not selected any restaurant.\n" RESET;
        return;
    }

    const int W_NO   = 4;
    const int W_NAME = 30;
    const int W_DIST = 22;
    const int W_TYPE = 10;
    const int W_PRICE = 12;

    auto repeat = [](const string& s, int n){
        string r; for(int i = 0; i < n; i++) r += s; return r;
    };

    string H="-", VT="|", TL="+", TR="+", BL="+", BR="+";
    string ML="+", MR="+", TM="+", BM="+", CR="+";

    auto top = [&](){
        cout << BRIGHT_YELLOW
             << TL << repeat(H, W_NO+2)   << TM << repeat(H, W_NAME+2)
             << TM << repeat(H, W_DIST+2) << TM << repeat(H, W_TYPE+2)
             << TM << repeat(H, W_PRICE+2) << TR << RESET << "\n";
    };
    auto mid = [&](){
        cout << BRIGHT_YELLOW
             << ML << repeat(H, W_NO+2)   << CR << repeat(H, W_NAME+2)
             << CR << repeat(H, W_DIST+2) << CR << repeat(H, W_TYPE+2)
             << CR << repeat(H, W_PRICE+2) << MR << RESET << "\n";
    };
    auto bot = [&](){
        cout << BRIGHT_YELLOW
             << BL << repeat(H, W_NO+2)   << BM << repeat(H, W_NAME+2)
             << BM << repeat(H, W_DIST+2) << BM << repeat(H, W_TYPE+2)
             << BM << repeat(H, W_PRICE+2) << BR << RESET << "\n";
    };
    auto row = [&](const string& no, const string& name, const string& dist,
                   const string& type, const string& price,
                   const char* cn, const char* cname, const char* cd,
                   const char* ct, const char* cp){
        cout << BRIGHT_YELLOW << VT << RESET
             << " " << cn    << left  << setw(W_NO)    << no    << RESET
             << " " << BRIGHT_YELLOW << VT << RESET
             << " " << cname << left  << setw(W_NAME)  << name  << RESET
             << " " << BRIGHT_YELLOW << VT << RESET
             << " " << cd    << left  << setw(W_DIST)  << dist  << RESET
             << " " << BRIGHT_YELLOW << VT << RESET
             << " " << ct    << left  << setw(W_TYPE)  << type  << RESET
             << " " << BRIGHT_YELLOW << VT << RESET
             << " " << cp    << right << setw(W_PRICE) << price << RESET
             << " " << BRIGHT_YELLOW << VT << RESET << "\n";
    };

    cout << "\n" << BOLD BRIGHT_YELLOW "===== YOUR SELECTED RESTAURANTS =====" RESET "\n";
    top();
    row(" No","Name","District","Type","Price (THB)",
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW,
        BOLD BRIGHT_YELLOW, BOLD BRIGHT_YELLOW);
    mid();

    for(int i = 0; i < (int)P.size(); i++){
        const char* c_row = (i % 2 == 0) ? BRIGHT_WHITE : BRIGHT_GREEN;
        row(" " + to_string(i+1),
            P[i].name, P[i].district, P[i].type,
            to_string(P[i].price) + " THB",
            BRIGHT_YELLOW, c_row, c_row, c_row, BRIGHT_GREEN);
        if(i < (int)P.size() - 1) mid();
    }
    bot();
}