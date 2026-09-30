// RecommenderApp.cpp - menus, input validation and showing recommendations
#include "RecommenderApp.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Loads the catalogue, then repeats: ask questions -> show results -> ask again?
int RecommenderApp::run() {
    srand(time(0));   // seed the random generator so "Surprise me" changes each run

    if (!catalogue.loadFromFile("netflix_titles.txt")) {
        cout << "Error: netflix_titles.txt not found." << endl;
        cout << "Make sure it is in the same folder as the program." << endl;
        return 1;
    }

    // Main loop: one recommendation per round until the user says no
    bool again = true;
    while (again) {
        showMenu();
        string genre = genreFromChoice(readChoice(1, 5));

        string type = askType();
        double minRating = askMinRating();
        int mode = askDisplayMode();

        showRecommendations(genre, type, minRating, mode == 2);

        again = askYesNo("\nWould you like another recommendation? (y/n): ");
        cout << endl;
    }

    cout << "Thanks for using the Netflix Recommendation Assistant. Enjoy your show!" << endl;
    return 0;
}

// Reads a menu number; re-asks on letters or out-of-range numbers
int RecommenderApp::readChoice(int min, int max) const {
    int choice;
    while (true) {
        cin >> choice;

        if (cin.eof()) {             // input ended (e.g. Ctrl+Z), stop cleanly
            cout << endl;
            exit(0);
        }

        if (cin.fail()) {            // user typed letters or symbols
            cin.clear();             // reset the error state
            cin.ignore(10000, '\n');  // throw away the bad input
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        } else if (choice < min || choice > max) {
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        } else {
            cin.ignore(10000, '\n');  // clear anything extra typed after the number
            return choice;
        }
    }
}

// Returns true for y/Y, false for n/N; re-asks on anything else
bool RecommenderApp::askYesNo(string question) const {
    string answer;
    while (true) {
        cout << question;
        if (!(cin >> answer)) {      // input ended, treat as "no"
            return false;
        }

        if (answer == "y" || answer == "Y") {
            return true;
        } else if (answer == "n" || answer == "N") {
            return false;
        }
        cout << "Please type y or n." << endl;
    }
}

// Prints the title banner and the genre menu
void RecommenderApp::showMenu() const {
    cout << "=========================================" << endl;
    cout << "   NETFLIX MOVIE RECOMMENDATION ASSISTANT" << endl;
    cout << "=========================================" << endl;
    cout << "Catalogue loaded: " << catalogue.size() << " titles" << endl;
    cout << "Choose a genre by entering a number:" << endl;
    cout << "1. Action" << endl;
    cout << "2. Comedy" << endl;
    cout << "3. Horror" << endl;
    cout << "4. Romance" << endl;
    cout << "5. Sci-Fi" << endl;
    cout << "Enter your choice (1-5): ";
}

// Turns the menu number into a genre name
string RecommenderApp::genreFromChoice(int choice) const {
    switch (choice) {
        case 1:
            return "Action";
        case 2:
            return "Comedy";
        case 3:
            return "Horror";
        case 4:
            return "Romance";
        case 5:
            return "Sci-Fi";
        default:
            return "";   // never reached: readChoice only allows 1-5
    }
}

// Asks movie or series
string RecommenderApp::askType() const {
    cout << "\nMovie or series?" << endl;
    cout << "1. Movie" << endl;
    cout << "2. Series" << endl;
    cout << "3. Either" << endl;
    cout << "Enter your choice (1-3): ";

    switch (readChoice(1, 3)) {
        case 1:
            return "Movie";
        case 2:
            return "Series";
        case 3:
            return "Any";
        default:
            return "";
    }
}

// Asks for the lowest IMDb rating the user will accept
double RecommenderApp::askMinRating() const {
    cout << "\nMinimum IMDb rating?" << endl;
    cout << "1. Any rating" << endl;
    cout << "2. 6.0 and above" << endl;
    cout << "3. 7.0 and above" << endl;
    cout << "4. 8.0 and above" << endl;
    cout << "Enter your choice (1-4): ";

    switch (readChoice(1, 4)) {
        case 1:
            return 0.0;
        case 2:
            return 6.0;
        case 3:
            return 7.0;
        case 4:
            return 8.0;
        default:
            return -1.0;
    }
}

// Asks whether to list every match (1) or pick one at random (2)
int RecommenderApp::askDisplayMode() const {
    cout << "\nHow should we show your results?" << endl;
    cout << "1. Show all matches (highest rated first)" << endl;
    cout << "2. Surprise me (one random pick)" << endl;
    cout << "Enter your choice (1-2): ";

    return readChoice(1, 2);
}

// Filters the catalogue and prints either all matches or one random pick
void RecommenderApp::showRecommendations(string genre, string type, double minRating,
                                         bool surpriseMe) const {
    vector<Title> matches = catalogue.findMatches(genre, type, minRating);

    cout << "\n-----------------------------------------" << endl;
    if (matches.empty()) {
        cout << "Sorry, no " << genre << " titles match your filters." << endl;
        cout << "Try choosing \"Either\" or a lower minimum rating." << endl;
        cout << "-----------------------------------------" << endl;
        return;
    }

    cout << fixed << setprecision(1);

    // Surprise me: pick one random title from the matches
    if (surpriseMe) {
        int pick = rand() % matches.size();
        cout << "Your surprise " << genre << " pick (1 of " << matches.size() << " matches):" << endl;
        cout << "-----------------------------------------" << endl;
        matches[pick].display();
        cout << "-----------------------------------------" << endl;
        return;
    }

    cout << matches.size() << " Netflix " << genre << " title(s) for you";
    if (minRating > 0) {
        cout << " (rated " << minRating << "+)";
    }
    cout << ":" << endl;
    cout << "-----------------------------------------" << endl;

    int originals = 0;
    for (const Title& t : matches) {
        t.display();
        cout << endl;
        if (t.isOriginal()) {
            originals++;
        }
    }

    cout << originals << " of " << matches.size() << " are Netflix Originals." << endl;
    cout << "-----------------------------------------" << endl;
}
