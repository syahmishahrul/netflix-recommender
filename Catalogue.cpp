#include "Catalogue.h"
#include <fstream>

bool Catalogue::loadFromFile(string fileName) {
    ifstream file(fileName);
    if (!file) {
        return false;
    }

    string line;
    getline(file, line);   // skip the header line

    while (getline(file, line)) {
        // Remove the hidden '\r' that Windows adds at the end of each line
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        if (line.empty()) {
            continue;
        }
        titles.push_back(parseLine(line));
    }

    file.close();
    return true;
}

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

    return Title(field[0], field[1], field[2], stoi(field[3]),
                 stod(field[4]), field[5] == "Y", field[6]);
}

int Catalogue::size() const {
    return titles.size();
}

vector<Title> Catalogue::findMatches(string genre, string type, double minRating) const {
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
        matches.push_back(t);
    }
    return matches;
}
