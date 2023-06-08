#Standard

NAME = philo
BONUS = philo_bonus
CC = cc
SRC_PATH = src/
OBJ_PATH = obj/
bonus_PATH = bonus/
CFLAGS = -Wall -Werror -Wextra -pthread -g -O3 -fsanitize=thread
INCLUDES = push_swap.h
RM = rm -fr

#Sources
FILES        =     	main

# BONUS_FILES	=		

PS_SRC = $(addsuffix .c, $(FILES))
PS_OBJ = $(addsuffix .o, $(FILES))
PS_SRC_BONUS = $(addsuffix .c, $(BONUS_FILES))
PS_OBJ_BONUS = $(addsuffix .o, $(BONUS_FILES))
SRC_BONUS = $(addprefix $(CHECKER_PATH), $(PS_SRC_BONUS))
OBJ_BONUS = $(addprefix $(CHECKER_PATH), $(PS_OBJ_BONUS))
OBJS =	$(addprefix $(OBJ_PATH), $(OBJ))
INCS = -I.

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME)

#MANDATORY
$(NAME):	$(PHILO_OBJ)
			@echo "$(YELLOW) Compiling: $@ $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(PHILO_OBJ) -o $@

%.o:		%.c
			@echo "$(YELLOW) Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -c $< -o $@

bonus:		$(OBJ_BONUS)
			@echo "$(YELLOW) Compiling: $@ $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS)
clean:
			@$(RM) *.o
			@echo "$(BLUE)All objects files cleaned!$(DEF_COLOR)"

fclean: 	clean
			@$(RM) $(NAME) $(CHECKER)
			@echo "$(CYAN)All executable files cleaned!$(DEF_COLOR)"

re: 		fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything$(DEF_COLOR)"

.PHONY: 		fclean all re clean
