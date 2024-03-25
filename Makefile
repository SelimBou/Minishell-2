##
## EPITECH PROJECT, 2023
## B-CPE-110-MAR-1-1-settingup-selim.bouasker
## File description:
## Makefile
##

SRC	=	main.c	\
		my_putchar.c	\
		my_putstr.c	\
		my_printf.c	\
		my_strlen.c	\
		my_strdup.c	\
		strcmp.c	\
		intern_com.c	\
		my_str_isalpha.c	\
		strncmp.c	\
		my_strcpy.c	\
		my_strcat.c	\
		is_alpha.c	\
		is_alpha_num.c	\
		check_malloc.c	\
		my_strtok.c	\
		token.c	\
		redirect.c	\
		my_strrchr.c	\
		pipe.c	\

OBJ	=	$(SRC:.c=.o)

NAME	= mysh

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc $(OBJ) -o $(NAME) -g3

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
