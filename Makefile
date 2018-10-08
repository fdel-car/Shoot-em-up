NAME = ft_retro

SRCS = $(shell find . -name '*.cpp')

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	clang++ -o $@ $^ -lncurses

$(OBJS): $(SRCS)
	clang++ $(CFLAGS) -c $^
	
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re