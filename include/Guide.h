#pragma once

#include <string>

#include "Person.h"

namespace pullweight {

class Member;

// The teacher / project guide. Virtual inheritance so TeamLead gets only one Person
class Guide : virtual public Person {
public:
    Guide();                                                                        // Default constructor
    Guide(const std::string& name, const std::string& pin, const std::string& department); // Parameterized constructor

    void display() const override;                             // Runtime polymorphism

    const std::string& getDepartment() const { return department; }

    bool canApprove(const Member& member) const;               // Declared now, defined in a later phase

private:
    std::string department;
};

} // namespace pullweight
