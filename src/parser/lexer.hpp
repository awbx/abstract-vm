#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

enum TokenType {
  OP = 1 << 0,
  INT8 = 1 << 1,
  INT16 = 1 << 2,
  INT32 = 1 << 3,
  FLOAT32 = 1 << 4,
  FLOAT64 = 1 << 5,
  INT_VALUE = 1 << 6,
  FLOAT_VALUE = 1 << 7,
  ILLEGAL_CHAR = 1 << 8,
  LP = 1 << 9,
  RP = 1 << 10,
  NL = 1 << 11,
  NEG = 1 << 12,
  // EXIT = 1 << 13,
  OPNOP = 1 << 13,
  _EOF = 1 << 14,
};

#define FLOAT_TYPES (TokenType::FLOAT32 | TokenType::FLOAT64)
#define INT_TYPES (TokenType::INT8 | TokenType::INT16 | TokenType::INT32)

struct Token {
  TokenType type;
  std::string lexeme;
  size_t line;
  size_t column;
};

class Lexer {
  std::istream &stream;

public:
  Lexer(std::istream &stream);

  std::vector<Token> tokenize();

private:
  char lookahead();
};