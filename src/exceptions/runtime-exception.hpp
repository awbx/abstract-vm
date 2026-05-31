#pragma once

#include "common.hpp"

class RuntimeException : public std::runtime_error {
public:
  RuntimeException();
  RuntimeException(const std::string &message);
  RuntimeException(const RuntimeException &other);
  RuntimeException &operator=(const RuntimeException &other);
  ~RuntimeException() override;
};
