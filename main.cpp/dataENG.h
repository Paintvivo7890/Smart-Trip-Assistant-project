#ifndef DATAENG_H
#define DATAENG_H

#include<iostream>
#include<vector>
using namespace std;
struct Place {
    string province;
    string district;
    string type;
    string name;
    int price;
};

extern vector<Place> allplace;

struct restaurant {
    
    string district;
    string type;
    string name;
    int price;
};
extern vector<restaurant> allrestaurant;
#endif
