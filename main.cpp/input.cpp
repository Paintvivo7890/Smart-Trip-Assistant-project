#include "input.h"
#include "recommendation.h"
#include "calculation.h"

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

    vector<Place> allSelectedPlaces;
    vector<Restaurant> foods;

    int day = 1;
    int place;

    line();
    cout << BOLD BG_CYAN "   ===>>> Smart Trip Assistant <<<===   " RESET << endl;
    cout << BRIGHT_WHITE "Please enter your travel information below.\n" RESET << endl;
    line();

    // จำนวนคน
    pref.people = getValid_Integer(BOLD BRIGHT_GREEN "Number of travelers : " RESET);

    // งบประมาณ
    pref.budget = getValid_Integer(BOLD BRIGHT_YELLOW "Total budget (THB) [Enter 0 if not specified] : " RESET);

    // จำนวนวัน
    pref.days = getValid_Integer(BOLD BRIGHT_CYAN "How many days will you be staying? : " RESET);
    day = pref.days;

    for(int i = 1; i <= day; i++){

        line();
        cout << BOLD BRIGHT_MAGENTA "[ Day " << i << " ]" RESET << endl;

        pref.num_place = getValid_Integer(
            BOLD BRIGHT_CYAN "How many places would you like to visit per day? : " RESET
        );
        place = pref.num_place;

        for(int j = 1; j <= place; j++){

            show_pv();
            line();
            cout << BOLD BRIGHT_BLUE "[ Place " << j << " ]" RESET << endl;

            int provinceChoice = getValid_Integer(
                BOLD YELLOW "Which province would you like to visit? : " RESET
            );

            line();

            show_style();
            int styleChoice = getValid_Integer(
                BOLD YELLOW "Enter 1-6 : " RESET
            );

            // เก็บ input
            pref.Province.push_back(provinceChoice);
            pref.tripStyle.push_back(styleChoice);

            // คัดจังหวัด
            vector<int> pvTemp;
            pvTemp.push_back(provinceChoice);

            vector<int> styleTemp;
            styleTemp.push_back(styleChoice);

            vector<Place> p1 = Screening_province(allplace, pvTemp);
            vector<Place> p2 = Recommendation_place(p1, styleTemp);

            // แสดงตาราง
            Show_Place(p2);

            if(p2.empty()) continue;

            // ให้ user เลือก
            int choice;
            cout << BOLD BRIGHT_CYAN
                 << "Select place number (0 to skip): "
                 << RESET;

            cin >> choice;
            clearInputBuffer();

            if(choice >= 1 && choice <= p2.size()){
                allSelectedPlaces.push_back(p2[choice-1]);

                cout << BRIGHT_GREEN
                     << "Added : " << p2[choice-1].name
                     << RESET << endl;
            }
            else if(choice != 0){
                cout << BRIGHT_RED
                     << "Invalid selection. Skipped."
                     << RESET << endl;
            }
        }
    }

    // Summary
    showTripSummary(allSelectedPlaces, foods, pref);

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
        if(cin >> value && value >= 0){
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
void showTripSummary(vector<Place> places, vector<Restaurant> foods, TravelPreference pref)
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