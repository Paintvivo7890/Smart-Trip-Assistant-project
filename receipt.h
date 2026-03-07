#ifndef RECEIPT_H
#define RECEIPT_H

#include <string>
#include <vector>
#include "input.h"
#include "dataENG.h"

using namespace std;

// ===== Helper Functions =====
string getProvinceName(int id);
string getStyleName(int id);
string getMealCategoryName(int id);
string getTimestamp();
void fileLine(ofstream& f);

// ===== Trip Receipt =====
void saveTripReceipt(const TravelPreference& pref,
                     vector<Place> allSelectedPlaces,
                     const string& filename = "trip_plan.txt");

// ===== Restaurant Receipt =====
void saveRestaurantReceipt(const restaurant& rest,
                           vector<restaurant> foods,
                           const string& filename = "restaurant_receipt.txt");

// ===== View Saved File =====
void viewSavedFile(const string& filename);

void printTitle(ofstream&, string text);

void printLine(ofstream&, int length);

#endif