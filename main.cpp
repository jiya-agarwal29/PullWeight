#include <iostream>

#include "Exceptions.h"
#include "TaskStatus.h"

using namespace pullweight;

int main() {
    std::cout << "PullWeight" << std::endl;
    std::cout << "Sample status: " << toString(TaskStatus::NOT_STARTED) << std::endl;

    try {
        throw SelfApprovalException();
    } catch (const std::exception& e) { // Catch by base reference: derived exception still works
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
