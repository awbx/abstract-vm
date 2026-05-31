#include "lexer.hpp"

Lexer::Lexer(std::istream &stream) : _stream(stream) {}

Lexer::~Lexer() {}

int Lexer::peekChar() { return _stream.peek(); }

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;

  const std::map<std::string, TokenType> keywords = {
      {"push", TokenType::OP},        {"assert", TokenType::OP},
      {"pop", TokenType::OPNOP},      {"dump", TokenType::OPNOP},
      {"add", TokenType::OPNOP},      {"sub", TokenType::OPNOP},
      {"mul", TokenType::OPNOP},      {"div", TokenType::OPNOP},
      {"mod", TokenType::OPNOP},      {"print", TokenType::OPNOP},
      {"exit", TokenType::OPNOP},     {"int8", TokenType::INT8},
      {"int16", TokenType::INT16},    {"int32", TokenType::INT32},
      {"float", TokenType::FLOAT32},  {"double", TokenType::FLOAT64},
  };

  size_t line = 1;
  size_t column = 1;
  char c;

  while (_stream.get(c)) {
    switch (c) {
    case ' ':
    case '\t':
    case '\r':
      column++;
      break;

    case ';': {
      if (peekChar() == ';') {
        tokens.push_back({TokenType::_EOF, ";;", line, column});
        return tokens;
      }
      while (_stream.get(c) && c != '\n')
        column++;
      if (_stream.eof()) {
        tokens.push_back({TokenType::_EOF, "EOF", line, column});
        return tokens;
      }
      tokens.push_back({TokenType::NL, "NL", line, column});
      line++;
      column = 1;
      break;
    }

    case '\n':
      tokens.push_back({TokenType::NL, "NL", line, column});
      line++;
      column = 1;
      break;

    case '(':
      tokens.push_back({TokenType::LP, "(", line, column});
      column++;
      break;
    case ')':
      tokens.push_back({TokenType::RP, ")", line, column});
      column++;
      break;
    case '-':
      tokens.push_back({TokenType::NEG, "-", line, column});
      column++;
      break;

    default:
      if (std::isalpha(static_cast<unsigned char>(c))) {
        std::string value(1, c);
        size_t startCol = column;
        column++;
        while (std::isalnum(static_cast<unsigned char>(peekChar()))) {
          _stream.get(c);
          value += c;
          column++;
        }
        auto it = keywords.find(value);
        if (it == keywords.end())
          tokens.push_back({TokenType::ILLEGAL_CHAR, value, line, startCol});
        else
          tokens.push_back({it->second, value, line, startCol});
      } else if (std::isdigit(static_cast<unsigned char>(c))) {
        std::string value(1, c);
        size_t startCol = column;
        column++;
        while (std::isdigit(static_cast<unsigned char>(peekChar()))) {
          _stream.get(c);
          value += c;
          column++;
        }
        if (peekChar() == '.') {
          _stream.get(c);
          value += c;
          column++;
          while (std::isdigit(static_cast<unsigned char>(peekChar()))) {
            _stream.get(c);
            value += c;
            column++;
          }
          tokens.push_back({TokenType::FLOAT_VALUE, value, line, startCol});
        } else {
          tokens.push_back({TokenType::INT_VALUE, value, line, startCol});
        }
      } else {
        tokens.push_back({TokenType::ILLEGAL_CHAR, std::string(1, c), line, column});
        column++;
      }
      break;
    }
  }

  tokens.push_back({TokenType::_EOF, "EOF", line, column});
  return tokens;
}
