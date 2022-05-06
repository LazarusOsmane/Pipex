# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: engooh <engooh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 12:52:16 by engooh            #+#    #+#              #
#    Updated: 2022/05/06 19:14:29 by engooh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/utils.c
SRC_BONUS = src/main_bonus.c src/utils_bonus.c
OBJ = ${SRC:%.c=%.o}
OBJ_BONUS = ${SRC_BONUS:%.c=%.o}
CFLAG = -g3 -Wall -Wextra -Werror

all: pipex

bonus: pipex_bonus 

pipex_bonus: $(OBJ_BONUS)
	gcc $(CFLAG) $(OBJ_BONUS) -o pipex share/Printf/libftprintf.a share/libft/libft.a 

pipex: $(OBJ)
	gcc $(CFLAG) $(OBJ) -o $@ share/Printf/libftprintf.a share/libft/libft.a 

%.o: %.c
	cd share/libft/ && make && cd ../../
	cd share/Printf/ && make && cd ../../
	gcc $(CFLAG) -c $^ -o $@ 

clean: 
	cd share/libft/ && make clean && cd ../../
	cd share/Printf/ && make clean && cd ../../
	rm src/*.o

fclean: clean 
	rm pipex

re: fclean all

.PHONY: all fclean clean re bonus
