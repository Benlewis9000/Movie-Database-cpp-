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

    // todo: can define lambdas like this, or whack them straight into args (probs more readable like this coz can label and RE-USE)
    //auto compareByRelease = [] (auto & direction, const Movie* a, const Movie* b) { return direction (a->getYearReleased(), b->getYearReleased() ); };

    /*
     * todo:
     *      - Finish main by answer queries using..
     *          - comparison lambdas and directions in .sortMovies
     *          - get sets of movies (sub databases) using lambdas and .getFrom
     */

    md.sortMovies(MovieDatabase::ascending<int>, [] (auto & direction, const Movie* a, const Movie* b) { return direction (a->getYearReleased(), b->getYearReleased() ); } );
    std::cout << md << "\n";
    //md.sortMovies(MovieDatabase::descending<int>, compareByRelease);
    std::cout << md << "\n";

    MovieDatabase comedies = md.getFromGenre("Comedy");
    std::cout << "comedies:\n" << comedies << "\n";

    MovieDatabase PGs = md.getFromCertificate(*Certificate::PG);
    std::cout << "PGs:\n" << PGs << "\n";

    auto isFilmNoir = [] (Movie* m) { return m->hasGenre("Film-Noir"); } ;
    MovieDatabase l = md.getFrom(isFilmNoir);
    std::cout << "Film-Noir:\n" << l << "\n";

    std::cout << "end\n";

}

static void runTests(){

    //Movie::testMovie();

    MovieDatabase::testMovieDatabase();

}