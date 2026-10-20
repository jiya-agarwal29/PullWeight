#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Guide.h"
#include "Member.h"
#include "Person.h"
#include "TeamLead.h"

using namespace pullweight;

int main() {
    auto asha = std::make_shared<Member>("Asha", "1234");
    auto ravi = std::make_shared<Member>("Ravi", "2345");
    auto meera = std::make_shared<Member>("Meera", "3456");
    auto guide = std::make_shared<Guide>("Dr. Rao", "9999", "Computer Science");
    auto lead = std::make_shared<TeamLead>("Karan", "4321", "Computer Science");

    asha->addPoints(40);
    ravi->addPoints(15.5);
    meera->addPoints(60);
    lead->addPoints(30);
    ravi->adjustCredibility(-0.25);

    // 1. Runtime polymorphism: one vector of Person pointers, display() picks the right version
    std::cout << "=== Runtime polymorphism ===" << std::endl;
    std::vector<std::shared_ptr<Person>> people = {asha, ravi, meera, guide, lead};
    for (const auto& p : people) {
        p->display(); // Runtime polymorphism
    }

    // 2. Diamond problem solved: TeamLead has only one Person part
    std::cout << "\n=== Diamond problem ===" << std::endl;
    const Member* asMember = lead.get();
    const Guide* asGuide = lead.get();
    const Person* personViaMember = asMember; // Person part reached through Member
    const Person* personViaGuide = asGuide;   // Person part reached through Guide
    std::cout << "TeamLead id: " << lead->getId() << " (only one id)" << std::endl;
    std::cout << "Same Person object via Member and Guide? "
              << (personViaMember == personViaGuide ? "yes" : "no") << std::endl;

    // 3. Sorting Members with operator<
    std::cout << "\n=== Members sorted by score (operator<) ===" << std::endl;
    std::vector<std::shared_ptr<Member>> members = {asha, ravi, meera, lead};
    std::sort(members.begin(), members.end(),
              [](const std::shared_ptr<Member>& a, const std::shared_ptr<Member>& b) { return *a < *b; });
    for (const auto& m : members) {
        std::cout << *m << std::endl; // Friend operator<<
    }

    // 4. operator==
    std::cout << "\n=== operator== (compares ids) ===" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "asha == asha: " << (*asha == *asha) << std::endl;
    std::cout << "asha == ravi: " << (*asha == *ravi) << std::endl;

    // 5. PIN tests
    std::cout << "\n=== PIN checks ===" << std::endl;
    std::cout << "Right PIN (1234): " << asha->checkPin("1234") << std::endl;
    std::cout << "Wrong PIN (0000): " << asha->checkPin("0000") << std::endl;

    for (const char* badPin : {"12a4", "123"}) {
        try {
            Member bad("Bad", badPin);
        } catch (const std::invalid_argument& e) {
            std::cout << "PIN \"" << badPin << "\" rejected: " << e.what() << std::endl;
        }
    }

    // 6. PIN never printed
    std::cout << "\n=== PIN is never printed ===" << std::endl;
    asha->display();
    std::cout << *asha << std::endl;
    std::cout << "(Asha's PIN is 1234, and it appears in neither line above)" << std::endl;

    return 0;
}
