#include "abstract-vm.hpp"
#include "common.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <fstream>

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cerr << "Usage: " << argv[0] << " [program.avm]" << std::endl;
    return 1;
  }

  std::ifstream file;
  std::istream *input = &std::cin;

  if (argc == 2) {
    file.open(argv[1]);
    if (!file.is_open()) {
      std::cerr << "Error: cannot open file '" << argv[1] << "'" << std::endl;
      return 1;
    }
    input = &file;
  }

  try {
    Lexer lexer(*input);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    const auto &instructions = parser.parse();

    AbstractVM vm;
    vm.execute(instructions);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
