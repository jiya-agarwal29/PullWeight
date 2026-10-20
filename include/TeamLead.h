#pragma once

#include <string>

#include "Guide.h"
#include "Member.h"

namespace pullweight {

// Multiple inheritance. Both parents inherit Person virtually, so there is only ONE Person inside TeamLead
class TeamLead : public Member, public Guide {
public:
    TeamLead();                                                                         // Default constructor
    TeamLead(const std::string& name, const std::string& pin, const std::string& department); // Parameterized constructor

    void display() const override;                             // Required: Member and Guide both override display()
};

} // namespace pullweight
