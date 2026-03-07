#ifndef DATAENG_H
#define DATAENG_H

#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Place {
    string province;
    string district;
    string type;
    string name;
    int price;
};

extern vector<Place> allplace;

struct Meal {
    int category;
    string result;
};

struct Person {
    int meals;
    vector<Meal> mealList;
};

struct restaurant {

    string province;
    string district;
    string type;
    string name;
    int price;

    int customer;
    int budget_food;

    vector<Person> peopleList;  

    int prov;
    int dis;
};

extern vector<restaurant> allrestaurant;

#endif