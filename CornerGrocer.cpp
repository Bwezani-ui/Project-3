//Bwezani Mukuka 
// 06/20/2025
// Project 3- Corner Grocer



#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits> // For input buffer clearing

using namespace std;

// Class to manage item tracking
class CornerGrocerTracker {
private:
    map<string, int> itemFrequency; // Stores item names and how many times each was purchased

public:
    // Constructor reads items from file and builds frequency map
    CornerGrocerTracker() {
        ifstream inputFile("CS210_Project_Three_Input_File.txt");
        string item;

        // Count each item from the file
        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close(); // Close the input file

        // Save the data to a backup file
        ofstream outputFile("frequency.dat");
        for (auto pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close(); // Close the backup file
    }

    // Returns how many times an item appears. Returns -1 if not found.
    int getItemFrequency(string item) {
        auto it = itemFrequency.find(item); // Look for item in map
        if (it != itemFrequency.end()) {
            return it->second; // Item found
        }
        else {
            return -1; // When the item is not found
        }
    }

    // Display all items and their counts
    void printAllFrequencies() {
        for (auto pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Show histogram with asterisks for frequency
    void printHistogram() {
        for (auto pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

// Main program
int main() {
    CornerGrocerTracker tracker; // Create object to load file data
    int choice;                  // Menu choice
    string item;                 // User item input

    do {
        // Show menu
        cout << endl;
        cout << "==============================" << endl;
        cout << "   CORNER GROCER: MAIN MENU   " << endl;
        cout << "==============================" << endl;
        cout << "1. Search for item" << endl;
        cout << "2. Show the number of frequency of item" << endl;
        cout << "3. Show histogram (Chart)" << endl;
        cout << "4. Exit" << endl;
        cout << "**Please select a number from the menu**:" << endl;

        cin >> choice;

        // To handle invalid input like letters
        if (cin.fail()) {
            cin.clear(); // Clear error
            cin.ignore(1000, '\n'); // Remove leftover input
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            cout << "Press Enter to continue." << endl;
            cin.get();
            cin.ignore(1000, '\n');
            continue; // Go back to menu
        }

        // Option 1: Search for item
        if (choice == 1) {
            cout << "Enter the name of the item:" << endl;
            cin >> ws;
            getline(cin, item); // Read full item name

            int freq = tracker.getItemFrequency(item);
            if (freq != -1) {
                cout << item << " appears " << freq << " times." << endl;
            }
            else {
                cout << "That item was not found." << endl;
            }

            cout << "Press Enter to return to the menu." << endl;
            cin.ignore();
            cin.get();
        }

        // Option 2: Show all items
        else if (choice == 2) {
            tracker.printAllFrequencies();
        }

        // Option 3: Show histogram
        else if (choice == 3) {
            tracker.printHistogram();
        }

        // Option 4: Exit program
        else if (choice == 4) {
            cout << endl << "Thank you for using Corner Grocer, Goodbye!" << endl;
        }

        // Any other number outside 1–4
        else {
            cout << "Invalid menu option. Please enter 1 to 4." << endl;
            cout << "Press Enter to return to the menu." << endl;
            cin.ignore();
            cin.get();
        }

    } while (choice != 4); // Loop until user chooses to exit

    return 0;
}