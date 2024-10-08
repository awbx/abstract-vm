#include "lexer.hpp"

Lexer::Lexer(std::istream &stream) : stream(stream) {}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  char c;

  std::map<std::string, TokenType> keywords = {
      {"push", TokenType::OP},        {"assert", TokenType::OP},
      {"dump", TokenType::OPNOP},     {"add", TokenType::OPNOP},
      {"mul", TokenType::OPNOP},      {"mod", TokenType::OPNOP},
      {"pop", TokenType::OPNOP},      {"sub", TokenType::OPNOP},
      {"div", TokenType::OPNOP},      {"print", TokenType::OPNOP},
      {"exit", TokenType::OPNOP},     {"int16", TokenType::INT16},
      {"float", TokenType::FLOAT32},  {")", TokenType::RP},
      {"int8", TokenType::INT8},      {"int32", TokenType::INT32},
      {"double", TokenType::FLOAT64}, {"(", TokenType::LP},
      {"-", TokenType::NEG},
  };

  size_t line = 1;
  size_t column = 1;

  while (stream.get(c)) {

    switch (c) {
    case ' ':
    case '\t':
      column++;
      break;

    case ';': {
      if (lookahead() == ';') {
        tokens.push_back({TokenType::_EOF, "EOF", line, column});
        return tokens;
      }
      while (stream.get(c) && c != '\n') {
        column++;
      }
      line++;
      break;
    }
    case '\n':
      while (stream.get(c) && c == '\n') {
        line++;
      }
      stream.unget();
      tokens.push_back({TokenType::NL, "NEW LINE", line, column});
      line++;
      column = 1;
      break;

    case '(':
    case ')':
    case '-':
      column++;
      tokens.push_back({keywords[std::string(1, c)], std::string(1, c), line, column});
      break;

    case 'a' ... 'z': {
      std::string value(1, c);
      while (stream.get(c) && isalnum(c)) {
        value += c;
        column++;
      }
      stream.unget();
      column++;
      if (keywords.find(value) == keywords.end()) {
        tokens.push_back({TokenType::ILLEGAL_CHAR, value, line, column});
        break;
      }

      tokens.push_back({keywords[value], value, line, column});
      break;
    }

    case '0' ... '9': {
      std::string value(1, c);
      while (stream.get(c) && isdigit(c)) {
        value += c;
        column++;
      }
      if (c == '.') {
        value += c;
        column++;
        while (stream.get(c) && isdigit(c)) {
          value += c;
          column++;
        }
        stream.unget();
        tokens.push_back({TokenType::FLOAT_VALUE, value, line, column});
        break;
      }
      stream.unget();
      column++;
      tokens.push_back({TokenType::INT_VALUE, value, line, column});
      break;
    }

    default:
      tokens.push_back({TokenType::ILLEGAL_CHAR, std::string(1, c), line, column});
      column++;
      break;
    };
  }
  tokens.push_back({TokenType::_EOF, "EOF", line, column});
  return tokens;
}

char Lexer::lookahead() {
  char c;
  stream.get(c);
  stream.unget();
  return c;
}