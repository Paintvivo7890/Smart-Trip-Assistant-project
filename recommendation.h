#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include<iostream>
#include<string>
#include<vector>
#include <iomanip>
#include "input.h"
#include "dataENG.h"

using namespace std;



//กรอง จังหวัด
vector<Place> Screening_province(vector<Place> &,vector<int>);

//แนะนำสถานที่
vector<Place> Recommendation_place(vector<Place> &,vector<int> );

//โชว์สถานที่
void Show_Place(vector<Place> &);

void showTripSummary(vector<Place> places, vector<restaurant> foods, TravelPreference pref);

//แยกอำเภอ
vector<string> getDistrictList(vector<restaurant> &, int);

//หาร้านอาหารตามอำเภอ
vector<restaurant> filterRestaurantsByDistricts(vector<string> &, vector<restaurant> &, int);

//เลือกประเภทร้าน
vector<restaurant> Recommendation_res(vector<restaurant> &, int );

//โชร้านทั้งหมด
void Show_restaurant(vector<restaurant> &);

//เลือกร้านจากที่โช
vector<restaurant> selectresrestaurant(vector<restaurant> &);

//โชว่าร้านนี้เลือกไปกี่ครั้ง
void Show_restaurantsellect(vector<restaurant> &);

vector<Place> selectPlace(vector<Place> &P);

void Show_PlaceSelect(vector<Place> &P);

//สรุปร้านอาหาร
void Show_Restaurant_Summary(vector<restaurant> &);


#endif