#pragma once

#include <string>

namespace pullweight {

// Scoped enum: values live inside TaskStatus and never convert to int by accident
enum class TaskStatus {
    NOT_STARTED,
    IN_PROGRESS,
    SUBMITTED,
    APPROVED,
    REJECTED
};

// Helper: turn a TaskStatus into readable text (inline so the header needs no .cpp)
inline std::string toString(TaskStatus status) {
    switch (status) {
        case TaskStatus::NOT_STARTED: return "NOT_STARTED";
        case TaskStatus::IN_PROGRESS: return "IN_PROGRESS";
        case TaskStatus::SUBMITTED:   return "SUBMITTED";
        case TaskStatus::APPROVED:    return "APPROVED";
        case TaskStatus::REJECTED:    return "REJECTED";
    }
    return "UNKNOWN";
}

} // namespace pullweight
