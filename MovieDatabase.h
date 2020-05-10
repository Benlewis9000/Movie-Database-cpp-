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
    std::vector<Movie*> movies;
public:
    // Constructors
    inline MovieDatabase();
    inline explicit MovieDatabase(const std::string& dataSourcePath);

    // Rule of three
    MovieDatabase(const MovieDatabase& md);
    MovieDatabase& operator=(const MovieDatabase& md);
    ~MovieDatabase();

    // Accessors
    inline const std::vector<Movie*>& getMovies() const;
    inline void addMovie(Movie& m); // blocks duplicates via mem/pointer
    inline bool containsMovie(Movie& m) const; // check via pointer
    inline void removeMovie(Movie& m);
    inline void removeMovie(int index);

    MovieDatabase getFromGenre(const std::string& g) const;
    MovieDatabase getFromCertificate(const Certificate& c) const;

    template <typename L>
    MovieDatabase getFrom(L qualifier);

    // Template funcs
    template <typename T>
    inline static bool ascending(const T& x, const T& y);
    template <typename T>
    inline static bool descending(const T& x, const T& y);
    template <typename T, typename L>
    inline void sortMovies(T direction, L comparison);

    // Test harness
    static void testMovieDatabase();

};

std::ostream& operator<<(std::ostream& ostr, const MovieDatabase& md);
std::istream& operator>>(std::istream& istr, MovieDatabase& md);


/*
 * Accessor methods for MovieDatabase class.
 */
inline const std::vector<Movie *>& MovieDatabase::getMovies() const{
    return this->movies;
}

/**
 * Add a Movie to the database.
 * @param m Movie to add.
 */
inline void MovieDatabase::addMovie(Movie& m) {
    // If database does not contain movie, add it
    if (!this->containsMovie(m)) {
        this->movies.push_back(&m);
    }
}

/** todo: is this chekcing via pointer or operator==? TEST TEST TEST!
 * Check if the Database contains a movie.
 * @param m pointer to Movie to check for.
 * @return true if the same Movie was found in the database.
 */
inline bool MovieDatabase::containsMovie(Movie& m) const {
    return (std::find(movies.begin(), movies.end(), &m) != movies.end());
}

/**
 * Remove a Movie from the database.
 * @param m the Movie to remove.
 */
inline void MovieDatabase::removeMovie(Movie& m) {
    this->movies.erase(std::remove(movies.end(), movies.begin(), &m));
}

/**
 * Remove a Movie from the database.
 * @param index of the Movie to remove.
 */
inline void MovieDatabase::removeMovie(int index){

    // Prevent attempt to remove an index outside of the vector
    if (index < this->getMovies().size()) this->removeMovie(*this->getMovies()[index]);
    else std::cout << "Error: could not remove movie at index " << index << " (out of bounds).\n";

}

inline MovieDatabase::MovieDatabase() {}

inline MovieDatabase::MovieDatabase(const std::string& dataSourcePath) {

    std::ifstream ifs(dataSourcePath, std::ifstream::in);

    ifs >> *this;

}

/*
 * Templates to be used in sorting to determine direction (ascending or descending).
 */
template <typename T>
inline bool MovieDatabase::ascending(const T& x, const T& y) {
    return x < y;
}
template <typename T>
inline bool MovieDatabase::descending(const T& x, const T& y) {
    return x > y;
}

/**
 * Sort the list of Movies in the MovieDatabase.
 * @tparam T direction (ascending or descending).
 * @param direction to sort in.
 */
template<typename T, typename L>
void MovieDatabase::sortMovies(T direction, L comparison) {

    // Sort movies vector via lambda function
    std::sort(std::begin(this->movies), std::end(this->movies),
              [direction, &comparison](const Movie* a, const Movie* b) -> bool {

                  // Direction dictates ascending or descending
                  return comparison(direction, a, b);
                  // return direction(a->getYearReleased(), b->getYearReleased()); // todo .yearReleased as placeholder

              } );       // todo Functor for what bit to sort eg Certificate sort?

}

template <typename L>
MovieDatabase MovieDatabase::getFrom(L qualifier){

    MovieDatabase md;

    for (Movie* m : this->getMovies()){

        if (qualifier(m)) md.addMovie(*m);

    }

    return md;
}

#endif //PROG2CW2_MOVIEDATABASE_H
