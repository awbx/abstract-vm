
#include "parser-exception.hpp"

ParserException::ParserException(const Token &token, const std::string &message) {
  _message = "SyntaxError:" + std::to_string(token.line) + ":" +
             std::to_string(token.column) + ": " + message;
}

const char *ParserException::what() const noexcept { return _message.c_str(); }