# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 12:38:40 by mcatalan          #+#    #+#              #
#    Updated: 2024/04/28 13:36:00 by mcatalan@st      ###   ########.fr        #
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
YLW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

NAME = philo

SRCS =	src/main.c			\
		src/init.c			\
		src/program.c		\
		src/checker.c		\
		src/clear_program.c	\
		src/utils/parsing.c	\
		src/utils/ft_atol.c	\
		src/utils/prints.c	\
		src/utils/time.c	\

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDE = -I./
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g #-fsanitize=thread

all: print_message $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

%.o: %.c
	@echo "$(YLW)Compiling...$(RESET)"
	@${CC} ${CFLAGS} -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YLW)Linking...$(RESET)"
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
