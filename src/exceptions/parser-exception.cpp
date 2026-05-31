#include "parser-exception.hpp"

ParserException::ParserException() : _message("Syntax error") {}

ParserException::ParserException(const std::string &raw) : _message(raw) {}

ParserException::ParserException(const Token &token, const std::string &message) {
  _message = "Line " + std::to_string(token.line) + " : SyntaxError at column " +
             std::to_string(token.column) + " : " + message;
}

ParserException::ParserException(size_t line, size_t column, const std::string &message) {
  _message = "Line " + std::to_string(line) + " : SyntaxError at column " +
             std::to_string(column) + " : " + message;
}

ParserException::ParserException(const ParserException &other) : _message(other._message) {}

ParserException &ParserException::operator=(const ParserException &other) {
  if (this != &other)
    _message = other._message;
  return *this;
}

ParserException::~ParserException() {}

const char *ParserException::what() const noexcept { return _message.c_str(); }
