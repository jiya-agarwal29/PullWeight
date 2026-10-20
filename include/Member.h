#pragma once

#include <iosfwd>
#include <string>

#include "Person.h"

namespace pullweight {

// "virtual public": all classes that inherit Member AND Guide will share ONE Person (solves the diamond)
class Member : virtual public Person {
public:
    Member();                                                  // Default constructor
    Member(const std::string& name, const std::string& pin);   // Parameterized constructor

    void display() const override;                             // Runtime polymorphism

    void addPoints(double points);
    double getScore() const { return score; }
    double getCredibility() const { return credibility; }
    void adjustCredibility(double delta);                      // Keeps credibility between 0.0 and 1.0

    bool operator<(const Member& other) const;                 // Compares by score (used for sorting)

    friend std::ostream& operator<<(std::ostream& os, const Member& member); // Friend: not a member, but may see private data

private:
    double score;
    double credibility;
};

} // namespace pullweight
