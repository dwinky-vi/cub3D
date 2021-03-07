MODULE_SRC	= \
			mlx_image.swift mlx_window.swift mlx_init.swift

SRC			= \
			interface.swift $(MODULE_SRC)

MODULE_OBJ	= $(MODULE_SRC:.swift=.swiftmodule)

OBJ			= $(SRC:.swift=.o)

C_SRC		= mlx_xpm.c mlx_png.c mlx_string_put.c

C_OBJ		= $(C_SRC:.c=.o)

CFLAGS		= -O3

NAME		= libmlx.dylib

INC			= -I.
#OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
		@swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz
		@printf "$(LIGHT_PURPLE)$(BOLD)$(NAME) –– [Success compiling] $(NO_COLOR)\n\n"

%.o:	%.swift
		@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
		@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@
		@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

%.swiftmodule: %.swift
		@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
		@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
		@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
		@rm -f $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~

fclean:
		@rm -f $(NAME)
		@printf "$(UNDER_LINE)$(BOLD)$(NAME)$(NO_COLOR)  $(LIGHT_RED)deleted$(NO_COLOR)\n"

################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m
NO_COLOR 	= \033[0m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
LIGHT_RED	= \033[1;31m
YELLOW 		= \033[1;33m
LIGHT_PURPLE= \033[1;35m

.PHONY: all clean fclean
.PHONY: MODULE_SRC MODULE_OBJ SRC OBJ C_SRC C_OBJ CFLAGS NAME INC UNDER_LINE NO_COLOR RED
.PHONY: UNDER_LINE BOLD NO_COLOR RED GREEN LIGHT_RED YELLOW LIGHT_PURPLE
