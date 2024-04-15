##
## EPITECH PROJECT, 2023
## B-CPE-110-MAR-1-1-settingup-selim.bouasker
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/my_putchar.c	\
		src/my_putstr.c	\
		src/my_printf.c	\
		src/my_strlen.c	\
		src/my_strdup.c	\
		src/strcmp.c	\
		src/intern_com.c	\
		src/my_str_isalpha.c	\
		src/strncmp.c	\
		src/my_strcpy.c	\
		src/my_strcat.c	\
		src/is_alpha.c	\
		src/is_alpha_num.c	\
		src/check_malloc.c	\
		src/my_strtok.c	\
		src/token.c	\
		src/redirect.c	\
		src/my_strrchr.c	\
		src/pipe.c	\

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
