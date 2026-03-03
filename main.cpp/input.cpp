#include "input.h"
#include "recommendation.h"


using namespace std;


void displayBanner(){
    cout << endl<<"===================================="<<endl;
    cout << endl<< "    SMART PLAN TRIP ASSITANT       "<<endl;
    cout << endl<<"===================================="<<endl;
}

void select_mode(){

    int select = 0; // 0 คือ สถานะยังไม่ได้เลือก
    string input = "";
    do {
        cout<<"[ 1 ] : Plan trip \n";
        cout<<"[ 2 ] : What to Eat Today ? \n";
        cout<<"[ 3 ] : Exit \n";
        cout<<"Select :  ";
        
        cin >> input;
        clearInputBuffer(); //ไม่มีก็ได้ แต่เผื่อเพิ่ม input ที่เป็น int

        if (input == "1") select = 1;
        else if (input == "2") select = 2;
        else if (input == "3") select = 3;
        else {
            Error();
            select = 0;
        }

        if(select != 1 && select != 2 && select != 3) Error();

        
    } while (select != 1 && select != 2 && select != 3);

    if(select == 1){
        //Feature 1 plan trip
        getUserInput_1(); // [**1**]

    }else if(select == 2){
        //Feature 2 restaurant
        getUserInput_2(); // [**2**]

    }else if(select == 3){
        //exit
        
    }
}

// Enter 1 plan trip [**1**]
TravelPreference getUserInput_1(){

    TravelPreference pref;
    int day = 1;
    int place,type_trip,people,budget;
    char again = 'n';

    line();
    cout<<"=====>>> Smart Trip Assistant <<<=====" << endl;
    cout<<"Please enter your travel information below.\n"<<endl;
    line();
    
    //1.ไปกี่คน
    pref.people = getValid_Integer("Number of travelers : ");
    people = pref.people;

    //2.งบประมาณ เลือก 1.บอก 2.ให้โปรแกรมคิดให้
    pref.budget = getValid_Integer("Total budget (THB) [Enter 0 if not specified] : ");
    budget = pref.budget;
    //long time กี่วัน
    pref.days = getValid_Integer("How many days will you be staying? : ");
    day = pref.days;
    
    for(int i = 1 ; i <= day ; i++){
        line();
        cout<< "[ Day "<< i <<" ] "<<endl;
        //วันที่ i ไปกี่ที่
        pref.num_place = getValid_Integer("How many places would you like to visit per day? : ");
        place = pref.num_place;

        for(int j = 1 ; j <= place ; j++){
            //1.เลือกจังหวัด
            show_pv();
            line();
            cout<< "[ place "<< j <<" ] "<<endl;
            // pref.province = getValid_Integer("Which province would you like to visit? : ");
            // pv = pref.province;
            pref.province.push_back(getValid_Integer("Which province would you like to visit? : "));
            line();
            //2.เลือกสไตล์
            show_style();
            // pref.tripStyle = getValid_Integer("Enter 1-6 : ");
            // ts =  pref.tripStyle;
            pref.tripStyle.push_back(getValid_Integer("Enter 1-5 : "));
            vector<Place> p1 = Screening_province(allplace, pref.Province);
            vector<Place> p2 = Recommendation_place(p1,pref.tripStyle);
            Show_Place(p2);
        }
       
    }

    return pref;
}

// Enter 2 Feature food
Restaurant getUserInput_2(){
    Restaurant rest;
    int ctm , ctgr ,btf , ml;

    cout<<"========== Restaurant ==========";
    
    //ถามจำนวนคน
    rest.customer = getValid_Integer("How many people are dining ? : ");
    ctm = rest.customer;
    

    for (int i = 0; i < ctm; i++){
        cout<<"People[ "<<i+1<<" ]"<<endl;
        Person p;
        
        p.meals = getValid_Integer("How many meals would you like ?\nEnter number: ");
        ml = p.meals;

        for(int j = 0 ; j < ml ; j ++){
            Meal m;

            cout<<"Meals[ "<<j+1<<" ]"<<endl;
            //เลือกเส้น หรือ ข้าว
            m.category = getValid_Integer("Select your preferred dish type:\n1. Noodles\n2. Rice\n3. Surprise me\nEnter your choice (1-3): ");
            ctgr = m.category;

            if(ctgr == 3){
                cout<<"Random";
                //random
                break;
            }
        }
    }
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
        if(cin >> value && value > 0){
            clearInputBuffer(); //ล้างสิ่งที่ผู้ใช้ป้อนค้างไว้ใน Buffer
            return value;
        }
        cout << "Error : Please enter a valid number or number more than zero. \n" ;
        clearInputBuffer(); //clear for next input
    }
}

// input type Yes/No แปลงเป็น Boolean
bool getYes_No_Input(const string &prompt){
    string input_YN;

    while(1){
        cout << prompt << "[Yes / No] : ";
        getline(cin,input_YN);

        for(char &text : input_YN){
            text = toupper(text);
        }
        
        if(input_YN == "YES" || input_YN == "Y"){
            return true;
        }else if(input_YN == "NO" || input_YN == "N"){
            return false;
        }else {
            cout << "Error: Please enter 'yes' or 'no'.\n";
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
        else cout << "Error : Input can't be empty"<<endl;

    }
}

// Error message helper
void Error(){
    cout<<"Error: Invalid input. Please try again."<<endl;
}

void line(){
    cout<<"------------------------------------------------------"<<endl;
}


//โขว์ข้อมูลจังงหวัด
void show_pv(){
    cout << left
         << setw(20) << "[1] Chiang Mai"
         << setw(20) << "[2] Chiang Rai"
         << setw(20) << "[3] Mae Hong Son"
         << setw(20) << "[4] Lamphun"
         << setw(20) << "[5] Lampang" << endl

         << setw(20) << "[6] Phayao"
         << setw(20) << "[7] Phrae"
         << setw(20) << "[8] Nan"
         << setw(20) << "[9] Uttaradit"
         << setw(20) << "[10] Tak" << endl

         << setw(20) << "[11] Sukhothai"
         << setw(20) << "[12] Phitsanulok"
         << setw(20) << "[13] Kamphaeng Phet"
         << setw(20) << "[14] Phetchabun"
         << setw(20) << "[15] Phichit" << endl

         << setw(20) << "[16] Nakhon Sawan"
         << setw(20) << "[17] Uthai Thani" << endl;
}

void show_style(){
    line();
    cout<<"Select your preferred dish type:"<<endl;
    line();
    cout<<left
        << setw(25) << "[ 1 ] Culture"
        << setw(25) << "[ 2 ] Adventure" << endl
        << setw(25) << "[ 3 ] Natural"
        << setw(25) << "[ 4 ] Photo" << endl

        << setw(25) << "[ 5 ] Cafe" 
        << setw(25) << "[ 6 ] Random" << endl;
}


void show_place(){
    cout<<"Place----------wait logic recomendation"<<endl;
}
