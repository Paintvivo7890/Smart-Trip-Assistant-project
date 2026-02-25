#include<iostream>
#include<limits>
#include "input.h"

using namespace std;


void displayBanner(){

    cout << endl<<"===================================="<<endl;
    cout << endl<< "    SMART TRIP PLANNER SYSTEM      "<<endl;
    cout << endl<<"===================================="<<endl;

}

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

// get input type Yes/No แปลงเป็น Boolean
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

string getString_Input(const string& prompt){
    string str;

    while(1){
        cout << prompt;
        getline(cin,str);

        if(!str.empty()){
            return str;
        }else{
            cout << "Error : Input can't be empty"<<endl;
        }
    }

}


// version 2
TravelPreference getUserInput(){

    TravelPreference pref;

    cout<<"=====>>> Smart Trip Assistant <<<=====" << endl;
    cout<<"Please enter your travel information below.\n"<<endl;

    // Assign ค่ากลับ + ใช้ Helper ให้ครบ
    pref.budget  = getValid_Integer("Budget [TH-Baht] : ");
    pref.days    = getValid_Integer("Number of travel days : ");
    pref.people  = getValid_Integer("Number of people : ");

    //// ใช้ getYes_No_Input แทน cin >> int (อ่านง่ายกว่า)
    // pref.hascar  = getYes_No_Input("Do you have a private car? ");

    // ใช้ getString_Input แทน getline เปล่าๆ (มี validation)
    pref.tripStyle = getString_Input("Preferred travel style (Relax / Adventure / Foodie / Photography) : ");

    return pref; 

}