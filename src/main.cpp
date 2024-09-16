#include "abstract-vm.hpp"
#include "common.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {
  Lexer lexer(std::cin);
  auto tokens = lexer.tokenize();

  // for (const auto &token : tokens) {
  //   std::cerr << "Token: " << token.lexeme << " Type: " << token.type
  //             << " Line: " << token.line << " Column: " << token.column << std::endl;
  // }

  try {
    Parser parser(tokens);

    auto instructions = parser.parse();

    // for (auto &instruction : instructions) {
    //   std::cout << instruction << std::endl;
    // }

    auto vm = AbstractVM();
    vm.execute(instructions);

  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}