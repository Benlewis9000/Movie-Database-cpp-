//
// Created by Ben on 06/05/2020.
//

#include <sstream>
#include <fstream>
#include "MovieDatabase.h"


/**
 * Destructor for MovieDatabase class.
 */
MovieDatabase::~MovieDatabase(){

    // Free memory for each Movie pointer
    for (Movie* movie : this->getMovies()) free(movie);
    // std::set will automatically run it's destructor

}

/**
 * Overloaded output stream operator.
 * @param ostr stream to output to.
 * @param md database of movies to output.
 * @return output stream used.
 */
std::ostream &operator<<(std::ostream &ostr, const MovieDatabase &md) {

    for (Movie* m : md.getMovies()) std::cout << *m << "\n";

    return ostr;

}

/**
 * Overloaded input stream operator.
 * @param istr to get data from.
 * @param md to insert data into.
 * @return the istream used.
 */
std::istream &operator>>(std::istream &istr, MovieDatabase &md) {

    // string to temp store each line in
    std::string line;

    while(std::getline(istr, line)){

        Movie* m = new Movie();
        std::stringstream s;
        s << line;
        s >> *m;

        md.addMovie(*m);

    }

    return istr;

}


/**
 * Copy constructor for MovieDatabase (deep copy).
 * @param md the database to copy.
 */
MovieDatabase::MovieDatabase(const MovieDatabase &md) {

    // For each movie in database passed, copy and add to this database
    for (Movie* m : md.getMovies()){

        Movie* copy = new Movie(*m);
        this->addMovie(*copy);

    }

}

/**
 * Overloaded copy assignment operator for MovieDatabase (deep copy).
 * @param md the database to copy.
 * @return reference to copy.
 */
MovieDatabase &MovieDatabase::operator=(const MovieDatabase &md) {

    // Prevent self assignment
    if (this != &md) {

        // For each movie in database passed, copy and add to this database
        for (Movie *m : md.getMovies()) {

            Movie *copy = new Movie(*m);
            this->addMovie(*copy);

        }

    }

    return *this;

}

/**
 * Test harness for MovieDatabase class.
 */
void MovieDatabase::testMovieDatabase() {

    MovieDatabase md;

    // Input file stream from "films.txt"
    std::ifstream ifs("films.txt", std::ifstream::in);
    // Test operator>>
    ifs >> md;
    // Test operator<<
    std::cout << md << "\n";

    // Test database modifiers (add, remove)
    std::set<Movie*>::iterator it = md.getMovies().begin();
    std::advance(it, 0);
    Movie* m = *it;
    md.removeMovie(*m);
    std::cout << md << "\n";
    md.removeMovie(0);
    std::cout << md << "\n";
    m = new Movie("Some Title", 2020, Certificate::UNKNOWN, "Horror/Comedy", 125, 0.1);
    md.addMovie(*m);
    std::cout << md << "\n";


}
