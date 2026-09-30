#include <iostream>
#include <string>
using namespace std;

int main() {
    int choice;

    cout << "=========================================" << endl;
    cout << "   NETFLIX MOVIE RECOMMENDATION ASSISTANT" << endl;
    cout << "=========================================" << endl;
    cout << "Choose a genre by entering a number:" << endl;
    cout << "1. Action" << endl;
    cout << "2. Comedy" << endl;
    cout << "3. Horror" << endl;
    cout << "4. Romance" << endl;
    cout << "5. Sci-Fi" << endl;
    cout << "Enter your choice (1-5): ";
    cin >> choice;

    string movie, rating, category;

    switch (choice) {
        case 1:
            movie = "Extraction 2";
            rating = "7.1/10";
            category = "Action";
            break;
        case 2:
            movie = "Murder Mystery";
            rating = "6.0/10";
            category = "Comedy";
            break;
        case 3:
            movie = "Hush";
            rating = "6.6/10";
            category = "Horror";
            break;
        case 4:
            movie = "To All the Boys I've Loved Before";
            rating = "7.0/10";
            category = "Romance";
            break;
        case 5:
            movie = "Stranger Things";
            rating = "8.7/10";
            category = "Sci-Fi";
            break;
        default:
            cout << "\nInvalid choice. Please run the program again and enter a number between 1 and 5." << endl;
            return 0;
    }

    cout << "\n-----------------------------------------" << endl;
    cout << "Recommended for you:" << endl;
    cout << "Title    : " << movie << endl;
    cout << "Category : " << category << endl;
    cout << "Rating   : " << rating << endl;
    cout << "-----------------------------------------" << endl;

    return 0;
}
