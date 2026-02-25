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
}