MODULE_SRC	= \
			mlx_image.swift mlx_window.swift mlx_init.swift

MODULE_OBJ	= \
			$(MODULE_SRC:.swift=.swiftmodule)

SRC			= \
			interface.swift $(MODULE_SRC)

OBJ			= $(SRC:.swift=.o)

C_SRC		= mlx_xpm.c mlx_png.c mlx_string_put.c

C_OBJ		= $(C_SRC:.c=.o)

CFLAGS		= -O3

NAME		= libmlx.dylib

INC			= -I.
#OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
		swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz

%.o:	%.swift
		swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
		swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

clean:
		rm -f $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~

fclean:
		@rm -f $(NAME)
		@printf "$(UNDER_LINE)$(NAME)$(NO_COLOR)  $(RED)deleted$(NO_COLOR)\n"

UNDER_LINE	= \033[4m
NO_COLOR 	= \033[0m
RED 	 	= \033[0;31m

.PHONY: all clean fclean
.PHONY: MODULE_SRC MODULE_OBJ SRC OBJ C_SRC C_OBJ CFLAGS NAME INC UNDER_LINE NO_COLOR RED
