
SRCS	= \
			t_unit.c \
			ft_utils.c \
			ft_parser.c \
			ft_printf.c \
			ft_print_c.c \
			ft_print_d.c \
			ft_print_p.c \
			ft_print_s.c \
			ft_print_u.c \
			ft_print_x.c \
			ft_processor.c \
			ft_dec_to_hex.c \
			ft_parser_utils.c \
			ft_print_percent.c

NAME		= libftprintf.a

LIBFT_PATH	= ../libft

HEADER		= ft_printf.h

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR	=		.obj/

# прописываем (добавляем) путь для каждого .o файла
OBJS	 	= 		$(addprefix $(OBJS_DIR), $(patsubst %.c, %.o, $(SRCS)))

NORM		= ~/.scripts/colorised_norm.sh

all:		make_lib $(NAME)

make_lib:
			@cp  $(LIBFT_PATH)/libft.a $(NAME)

$(NAME): 	$(OBJS)
			@ar rc $(NAME) $?
			@printf "$(LIGHT_PURPLE)$(BOLD)ft_printf –– [Success compiling] $(NO_COLOR)\n\n"

$(OBJS_DIR)%.o:		%.c $(HEADER) $(LIBFT_PATH)/.obj/*
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
		@rm -rf $(OBJS) $(BONUS_OBJS)
		@/bin/rm -rf $(OBJS_DIR)

fclean: clean
		@rm -rf $(NAME)
		@printf "$(UNDER_LINE)$(BOLD)$(NAME)$(NO_COLOR) $(LIGHT_RED)deleted$(NO_COLOR)\n"

re: 	fclean all

norm:		
		@$(NORM) $(SRCS) $(HEADER)

run:	all
		@echo "$(YELLOW)gcc -Wall -Werror -Wextra -L. -lftprintf main.c && ./a.out$(NO_COLOR)"
		@${CC} $(CFLAGS) -L. -lftprintf main.c && ./a.out
		@rm a.out

################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m
NO_COLOR 	= \033[0m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
LIGHT_RED	= \033[1;31m
LIGHT_PURPLE= \033[1;35m
YELLOW 		= \033[1;33m

.PHONY: all bonus clean fclean re norm run
.PHONY: SRCS NAME BONUS_SRCS LIBS LIBFT_PATH CC CFLAGS OBJS BONUS_OBJS OBJS_DIR CRT HEADER NORM
.PHONY: UNDER_LINE BOLD NO_COLOR RED GREEN LIGHT_RED LIGHT_PURPLE YELLOW
