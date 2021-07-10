NAME	=	philo_one

SRC		=	main.c					\
			philosophers_routine.c	\
			time_functions.c		\
			utils_error.c			\
            init.c					\
            routines.c				\
            utils.c


HEADER	=	philo_one.h

OBJ		=	$(SRC:.c=.o)

CC		=	gcc

.PHONY:	all clean fclean re
all:	$(NAME)

$(NAME):	$(OBJ) Makefile
			$(CC) -o $@ $(OBJ)

%.o			:	%.c $(HEADER)

clean:
			-rm -f $(OBJ)

fclean:		clean
			-rm -f $(NAME)

re:			fclean all

