# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 12:38:40 by mcatalan          #+#    #+#              #
#    Updated: 2024/03/07 11:42:42 by mcatalan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MACOS
# Print MINISHELL and authors' names
MINISHELL_MSG = PHILOSOPHERS
AUTHORS_MSG = by mcatalan
MESSAGE_LEN = $$(($(shell echo $(MINISHELL_MSG) | wc -c) - 1))

PRINT_MINISHELL = @printf "$(VIOLET)%*s$(RESET)\n" $(MESSAGE_LEN) $(MINISHELL_MSG)
PRINT_AUTHORS = @echo "$(BLUE)$(AUTHORS_MSG)$(RESET)"

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

LIBFT_D = includes/libft/
LIBFT = libft.a

NAME = philosphers

SRCS =	src/main.c							

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

INCLUDE = -I./
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g #-fsanitize=address

all: print_message libft $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

libft:
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_D)

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

%.o: %.c
	@echo "$(YELLOW)Compiling...$(RESET)"
	@${CC} ${CFLAGS} -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_D)$(LIBFT)
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) $(OFLAGS)
	@echo "$(GREEN)Linked!$(RESET)✅"
-include $(DEPS)

clean:
	@make clean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(RED)Cleaned minishell!$(RESET)✅"

fclean:
	@make fclean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(NAME) $(DEPS) $(OBJS)
	@echo "$(RED)Fcleaned minishell!$(RESET)✅"

re: fclean all

.PHONY: all clean fclean re libft
