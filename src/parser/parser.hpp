#pragma once

#include "common.hpp"
#include "instruction.hpp"
#include "ioperand.hpp"
#include "lexer.hpp"
#include "operand-factory.hpp"
#include "parser-exception.hpp"

class Parser {
private:
  std::vector<Token> &_tokens;
  size_t _pos;
  std::vector<Instruction> _instructions;
  std::vector<std::string> _errors;

public:
  Parser(std::vector<Token> &tokens);
  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;
  ~Parser();

  const std::vector<Instruction> &parse();

private:
  Instruction parseInstruction();
  std::shared_ptr<const IOperand> parseOperand();
  std::string parseValue(const Token &typeToken);

  bool isExhausted() const;
  bool match(int type);
  void consume(int type, const std::string &message);
  void advance();
  const Token &peek() const;
  void skipToNextStatement();
};
