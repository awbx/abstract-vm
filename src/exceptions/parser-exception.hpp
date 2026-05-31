#pragma once

#include "common.hpp"
#include "lexer.hpp"

class ParserException : public std::logic_error {
public:
  ParserException();
  ParserException(const std::string &raw);
  ParserException(const Token &token, const std::string &message);
  ParserException(size_t line, size_t column, const std::string &message);
  ParserException(const ParserException &other);
  ParserException &operator=(const ParserException &other);
  ~ParserException() override;
};
