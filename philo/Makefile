CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

SRC = init.c\
		main.c\
		options.c\
		philo.c\
		routine.c\
		state.c\
		time.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re