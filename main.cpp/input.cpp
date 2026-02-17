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

int getValid_Intiger(const string &prompt){
    int value;

    while(1){
        cout << prompt;
        cin >> value;
        
        //check ว่าเป็น Number มั้ย
        if(value < 0){
            cout << "Error : Please enter a valid number or number more than zero. \n" ;
            clearInputBuffer(); //ล้างสิ่งที่ผู้ใช้ป้อนค้างไว้ใน Buffer
            continue;
        }

        clearInputBuffer(); //clear for next input
        return value;
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
        
        if(input_YN == "Yes" || "y" || "yes"){
            return true;
        }else if(input_YN == "No" || "n" || "no"){
            return false;
        }else {
            cout << "Error: Please enter 'yes' or 'no'.\n";
        }

    }

}

string getString_Input(const string& prompt){
    string str;
    string g;

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



TravelPreference getUserInput(){

    TravelPreference pref;

    cout<<"=====>>> Smart Trip Assistant <<<=====" << endl;
    cout<<"Please enter your travel information below.\n"<<endl;

    cout << "Budget [TH-Bath] : ";
    cin >> pref.budget;

    cout << "Number of travel days : ";
    cin >> pref.days;

    cout << "Number of people : ";
    cin >> pref.people;

    cout << "Do you have a private car? [1 = Yes , 0 = No] : ";
    cin >> pref.hascar;

    cin.ignore(); //clear เพราะเดี๋ยวจะใช้ getline

    cout << "Preferred travel style (Relax / Adventure / Foodie / Photography): ";
    getline(cin,pref.tripStyle);

}

// version 2
TravelPreference getUserInput(){

    TravelPreference pref;

    cout<<"=====>>> Smart Trip Assistant <<<=====" << endl;
    cout<<"Please enter your travel information below.\n"<<endl;

    cout << "Budget [TH-Bath] : ";
    getValid_Intiger("Enter budked");

    cout << "Number of travel days : ";
    getValid_Intiger("Enter travelof days");

    cout << "Number of people : ";
    cin >> pref.people;

    cout << "Do you have a private car? [1 = Yes , 0 = No] : ";
    cin >> pref.hascar;

    cin.ignore(); //clear เพราะเดี๋ยวจะใช้ getline

    cout << "Preferred travel style (Relax / Adventure / Foodie / Photography): ";
    getline(cin,pref.tripStyle);

}
