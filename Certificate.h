/*
 * Certificate.h
 * Offline Movie Database in C++ (Programming 2 CW2)
 * Author: Ben Lewis, 100250459
 * Last edited: 06/05/2020 13:52
 *
 * Written for C++17.
 */

#include <string>
#include <ostream>
#include <vector>

#ifndef PROG2CW2_CERTIFICATION_H
#define PROG2CW2_CERTIFICATION_H


/**
 * Enum representation of a Movies viewer certificate.
 * NOTE: Application is constrained to predefined types, defaulting to UNKNOWN if a valid type could not be found.
 */
class Certificate {
private:
    std::string name;

    inline Certificate(std::string n) : name(n){}

public:
    static const Certificate* NA;
    static const Certificate* UNRATED;
    static const Certificate* NOT_RATED;
    static const Certificate* G;
    static const Certificate* PG;
    static const Certificate* PG_13;
    static const Certificate* TV_14;
    static const Certificate* M;
    static const Certificate* R;
    static const Certificate* X;
    static const Certificate* APPROVED;
    static const Certificate* PASSED;
    static const Certificate* UNKNOWN;

    inline std::string getName() const;

    inline static const Certificate* deserialize(const std::string &str);

};

// Pointers to Certificate constants
inline const Certificate* Certificate::NA = new Certificate("N/A");
inline const Certificate* Certificate::UNRATED = new Certificate("UNRATED");
inline const Certificate* Certificate::NOT_RATED = new Certificate("NOT RATED");
inline const Certificate* Certificate::G = new Certificate("G");
inline const Certificate* Certificate::PG = new Certificate("PG");
inline const Certificate* Certificate::PG_13 = new Certificate("PG-13");
inline const Certificate* Certificate::TV_14 = new Certificate("TV-14");
inline const Certificate* Certificate::M = new Certificate("M");
inline const Certificate* Certificate::R = new Certificate("R");
inline const Certificate* Certificate::X = new Certificate("X");
inline const Certificate* Certificate::APPROVED = new Certificate("APPROVED");
inline const Certificate* Certificate::PASSED = new Certificate("PASSED");
inline const Certificate* Certificate::UNKNOWN = new Certificate("UNKNOWN");

/**
 * Get the name of a Certificate.
 * @return a copy of the name as string.
 */
inline std::string Certificate::getName() const {

    return this->name;

}

/**
 * Overloaded output stream, stream out Certificate as it's name.
 * @param str output stream.
 * @param c Certificate to act on.
 * @return output stream passed with Certificate name injected.
 */
inline std::ostream& operator<<(std::ostream& str, const Certificate& c){

    return str << c.getName();

}

/**
 * Get the Certificate type from a string representation.
 * @param str representing type.
 * @return corresponding Certificate or Certificate::UNKNOWN if not found.
 */
inline const Certificate* Certificate::deserialize(const std::string &str) {

    // (switch statement unavailable for string types)
    // Check each string,
    if (str == "N/A") return Certificate::NA;
    if (str == "UNRATED") return Certificate::UNRATED;
    if (str == "NOT RATED") return Certificate::NOT_RATED;
    if (str == "G") return Certificate::G;
    if (str == "PG") return Certificate::PG;
    if (str == "PG-13") return Certificate::PG_13;
    if (str == "TV-14") return Certificate::TV_14;
    if (str == "M") return Certificate::M;
    if (str == "R") return Certificate::R;
    if (str == "X") return Certificate::X;
    if (str == "APPROVED") return Certificate::APPROVED;
    if (str == "PASSED") return Certificate::PASSED;
    // Default (unknown string input)
    return Certificate::UNKNOWN;

}

#endif //PROG2CW2_CERTIFICATION_H
