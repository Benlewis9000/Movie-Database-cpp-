/*
 * Movie.cpp
 * Offline Movie Database in C++ (Programming 2 CW2)
 * Author: Ben Lewis, 100250459
 * Last edited: 06/05/2020 13:52
 *
 * Written for C++17.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "Movie.h"


/**
 * Convert the Movie to a formatted string.
 * @return the Movie as a string.
 */
std::string Movie::toString() const {

    // Add elements to string (using append over operator+ for efficiency)
    std::string movie;
    movie.append("\"").append(this->getTitle()).append("\",")
            .append(std::to_string(this->getYearReleased()).append(","))
            .append("\"").append(this->getCertificate()->getName()).append("\",")
            .append("\"").append(this->getGenres()).append("\",");

    // Restrict rating to 1dp
    std::stringstream rating;
    rating << std::fixed << std::setprecision(1) << this->getRating();

    // Finish adding elements
    movie.append(std::to_string(this->getDuration())).append(",")
            .append(rating.str());

    return movie;

}

/**
 * Overloaded input stream operator.
 * @param istr stream to receive data from.
 * @param m movie to populate with data.
 * @return the stream being read from.
 */
std::istream& operator>>(std::istream& istr, Movie& m){

    std::vector<std::string> words;
    std::string word;
    bool inQuotes = false;

    // Read stream in char by char until EOF reached (thus end of stream)
    for (char c = istr.get(); c != EOF; c = istr.get()){

        switch (c){

            case '"':   // Invert inQuotes flag
                inQuotes = !inQuotes;
                break;
            case ',':   // If not in quotes, add current word to words and clear string
                if (!inQuotes) {
                    words.push_back(word);
                    word.clear();
                }
                else {  // Else, append the char
                    word.push_back(c);
                }
                break;
            default:    // Add the char to word
                word.push_back(c);
                break;

        }

    }
    // Add final remaining word
    words.push_back(word);

    // Construct movie
    Movie movie(words[0], stoi(words[1]), Certificate::deserialize(words[2]), words[3], stoi(words[4]), stod(words[5]));

    // Copy new movie values into given movie reference
    m = movie;

    return istr;

}

/**
 * Test Movie functionality.
 */
void Movie::testMovie(){

    Movie m("Lock, Stock and Two Smoking Barrels",1998,Certificate::R,"Comedy/Crime",107,2.5);

    // Print out data put in
    std::cout << "Title:" << m.getTitle() << "\n"
              << "Released:" <<  m.getYearReleased() << "\n"
              << "Certificate:" << m.getCertificate() << "\n"
              << "Genres: " << m.getGenres() << "\n"
              << "Duration:" << m.getDuration() << "\n"
              << "Rating:" << m.getRating() << "\n";

    // Test toString()
    std::cout << m.toString() << "\n";

    // Test operator<<
    std::cout << m << "\n";

    // Test operator>>
    std::cout << "Please input data for a movie: ";
    Movie mIn;
    std::cin >> mIn;
    std::cout << mIn << "\n";

    // Test hasGenre
    std::cout << "Please enter a genre to check for: ";
    std::string genre;
    std::cin >> genre;
    std::string hasGenre = mIn.hasGenre(genre) ? "DOES" : "does NOT";
    std::cout << mIn.getTitle() << " " << hasGenre << " contain " << genre << "\n";

    // Test operator==
    Movie mInCopy = mIn;
    std::string equals = mInCopy == mIn ? "True" : "False";
    std::cout << mIn << " == " << mInCopy << ": " << equals << "\n";
    mInCopy.title = "Some Title";
    equals = mInCopy == mIn ? "True" : "False";
    std::cout << mIn << " == " << mInCopy << ": " << equals << "\n";

}