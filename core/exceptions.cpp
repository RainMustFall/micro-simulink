#include "exceptions.h"

ResultIsNotScalar::ResultIsNotScalar(const std::string &message)
    : std::runtime_error(message) {}

GraphIsIncomplete::GraphIsIncomplete(const std::string &message)
    : std::runtime_error(message) {}
