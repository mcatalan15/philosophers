# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 12:38:40 by mcatalan          #+#    #+#              #
#    Updated: 2024/03/11 18:08:54 by mcatalan@st      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

NAME = philo

SRCS =	src/main.c		\
		src/utils/utils.c	\


OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDE = -I./
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-v
OFLAGS = -g #-fsanitize=address

all: print_message $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

%.o: %.c
	@echo "$(YELLOW)Compiling...$(RESET)"
	@${CC} ${CFLAGS} -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(OFLAGS)
	@echo "$(GREEN)Linked!$(RESET)✅"
-include $(DEPS)

clean:
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(RED)Cleaned philo!$(RESET)✅"

fclean:
	@$(RM) $(NAME) $(DEPS) $(OBJS)
	@echo "$(RED)Fcleaned philo!$(RESET)✅"

re: fclean all

.PHONY: all clean fclean re
