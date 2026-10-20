#include "Guide.h"

#include <iostream>

namespace pullweight {

Guide::Guide() : Guide("Unknown", "0000", "Unknown") {} // Constructor chaining

Guide::Guide(const std::string& name, const std::string& pin, const std::string& department)
    : Person(name, pin), department(department) {}

void Guide::display() const {
    std::cout << "[Guide] id=" << getId() << " name=" << getName()
              << " department=" << department << std::endl;
}

} // namespace pullweight
