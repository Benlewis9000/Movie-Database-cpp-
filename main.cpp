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
#include "Movie.h"
#include "MovieDatabase.h"

static void runTests();

int main() {

    MovieDatabase md("films.txt");
    MovieDatabase mdCopy = md;
    std::cout << "Pointer " << md.getMovie(0) << " in original database points to Movie " << *md.getMovie(0) << "\n";
    std::cout << "Pointer " << mdCopy.getMovie(0) << " in copy database points to Movie " << *mdCopy.getMovie(0) << "\n";
    std::cout << "(observe \"same\" movie, different memory address, hence deep copy)" << "\n";

    std::cout << md << "\n";
    std::cout << mdCopy << "\n";


    //runTests();

}

static void runTests(){

    //Movie::testMovie();

    MovieDatabase::testMovieDatabase();

}