#include "runtime-exception.hpp"

RuntimeException::RuntimeException() : _message("Runtime error") {}

RuntimeException::RuntimeException(const std::string &message) : _message(message) {}

RuntimeException::RuntimeException(const RuntimeException &other) : _message(other._message) {}

RuntimeException &RuntimeException::operator=(const RuntimeException &other) {
  if (this != &other)
    _message = other._message;
  return *this;
}

RuntimeException::~RuntimeException() {}

const char *RuntimeException::what() const noexcept { return _message.c_str(); }
