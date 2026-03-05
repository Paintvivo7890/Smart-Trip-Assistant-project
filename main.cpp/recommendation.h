#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include "dataENG.h"

using namespace std;



//กรอง จังหวัด
vector<Place> Screening_province(vector<Place> &,vector<int>);

//แนะนำสถานที่
vector<Place> Recommendation_place(vector<Place> &,vector<int> );

//โชว์สถานที่
void Show_Place(vector<Place> &);

//แยกอำเภอ
vector<string> getDistrictList(vector<Place> );

//หาร้านอาหารตามอำเภอ
vector<Restaurant> filterRestaurantsByDistricts(vector<string> , vector<Restaurant> );

//เลือกประเภทร้าน
vector<Restaurant> Recommendation_place(vector<Restaurant> &, int );

//โชร้านทั้งหมด
void Show_Restaurant(vector<Restaurant> &);

//เลือกร้านจากที่โช
vector<Restaurant> selectresRestaurant(vector<Restaurant> &);

//โชว่าร้านนี้เลือกไปกี่ครั้ง
void Show_Restaurantsellect(vector<Restaurant> &);

#endif
