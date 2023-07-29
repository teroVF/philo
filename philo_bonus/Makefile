#Standard

NAME = philo_bonus
CC = cc
SRC_PATH = src/
OBJ_PATH = obj/
bonus_PATH = bonus/
CFLAGS = -Wall -Werror -Wextra -pthread
DEBUG = -fsanitize=address
DEBUG_T = -g -fsanitize=thread
PERFORMANCE = -O3 -march=native -flto -funroll-loops
RM = rm -fr

#Sources
FILES        =     	main validate utls philo time routine sem

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
			@$(CC) $(INCS) $(CFLAGS) $(PHILO_OBJ) -o $@

$(OBJ_PATH)%.o:		$(SRC_PATH)%.c
			@mkdir -p $(OBJ_PATH)
			@echo "$(YELLOW) Compiling: $< $(DEF_COLOR)"
			@$(CC) $(INCS) $(CFLAGS) -c $< -o $@

PERF:		fclean $(PHILO_OBJ)
			@echo "$(YELLOW) Compiling: $@ $(DEF_COLOR)"
			@$(CC) $(INCS) $(CFLAGS) $(PERFORMANCE) $(PHILO_OBJ) -o $(NAME)

debug:		fclean $(PHILO_OBJ)
			@echo "$(YELLOW) Compiling: $@ $(DEF_COLOR)"
			@$(CC) $(INCS) $(CFLAGS) $(DEBUG) $(PHILO_OBJ) -o $(NAME)

debug_t:	fclean $(PHILO_OBJ)
			@echo "$(YELLOW) Compiling: $@ $(DEF_COLOR)"
			@$(CC) $(INCS) $(CFLAGS) $(DEBUG_T) $(PHILO_OBJ) -o $(NAME)

size: 
			@echo "$(YELLOW)Size of the executable:$(DEF_COLOR)"
			@wc -c $(NAME) | echo `awk '{print $$1}'` bytes

assemble:
			@echo "$(YELLOW)Assembling:$(DEF_COLOR)"
			@objdump -d $(NAME) > $(NAME).s

assemble_s:
			@echo "$(YELLOW)Assembling:$(DEF_COLOR)"
			@objdump -d $(NAME) | wc -l

clean:
			@$(RM) $(OBJ_PATH)
			@echo "$(BLUE)All objects files cleaned!$(DEF_COLOR)"

fclean: 	clean
			@$(RM) $(NAME)\
			@echo "$(CYAN)All executable files cleaned!$(DEF_COLOR)"

re: 		fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything$(DEF_COLOR)"

.PHONY: 	fclean all re clean
