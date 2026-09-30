#include "RecommenderApp.h"
#include <iostream>

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

    showRecommendations(genre);
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

void RecommenderApp::showRecommendations(string genre) const {
    vector<Title> matches = catalogue.findByGenre(genre);

    cout << "\n-----------------------------------------" << endl;
    cout << "Netflix " << genre << " titles for you:" << endl;
    cout << "-----------------------------------------" << endl;

    for (const Title& t : matches) {
        t.display();
        cout << endl;
    }

    cout << "-----------------------------------------" << endl;
}
