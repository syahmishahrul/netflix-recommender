#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// One Netflix title (one line of netflix_titles.txt)
struct Title {
    string name;
    string genre;
    string type;        // "Movie" or "Series"
    int year;
    double rating;      // IMDb rating out of 10
    bool isOriginal;    // true = Netflix Original, false = licensed
    string description;
};

const int MAX_TITLES = 100;

// Reads the catalogue file into the titles array.
// Returns how many titles were loaded, or -1 if the file cannot be opened.
int loadTitles(string fileName, Title titles[]) {
    ifstream file(fileName);
    if (!file) {
        return -1;
    }

    string line;
    getline(file, line);   // skip the header line

    int count = 0;
    while (getline(file, line) && count < MAX_TITLES) {
        // Remove the hidden '\r' that Windows adds at the end of each line
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        if (line.empty()) {
            continue;
        }

        // Split the line at each '|' into 7 fields
        string field[7];
        int f = 0;
        for (char c : line) {
            if (c == '|' && f < 6) {
                f++;
            } else {
                field[f] += c;
            }
        }

        titles[count].name        = field[0];
        titles[count].genre       = field[1];
        titles[count].type        = field[2];
        titles[count].year        = stoi(field[3]);
        titles[count].rating      = stod(field[4]);
        titles[count].isOriginal  = (field[5] == "Y");
        titles[count].description = field[6];
        count++;
    }

    file.close();
    return count;
}

int main() {
    Title titles[MAX_TITLES];
    int totalTitles = loadTitles("netflix_titles.txt", titles);

    if (totalTitles == -1) {
        cout << "Error: netflix_titles.txt not found." << endl;
        cout << "Make sure it is in the same folder as the program." << endl;
        return 1;
    }

    int choice;

    cout << "=========================================" << endl;
    cout << "   NETFLIX MOVIE RECOMMENDATION ASSISTANT" << endl;
    cout << "=========================================" << endl;
    cout << "Catalogue loaded: " << totalTitles << " titles" << endl;
    cout << "Choose a genre by entering a number:" << endl;
    cout << "1. Action" << endl;
    cout << "2. Comedy" << endl;
    cout << "3. Horror" << endl;
    cout << "4. Romance" << endl;
    cout << "5. Sci-Fi" << endl;
    cout << "Enter your choice (1-5): ";
    cin >> choice;

    string category;

    // Turn the menu number into a genre name
    switch (choice) {
        case 1:
            category = "Action";
            break;
        case 2:
            category = "Comedy";
            break;
        case 3:
            category = "Horror";
            break;
        case 4:
            category = "Romance";
            break;
        case 5:
            category = "Sci-Fi";
            break;
        default:
            cout << "\nInvalid choice. Please run the program again and enter a number between 1 and 5." << endl;
            return 0;
    }

    // Show every title in the catalogue that matches the chosen genre
    cout << fixed << setprecision(1);   // always show ratings like 7.0, not 7
    cout << "\n-----------------------------------------" << endl;
    cout << "Netflix " << category << " titles for you:" << endl;
    cout << "-----------------------------------------" << endl;

    for (int i = 0; i < totalTitles; i++) {
        if (titles[i].genre == category) {
            cout << "Title       : " << titles[i].name << " (" << titles[i].year << ")" << endl;
            cout << "Type        : " << titles[i].type << endl;
            cout << "Rating      : " << titles[i].rating << "/10" << endl;
            cout << "Description : " << titles[i].description << endl;
            cout << endl;
        }
    }

    cout << "-----------------------------------------" << endl;

    return 0;
}
