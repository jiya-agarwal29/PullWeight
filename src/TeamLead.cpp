#include "TeamLead.h"

#include <iostream>

namespace pullweight {

TeamLead::TeamLead() : TeamLead("Unknown", "0000", "Unknown") {} // Constructor chaining

// The most-derived class builds the virtual base itself, so Person(...) is called HERE, directly.
// The Person(...) calls inside Member's and Guide's constructors are skipped.
TeamLead::TeamLead(const std::string& name, const std::string& pin, const std::string& department)
    : Person(name, pin), Member(name, pin), Guide(name, pin, department) {}

void TeamLead::display() const {
    std::cout << "[TeamLead] id=" << getId() << " name=" << getName()
              << " department=" << getDepartment()
              << " score=" << getScore() << " credibility=" << getCredibility() << std::endl;
}

} // namespace pullweight
