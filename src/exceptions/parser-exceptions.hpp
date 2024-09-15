#pragma once

#include <exception>
#include <string>

class ParserException : public std::exception {
  const std::string &_message;

public:
  ParserException(const std::string &message);

  const char *what() const noexcept override;
};