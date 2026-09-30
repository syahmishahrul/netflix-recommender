#ifndef TITLE_H
#define TITLE_H

#include <string>
using namespace std;

// Represents one Netflix title (one line of netflix_titles.txt)
class Title {
private:
    string name;
    string genre;
    string type;        // "Movie" or "Series"
    int year;
    double rating;      // IMDb rating out of 10
    bool original;      // true = Netflix Original, false = licensed
    string description;

public:
    Title(string name, string genre, string type, int year,
          double rating, bool original, string description);

    string getName() const;
    string getGenre() const;
    string getType() const;
    int getYear() const;
    double getRating() const;
    bool isOriginal() const;
    string getDescription() const;

    // Prints this title's details to the screen
    void display() const;
};

#endif
