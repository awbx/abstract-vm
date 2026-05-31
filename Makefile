CXX := c++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -O2

SRCS := $(shell find src -name '*.cpp' -type f)
OBJS := $(SRCS:.cpp=.o)
HEADERS := $(shell find src include -name '*.hpp' -type f)

INCLUDE_DIRS := $(sort $(dir $(HEADERS)))
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIRS))

TARGET := bin/avm

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf bin

re: fclean all

.PHONY: all clean fclean re
