<<<<<<< Updated upstream
#include <iostream>
#include "menu.h"

using namespace std;

// function prototype
void runProgram();

int main() {
    runProgram();
    return 0;
}

void runProgram() {
    int choice;

    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- Input Trip Data ---\n";
                // ยังไม่เรียก getUserInput()
                break;

            case 2:
                cout << "\n--- Calculate Trip ---\n";
                // ยังไม่เรียก calculation
                break;

            case 3:
                cout << "\n--- Recommendation ---\n";
                // ยังไม่เรียก recommendation
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

        cout << endl;

    } while (choice != 0);
=======
#include<iostream>
#include "input.h"

using namespace std;

int main(){
     displayBanner();
    
    TravelPreference pref = getUserInput();
    
    // ทดสอบ print ค่าที่รับมา
    cout << "\n===== Your Travel Info =====" << endl;
    cout << "Budget     : " << pref.budget    << " Baht" << endl;
    cout << "Days       : " << pref.days       << " days" << endl;
    cout << "People     : " << pref.people     << " people" << endl;
    cout << "Has Car    : " << (pref.hascar ? "Yes" : "No") << endl;
    cout << "Trip Style : " << pref.tripStyle  << endl;
    
    return 0;
>>>>>>> Stashed changes
}