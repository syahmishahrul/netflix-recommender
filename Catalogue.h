#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "Title.h"
#include <string>
#include <vector>
using namespace std;

// Holds every title loaded from the catalogue file
class Catalogue {
private:
    vector<Title> titles;

    // Turns one '|'-separated line into a Title
    Title parseLine(string line) const;

public:
    // Reads the file. Returns false if the file cannot be opened.
    bool loadFromFile(string fileName);

    int size() const;

    // Returns all titles that match the genre, type and minimum rating.
    // type can be "Movie", "Series" or "Any". Sorted highest rating first.
    vector<Title> findMatches(string genre, string type, double minRating) const;
};

#endif
