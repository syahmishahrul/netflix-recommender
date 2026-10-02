// Watchlist.h - declares the Watchlist class (titles the user wants to watch later)
#ifndef WATCHLIST_H
#define WATCHLIST_H

#include "Title.h"
#include <string>
#include <vector>
using namespace std;

// Keeps the titles picked during this session and saves them to a file
class Watchlist {
private:
    vector<Title> items;

public:
    // Adds one title to the watchlist
    void add(const Title& t);

    // Number of titles in the watchlist
    int size() const;

    // Prints each title as "- Name (Year)"
    void display() const;

    // Adds the titles to the end of the file. Returns false if it cannot be opened.
    bool saveToFile(string fileName) const;
};

#endif
