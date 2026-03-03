#include "recommendation.h"



// pv คือ เลขที่ผู้ใช้เลือกจังหวัด
vector<Place> Screening_province(vector<Place> &ap, vector<int> Pro){
    vector<Place> province_accordingto_condition;
    
    int pv = Pro[Pro.size() - 1];
    string PV;
    if(pv == 1) PV = "Chiang Mai";
    if(pv == 2) PV = "Chiang Rai";
    if(pv == 3) PV = "Mae Hong Son";
    if(pv == 4) PV = "Lamphun";
    if(pv == 5) PV = "Lampang";
    if(pv == 6) PV = "Phayao";
    if(pv == 7) PV = "Phrae";
    if(pv == 8) PV = "Nan";
    if(pv == 9) PV = "Uttaradit";
    if(pv == 10) PV = "Tak";
    if(pv == 11) PV = "Sukhothai";
    if(pv == 12) PV = "Phitsanulok";
    if(pv == 13) PV = "Kamphaeng Phet";
    if(pv == 14) PV = "Phetchabun";
    if(pv == 15) PV = "Phichit";
    if(pv == 16) PV = "Nakhon Sawan";
    if(pv == 17) PV = "Uthai Thani";

    for(int i = 0; i < ap.size(); i++){
        Place p = ap[i];
        if(PV == p.province){
            province_accordingto_condition.push_back(ap[i]);
        }
    }
    return province_accordingto_condition;
}

// ts คือ เลขที่ผู้ใช้เลือก type สถานที่
vector<Place> Recommendation_place(vector<Place> &pac, vector<int> T ){
    vector<Place> Place_accordingto_condition;
    int ts = T[T.size() - 1 ];
    string TS;
    if(ts == 1) TS = "Culture";
    if(ts == 2) TS = "Adventure";
    if(ts == 3) TS = "Natural";
    if(ts == 4) TS = "Photo";
    if(ts == 5) TS = "Cafe";

    for(int i = 0; i < pac.size(); i++){
        Place p = pac[i];
        if(TS == p.type){
            Place_accordingto_condition.push_back(pac[i]);
        }
    }
    return Place_accordingto_condition;
}


// โชว์สถานที่ ที่ตรงกับเงื่อนไข
void Show_Place(vector<Place> &P){
    cout << "========================================" << endl;
    for(int i = 0; i < P.size(); i++){
        Place p = P[i];
        cout << "Name of place " << "[" << i+1 << "] : " << p.name << endl;
        cout << "District : " << p.district << endl;
        cout << "Entrance Fee : " << p.price << endl;
        cout << "========================================" << endl;
    }
}

//รับเวคเตอร์จากtrip
vector<string> getDistrictList(vector<Place> tripPlaces) {
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
        select.push_back(P[noForselect - 1]);
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


