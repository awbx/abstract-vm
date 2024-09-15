#include "abstract-vm.hpp"
#include "common.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {
  Lexer lexer(std::cin);
  auto tokens = lexer.tokenize();

  for (const auto &token : tokens) {
    std::cout << "Token: " << token.lexeme << " | type: " << token.type << std::endl;
  }

  Parser parser(tokens);

  auto instructions = parser.parse();

  for (auto &instruction : instructions) {
    std::cout << instruction << std::endl;
  }

  auto vm = AbstractVM();

  vm.execute(instructions);

  return 0;
}