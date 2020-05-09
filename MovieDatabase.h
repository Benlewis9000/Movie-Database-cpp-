//
// Created by Ben on 06/05/2020.
//
#include <fstream>
#include <vector>
#include "Movie.h"

#ifndef PROG2CW2_MOVIEDATABASE_H
#define PROG2CW2_MOVIEDATABASE_H


class MovieDatabase {
private:
    std::set<Movie*> movies;
public:
    inline MovieDatabase();
    inline explicit MovieDatabase(const std::string& dataSourcePath);
    // Rule of three:
    MovieDatabase(const MovieDatabase& md);
    MovieDatabase& operator=(const MovieDatabase& md);
    ~MovieDatabase();

    /*
     *  todo:
     *      - test getMovie
     *      - test rule of three funcs ^ (how?)
     *      - change query methods to be more generic (use types?) - or nah? just templates for sorting
     *      - implement an ordering func that can take diff funcs for diff orders
     *      - ^ answer queries with these in main
     */
    inline const std::set<Movie*>& getMovies() const;
    inline void addMovie(Movie& m); // blocks duplicates via mem/pointer
    inline bool containsMovie(Movie& m) const; // check via pointer
    inline Movie* getMovie(int index);
    inline void removeMovie(Movie& m);
    inline void removeMovie(int index);

    static void testMovieDatabase();

};

std::ostream& operator<<(std::ostream& ostr, const MovieDatabase& md);
std::istream& operator>>(std::istream& istr, MovieDatabase& md);


/*
 * Accessor methods for MovieDatabase class.
 */
inline const std::set<Movie *>& MovieDatabase::getMovies() const {
    return this->movies;
}


inline void MovieDatabase::addMovie(Movie& m) {
    this->movies.insert(&m);
}

/**
 * Check if the Database contains a movie.
 * @param m pointer to Movie to check for.
 * @return true if the same Movie was found in the database.
 */
inline bool MovieDatabase::containsMovie(Movie& m) const {
    return (this->movies.find(&m) != movies.end());
}

Movie *MovieDatabase::getMovie(int index) {

    if (index < this->getMovies().size()) {

        // Get iterator for set, advance by index position given, and return object at that position
        return *std::next(this->getMovies().begin(), index);

    }
    else return nullptr;

}

/**
 * Remove a Movie from the database.
 * @param m the Movie to remove.
 */
inline void MovieDatabase::removeMovie(Movie& m) {
    this->movies.erase(&m);
}

/**
 * Remove a Movie from the database.
 * @param index of the Movie to remove.
 */
inline void MovieDatabase::removeMovie(int index){

    // Prevent attempt to remove an index outside of the set
    if (index < this->getMovies().size()) {

        this->removeMovie(*this->getMovie(index));

    }

}

inline MovieDatabase::MovieDatabase() {}

inline MovieDatabase::MovieDatabase(const std::string& dataSourcePath) {

    std::ifstream ifs(dataSourcePath, std::ifstream::in);

    ifs >> *this;

}

#endif //PROG2CW2_MOVIEDATABASE_H
