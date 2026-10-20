#pragma once

#include <cstddef>
#include <string>

namespace pullweight {

// Abstract base class: has a pure virtual function, so you cannot create a Person directly
class Person {
public:
    Person();                                                  // Default constructor
    Person(const std::string& name, const std::string& pin);   // Parameterized constructor
    virtual ~Person() = default;                               // Virtual destructor: deleting via Person* destroys the full object

    virtual void display() const = 0;                          // Pure virtual: every subclass must provide its own

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    bool checkPin(const std::string& attempt) const;           // Compares hashes; the PIN itself is never stored

    bool operator==(const Person& other) const;                // Operator overloading: same id means same person

private:
    static std::size_t hashPin(const std::string& pin);        // Validates (4 digits) then hashes

    static int nextId;                                         // Static member: one counter shared by ALL persons

    // Declaration order = initialization order. pinHash comes before id so a bad PIN throws
    // BEFORE an id is used up.
    std::string name;
    std::size_t pinHash;
    int id;
};

} // namespace pullweight
