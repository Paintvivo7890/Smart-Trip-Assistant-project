#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include<iostream>
#include<string>
#include<vector>
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
vector<restaurant> filterRestaurantsByDistricts(vector<string> , vector<restaurant> );

//เลือกประเภทร้าน
vector<restaurant> Recommendation_place(vector<restaurant> &, int );

//โชร้านทั้งหมด
void Show_restaurant(vector<restaurant> &);

//เลือกร้านจากที่โช
vector<restaurant> selectresrestaurant(vector<restaurant> &);

//โชว่าร้านนี้เลือกไปกี่ครั้ง
void Show_restaurantsellect(vector<restaurant> &);

#endif
