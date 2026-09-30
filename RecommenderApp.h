#ifndef RECOMMENDERAPP_H
#define RECOMMENDERAPP_H

#include "Catalogue.h"
#include <string>
using namespace std;

// Runs the program: shows the menu, reads the user's choice, prints results
class RecommenderApp {
private:
    Catalogue catalogue;

    void showMenu() const;
    string genreFromChoice(int choice) const;
    void showRecommendations(string genre) const;

public:
    // Returns 0 on success, 1 if the catalogue could not be loaded
    int run();
};

#endif
