#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <sstream>
#include<string>

using namespace std;

struct TravelPreference{
    int province; //จังหวัด
    int num_place; //จำนวนที่เที่ยว
    int budget = 0; //งบ
    int days; // จน.วันที่ไป
    int people; // จน.คนที่ไป

    bool hascar; // มีรถบ่
    int tripStyle; //ชอบเที่ยวแบบไหนหงะ


};

struct Restaurant{
    string name; //ชื่อร้าน
    string category; //เส้น หรือ ข้าว
    string location;
    

};


TravelPreference getUserInput(); //Feature [1]


//help for validation
int getValid_Integer(const string &prompt);
bool getYes_No_Input(const string &prompt);
string getString_Input(const string &prompt);

//Show UI
void displayBanner();
void clearInputBuffer();

//Error try
void Error();

//check is number
bool Check_number(const string & str);

//Trip style
string Trip();

void select_mode();

void line(); //เส้นกั้น

void show_pv();
void show_place();

#endif