#include "recommendation.h"

// เช็คว่า tripstyleของผู้ใช้ ตรงกับ styleของสถานที่นั้นรึเปล่า 
//อันนี้กรณีที่tripstyleของสถานที่นั้นเป็นvector คือ สถานที่นั้นมีหลายstyle
bool Check_tripstyle(Place &P, string ts){
    for(int i = 0; i < P.tripstyle.size(); i++){
        if(ts == P.tripstyle[i]){
            return true;
            break;
        }else return false;
    }
}

// แนะนำสถานที่ ตาม จังหวัดที่เลือก,สไตล์การเที่ยว
// TS = TripStyle 
vector<Place> Recommendation_place(vector<Place> &province, string TS){
    vector<Place> Place_accordingto_condition;
    
    for(int i = 0; i < province.size(); i++){
        if(Check_tripstyle(province[i],TS)){
            Place_accordingto_condition.push_back(province[i]);
        }
    }
    return Place_accordingto_condition;
}


// โชว์สถานที่ ที่ตรงกับเงื่อนไขจากฟังก์ชัน Recommendation_place
void Show_Place(vector<Place> &P){
    cout << "====================";
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

//รับเวคเตอร์จากtrip
vector<string> getDistrictList(vector<place> tripPlaces) {
    vector<string> result;
    for (int i = 0; i < tripPlaces.size(); i++) {
        string currentDistrict = tripPlaces[i].district;
        bool isDuplicate = false;
        for (int j = 0; j < result.size(); j++) {
            if (result[j] == currentDistrict) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            result.push_back(currentDistrict);
        }
    }
    return result;
}
//รรับ result ของ  getDistrictList
vector<restaurant> filterRestaurantsByDistricts(vector<string> districtList, vector<restaurant> allRestaurants) {
    vector<restaurant> filteredResult;  
    for (int i = 0; i < allRestaurants.size(); i++) {
        for (int j = 0; j < districtList.size(); j++) {
            if (allRestaurants[i].district == districtList[j]) {
                filteredResult.push_back(allRestaurants[i]);
                break; 
            }
        }
    }
    return filteredResult;
}
// รับ filteredResult เพื่อนำมาแยกประเภท
vector<restaurant> Recommendation_place(vector<restaurant> &pac, int ts) {
    vector<restaurant> restaurant_accordingto_condition;
    string TS = "";
    if (ts == 1) TS = "Noodle";
    else if (ts == 2) TS = "Rice";

    for (int i = 0; i < pac.size(); i++) {
        if (pac[i].type == TS) {
            restaurant_accordingto_condition.push_back(pac[i]);
        }
    }
    return restaurant_accordingto_condition;
}
void Show_restaurant(vector<restaurant> &P) {
    if (P.size()==0) {
        cout << ">>> No restaurants found! <<<" << endl;
        return;
    }
    cout << "\n========== RECOMMENDED RESTAURANTS ==========" << endl;
    for (int i = 0; i < P.size(); i++) {
        cout << "NO. "<< i +1 <<endl;
        cout << "Name     : " << P[i].name << endl;
        cout << "District : " << P[i].district << endl;
        cout << "Type     : " << P[i].type << endl;
        cout << "Price    : " << P[i].price << " THB" << endl;
        cout << "--------------------------------------------" << endl;
    }
}
vector<restaurant> selectresrestaurant(vector<restaurant> &P){
    vector<restaurant> select;
    int noForselect;
    do{
    cin >> noForselect;
    if (noForselect > 0 && noForselect <= P.size()) {
        sellect.push_back(P[noForselect - 1]);
         cout << "Added: " << P[noForselect - 1].name << endl;
    } 
    else if (noForselect != 0) {
        cout << "Invalid Selection!" << endl;
    }
    } while(noForselect != 0);
    return select;
}

void Show_restaurantsellect(vector<restaurant> &P) {
    if (P.size()==0) {
        cout << ">>>You not select restaurant <<<" << endl;
        return;
    }
    cout << "\n========== RESTAURANT YOUR SELLECT ==========" << endl;
    for (int i = 0; i < P.size(); i++) {
        cout << "Name     : " << P[i].name << endl;
        cout << "District : " << P[i].district << endl;
        cout << "Type     : " << P[i].type << endl;
        cout << "Price    : " << P[i].price << " THB" << endl;
        cout << "--------------------------------------------" << endl;
    }
}

