#pragma once

#include "instruction.hpp"
#include "ioperand.hpp"
#include "lexer.hpp"
#include "operand-factory.hpp"
#include "parser-exception.hpp"

class Parser {

  std::vector<Token> &_tokens;
  size_t _pos = 0;

  std::vector<Instruction> _instructions;

public:
  Parser(std::vector<Token> &tokens);
  const std::vector<Instruction> &parse();

  ~Parser();

private:
  Instruction parseInstruction();
  std::shared_ptr<const IOperand> parseOperand();
  const std::string parseValue(const Token &token);

private:
  bool isExhausted();
  bool match(int type);
  void consume(int type, const std::string &message);
  void advance();
  const Token &peek();
};