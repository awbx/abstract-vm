
#include "parser-exceptions.hpp"

ParserException::ParserException(const std::string &message) : _message(message) {}

const char *ParserException::what() const noexcept { return _message.c_str(); 
}