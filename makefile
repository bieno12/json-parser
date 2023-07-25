NAME=test_program
CC = g++
FLAGS = -Wall -Wextra -Werror  -std=c++17

INCLUDE= -I./include/
SRC =	src/main.cpp \
		src/myjson/Value.cpp \
		src/myjson/reader/Parser.cpp \
		src/myjson/reader/Scanner.cpp \
		src/myjson/reader/Token.cpp \
		src/myjson/json.cpp 


OBJECTS = $(SRC:.cpp=.o)
HEADERS =	include/myjson/json.hpp \
			include/myjson/Value.hpp \
			include/myjson/reader/Parser.hpp \
			include/myjson/reader/Scanner.hpp \
			include/myjson/reader/Token.hpp 

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDE)  $(OBJECTS) -o $(NAME)
	@echo "$(NAME) created!"


%.o : %.cpp $(HEADERS)
	@echo "compiling $<"
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean: 
	@rm -rf $(OBJECTS)

fclean: 
	@rm -rf $(OBJECTS)
	rm -f $(NAME)

re: fclean all
.PHONY: clean fclean