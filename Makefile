#######################################################
## ARGUMENTS

NAME = pipex
BONUS = pipex_bonus

CC	= cc
RM = rm -rf
FLAGS	= -Wall -Wextra -Werror -g3
DEP_FLAGS	:=	-MMD -MP


#######################################################
## SOURCES

SRCS_FILES = pipex.c exec_process.c utils.c \

LIB_SRCS_FILES = ft_putstr_fd.c ft_split.c ft_strjoin.c \
				ft_strncmp.c ft_strnstr.c \
			

BONUS_SRCS_FILES = pipex_bonus.c \

SRCS_DIR = ./srcs
LIB_DIR = ./lib
BONUS_SRCS_DIR = ./srcs_bonus

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
LIB_SRCS = $(addprefix $(LIB_DIR)/, $(LIB_SRCS_FILES))
BONUS_SRCS = $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SRCS_FILES))

OBJECTS = $(SRCS:.c=.o) $(LIB_SRCS:.c=.o)
DEP	= $(OBJECTS:.o=.d) $(BONUS_OBJECTS;.o=.d)
BONUS_OBJECTS = $(BONUS_SRCS:.c=.o)


#######################################################
## RULES

$(NAME): $(OBJECTS)
			$(CC) $(DEP_FLAGS) $(FLAGS) $(OBJECTS) -o $@
			
all: $(NAME) $(BONUS)


bonus: $(BONUS)


.c.o:
	$(CC) $(DEP_FLAGS) $(FLAGS) -c $< -o $(<:.c=.o)


$(BONUS): $(BONUS_OBJECTS)
			$(CC) $(FLAGS) $(BONUS_OBJECTS) -o $@

clean:
			$(RM) $(OBJECTS) $(DEP)

clean_bonus:
			$(RM) $(BONUS_OBJECTS)
fclean: clean clean_bonus
			$(RM) $(NAME) $(BONUS)

re:	fclean $(NAME)

re_bonus: fclean bonus

.PHONY: all bonus clean clean_bonus fclean re re_bonus