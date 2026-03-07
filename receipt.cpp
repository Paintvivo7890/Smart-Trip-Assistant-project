#include "receipt.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include "input.h"      // TravelPreference
#include "dataENG.h"    // Place, restaurant, Person, Meal
#include "calculation.h"

using namespace std;

// ===== ANSI Color =====
#define RESET           "\033[0m"
#define BOLD            "\033[1m"
#define BRIGHT_RED      "\033[91m"
#define BRIGHT_GREEN    "\033[92m"
#define BRIGHT_YELLOW   "\033[93m"
#define BRIGHT_MAGENTA  "\033[95m"
#define BRIGHT_CYAN     "\033[96m"
#define BRIGHT_WHITE    "\033[97m"

// ================================================================
//  Helper : แปลง id -> ชื่อ
// ================================================================
string getProvinceName(int id) {
    switch(id) {
        case 1:  return "Chiang Mai";       case 2:  return "Chiang Rai";
        case 3:  return "Mae Hong Son";     case 4:  return "Lamphun";
        case 5:  return "Lampang";          case 6:  return "Phayao";
        case 7:  return "Phrae";            case 8:  return "Nan";
        case 9:  return "Uttaradit";        case 10: return "Tak";
        case 11: return "Sukhothai";        case 12: return "Phitsanulok";
        case 13: return "Kamphaeng Phet";   case 14: return "Phetchabun";
        case 15: return "Phichit";          case 16: return "Nakhon Sawan";
        case 17: return "Uthai Thani";
        default: return "Unknown";
    }
}

string getStyleName(int id) {
    switch(id) {
        case 1: return "Culture";   case 2: return "Adventure";
        case 3: return "Natural";   case 4: return "Photo";
        case 5: return "Cafe";      case 6: return "Random";
        default: return "Unknown";
    }
}

string getMealCategoryName(int id) {
    switch(id) {
        case 1: return "Noodles";
        case 2: return "Rice";
        case 3: return "Surprise me (Random)";
        default: return "Unknown";
    }
}

string getTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

void fileLine(ofstream& f) {
    f << "------------------------------------------------------\n";
}

void printLine(ofstream& f, int length = 70){
    for(int i = 0; i < length; i++) f << "-";
    f << "\n";
}

void printTitle(ofstream& f, string text){
    f << "\n";
    for(int i=0;i<70;i++) f<<"=";
    f << "\n";
    f << "   " << text << "\n";
    for(int i=0;i<70;i++) f<<"=";
    f << "\n";
}

// ================================================================
//  saveTripReceipt
//  - บันทึก Plan Trip ลง trip_plan.txt (append ต่อท้ายทุกครั้ง)
//  - รับ allSelectedPlaces ที่ user เลือกมาจาก selectPlace()
//  - รับ pref สำหรับข้อมูล travelers / days / budget
// ================================================================
void saveTripReceipt(const TravelPreference& pref,
                     vector<Place> allSelectedPlaces,
                     const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << BRIGHT_RED "[!] Cannot open file '" << filename << "'\n" RESET;
        return;
    }

    // ---- คำนวณด้วย calculation.h ----
    int placeCost    = calculatePlaceCost(allSelectedPlaces);
    double perPerson = calculateCostPerPerson(placeCost, pref.people);
    double perDay    = calculateCostPerDay(placeCost, pref.days);
    bool ok          = isWithinBudget(placeCost, pref.budget);
    int remaining    = calculateRemainingBudget(pref.budget, placeCost);

    // ---- header ----
    file << "======================================================\n";
    file << "        SMART PLAN TRIP ASSISTANT                     \n";
    file << "        [ TRIP PLAN RECEIPT ]                         \n";
    file << "======================================================\n";
    file << "  Date & Time   : " << getTimestamp() << "\n";
    fileLine(file);

    // ---- travel info ----
    file << "  Travelers     : " << pref.people << " person(s)\n";
    file << "  Duration      : " << pref.days   << " day(s)\n";
    file << "  Budget        : ";
    if (pref.budget == 0) file << "Not specified\n";
    else                  file << pref.budget << " THB\n";

    file << "  Province(s)   : ";
    for (int i = 0; i < (int)pref.Province.size(); i++) {
        file << getProvinceName(pref.Province[i]);
        if (i < (int)pref.Province.size() - 1) file << ", ";
    }
    file << "\n";

    file << "  Style(s)      : ";
    for (int i = 0; i < (int)pref.tripStyle.size(); i++) {
        file << getStyleName(pref.tripStyle[i]);
        if (i < (int)pref.tripStyle.size() - 1) file << ", ";
    }
    file << "\n";
    fileLine(file);

// ---- selected places table ----
file << "\nPLACES YOU SELECTED\n";
printLine(file);

if (allSelectedPlaces.empty()) {

    file << "No places selected\n";

} else {

    file << left
         << setw(5)  << "No"
         << setw(30) << "Place Name"
         << setw(18) << "District"
         << setw(12) << "Type"
         << setw(10) << "Fee"
         << "\n";

    printLine(file);

    for (int i = 0; i < (int)allSelectedPlaces.size(); i++) {

        string fee = (allSelectedPlaces[i].price == 0)
                     ? "Free"
                     : to_string(allSelectedPlaces[i].price);

        file << left
             << setw(5)  << i+1
             << setw(30) << allSelectedPlaces[i].name
             << setw(18) << allSelectedPlaces[i].district
             << setw(12) << allSelectedPlaces[i].type
             << setw(10) << fee
             << "\n";
    }

    printLine(file);

    // ---- cost breakdown ----
    file << "\nCOST BREAKDOWN\n";
    printLine(file);

    file << "Total places        : " << allSelectedPlaces.size() << "\n";
    file << "Entrance fee total  : " << placeCost  << " THB\n";
    file << "Cost per person     : " << fixed << setprecision(2) << perPerson << " THB\n";
    file << "Cost per day        : " << fixed << setprecision(2) << perDay    << " THB\n";

    if (pref.budget > 0) {
        file << "Budget status       : "
             << (ok ? "Within budget (OK)" : "Over budget") << "\n";
        file << "Remaining budget    : " << remaining << " THB\n";
    }   

    printLine(file);

    file << "\n";
    file << "======================================================\n\n";

    file.close();

    cout << BRIGHT_GREEN
         << "[OK] Trip plan saved to '" << filename << "'\n"
         << RESET;
    }
}

// ================================================================
//  saveRestaurantReceipt
//  - บันทึก Restaurant receipt ลง restaurant_receipt.txt (append)
//  - รับ rest (มี peopleList / customer)
//  - รับ foods = ร้านที่ user เลือกมาทั้งหมด (สะสมจากทุก meal)
// ================================================================
    void saveRestaurantReceipt(const restaurant& rest,
                           vector<restaurant> foods,
                           const string& filename){
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << BRIGHT_RED "[!] Cannot open file '" << filename << "'\n" RESET;
        return;
    }

    // ---- คำนวณด้วย calculation.h ----
    int totalCost    = calculateRestaurantCost(foods);
    double perPerson = calculateCostPerPerson(totalCost, rest.customer);

    // ---- header ----
    file << "======================================================\n";
    file << "        SMART PLAN TRIP ASSISTANT                     \n";
    file << "        [ RESTAURANT RECEIPT ]                        \n";
    file << "======================================================\n";
    file << "  Date & Time     : " << getTimestamp() << "\n";
    fileLine(file);

    // ---- info ----
    file << "  Province        : " << getProvinceName(rest.prov) << "\n";
    file << "  Total diners    : " << rest.customer << " person(s)\n";
    fileLine(file);

    // ---- meal detail per person ----
    file << "  ORDER DETAIL :\n";
    for (int i = 0; i < (int)rest.peopleList.size(); i++) {
        file << "  Person [" << (i+1) << "] :\n";
        for (int j = 0; j < (int)rest.peopleList[i].mealList.size(); j++) {
            file << "    Meal " << (j+1) << " : "
                 << getMealCategoryName(rest.peopleList[i].mealList[j].category);
            if (!rest.peopleList[i].mealList[j].result.empty())
                file << "  ->  " << rest.peopleList[i].mealList[j].result;
            file << "\n";
        }
    }
    fileLine(file);

    // ---- selected restaurants table ----
    file << "\nRESTAURANTS SELECTED\n";
    printLine(file);

    if (foods.empty()) {

        file << "No restaurants selected\n";

    } else {

        file << left
             << setw(5)  << "No"
            << setw(28) << "Restaurant"
            << setw(18) << "District"
            << setw(12) << "Type"
            << setw(10) << "Price"
            << "\n";

        printLine(file);

        for (int i = 0; i < (int)foods.size(); i++) {

            file << left
                 << setw(5)  << i+1
                << setw(28) << foods[i].name
                << setw(18) << foods[i].district
                << setw(12) << foods[i].type
                << setw(10) << foods[i].price
                << "\n";
        }

        printLine(file);

        file << "\n";
        file << "Total restaurants : " << foods.size() << "\n";
        file << "Total price       : " << totalCost << " THB\n";
        file << "Price per person  : " << fixed << setprecision(2)
             << perPerson << " THB\n";
    }

    file << "======================================================\n\n";
    file.close();

    cout << BRIGHT_GREEN "[OK] Restaurant receipt saved to '" << filename << "'\n" RESET;
}

// ================================================================
//  viewSavedFile  –  อ่านและแสดงไฟล์บน console
// ================================================================
void viewSavedFile(const string& filename) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << BRIGHT_RED 
             << "[!] No records found. ('" << filename << "' does not exist yet)\n"
             << RESET;
        return;
    }

    cout << endl;
    cout << BRIGHT_CYAN 
         << "==================== HISTORY ====================" 
         << RESET << endl;

    string ln;

    while (getline(file, ln)) {

        if (ln.find("SMART PLAN") != string::npos)
            cout << BOLD << BRIGHT_WHITE << ln << RESET << endl;

        else if (ln.find("PLACES") != string::npos)
            cout << BOLD << BRIGHT_YELLOW << ln << RESET << endl;

        else if (ln.find("RESTAURANTS") != string::npos)
            cout << BOLD << BRIGHT_YELLOW << ln << RESET << endl;

        else if (ln.find("====") != string::npos)
            cout << BRIGHT_YELLOW << ln << RESET << endl;

        else if (ln.find("Total") != string::npos)
            cout << BRIGHT_GREEN << ln << RESET << endl;

        else if (ln.find("Price") != string::npos)
            cout << BRIGHT_CYAN << ln << RESET << endl;

        else if (ln.find("Person") != string::npos)
            cout << BRIGHT_MAGENTA << ln << RESET << endl;

        else
            cout << ln << endl;
    }

    cout << BRIGHT_CYAN 
         << "================================================="
         << RESET << endl;

    file.close();
}