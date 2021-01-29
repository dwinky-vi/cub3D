
SRCS	= \
		ft_memset.c  ft_bzero.c   ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
		ft_strlen.c  ft_strlcpy.c ft_strlcat.c ft_strchr.c  ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
		ft_strdup.c  ft_calloc.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_tolower.c ft_toupper.c \
		ft_substr.c  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putchar.c ft_putstr.c ft_putnbr.c ft_putnbr_u_int.c \
		ft_max.c ft_min.c ft_isspace.c ft_swap.c ft_abs.c \
		ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstiter.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c \
		get_next_line.c get_next_line_utils.c

NAME	= libft.a

HEADER	= libft.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

# about other flags
# -Wfloat-equal выдаст ошибку при сравнении чисел с плавующей точкой
# -Wundef предупреждать, если неинициализированный идентификатор оценивается в случае
# -Wconversion неявное приведение типов
#  -ftrapv переполнение целовего числа
# -Wunreachable-code # 

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR =			.obj

# прописываем (добавляем) путь для каждого .o файла
OBJS	= 			$(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

NORM 	=			~/.scripts/colorised_norm.sh
# ~/.scripts/colorised_norm.sh

all:		$(NAME)

$(NAME): 	$(OBJS)
			@ar rc $(NAME) $?
			@printf "$(GREEN)$(BOLD)libft –– [Success compiling]        $(NO_COLOR)\n\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER)
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS)
			@/bin/rm -rf $(OBJS_DIR)

fclean: 	clean
			@rm -rf $(NAME)
			@printf "$(UNDER_LINE)$(NAME) $(RED)deleted$(NO_COLOR)\n"

norm:		
			@$(NORM) $(SRCS) $(HEADER)

re: 		fclean all

.PHONY:	all clean fclean re norm
.PHONY: SRCS SRCS CC CFLAGS OBJS OBJS_DIR HEADER NORM


################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m

NO_COLOR 	= \033[0m
BLACK	 	= \033[0;30m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
BROWN 	 	= \033[0;33m
BLUE 		= \033[0;34m
PURPLE 	 	= \033[0;35m
CYAN 	 	= \033[0;36m
LIGHT_GRAY	= \033[0;37m

DARK_GRAY	= \033[1;30m
LIGHT_RED	= \033[1;31m
LIGHT_GREEN	= \033[1;32m
YELLOW 		= \033[1;33m
LIGHT_BLUE	= \033[1;34m
LIGHT_PURPLE= \033[1;35m
LIGHT_CYAN	= \033[1;36m
WHITE 		= \033[1;37m
