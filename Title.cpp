#include "Title.h"
#include <iostream>
#include <iomanip>

Title::Title(string name, string genre, string type, int year,
             double rating, bool original, string description) {
    this->name = name;
    this->genre = genre;
    this->type = type;
    this->year = year;
    this->rating = rating;
    this->original = original;
    this->description = description;
}

string Title::getName() const { return name; }
string Title::getGenre() const { return genre; }
string Title::getType() const { return type; }
int Title::getYear() const { return year; }
double Title::getRating() const { return rating; }
bool Title::isOriginal() const { return original; }
string Title::getDescription() const { return description; }

void Title::display() const {
    cout << fixed << setprecision(1);   // always show ratings like 7.0, not 7
    cout << "Title       : " << name << " (" << year << ")" << endl;
    cout << "Type        : " << type << endl;
    cout << "Rating      : " << rating << "/10" << endl;
    if (original) {
        cout << "Source      : Netflix Original" << endl;
    } else {
        cout << "Source      : Licensed from another studio" << endl;
    }
    cout << "Description : " << description << endl;
}
