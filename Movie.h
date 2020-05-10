/*
 * Movie.h
 * Offline Movie Database in C++ (Programming 2 CW2)
 * Author: Ben Lewis, 100250459
 * Last edited: 06/05/2020 13:52
 *
 * Written for C++17.
 */

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include "Certificate.h"

#ifndef PROG2CW2_MOVIE_H
#define PROG2CW2_MOVIE_H

class Movie {
private:
    std::string title;
    int yearReleased;
    const Certificate* certificate;
    std::string genres;
    int duration;
    double rating;

public:
    // Constructor (with defaults)
    inline explicit Movie(std::string title = "", int yearReleased = 0, const Certificate* certificate = Certificate::UNKNOWN,
            std::string genres = "", int duration = 0, double rating = 0.0);
    // No destructor needed as member variables created only exist within scope of class (all stack, no new pointers to heap)

    // Accessors
    inline const std::string& getTitle() const;
    inline int getYearReleased() const;
    inline const Certificate* getCertificate() const;
    inline const std::string getGenres() const;
    inline int getDuration() const;
    inline double getRating() const;

    inline bool hasGenre(const std::string& genre) const;
    std::string toString() const;

    // Test harness
    static void testMovie();

};

// Operator overloads
inline bool operator==(const Movie& m1, const Movie& m2);
inline bool operator!=(const Movie& m1, const Movie& m2);
inline std::ostream& operator<<(std::ostream& ostr, const Movie& m);
std::istream& operator>>(std::istream& istr, Movie& m);


/**
 * Movie constructor.
 * @param title of movie.
 * @param yearReleased for movie ( > 0).
 * @param genres in movie.
 * @param certificate of movie.
 * @param duration of movie ( > 0).
 * @param rating scored for movie (0 to 5).
 */
inline Movie::Movie(std::string title, int yearReleased, const Certificate* certificate, std::string genres,
             int duration, double rating)
             // Set fields with initialiser (constrain values as needed)
             : title(title), yearReleased(yearReleased < 0 ? 0 : yearReleased), genres(genres), certificate(certificate),
                    duration(duration < 0 ? 0 : duration), rating(std::clamp(0.0,rating,5.0)) {}


/*
 * Accessor methods for Movie class.
 */
inline const std::string& Movie::getTitle() const {
    return this->title;
}

inline int Movie::getYearReleased() const {
    return this->yearReleased;
}

inline const Certificate* Movie::getCertificate() const {
    return this->certificate;
}

inline const std::string Movie::getGenres() const {
    return this->genres;
}

inline int Movie::getDuration() const {
    return this->duration;
}

inline double Movie::getRating() const {
    return this->rating;
}


/**
 * Check if a Movie has a certain genre.
 * @param genre to look for.
 * @return true if Movie has genre, false if not.
 */
inline bool Movie::hasGenre(const std::string &genre) const {

    // Search Movies genres string for genre substring
    // If npos returned, genre not found, thus returns false, otherwise genre found, returns true
    return (this->getGenres().find(genre) != std::string::npos);

}



/**
 * Overloaded output stream operator.
 * @param ostr stream to put data into.
 * @param m Movie to get data from.
 * @return modified ostream.
 */
inline std::ostream& operator<<(std::ostream &ostr, const Movie &m) {

    return ostr << m.toString();

}

/**
 * Overloaded equals operator.
 * @param m1 first Movie to compare.
 * @param m2 second Movie to compare.
 * @return true if values of all variables are equal.
 */
inline bool operator==(const Movie &m1, const Movie &m2) {

    return m1.getTitle().compare(m2.getTitle()) == 0
           && m1.getYearReleased() == m2.getYearReleased()
           && m1.getCertificate() == m2.getCertificate()
           && m1.getGenres().compare(m2.getGenres()) == 0
           && m1.getDuration() == m2.getDuration()
           && m1.getRating() == m2.getRating();

}

/**
 * Overloaded not equal operator.
 * @param m1 first Movie to compare.
 * @param m2 second Movie to compare.
 * @return true if any value of one Movie does not equal the corresponding value of the other Movie.
 */
inline bool operator!=(const Movie &m1, const Movie &m2){

    // Inverse of operator==
    return (!(m1==m2));

}

#endif //PROG2CW2_MOVIE_H
