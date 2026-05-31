#include "runtime-exception.hpp"

RuntimeException::RuntimeException() : std::runtime_error("Runtime error") {}

RuntimeException::RuntimeException(const std::string &message)
    : std::runtime_error(message) {}

RuntimeException::RuntimeException(const RuntimeException &other)
    : std::runtime_error(other) {}

RuntimeException &RuntimeException::operator=(const RuntimeException &other) {
  if (this != &other)
    std::runtime_error::operator=(other);
  return *this;
}

RuntimeException::~RuntimeException() {}
