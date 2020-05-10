/*
 * main.cpp
 * Offline Movie Database in C++ (Programming 2 CW2)
 * Author: Ben Lewis, 100250459
 * Last edited: 06/05/2020 13:52
 *
 * Written for C++17.
 */

#include <iostream>
#include <vector>
#include <functional>
#include "Movie.h"
#include "MovieDatabase.h"

static void runTests();

int main() {

    MovieDatabase md("films.txt");

    auto compareByYearReleased = [](auto & direction, const Movie* a, const Movie* b) { return direction(a->getYearReleased(), b->getYearReleased()); };
    md.sortMovies(MovieDatabase::ascending<int>, compareByYearReleased);
    std::cout << md << "\n";

    auto isFilmNoir = [](const Movie* m) { return m->hasGenre("Film-Noir"); };
    auto compareByDuration = [](auto & direction, const Movie* a, const Movie* b) { return direction(a->getDuration(), b->getDuration()); };
    MovieDatabase filmNoirs = md.getFrom(isFilmNoir);
    filmNoirs.sortMovies(MovieDatabase::descending<int>, compareByDuration);
    std::cout << *filmNoirs.getMovies()[2] << "\n\n";

    auto isUnrated = [](const Movie* m) { return m->getCertificate() == Certificate::UNRATED; };
    MovieDatabase unratedFilms = md.getFrom(isUnrated);
    unratedFilms.sortMovies(MovieDatabase::descending<int>, compareByYearReleased);
    std::cout << *unratedFilms.getMovies()[7] << "\n\n";

    auto compareByTitleLength = [](auto & direction, const Movie* a, const Movie* b) { return direction(a->getTitle().length(), b->getTitle().length()); };
    md.sortMovies(MovieDatabase::descending<int>, compareByTitleLength);
    std::cout << *md.getMovies()[0] << "\n\n";

}

static void runTests(){

    //Movie::testMovie();

    MovieDatabase::testMovieDatabase();

}