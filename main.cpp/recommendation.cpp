#include "recommendation.h"

// เช็คว่า tripstyleของผู้ใช้ ตรงกับ styleของสถานที่นั้นรึเปล่า 
//อันนี้กรณีที่tripstyleของสถานที่นั้นเป็นvector คือ สถานที่นั้นมีหลายstyle


// แนะนำสถานที่ ตาม จังหวัดที่เลือก,สไตล์การเที่ยว
// TS = TripStyle 
vector<place> Recommendation_place(vector<place> &allplace, string ){
    vector<place> Place_accordingto_condition;
    
    for(int i = 0; i < allplace.size(); i++){
        if(TS == allplace.type[i]){
            Place_accordingto_condition.push_back(province[i]);
        }
    }
    return Place_accordingto_condition;
}


// โชว์สถานที่ ที่ตรงกับเงื่อนไขจากฟังก์ชัน Recommendation_place
void Show_Place(vector<place> &P){
    cout << "===================="
    for(int i = 0; i < P.size(); i++){
        cout << "Name of place " << "[" << i+1 << "] : " << P.name << endl;
        cout << "Total cost (Mininum) : " << P.cost << endl;
        cout << "The style of place : ";
        for(int j = 0, j < P.tripstyle.size(), i++){
            if(j < P.tripstyle.size() - 1){
                cout << P.tripstyle[j]; << " , ";
            }else cout << P.tripstyle[j] << endl;
        }
        cout << "====================" << endl;
    }
}
