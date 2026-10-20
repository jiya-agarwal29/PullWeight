#include "Member.h"

#include <iostream>

namespace pullweight {

Member::Member() : Member("Unknown", "0000") {} // Constructor chaining

Member::Member(const std::string& name, const std::string& pin)
    : Person(name, pin), score(0.0), credibility(1.0) {} // Calls the virtual base directly (ignored if a subclass builds it)

void Member::display() const {
    std::cout << "[Member] id=" << getId() << " name=" << getName()
              << " score=" << score << " credibility=" << credibility << std::endl;
}

void Member::addPoints(double points) {
    score += points;
}

void Member::adjustCredibility(double delta) {
    credibility += delta;
    if (credibility < 0.0) credibility = 0.0;
    if (credibility > 1.0) credibility = 1.0;
}

bool Member::operator<(const Member& other) const {
    return score < other.score;
}

std::ostream& operator<<(std::ostream& os, const Member& member) {
    os << member.getName() << " (id " << member.getId() << ", score " << member.score << ")";
    return os;
}

} // namespace pullweight
