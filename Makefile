# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mathishuguenot <mathishuguenot@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 02:30:33 by mhugueno          #+#    #+#              #
#    Updated: 2024/10/06 16:54:50 by mathishugue      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME		= irc

CC			= c++
FLAGS		= -Wall -Wextra -Werror -std=c++11
RM			= rm -rf

SRC_DIR = src

OBJDIR = obj

FILES		= main mode parsing running serveur client chat channel

SRC			= $(addprefix $(SRC_DIR)/, $(FILES:=.cpp))
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= $(SRC_DIR)/irc.hpp

RED = \033[38;5;196m
ORANGE = \033[38;5;208m
YELLOW = \033[38;5;226m
LIGHT_GREEN = \033[38;5;154m
GREEN = \033[38;5;46m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(OBJ) $(OPTS) -o $(NAME)
	@echo ""
	@python3 skin.py "$(NAME)"
	@echo ""
	@echo "Here the featurs of IfPeachill :"
	@echo "./ircserv <port> <password>"
	@echo "/JOIN <channel> <password (Only if channel need one)>"
	@echo "/PART <channel>"
	@echo "/MSG <nickname> <message>"
	@echo "/KICK <nickname> <channel>"
	@echo "/INVITE <nickname> <channel>"
	@echo "/TOPIC <topic (Only if you want to setup a topic for the channel)>"
	@echo "/SEND <nickname> <PathToFile>"
	@echo "/MODE :"
	@echo "		- +i / -i (Define or delete the on invite only mode for the channel)"
	@echo "		- +t / -t (Define or delete the restriction to use the /TOPIC command)"
	@echo "		- +k <password> / -k (Define or delete the password for the channel)"
	@echo "		- +o <nickname> / -o <nickname> (Define or delete the Operator permission for the user)"
	@echo "		- +l <limit> / -l (Define or delete the limit of client for this channel)"

$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@echo -n -e "$(NC)  [$(RED)■■ / 5%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(RED)■■■ / 10%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(RED)■■■■ / 15%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(RED)■■■■■■ / 20%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■ / 25%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■■■ / 30%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■■■■ / 35%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(ORANGE)■■■■■■■■■■■■ / 40%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■ / 45%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■■■ / 50%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■■■■ / 55%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(YELLOW)■■■■■■■■■■■■■■■■■■ / 60%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■ / 65%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■■■ / 70%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■■■■ / 75%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(LIGHT_GREEN)■■■■■■■■■■■■■■■■■■■■■■■■ / 80%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■ / 85%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■■■ / 90%$(NC)] - $<\r"
	@sleep 0.05
	@echo -n -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■■■■ / 95%$(NC)] - $<\r"
	@sleep 0.05
	@echo -e "$(NC)  [$(GREEN)■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ / 100%$(NC)] - $<\r"
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
