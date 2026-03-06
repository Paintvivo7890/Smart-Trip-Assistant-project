#ifndef DATAENG_H
#define DATAENG_H

#include<iostream>
#include<vector>
using namespace std;

struct Place {
    string Province;
    string district;
    string type;
    string name;
    int price;
};

extern vector<Place> allplace;

struct Meal {
    int category; // 1=Noodles, 2=Rice, 3=Surprise
    string result;
};

struct Person {
    int meals;
    vector<Meal> mealList;
};

struct Restaurant {
    string district;
    string type;
    string name;

    int customer;
    int budget_food;

    vector<Person> peopleList;

    int price;
};
extern vector<Restaurant> allRestaurants;
#endif
