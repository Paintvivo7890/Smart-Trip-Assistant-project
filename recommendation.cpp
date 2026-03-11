#include "recommendation.h"
#include "input.h"
#include "calculation.h"

#include <iostream>
#include <iomanip>
#include <vector>

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


// pv คือ เลขที่ผู้ใช้เลือกจังหวัด
vector<Place> Screening_province(vector<Place> &ap, vector<int> Pro){
    vector<Place> province_accordingto_condition;
    
    int pv = Pro[Pro.size() - 1];
    string PV;
    if(pv == 1) PV = "Chiang Mai";
    if(pv == 2) PV = "Chiang Rai";
    if(pv == 3) PV = "Mae Hong Son";
    if(pv == 4) PV = "Lamphun";
    if(pv == 5) PV = "Lampang";
    if(pv == 6) PV = "Phayao";
    if(pv == 7) PV = "Phrae";
    if(pv == 8) PV = "Nan";
    if(pv == 9) PV = "Uttaradit";
    if(pv == 10) PV = "Tak";
    if(pv == 11) PV = "Sukhothai";
    if(pv == 12) PV = "Phitsanulok";
    if(pv == 13) PV = "Kamphaeng Phet";
    if(pv == 14) PV = "Phetchabun";
    if(pv == 15) PV = "Phichit";
    if(pv == 16) PV = "Nakhon Sawan";
    if(pv == 17) PV = "Uthai Thani";

    for(int i = 0; i < ap.size(); i++){
        Place p = ap[i];
        if(PV == p.province){
            province_accordingto_condition.push_back(ap[i]);
        }
    }
    return province_accordingto_condition;
}

// ts คือ เลขที่ผู้ใช้เลือก type สถานที่
vector<Place> Recommendation_place(vector<Place> &pac, vector<int> T ){
    vector<Place> Place_accordingto_condition;
    int ts = T[T.size() - 1 ];
    string TS;
    if(ts == 1) TS = "Culture";
    if(ts == 2) TS = "Adventure";
    if(ts == 3) TS = "Natural";
    if(ts == 4) TS = "Photo";
    if(ts == 5) TS = "Cafe";

    for(int i = 0; i < pac.size(); i++){
        Place p = pac[i];
        if(TS == p.type){
            Place_accordingto_condition.push_back(pac[i]);
        }
    }
    return Place_accordingto_condition;
}


// โชว์สถานที่ ที่ตรงกับเงื่อนไข
void Show_Place(vector<Place> &P){

    cout << endl;
    cout << BOLD BRIGHT_GREEN
         << "              RECOMMENDED PLACES"
         << RESET << endl;

    cout << BRIGHT_CYAN
         << "+----+------------------------------+----------------------+--------------+--------+\n"
         << "| No | Place                        | District             | Type         | Price  |\n"
         << "+----+------------------------------+----------------------+--------------+--------+"
         << RESET << endl;

    for(int i=0;i<P.size();i++){

        cout << BRIGHT_CYAN << "| " << RESET
             << setw(2) << i+1 << " "
             << BRIGHT_CYAN << "| " << RESET
             << setw(28) << left << P[i].name
             << BRIGHT_CYAN << "| " << RESET
             << setw(20) << left << P[i].district
             << BRIGHT_CYAN << "| " << RESET
             << setw(12) << left << P[i].type
             << BRIGHT_CYAN << "| " << RESET
             << setw(6) << right << P[i].price
             << BRIGHT_CYAN << " |" << RESET
             << endl;
    }

    cout << BRIGHT_CYAN
         << "+----+------------------------------+----------------------+--------------+--------+"
         << RESET << endl;
}


//รับเวคเตอร์จากtrip
vector<string> getDistrictList(vector<restaurant> &allres, int pv) {
    vector<string> dis_accordingto_condition;
    
    
    string PV;
    if(pv == 1) PV = "Chiang Mai";
    if(pv == 2) PV = "Chiang Rai";
    if(pv == 3) PV = "Mae Hong Son";
    if(pv == 4) PV = "Lamphun";
    if(pv == 5) PV = "Lampang";
    if(pv == 6) PV = "Phayao";
    if(pv == 7) PV = "Phrae";
    if(pv == 8) PV = "Nan";
    if(pv == 9) PV = "Uttaradit";
    if(pv == 10) PV = "Tak";
    if(pv == 11) PV = "Sukhothai";
    if(pv == 12) PV = "Phitsanulok";
    if(pv == 13) PV = "Kamphaeng Phet";
    if(pv == 14) PV = "Phetchabun";
    if(pv == 15) PV = "Phichit";
    if(pv == 16) PV = "Nakhon Sawan";
    if(pv == 17) PV = "Uthai Thani";

    for(int i = 0; i < allres.size(); i++){
        restaurant r = allres[i];
        if(PV == r.province){
            dis_accordingto_condition.push_back(allres[i].district);
            for(int j = 0; j < dis_accordingto_condition.size() - 1; j++){
                if(dis_accordingto_condition[j] == dis_accordingto_condition[dis_accordingto_condition.size() - 1]){
                    dis_accordingto_condition.pop_back();
                    break;
                }
            }
        }
    }
    return dis_accordingto_condition;
}

//รรับ result ของ  getDistrictList
vector<restaurant> filterRestaurantsByDistricts(vector<string> &districtList, vector<restaurant> &allRestaurants, int Dis) {
    vector<restaurant> filteredResult;
    
    string DS_str;
    for(int i = 0; i < districtList.size(); i++){
        if(Dis == i + 1){
            DS_str = districtList[i];
        }
        
    }
    for(int j = 0; j < allRestaurants.size(); j++){
        restaurant r = allRestaurants[j];
        if(r.district == DS_str){
            filteredResult.push_back(allRestaurants[j]);
        }
    }
    return filteredResult;
}
// รับ filteredResult เพื่อนำมาแยกประเภท
vector<restaurant> Recommendation_res(vector<restaurant> &pac, int ts) {
    vector<restaurant> restaurant_accordingto_condition;
    string TS = "";
    if (ts == 1) TS = "Noodle";
    else if (ts == 2) TS = "Rice";

    if(ts == 3){
        vector<restaurant> result;
        srand(time(0));
        do{
        int r = rand() % pac.size();
        result.push_back(pac[r]);
        for(int i = 0; i < result.size() - 1; i++){
            if(result[i].name == result[result.size() - 1].name){
                result.pop_back();
                break;
            }
        }
        }
        while(result.size() < 5);
        return result;
    }
        
    for(int i = 0; i < pac.size(); i++){
        if(pac[i].type == TS)
            restaurant_accordingto_condition.push_back(pac[i]);
    }
    return restaurant_accordingto_condition;

}

void Show_restaurant(vector<restaurant> &P){

    if(P.empty()){
        cout << BRIGHT_RED << "No restaurants found\n" << RESET;
        return;
    }

    cout << endl;
    cout << BOLD BRIGHT_YELLOW
         << "            RECOMMENDED RESTAURANTS"
         << RESET << endl;

    cout << BRIGHT_CYAN
         << "+----+------------------------------+----------------------+----------+--------+\n"
         << "| No | Name                         | District             | Type     | Price  |\n"
         << "+----+------------------------------+----------------------+----------+--------+"
         << RESET << endl;

    for(int i=0;i<P.size();i++){

        cout << BRIGHT_CYAN << "| " << RESET
             << setw(2) << i+1 << " "
             << BRIGHT_CYAN << "| " << RESET
             << setw(28) << left << P[i].name
             << BRIGHT_CYAN << "| " << RESET
             << setw(20) << left << P[i].district
             << BRIGHT_CYAN << "| " << RESET
             << setw(8) << left << P[i].type
             << BRIGHT_CYAN << "| " << RESET
             << setw(6) << right << P[i].price
             << BRIGHT_CYAN << " |" << RESET
             << endl;
    }

    cout << BRIGHT_CYAN
         << "+----+------------------------------+----------------------+----------+--------+"
         << RESET << endl;
}

vector<restaurant> selectRestaurant(vector<restaurant> &P){
    vector<restaurant> select;
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




vector<Place> selectPlace(vector<Place> &P){
    vector<Place> select;
    int noForselect;
    do{
        cout << BRIGHT_GREEN "Enter the number of the place you want to select (0 to finish): " RESET ;
    cin >> noForselect;
    if (noForselect > 0 && noForselect <= P.size()) {
        select.push_back(P[noForselect - 1]);
         cout << BRIGHT_MAGENTA "Added: " RESET << P[noForselect - 1].name << endl;
    } 
    else if (noForselect != 0) {
        cout << BOLD RED "Invalid Selection!" RESET << endl;
    }
    } while(noForselect != 0);
    return select;
}

void Show_restaurantsellect(vector<restaurant> &P) {

    if (P.size()==0) {
        cout << BRIGHT_RED
             << ">>> You did not select any restaurant <<<"
             << RESET << endl;
        return;
    }

    cout << BOLD << BRIGHT_YELLOW
         << "\n=========== RESTAURANTS YOU SELECTED ==========="
         << RESET << endl;

    for (int i = 0; i < P.size(); i++) {

        cout << BRIGHT_CYAN
             << "\nRestaurant [" << i+1 << "]"
             << RESET << endl;

        cout << BRIGHT_YELLOW
             << "--------------------------------------------"
             << RESET << endl;

        cout << BRIGHT_MAGENTA << "Name     : "
             << BRIGHT_WHITE << P[i].name
             << RESET << endl;

        cout << BRIGHT_MAGENTA << "District : "
             << RESET << P[i].district << endl;

        cout << BRIGHT_MAGENTA << "Type     : "
             << RESET << P[i].type << endl;

        cout << BRIGHT_MAGENTA << "Price    : "
             << BRIGHT_GREEN << P[i].price << " THB"
             << RESET << endl;

        cout << BRIGHT_YELLOW
             << "--------------------------------------------"
             << RESET << endl;
    }
}

void Show_PlaceSelect(vector<Place> &P) {

    if (P.size()==0) {
        cout << BRIGHT_RED << ">>> You did not select any place <<<" << RESET << endl;
        return;
    }

    cout << BOLD << BRIGHT_YELLOW
         << "\n============== PLACES YOU SELECTED =============="
         << RESET << endl;

    for (int i = 0; i < P.size(); i++) {

        cout << BRIGHT_CYAN
             << "\nPlace [" << i+1 << "]"
             << RESET << endl;

        cout << BRIGHT_YELLOW
             << "--------------------------------------------"
             << RESET << endl;

        cout << BRIGHT_MAGENTA << "Name     : " << RESET
             << BRIGHT_WHITE << P[i].name << RESET << endl;

        cout << BRIGHT_MAGENTA << "District : " << RESET
             << P[i].district << endl;

        cout << BRIGHT_MAGENTA << "Type     : " << RESET
             << P[i].type << endl;

        cout << BRIGHT_MAGENTA << "Price    : "
             << BRIGHT_GREEN << P[i].price << " THB"
             << RESET << endl;

        cout << BRIGHT_YELLOW
             << "--------------------------------------------"
             << RESET << endl;
    }
}

//สรุปสถานที่เที่ยว
void showTripSummary(vector<Place> places, vector<restaurant> foods, TravelPreference pref)
{
    line();
    cout << BOLD BRIGHT_YELLOW "========== TRIP SUMMARY ==========" RESET << endl;
    line();

    int placeCost = calculatePlaceCost(places);
    int foodCost = calculateRestaurantCost(foods);
    int totalCost = calculateTotalCost(places, foods);

    double costPerPerson = calculateCostPerPerson(totalCost, pref.people);
    double costPerDay = calculateCostPerDay(totalCost, pref.days);

    cout << BRIGHT_CYAN "Total places visited : " 
         << BOLD BRIGHT_WHITE << places.size() << RESET << endl;

    cout << BRIGHT_GREEN "Entrance fees total : " 
         << BOLD BRIGHT_YELLOW << placeCost << " THB" << RESET << endl;

    cout << BRIGHT_GREEN "Food cost total : " 
         << BOLD BRIGHT_YELLOW << foodCost << " THB" << RESET << endl;

    cout << BRIGHT_MAGENTA "Total trip cost : " 
         << BOLD BRIGHT_YELLOW << totalCost << " THB" << RESET << endl;

    cout << BRIGHT_BLUE "Cost per person : " 
         << BOLD BRIGHT_WHITE << costPerPerson << " THB" << RESET << endl;

    cout << BRIGHT_BLUE "Cost per day : " 
         << BOLD BRIGHT_WHITE << costPerDay << " THB" << RESET << endl;

    if(pref.budget != 0){
        int remain = calculateRemainingBudget(pref.budget, totalCost);

        if(remain >= 0){
            cout << BRIGHT_GREEN "Budget remaining : "
                 << BOLD BRIGHT_WHITE << remain << " THB" << RESET << endl;
        }
        else{
            cout << BRIGHT_RED "Over budget : "
                 << BOLD BRIGHT_WHITE << -remain << " THB" << RESET << endl;
        }
    }

    line();
}

// สรุปร้านอาหาร
void Show_Restaurant_Summary(vector<restaurant> &R){
    if(R.empty()){
        cout << BOLD BRIGHT_RED "No restaurants selected.\n" RESET;
        return;
    }

    const int W_NO   = 4;
    const int W_NAME = 30;
    const int W_TYPE = 20;
    const int W_PRICE= 12;

    auto repeat = [](string s,int n){
        string r;
        for(int i=0;i<n;i++) r+=s;
        return r;
    };

    string H="-", VT="|", TL="+", TR="+", BL="+", BR="+";
    string ML="+", MR="+", TM="+", BM="+", CR="+";

    auto top=[&](){
        cout<<BRIGHT_CYAN
        <<TL<<repeat(H,W_NO+2)
        <<TM<<repeat(H,W_NAME+2)
        <<TM<<repeat(H,W_TYPE+2)
        <<TM<<repeat(H,W_PRICE+2)
        <<TR<<RESET<<endl;
    };

    auto mid=[&](){
        cout<<BRIGHT_CYAN
        <<ML<<repeat(H,W_NO+2)
        <<CR<<repeat(H,W_NAME+2)
        <<CR<<repeat(H,W_TYPE+2)
        <<CR<<repeat(H,W_PRICE+2)
        <<MR<<RESET<<endl;
    };

    auto bot=[&](){
        cout<<BRIGHT_CYAN
        <<BL<<repeat(H,W_NO+2)
        <<BM<<repeat(H,W_NAME+2)
        <<BM<<repeat(H,W_TYPE+2)
        <<BM<<repeat(H,W_PRICE+2)
        <<BR<<RESET<<endl;
    };

    auto row=[&](string no,string name,string type,string price){
        cout<<BRIGHT_CYAN<<VT<<RESET
        <<" "<<left<<setw(W_NO)<<no
        <<" "<<BRIGHT_CYAN<<VT<<RESET
        <<" "<<left<<setw(W_NAME)<<name
        <<" "<<BRIGHT_CYAN<<VT<<RESET
        <<" "<<left<<setw(W_TYPE)<<type
        <<" "<<BRIGHT_CYAN<<VT<<RESET
        <<" "<<right<<setw(W_PRICE)<<price
        <<" "<<BRIGHT_CYAN<<VT<<RESET
        <<endl;
    };

    top();
    row("No","Restaurant","Type","Price");
    mid();

    for(int i=0;i<R.size();i++){

        row(
            to_string(i+1),
            R[i].name,
            R[i].type,
            to_string(R[i].price)
        );

        if(i<R.size()-1) mid();
    }

    bot();

    cout<<BRIGHT_CYAN<<"Total : "<<RESET
        <<BOLD BRIGHT_YELLOW<<R.size()<<" restaurant(s)\n"<<RESET;
}
