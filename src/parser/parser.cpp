#include "parser.hpp"

Parser::Parser(std::vector<Token> &tokens) : _tokens(tokens) {}

const std::vector<Instruction> &Parser::parse() {

  // skip any NL
  while (match(TokenType::NL))
    ;

  while (!isExhausted()) {
    auto op = parseInstruction();
    _instructions.push_back(op);

    if (!(peek().type & (TokenType::NL | TokenType::_EOF)))
      throw std::runtime_error("Expected new line or EOF");

    if (peek().type & TokenType::NL)
      advance();
  }
  return _instructions;
}

Instruction Parser::parseInstruction() {

  auto opToken = peek();
  auto instruction = Instruction(opToken.lexeme);

  consume(TokenType::OP | TokenType::EXIT, "Expected operation");

  auto token = peek();
  if ((token.type & (TokenType::NL | TokenType::_EOF))) {
    return instruction;
  }

  auto operand = parseOperand();
  instruction.setOperand(operand);
  return instruction;
}

const std::string Parser::parseValue(const Token &token) {

  auto sign = match(TokenType::NEG) ? '-' : '+';

  auto valueToken = peek();

  if (token.type & INT_TYPES && !match(TokenType::INT_VALUE)) {
    throw std::runtime_error("Expected integer value");
  }
  if (token.type & FLOAT_TYPES && !match(TokenType::FLOAT_VALUE)) {
    throw std::runtime_error("Expected float value");
  }

  return std::string(1, sign) + valueToken.lexeme;
}

std::shared_ptr<const IOperand> Parser::parseOperand() {

  auto typeToken = peek(); // use it later

  consume(TokenType::INT8 | TokenType::INT16 | TokenType::INT32 | TokenType::FLOAT32 |
              TokenType::FLOAT64,
          "Expected type");
  consume(TokenType::LP, "Expected '('");
  auto value = parseValue(typeToken);
  consume(TokenType::RP, "Expected ')'");

  auto operandFactory = OperandFactory();

  std::map<TokenType, eOperandType> typeMap = {
      {TokenType::INT8, eOperandType::Int8},
      {TokenType::INT16, eOperandType::Int16},
      {TokenType::INT32, eOperandType::Int32},
      {TokenType::FLOAT32, eOperandType::Float},
      {TokenType::FLOAT64, eOperandType::Double},
  };

  auto operand = operandFactory.createOperand(typeMap[typeToken.type], value);

  return operand;
}

Parser::~Parser() {}

// parse utils

bool Parser::isExhausted() {
  return _pos >= _tokens.size() || _tokens[_pos].type & TokenType::_EOF;
}

bool Parser::match(int type) {
  if (_tokens[_pos].type & type) {
    advance();
    return true;
  }

  return false;
}

void Parser::consume(int type, const std::string &message) {
  if (!match(type)) {
    throw std::runtime_error(message); // TODO: change it with parser error
  }
}

void Parser::advance() { _pos++; }

const Token &Parser::peek() { return _tokens[_pos]; }