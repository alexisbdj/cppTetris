##
## EPITECH PROJECT, 2020
## tetris (Workspace)
## File description:
## Makefile
##

SRC	=	./src/main.cpp				\
		./src/Environment.cpp		\
		./src/Graphical.cpp			\
		./src/Tetriminos.cpp		\
		./src/ActiveTetrimino.cpp	\
		./src/SevenBag.cpp			\
		./src/Marathon.cpp			\
		./src/Game.cpp				\
		./src/Menu.cpp				\
		./src/Button.cpp			\
		./src/WindowHandling.cpp	\
		./src/Sprint.cpp			\
		./src/Ultra.cpp				\
		./src/WallKick.cpp			\

OBJ	=	$(SRC:.cpp=.o)

NAME	=	tetris

CXXFLAGS	=	-I./include -Wall -Wextra

LD	=	-lsfml-graphics -lsfml-window -lsfml-system

CC	=	g++

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LD)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean	all

.PHONY:	all	clean	fclean	re
