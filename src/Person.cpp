#include "Person.h"

#include <cctype>
#include <functional>
#include <stdexcept>

namespace pullweight {

int Person::nextId = 1; // Static member must be defined once, outside the class

// NOTE: std::hash is NOT real security. It is fast, unsalted and not designed to resist attacks,
// and there are only 10,000 possible 4-digit PINs, so anyone could try them all instantly.
// A real system would use a slow, salted password-hashing algorithm (bcrypt, scrypt or Argon2).
std::size_t Person::hashPin(const std::string& pin) {
    if (pin.size() != 4) {
        throw std::invalid_argument("PIN must be exactly 4 digits");
    }
    for (char c : pin) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("PIN must contain digits only");
        }
    }
    return std::hash<std::string>{}(pin);
}

Person::Person() : Person("Unknown", "0000") {} // Constructor chaining: delegates to the parameterized one

Person::Person(const std::string& name, const std::string& pin)
    : name(name), pinHash(hashPin(pin)), id(nextId++) {} // Initializer list

bool Person::checkPin(const std::string& attempt) const {
    // A malformed attempt is simply a wrong PIN, not an error
    if (attempt.size() != 4) return false;
    return std::hash<std::string>{}(attempt) == pinHash;
}

bool Person::operator==(const Person& other) const {
    return id == other.id;
}

} // namespace pullweight
