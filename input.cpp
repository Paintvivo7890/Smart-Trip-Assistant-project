#include "input.h"
#include "recommendation.h"
#include "calculation.h"
#include "dataENG.h"
#include "receipt.h"
#include <map>

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
        cout << BOLD BRIGHT_GREEN  "[1] Plan Trip\n"                    RESET;
        cout << BOLD BRIGHT_YELLOW "[2] What to Eat Today\n"            RESET;
        cout << BOLD BRIGHT_CYAN   "[3] View My Trip History\n"         RESET;
        cout << BOLD BRIGHT_CYAN   "[4] View My Restaurant History\n"   RESET;
        cout << BOLD BRIGHT_RED    "[5] Exit\n"                         RESET;
        line();
        cout << BOLD BRIGHT_CYAN "Select option : " RESET;
        
        cin >> input;
        clearInputBuffer();

        if      (input == "1") select = 1;
        else if (input == "2") select = 2;
        else if (input == "3") select = 3;
        else if (input == "4") select = 4;
        else if (input == "5") select = 5;
        else { Error(); select = 0; }

    } while (select < 1 || select > 5);

    if (select == 1) {
        getUserInput_1();
    } else if (select == 2) {
        getUserInput_2();
    } else if (select == 3) {
        // ดูประวัติ Trip ที่บันทึกไว้
        viewSavedFile("trip_plan.txt");
    } else if (select == 4) {
        // ดูประวัติ Restaurant ที่บันทึกไว้
        viewSavedFile("restaurant_receipt.txt");
    } else if (select == 5) {
        cout << BOLD BRIGHT_RED "\nGoodbye! Safe travels!\n" RESET << endl;
    }
}

// Enter 1 plan trip [**1**]
TravelPreference getUserInput_1(){

    vector<Place> allSelectedPlaces;
    vector<restaurant> foods;

    TravelPreference pref;
    
    int day = 1;
    int place,type_trip,people,budget;
    string yn;

    line();
    cout << BOLD BG_CYAN "   ===>>> Smart Trip Assistant <<<===   " RESET << endl;
    cout << BRIGHT_WHITE "Please enter your travel information below.\n" RESET << endl;
    line();
    
    //1.ไปกี่คน
    pref.people = getValid_Integer(BOLD BRIGHT_GREEN "Number of travelers : " RESET);
    people = pref.people;

    //2.งบประมาณ เลือก 1.บอก 2.ให้โปรแกรมคิดให้
    pref.budget = getValid_Integer(BOLD BRIGHT_YELLOW "Total budget (THB) [Enter 0 if not specified] : " RESET);
    budget = pref.budget;

    //3.long time กี่วัน
    pref.days = getValid_Integer(BOLD BRIGHT_CYAN "How many days will you be staying? : " RESET);
    day = pref.days;
    
    for(int i = 1 ; i <= day ; i++){
        line();
        cout << BOLD BRIGHT_MAGENTA "[ Day " << i << " ]" RESET << endl;
        //วันที่ i ไปกี่ที่
        
        place = pref.num_place;
        //1.เลือกจังหวัด
            show_pv();
            line();
            

            pref.Province.push_back(getValid_Integer(BOLD BRIGHT_CYAN "Which province would you like to visit? : " RESET));

            line();
            //2.เลือกสไตล์
            show_style();
            
            pref.tripStyle.push_back(getValid_Integer(BOLD YELLOW "Enter 1-6 : " RESET));

            vector<Place> p1 = Screening_province(allplace, pref.Province);
            vector<Place> p2 = Recommendation_place(p1,pref.tripStyle);
            Show_Place(p2);

            vector<Place> selectedPlaces = selectPlace(p2);
            Show_PlaceSelect(selectedPlaces);

            for(auto &p : selectedPlaces){
                allSelectedPlaces.push_back(p);
            }

            cout << BOLD BRIGHT_GREEN "You have selected " RESET << selectedPlaces.size() << BOLD BRIGHT_GREEN " place(s) for Day " RESET << i << "." << endl;
            line();

        
    }

    showTripSummary(allSelectedPlaces, foods, pref);

    
    // ===== บันทึกลงไฟล์ =====
    saveTripReceipt(pref, allSelectedPlaces);

   line();
    do{
        cout<<BOLD BRIGHT_GREEN"View My Trip History (y/n) :"<<RESET;
        cin>> yn;

        if(yn == "y" ||yn == "Y"){
            viewSavedFile("trip_plan.txt");
            break;
        }

    }while(yn != "y" && yn != "n");
    
    

    return pref;
}


// Enter 2 Feature food
restaurant getUserInput_2(){

    vector<restaurant> foods;

    restaurant rest;
    int ctm , ctgr ,btf , ml;
    string yn;
    

    cout << BOLD BRIGHT_YELLOW "========== [ Restaurant ] ==========" RESET << endl;

    line();
    //1.ถามจังหวัด
    show_pv();
    line();
    rest.prov = getValid_Integer(BOLD BRIGHT_GREEN "Which province would you like to eat in? : " RESET);
    vector<string> DISlist = getDistrictList(allrestaurant, rest.prov);
    line();
    //2.ถามอำเภอ
    show_district(rest.prov);
    line();
    rest.dis = getValid_Integer(BOLD YELLOW "Which district are you interested in? : " RESET);
    vector<restaurant> FR = filterRestaurantsByDistricts(DISlist, allrestaurant, rest.dis);
    
    line();


    

    //ถามจำนวนคน
    rest.customer = getValid_Integer(BOLD YELLOW "How many people are dining ? : " RESET);
    ctm = rest.customer;
    line();

    for (int i = 0; i < ctm; i++){
        cout<<BOLD BRIGHT_MAGENTA "People[ "<<i+1<<" ]" RESET <<endl;
        Person p;
        
        p.meals = getValid_Integer(BOLD YELLOW "How many meals would you like ? : " RESET);
        ml = p.meals;

        for(int j = 0 ; j < ml ; j ++){
            Meal m;

            cout<< BOLD BRIGHT_MAGENTA "Meals[ "<<j+1<<" ]" RESET <<endl;
            //เลือกเส้น หรือ ข้าว
            m.category = getValid_Integer(BOLD "Select your preferred dish type:\n"
                BRIGHT_GREEN "1.Noodles\n"
                BRIGHT_YELLOW "2.Rice\n" RESET
                BRIGHT_CYAN "3. Surprise me\n" RESET
                BOLD CYAN "Enter your choice (1-3): " RESET 
            );
    
            vector<restaurant> recomRES =Recommendation_res(FR, m.category);
            Show_restaurant(recomRES);
            vector<restaurant> selectedRestaurants = selectRestaurant(recomRES);
            Show_restaurantsellect(selectedRestaurants);

            for(auto &r : selectedRestaurants){
                foods.push_back(r);
            } 
            p.mealList.push_back(m);
        }
        rest.peopleList.push_back(p); 
    }

    Show_Restaurant_Summary(foods);

    // ===== บันทึกลงไฟล์ =====
    saveRestaurantReceipt(rest, foods);

    line();
    do{
        cout<<BOLD BRIGHT_GREEN"View My Restaurant History (y/n) :"<<RESET;
        cin>> yn;

        if(yn == "y" ||yn == "Y"){
            viewSavedFile("restaurant_receipt.txt");
            break;
        }

    }while(yn != "y" && yn != "n");

    return rest;
}


//เคลียร์บัฟเฟอร์
void clearInputBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');//reset error state ลบทุกอย่างจนกว่าจะเจอ newline
}

int getValid_Integer(const string &prompt){
    int value;

    while(1){
        cout << prompt;
        //check ว่าเป็น Number มั้ย
        if(cin >> value){
        if(value > 0){
            clearInputBuffer(); //ล้างสิ่งที่ผู้ใช้ป้อนค้างไว้ใน Buffer
            return value;
        }else if(value == 0){
            cout<< BRIGHT_GREEN "Thank you. calculati system.\n" RESET ;
            clearInputBuffer(); //clear for next input
            return 0;
        }
        
        }else{
            cout << BRIGHT_RED "Error : Please enter a valid number or number more than zero. \n" RESET;
            
            }
        clearInputBuffer(); //clear for next input
}
}

// input type Yes/No แปลงเป็น Boolean
bool getYes_No_Input(const string &prompt){
    string input_YN;

    while(1){
        cout << prompt << "[" BRIGHT_GREEN "Yes" RESET " / " BRIGHT_RED "No" RESET "]"":";
        getline(cin,input_YN);

        for(char &text : input_YN){
            text = toupper(text);
        }
        
        if(input_YN == "YES" || input_YN == "Y"){
            return true;
        }else if(input_YN == "NO" || input_YN == "N"){
            return false;
        }else {
            cout << BRIGHT_RED "Error: Please enter 'yes' or 'no'.\n" RESET;
        }
    }

}

//input type string
string getString_Input(const string& prompt){
    string str;

    while(1){
        cout << prompt;
        getline(cin,str);
        line(); //เส้นกั้น

        if(!str.empty()) return str;
        else cout << BRIGHT_RED "Error : Input can't be empty" RESET <<endl;

    }
}

// Error message helper
void Error(){
    cout<< BOLD RED "Error: Invalid input. Please try again." RESET <<endl;
}

void line(){
    cout<< BRIGHT_BLUE "------------------------------------------------------" RESET <<endl;
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
         << BOLD BRIGHT_CYAN   << setw(25) << "[ 5 ] Cafe"      << RESET << endl;
        //  << BOLD BRIGHT_MAGENTA<< setw(25) << "[ 6 ] Random"    
}

//summary


//โขว์ข้อมูลจังงหวัด
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


int getValid_Integer_for_budget(const string &prompt){
    int value;

    while(true){
        cout << prompt;

        if(cin >> value){
            if(value >= 0){
                clearInputBuffer();
                return value;
            }
        }

        cout << "Error: Please enter a valid number.\n";
        clearInputBuffer();
    }
}

map<int, vector<string>> districts = {

    {1, {"Mueang Chiang Mai","Chom Thong","Mae Rim","Hang Dong",
         "Chiang Dao","Mae Taeng","Samoeng"}},

    {2, {"Mueang Chiang Rai","Mae Suai","Mae Sai","Thoeng",
        "Wiang Kaen","Mae Fa Luang","Chiang Saen",
        "Mae Chan"}},

    {3, {"Mueang Mae Hong Son","Khun Yuam","Pang Mapha","Pai"}},

    {4, {"Mueang Lamphun","Li","Thung Hua Chang","Mae Tha","Pa Sang"}},

    {5, {"Mueang Lampang","Ko Kha","Mae Tha",
        "Chae Hom","Mueang Pan","Ngao",
        "Mae Mo","Hang Chat"}},
    {6, {"Mueang Phayao","Chiang Kham","Pong","Phu Sang","Chiang Muan","Mae Chai"}},

    {7, {"Mueang Phrae","Den Chai","Rong Kwang","Long",
        "Wang Chin","Song"}},

    {8, {"Mueang Nan", "Phu Phiang", "Pua", "Tha Wang Pha", "Na Noi", "Bo Kluea", "Chiang Klang"}},

    {9, {"Mueang Uttaradit", "Nam Pat", "Lablae", "Tha Pla", "Phichai"}},

    {10, {"Mueang Tak", "Umphang", "Tha Song Yang", "Phop Phra", "Mae Ramat",
         "Mae Sot", "Ban Tak", "Sam Ngao"}},

    {11, {"Mueang Sukhothai", "Khiri Mat", "Si Satchanalai", "Sawankhalok",
         "Thung Saliam", "Ban Dan Lan Hoi", "Si Samrong"}},

    {12, {"Mueang Phitsanulok", "Nakhon Thai", "Wang Thong",
         "Noen Maprang", "Chat Trakan", "Wat Bot"}},

    {13, {"Mueang Kamphaeng Phet", "Pang Sila Thong",
         "Khlong Lan", "Kosamphi Nakhon", "Phran Kratai"}},

    {14, {"Mueang Phetchabun", "Si Thep", "Khao Kho",
         "Lom Kao", "Lom Sak", "Nam Nao", "Wang Pong"}},

    {15, {"Mueang Phichit", "Pho Prathap Chang", "Sam Ngam",
         "Thap Khlo", "Bang Mun Nak", "Pho Thale"}},

    {16, {"Mueang Nakhon Sawan", "Takhli", "Banphot Phisai", "Tha Tako", "Chum Saeng",
         "Mae Poen", "Chum Ta Bong", "Tak Fa", "Kao Liao", "Phayuha Khiri"}},

    {17, {"Mueang Uthai Thani", "Lan Sak", "Ban Rai"}},

};

// void show_district(int pv){
//     cout<<"<<<=======district=======>>>"<<endl;
//     line();
//     vector<string> dis = districts[pv];

//     for(int i = 0; i < dis.size(); i++){
//         string text = "[" + to_string(i+1) + "] " + dis[i];
//         cout << left << setw(25) << text;
//         if((i+1)%4==0)
//         cout<<endl;
//         if(i == dis.size() - 1 && dis.size() % 4 != 0){
//             cout << endl;
//         }
//     }

// }

void show_district(int pv){

    cout << endl;
    cout << BOLD BRIGHT_CYAN
         << "               SELECT DISTRICT"
         << RESET << endl;

    cout << BRIGHT_CYAN
         << "+----+--------------------------+\n"
         << "| No | District                 |\n"
         << "+----+--------------------------+"
         << RESET << endl;

    vector<string> dis = districts[pv];

    for(int i = 0; i < dis.size(); i++){

        cout << BRIGHT_CYAN << "| " << RESET
             << setw(2) << i+1
             << BRIGHT_CYAN << " | " << RESET
             << setw(24) << left << dis[i]
             << BRIGHT_CYAN << " |" << RESET
             << endl;
    }

    cout << BRIGHT_CYAN
         << "+----+--------------------------+"
         << RESET << endl;
}