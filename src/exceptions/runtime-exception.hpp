#pragma once

#include "common.hpp"

class RuntimeException : public std::exception {
private:
  std::string _message;

public:
  RuntimeException();
  RuntimeException(const std::string &message);
  RuntimeException(const RuntimeException &other);
  RuntimeException &operator=(const RuntimeException &other);
  ~RuntimeException() override;

  const char *what() const noexcept override;
};
