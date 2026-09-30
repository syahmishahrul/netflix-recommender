// tests.cpp - automated tests for the Netflix Movie Recommendation Assistant
//
// Build and run (from the project folder):
//   g++ tests.cpp Title.cpp Catalogue.cpp RecommenderApp.cpp -o tests.exe
//   .\tests.exe
//
// Two kinds of tests:
//   1. Unit tests    - call Catalogue directly and check what it returns.
//   2. Program tests - "type" inputs into RecommenderApp by swapping cin/cout
//                      for text streams, then check the printed output.
#include "Catalogue.h"
#include "RecommenderApp.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <cstdio>
using namespace std;

int passed = 0;
int failed = 0;

// Prints PASS or FAIL for one test and keeps count
void check(string testName, bool condition, string detail = "") {
    if (condition) {
        cout << "PASS  " << testName << endl;
        passed++;
    } else {
        cout << "FAIL  " << testName;
        if (detail != "") {
            cout << "  (" << detail << ")";
        }
        cout << endl;
        failed++;
    }
}

// Runs the whole program with the given inputs (one per line) and returns
// everything it printed. cin and cout are swapped for string streams, then restored.
// Inputs must end with "n" (exit), otherwise the program reaches the end of
// input and stops the whole test program.
string runApp(string inputs) {
    istringstream fakeInput(inputs);
    ostringstream fakeOutput;

    streambuf* realIn = cin.rdbuf(fakeInput.rdbuf());
    streambuf* realOut = cout.rdbuf(fakeOutput.rdbuf());

    RecommenderApp app;
    app.run();

    cin.rdbuf(realIn);
    cout.rdbuf(realOut);
    cin.clear();

    return fakeOutput.str();
}

// True if `text` appears somewhere in `output`
bool contains(string output, string text) {
    return output.find(text) != string::npos;
}

int main() {
    cout << "===== Unit tests: Catalogue =====" << endl;

    Catalogue catalogue;
    bool loaded = catalogue.loadFromFile("netflix_titles.txt");
    check("Catalogue file loads", loaded);
    check("29 titles loaded", catalogue.size() == 29,
          "got " + to_string(catalogue.size()));

    // Test 1: Horror, Series, 8.0+
    vector<Title> r1 = catalogue.findMatches("Horror", "Series", 8.0);
    check("T1  Horror/Series/8.0+ gives 2 titles, highest first",
          r1.size() == 2 && r1[0].getName() == "The Haunting of Hill House"
                         && r1[1].getName() == "Kingdom");

    // Test 2: Romance, Series, any rating - sorted and Originals counted
    vector<Title> r2 = catalogue.findMatches("Romance", "Series", 0.0);
    int originals = 0;
    for (const Title& t : r2) {
        if (t.isOriginal()) {
            originals++;
        }
    }
    check("T2  Romance/Series gives 3 titles, Crash Landing on You first",
          r2.size() == 3 && r2[0].getName() == "Crash Landing on You");
    check("T2  2 of the 3 are Netflix Originals", originals == 2,
          "got " + to_string(originals));

    // Test 3: Sci-Fi, Movie, 8.0+
    vector<Title> r3 = catalogue.findMatches("Sci-Fi", "Movie", 8.0);
    check("T3  Sci-Fi/Movie/8.0+ gives only Interstellar",
          r3.size() == 1 && r3[0].getName() == "Interstellar");

    // Test 4: Action, Movie, 7.0+
    vector<Title> r4 = catalogue.findMatches("Action", "Movie", 7.0);
    check("T4  Action/Movie/7.0+ gives only Extraction 2",
          r4.size() == 1 && r4[0].getName() == "Extraction 2");

    // Test 6: no matches
    vector<Title> r6 = catalogue.findMatches("Horror", "Movie", 8.0);
    check("T6  Horror/Movie/8.0+ gives no titles", r6.empty());

    // Test 11: missing file
    Catalogue missing;
    check("T11 Missing file returns false",
          !missing.loadFromFile("this_file_does_not_exist.txt"));

    // Test 12: a badly formatted line is skipped, not a crash.
    // Makes a temporary copy of the catalogue with one broken line added.
    {
        ifstream original("netflix_titles.txt");
        ofstream copy("test_bad_catalogue.txt");
        copy << original.rdbuf() << "Broken|Action|Movie|abc|7.0|Y|test\n";
    }
    Catalogue badData;
    ostringstream warnings;
    streambuf* realOut = cout.rdbuf(warnings.rdbuf());   // capture the warning
    badData.loadFromFile("test_bad_catalogue.txt");
    cout.rdbuf(realOut);
    remove("test_bad_catalogue.txt");
    check("T12 Broken line skipped, other 29 titles still load",
          badData.size() == 29 && contains(warnings.str(), "Warning: skipped badly formatted line 31"),
          "loaded " + to_string(badData.size()));

    cout << "\n===== Program tests: RecommenderApp =====" << endl;

    // Test 7: letters at the genre menu, then a valid choice
    string out7 = runApp("abc\n3\n3\n1\n1\nn\n");
    check("T7  Letters rejected and re-asked",
          contains(out7, "Invalid input. Please enter a number between 1 and 5:")
          && contains(out7, "Netflix Horror title(s)"));

    // Test 8: out-of-range number, then a valid choice
    string out8 = runApp("9\n3\n3\n1\n1\nn\n");
    check("T8  Out-of-range number rejected and re-asked",
          contains(out8, "Invalid choice. Please enter a number between 1 and 5:")
          && contains(out8, "Netflix Horror title(s)"));

    // Test 9: invalid answer to the y/n question
    string out9 = runApp("3\n3\n1\n1\nmaybe\nn\n");
    check("T9  'maybe' at y/n is rejected",
          contains(out9, "Please type y or n.") && contains(out9, "Thanks for using"));

    // Test 10: two rounds using 'y', then exit with 'n'
    string out10 = runApp("3\n3\n1\n1\ny\n5\n1\n4\n1\nn\n");
    check("T10 'y' starts a second round, 'n' exits",
          contains(out10, "Netflix Horror title(s)") && contains(out10, "Interstellar (2014)")
          && contains(out10, "Thanks for using"));

    // Test 5: Surprise me - 10 rounds in one run should not all pick the same title
    string rounds = "";
    for (int i = 0; i < 10; i++) {
        rounds += "1\n3\n1\n2\n";                  // Action, Either, Any, Surprise me
        rounds += (i < 9) ? "y\n" : "n\n";
    }
    string out5 = runApp(rounds);
    set<string> picks;
    istringstream lines(out5);
    string line;
    while (getline(lines, line)) {
        if (line.rfind("Title       :", 0) == 0) {
            picks.insert(line);
        }
    }
    check("T5  Surprise me picks different titles across 10 rounds",
          contains(out5, "Your surprise Action pick") && picks.size() > 1,
          to_string(picks.size()) + " different titles");

    cout << "\n" << passed << " passed, " << failed << " failed" << endl;
    return failed == 0 ? 0 : 1;
}
