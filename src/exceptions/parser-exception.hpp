#pragma once

#include "common.hpp"
#include "parser.hpp"

class ParserException : public std::exception {
  std::string _message;

public:
  ParserException(const Token &token, const std::string &message);

  const char *what() const noexcept override;
};