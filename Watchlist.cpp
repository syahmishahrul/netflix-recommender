// Watchlist.cpp - adds, shows and saves the user's watchlist
#include "Watchlist.h"
#include <iostream>
#include <fstream>

void Watchlist::add(const Title& t) {
    items.push_back(t);
}

int Watchlist::size() const {
    return items.size();
}

void Watchlist::display() const {
    for (const Title& t : items) {
        cout << "- " << t.getName() << " (" << t.getYear() << ")" << endl;
    }
}

bool Watchlist::saveToFile(string fileName) const {
    ofstream file(fileName, ios::app);   // ios::app = add to the end, keep old entries
    if (!file) {
        return false;
    }

    for (const Title& t : items) {
        file << t.getName() << " (" << t.getYear() << ") - " << t.getGenre() << endl;
    }

    file.close();
    return true;
}
