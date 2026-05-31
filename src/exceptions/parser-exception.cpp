#include "parser-exception.hpp"

static std::string formatTokenMessage(const Token &token,
                                      const std::string &message) {
  return "Line " + std::to_string(token.line) + " : SyntaxError at column " +
         std::to_string(token.column) + " : " + message;
}

static std::string formatPositionMessage(size_t line, size_t column,
                                         const std::string &message) {
  return "Line " + std::to_string(line) + " : SyntaxError at column " +
         std::to_string(column) + " : " + message;
}

ParserException::ParserException() : std::logic_error("Syntax error") {}

ParserException::ParserException(const std::string &raw) : std::logic_error(raw) {}

ParserException::ParserException(const Token &token, const std::string &message)
    : std::logic_error(formatTokenMessage(token, message)) {}

ParserException::ParserException(size_t line, size_t column,
                                 const std::string &message)
    : std::logic_error(formatPositionMessage(line, column, message)) {}

ParserException::ParserException(const ParserException &other)
    : std::logic_error(other) {}

ParserException &ParserException::operator=(const ParserException &other) {
  if (this != &other)
    std::logic_error::operator=(other);
  return *this;
}

ParserException::~ParserException() {}
