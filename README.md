# Netflix Movie Recommendation Assistant

LDCW6123 Fundamentals of Digital Competence for Programmer, Group Project Part 2

An interactive C++ console program that recommends Netflix movies and series
from a small catalogue, based on the user's preferences.

## Link to Part 1 (Christensen's disruptive innovation model)

Our poster traces how Netflix disrupted the video rental market (e.g. Blockbuster).
The program reflects two parts of that story:

- **Personalised recommendations.** Netflix competed by helping users find
  something to watch without visiting a store. Our program filters a catalogue by
  the user's preferences and ranks results by rating.
- **Netflix Originals vs licensed content.** Netflix moved from licensing other
  studios' content to producing its own. Each result shows its source, and the
  program reports how many matches are Netflix Originals.

## Features

- Loads 29 titles from `netflix_titles.txt` (the file can be extended without recompiling)
- Filters by genre, movie/series, and minimum IMDb rating
- Shows all matches (highest rated first) or a random "Surprise me" pick
- Validates input: letters or out-of-range numbers are rejected and re-asked
- Repeats until the user chooses to exit
- Skips badly formatted catalogue lines with a warning instead of crashing

## Inputs and outputs

| Input | Options |
|---|---|
| Genre | Action, Comedy, Horror, Romance, Sci-Fi |
| Type | Movie, Series, Either |
| Minimum rating | Any, 6.0+, 7.0+, 8.0+ |
| Display mode | Show all, Surprise me |
| Another round? | y / n |

**Output:** title, year, type, rating, source (Netflix Original or licensed) and a short description.

## Program structure

| File | Class | Responsibility |
|---|---|---|
| `Title.h/.cpp` | `Title` | One movie or series; private data with getters and `display()` |
| `Catalogue.h/.cpp` | `Catalogue` | Loads the catalogue file and searches it with `findMatches()` |
| `RecommenderApp.h/.cpp` | `RecommenderApp` | Menus, input validation, program loop, printing results |
| `main.cpp` | none | Creates the app and calls `run()` |
| `netflix_titles.txt` | none | The catalogue data |

## How to compile and run

Requires a C++11 compiler (e.g. g++ from MinGW-w64).

```
g++ main.cpp Title.cpp Catalogue.cpp RecommenderApp.cpp -o recommender.exe
.\recommender.exe
```

Run it from the folder that contains `netflix_titles.txt`.

## Catalogue file format

One title per line, fields separated by `|`. The first line is a header.

```
title|genre|type|year|rating|original|description
Hush|Horror|Movie|2016|6.6|Y|A deaf writer living alone in the woods is stalked by a masked killer.
```

`original` is `Y` for a Netflix Original and `N` for licensed content.

## Data source

Ratings are IMDb user ratings, rounded to one decimal place, checked on DD MMM 2026.
Ratings change over time. Availability of licensed titles varies by country.

## Team

| Name | Student ID | Contribution |
|---|---|---|
| | | |
