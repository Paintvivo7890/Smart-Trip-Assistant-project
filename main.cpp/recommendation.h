#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include<iostream>
#include<string>
#include<vector>
#include "trip.h"

using namespace std;

//เช็ค tripstyle
bool Check_tripstyle(Place &P, string ts);

//แนะนำสถานที่
vector<Place> Recommendation_place(vector<Place> &province, string TS);

//โชว์สถานที่
void Show_Place(vector<Place> &P);
#endif