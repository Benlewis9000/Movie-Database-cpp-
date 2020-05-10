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
    // std::vector will automatically run it's destructor

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
 * Get a database of all movies of a certain genre from the current database.
 * @param g genre required as a string.
 * @return MovieDatabase where each Movie contains genre passed.
 */
MovieDatabase MovieDatabase::getFromGenre(const std::string &g) const {

    MovieDatabase md;

    // Iterate through movies, if it has specified genres, add to new database
    for (Movie* m : this->getMovies()){

        if (m->hasGenre(g)) md.addMovie(*m);

    }

    //return new database
    return md;
}

/**
 * Get a database of all movies of a certain Certificate from the current database.
 * @param c Certificate required.
 * @return MovieDatabase where each Movie has the Certificate passed.
 */
MovieDatabase MovieDatabase::getFromCertificate(const Certificate &c) const {

    MovieDatabase md;

    // Iterate through movies, if it has specified Certificate, add to new database
    for (Movie* m : this->getMovies()){

        if (m->getCertificate() == &c) md.addMovie(*m);

    }

    // return new database
    return md;
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

    /* Todo: remove - no longer need iterator, vector sys porovides random access []
     * std::vector<Movie*>::const_iterator it = md.getMovies().cbegin();
     * auto it = md.getMovies().begin();
     * std::advance(it, 0);
    */
    Movie* m = md.getMovies()[0];
    std::cout << "Removing movie (by pointer): " << *m << "\n";
    md.removeMovie(*m);
    //std::cout << md << "\n";
    std::cout << "Removing movie (by index) at [0]: " << *md.getMovies()[0] << "\n";
    md.removeMovie(0);
    std::cout << "Attempt to remove movie at [999999]:\n";
    md.removeMovie(999999);
    //std::cout << md << "\n";
    m = new Movie("Some Title", 2020, Certificate::UNKNOWN, "Horror/Comedy", 125, 0.1);
    std::cout << "Adding movie: " << *m << "\n\n";
    md.addMovie(*m);
    std::cout << md << "\n";

    // Test copy assignment operator
    MovieDatabase mdCopy1 = md;
    std::cout << "Copying database using copy assignment operator= :\n";
    std::cout << "Pointer " << md.getMovies()[0] << " in original database points to Movie " << *md.getMovies()[0] << "\n";
    std::cout << "Pointer " << mdCopy1.getMovies()[0] << " in copy database points to Movie " << *mdCopy1.getMovies()[0] << "\n\n";
    MovieDatabase mdCopy2(md);
    std::cout << "Copying database using copy constructor:\n";
    std::cout << "Pointer " << md.getMovies()[0] << " in original database points to Movie " << *md.getMovies()[0] << "\n";
    std::cout << "Pointer " << mdCopy2.getMovies()[0] << " in copy database points to Movie " << *mdCopy2.getMovies()[0] << "\n\n";
    std::cout << "(observe \"same\" movie, different memory address, hence deep copy)" << "\n\n";

    std::cout << "End of MovieDatabase tests.\n";

}




