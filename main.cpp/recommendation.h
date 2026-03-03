#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;



//กรอง จังหวัด
vector<place> Screening_provice(vector<place> &, int );

//แนะนำสถานที่
vector<place> Recommendation_place(vector<place> &, int );

//โชว์สถานที่
void Show_Place(vector<place> &);

//แยกอำเภอ
vector<string> getDistrictList(vector<place> );

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