// Catalogue.cpp - loads netflix_titles.txt and searches it
#include "Catalogue.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

// Reads every line of the catalogue file into the titles vector
bool Catalogue::loadFromFile(string fileName) {
    ifstream file(fileName);
    if (!file) {
        return false;
    }

    string line;
    getline(file, line);   // skip the header line
    int lineNumber = 1;

    while (getline(file, line)) {
        lineNumber++;
        // Remove the hidden '\r' that Windows adds at the end of each line
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        if (line.empty()) {
            continue;
        }

        // A badly formatted line is skipped instead of crashing the program
        try {
            titles.push_back(parseLine(line));
        } catch (...) {
            cout << "Warning: skipped badly formatted line " << lineNumber
                 << " in " << fileName << endl;
        }
    }

    file.close();
    return true;
}

// Splits one line like "Hush|Horror|Movie|2016|6.6|Y|..." into a Title.
// Throws an error if the line is badly formatted.
Title Catalogue::parseLine(string line) const {
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

    if (f != 6) {
        throw runtime_error("wrong number of fields");
    }

    return Title(field[0], field[1], field[2], stoi(field[3]),
                 stod(field[4]), field[5] == "Y", field[6]);
}

// Number of titles successfully loaded
int Catalogue::size() const {
    return titles.size();
}

// Keeps only the titles that pass all three filters
vector<Title> Catalogue::findMatches(string genre, string type, double minRating,
                                     bool originalsOnly) const {
    vector<Title> matches;
    for (const Title& t : titles) {
        if (t.getGenre() != genre) {
            continue;                       // wrong genre
        }
        if (type != "Any" && t.getType() != type) {
            continue;                       // user wanted only movies or only series
        }
        if (t.getRating() < minRating) {
            continue;                       // rating too low
        }
        if (originalsOnly && !t.isOriginal()) {
            continue;                       // user wanted Netflix Originals only
        }
        matches.push_back(t);
    }

    // Highest rated first, like Netflix's "Top picks"
    sort(matches.begin(), matches.end(), [](const Title& a, const Title& b) {
        return a.getRating() > b.getRating();
    });

    return matches;
}
