#include "parser.hpp"
#include "runtime-exception.hpp"

Parser::Parser(std::vector<Token> &tokens) : _tokens(tokens), _pos(0) {}

Parser::~Parser() {}

const std::vector<Instruction> &Parser::parse() {
  while (match(TokenType::NL))
    ;

  while (!isExhausted()) {
    try {
      Instruction instr = parseInstruction();
      _instructions.push_back(instr);

      if (!(peek().type & (TokenType::NL | TokenType::_EOF))) {
        throw ParserException(peek(), "Expected newline or end of file");
      }
      while (match(TokenType::NL))
        ;
    } catch (const ParserException &e) {
      _errors.push_back(e.what());
      skipToNextStatement();
    } catch (const std::exception &e) {
      _errors.push_back(std::string("Line ") + std::to_string(peek().line) +
                        " : " + e.what());
      skipToNextStatement();
    }
  }

  if (!_errors.empty()) {
    std::string joined;
    for (size_t i = 0; i < _errors.size(); ++i) {
      joined += _errors[i];
      if (i + 1 < _errors.size())
        joined += "\n";
    }
    throw ParserException(joined);
  }

  return _instructions;
}

void Parser::skipToNextStatement() {
  while (!isExhausted() && peek().type != TokenType::NL)
    advance();
  while (match(TokenType::NL))
    ;
}

Instruction Parser::parseInstruction() {
  Token opToken = peek();

  if (opToken.type == TokenType::ILLEGAL_CHAR) {
    advance();
    throw ParserException(opToken, "Unknown token '" + opToken.lexeme + "'");
  }

  Instruction instruction(opToken.lexeme, opToken.line);
  consume(TokenType::OP | TokenType::OPNOP, "Expected instruction");

  bool isNop = (opToken.type & TokenType::OPNOP) != 0;
  bool atTerminator = (peek().type & (TokenType::NL | TokenType::_EOF)) != 0;

  if (isNop && !atTerminator)
    throw ParserException(peek(), "Instruction '" + opToken.lexeme +
                                       "' takes no operand");
  if (isNop)
    return instruction;

  instruction.setOperand(parseOperand());
  return instruction;
}

std::shared_ptr<const IOperand> Parser::parseOperand() {
  Token typeToken = peek();
  int typeMask = TokenType::INT8 | TokenType::INT16 | TokenType::INT32 |
                 TokenType::FLOAT32 | TokenType::FLOAT64;
  consume(typeMask, "Expected operand type (int8, int16, int32, float, double)");
  consume(TokenType::LP, "Expected '(' after type");
  std::string value = parseValue(typeToken);
  consume(TokenType::RP, "Expected ')' after value");

  static const std::map<TokenType, eOperandType> typeMap = {
      {TokenType::INT8, eOperandType::Int8},
      {TokenType::INT16, eOperandType::Int16},
      {TokenType::INT32, eOperandType::Int32},
      {TokenType::FLOAT32, eOperandType::Float},
      {TokenType::FLOAT64, eOperandType::Double},
  };

  OperandFactory factory;
  return factory.createOperand(typeMap.at(typeToken.type), value);
}

std::string Parser::parseValue(const Token &typeToken) {
  std::string sign = match(TokenType::NEG) ? "-" : "";
  Token valueToken = peek();

  if (typeToken.type & INT_TYPES) {
    if (!match(TokenType::INT_VALUE))
      throw ParserException(valueToken, "Expected integer value");
  } else if (typeToken.type & FLOAT_TYPES) {
    if (!match(TokenType::FLOAT_VALUE))
      throw ParserException(valueToken, "Expected decimal value");
  }
  return sign + valueToken.lexeme;
}

bool Parser::isExhausted() const {
  return _pos >= _tokens.size() || _tokens[_pos].type == TokenType::_EOF;
}

bool Parser::match(int type) {
  if (_pos < _tokens.size() && (_tokens[_pos].type & type)) {
    advance();
    return true;
  }
  return false;
}

void Parser::consume(int type, const std::string &message) {
  if (!match(type))
    throw ParserException(peek(), message);
}

void Parser::advance() { _pos++; }

const Token &Parser::peek() const { return _tokens[_pos]; }
