#ifndef INPUT_H
#define INPUT_H

#include<string>
using namespace std;

struct TravelPreference{
    int budget; //งบ
    int days; // จน.วันที่ไป
    int people; // จน.คนที่ไป

    bool hascar; // มีรถบ่
    string tripStyle; //ชอบเที่ยวแบบไหนหงะ


};

TravelPreference getUserInput(); //Prototype of function input #1.

//help for validation
int getValid_Intiger(const string &prompt);
bool getYes_No_Input(const string &prompt);
string getString_Input(const string &prompt);


//Show UI
void displayBanner();
void clearInputBuffer();

//Error
void Error();




#endif