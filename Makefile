CXXFLAGS = -std=c++17 -Wextra -Wall -g -O3 #-Werror 

SRCS := $(shell find . -name '*.cpp' -type f)

OBJS := $(SRCS:.cpp=.o)


HEADERS= $(shell find . -name "*.hpp")


INCLUDE := $(shell find . -name "*.hpp" | sed 's/[^/]*$$//g' | sort | uniq)
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE))

TARGET = bin/abstract-vm

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@ -fsanitize=address

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all 


.PHONY: all clean fclean re