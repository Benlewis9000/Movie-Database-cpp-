/*
 * main.cpp
 * Offline Movie Database in C++ (Programming 2 CW2)
 * Author: Ben Lewis, 100250459
 * Last edited: 10/05/2020 13:39
 *
 * Written for C++17.
 */

#include <iostream>
#include "Movie.h"
#include "MovieDatabase.h"

static void runTests();

int main() {

    // New database md, reading in data from "films.txt"
    MovieDatabase md("films.txt");

    // lambda comparing movies by year released
    auto compareByYearReleased = [](auto & direction, const Movie* a, const Movie* b) { return direction(a->getYearReleased(), b->getYearReleased()); };
    // sort md via lambda
    md.sortMovies(MovieDatabase::ascending<int>, compareByYearReleased);
    std::cout << md << "\n";

    // lambda checking if a film is of genre Film-Noir
    auto isFilmNoir = [](const Movie* m) { return m->hasGenre("Film-Noir"); };
    // lambda comparing movies by duration
    auto compareByDuration = [](auto & direction, const Movie* a, const Movie* b) { return direction(a->getDuration(), b->getDuration()); };
    // New database of Film-Noirs, subset of md
    MovieDatabase filmNoirs = md.getFrom(isFilmNoir);
    // sort filmNoirs by duration, descending
    filmNoirs.sortMovies(MovieDatabase::descending<int>, compareByDuration);
    // output 3rd Movie in filmNoirs
    std::cout << *filmNoirs.getMovies()[2] << "\n\n";

    // lambda checking if a film has certificate UNRATED
    auto isUnrated = [](const Movie* m) { return m->getCertificate() == Certificate::UNRATED; };
    // New database of UNRATED movies, subset of md
    MovieDatabase unratedFilms = md.getFrom(isUnrated);
    // sort unratedFilms by year released, descending
    unratedFilms.sortMovies(MovieDatabase::descending<int>, compareByYearReleased);
    // output 8th Movie in unratedFilms
    std::cout << *unratedFilms.getMovies()[7] << "\n\n";

    // lambda comparing movies by title length
    auto compareByTitleLength = [](auto & direction, const Movie* a, const Movie* b) { return direction(a->getTitle().length(), b->getTitle().length()); };
    // sort md by title length, descending
    md.sortMovies(MovieDatabase::descending<int>, compareByTitleLength);
    // output 1st movie in md
    std::cout << *md.getMovies()[0] << "\n\n";

}

/**
 * Run test harnesses for each object.
 */
static void runTests(){

    Movie::testMovie();

    MovieDatabase::testMovieDatabase();

}