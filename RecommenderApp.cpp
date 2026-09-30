#include "RecommenderApp.h"
#include <iostream>
#include <iomanip>

int RecommenderApp::run() {
    if (!catalogue.loadFromFile("netflix_titles.txt")) {
        cout << "Error: netflix_titles.txt not found." << endl;
        cout << "Make sure it is in the same folder as the program." << endl;
        return 1;
    }

    showMenu();

    int choice;
    cin >> choice;

    string genre = genreFromChoice(choice);
    if (genre == "") {
        cout << "\nInvalid choice. Please run the program again and enter a number between 1 and 5." << endl;
        return 0;
    }

    string type = askType();
    if (type == "") {
        cout << "\nInvalid choice. Please run the program again and enter a number between 1 and 3." << endl;
        return 0;
    }

    double minRating = askMinRating();
    if (minRating < 0) {
        cout << "\nInvalid choice. Please run the program again and enter a number between 1 and 4." << endl;
        return 0;
    }

    showRecommendations(genre, type, minRating);
    return 0;
}

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

// Turns the menu number into a genre name ("" means invalid)
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
            return "";
    }
}

// Asks movie or series ("" means invalid)
string RecommenderApp::askType() const {
    cout << "\nMovie or series?" << endl;
    cout << "1. Movie" << endl;
    cout << "2. Series" << endl;
    cout << "3. Either" << endl;
    cout << "Enter your choice (1-3): ";

    int choice;
    cin >> choice;

    switch (choice) {
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

// Asks for the lowest IMDb rating the user will accept (-1 means invalid)
double RecommenderApp::askMinRating() const {
    cout << "\nMinimum IMDb rating?" << endl;
    cout << "1. Any rating" << endl;
    cout << "2. 6.0 and above" << endl;
    cout << "3. 7.0 and above" << endl;
    cout << "4. 8.0 and above" << endl;
    cout << "Enter your choice (1-4): ";

    int choice;
    cin >> choice;

    switch (choice) {
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

void RecommenderApp::showRecommendations(string genre, string type, double minRating) const {
    vector<Title> matches = catalogue.findMatches(genre, type, minRating);

    cout << "\n-----------------------------------------" << endl;
    if (matches.empty()) {
        cout << "Sorry, no " << genre << " titles match your filters." << endl;
        cout << "Try choosing \"Either\" or a lower minimum rating." << endl;
        cout << "-----------------------------------------" << endl;
        return;
    }

    cout << fixed << setprecision(1);
    cout << matches.size() << " Netflix " << genre << " title(s) for you";
    if (minRating > 0) {
        cout << " (rated " << minRating << "+)";
    }
    cout << ":" << endl;
    cout << "-----------------------------------------" << endl;

    for (const Title& t : matches) {
        t.display();
        cout << endl;
    }

    cout << "-----------------------------------------" << endl;
}
