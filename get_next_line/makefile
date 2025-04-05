NAME   = get_next_line

CC     = gcc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

SRCS   = get_next_line.c get_next_line_utils.c
OBJS   = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile .c files into .o files
%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

# Remove compiled files
clean:
	rm -f $(OBJS)

# Remove compiled files and executable
fclean: clean
	rm -f $(NAME)

# Recompile everything
re: fclean all

# Avoid conflicts with file names
.PHONY: all clean fclean re
