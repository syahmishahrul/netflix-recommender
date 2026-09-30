# Test Cases

## Automated run

`tests.cpp` checks all 12 cases automatically. Build and run it from the project folder
(it replaces `main.cpp` in the build, since it has its own `main`):

```
g++ tests.cpp Title.cpp Catalogue.cpp RecommenderApp.cpp -o tests.exe
.\tests.exe
```

It prints PASS/FAIL for each check and a total at the end.

- **Unit tests** (1-4, 6, 11, 12) call `Catalogue` directly and check the titles it returns.
- **Program tests** (5, 7-10) run the whole `RecommenderApp`, feeding it inputs by
  swapping `cin`/`cout` for string streams, then check what it printed.
- Test 12 writes a temporary broken copy of the catalogue and deletes it afterwards,
  so the real `netflix_titles.txt` is never changed.

## Manual run

Compile, run `.\recommender.exe`, type the inputs shown, and compare with the expected result.

## Normal use

| # | Inputs (genre, type, rating, mode) | Expected result | Pass? |
|---|---|---|---|
| 1 | Horror, Series, 8.0+, Show all | 2 titles: The Haunting of Hill House (8.6), Kingdom (8.3); "2 of 2 are Netflix Originals." | |
| 2 | Romance, Series, Any, Show all | 3 titles, highest first: Crash Landing on You (8.7, licensed), Bridgerton (7.3), Emily in Paris (6.9); "2 of 3 are Netflix Originals." | |
| 3 | Sci-Fi, Movie, 8.0+, Show all | 1 title: Interstellar (8.7, licensed) | |
| 4 | Action, Movie, 7.0+, Show all | 1 title: Extraction 2 (7.0) | |
| 5 | Action, Either, Any, Surprise me, then `y` and repeat several rounds | One random Action title each round; the pick changes between rounds | |

## Edge cases and invalid input

| # | What to do | Expected result | Pass? |
|---|---|---|---|
| 6 | Horror, Movie, 8.0+, Show all | "Sorry, no Horror titles match your filters." plus a suggestion | |
| 7 | Type `abc` at the genre menu | "Invalid input. Please enter a number between 1 and 5:" and asks again | |
| 8 | Type `9` at the genre menu | "Invalid choice. Please enter a number between 1 and 5:" and asks again | |
| 9 | Type `maybe` at "another recommendation?" | "Please type y or n." and asks again | |
| 10 | Answer `y`, then complete a second round, then `n` | Menu restarts; after `n` shows "Thanks for using..." and exits | |
| 11 | Rename `netflix_titles.txt` and run | "Error: netflix_titles.txt not found." and exits | |
| 12 | Add the line `Broken|Action|Movie|abc|7.0|Y|test` to the catalogue | "Warning: skipped badly formatted line 31..." and the program still runs with 29 titles | |
