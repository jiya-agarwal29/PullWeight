#pragma once

#include <exception>
#include <string>

namespace pullweight {

// Each exception derives from std::exception (inheritance) and overrides what() (polymorphism)

class InvalidRatingException : public std::exception {
public:
    const char* what() const noexcept override { // Runtime polymorphism
        return "Invalid rating: a rating must be between 1 and 5";
    }
};

class SelfRatingException : public std::exception {
public:
    const char* what() const noexcept override { // Runtime polymorphism
        return "A member cannot rate themselves";
    }
};

class SelfApprovalException : public std::exception {
public:
    const char* what() const noexcept override { // Runtime polymorphism
        return "A person cannot approve their own task";
    }
};

class TaskNotApprovedException : public std::exception {
public:
    const char* what() const noexcept override { // Runtime polymorphism
        return "Task is not approved yet";
    }
};

class ProofMissingException : public std::exception {
public:
    const char* what() const noexcept override { // Runtime polymorphism
        return "Proof (commit link or file name) is missing";
    }
};

} // namespace pullweight
