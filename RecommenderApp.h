#ifndef RECOMMENDERAPP_H
#define RECOMMENDERAPP_H

#include "Catalogue.h"
#include <string>
using namespace std;

// Runs the program: shows the menu, reads the user's choice, prints results
class RecommenderApp {
private:
    Catalogue catalogue;

    // Keeps asking until the user types a whole number from min to max
    int readChoice(int min, int max) const;
    // Keeps asking until the user types y or n
    bool askYesNo(string question) const;

    void showMenu() const;
    string genreFromChoice(int choice) const;
    string askType() const;
    double askMinRating() const;
    int askDisplayMode() const;
    void showRecommendations(string genre, string type, double minRating,
                             bool surpriseMe) const;

public:
    // Returns 0 on success, 1 if the catalogue could not be loaded
    int run();
};

#endif
