#Standard

NAME = philo
BONUS = philo_bonus
CC = cc
SRC_PATH = src/
OBJ_PATH = obj/
bonus_PATH = bonus/
CFLAGS = -Wall -Werror -Wextra -pthread
DEBUG = -g3 -fsanitize=address
DEBUG_T = -g3 -fsanitize=thread
PERFORMANCE = -Ofast -march=native -flto -funroll-loops
RM = rm -fr

#Sources
FILES        =     	main validate utls philo time routine

# BONUS_FILES	=		

PHILO_SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
PHILO_OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJS =	$(addprefix $(OBJ_PATH), $(OBJ))
INCS = -I ../includes

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
			@$(CC) $(INCS) $(CFLAGS) $(DEBUG_T) $(PHILO_OBJ) -o $@

$(OBJ_PATH)%.o:		$(SRC_PATH)%.c
			@mkdir -p $(OBJ_PATH)
			@echo "$(YELLOW) Compiling: $< $(DEF_COLOR)"
			@$(CC) $(INCS) $(CFLAGS) -c $< -o $@

#BONUS
# bonus:		$(OBJ_BONUS)
# 			@echo "$(YELLOW) Compiling: $@ $(DEF_COLOR)"
# 			@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS)
clean:
			@$(RM) $(OBJ_PATH)
			@echo "$(BLUE)All objects files cleaned!$(DEF_COLOR)"

fclean: 	clean
			@$(RM) $(NAME) $(CHECKER)
			@echo "$(CYAN)All executable files cleaned!$(DEF_COLOR)"

re: 		fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything$(DEF_COLOR)"

.PHONY: 		fclean all re clean
