# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 15:41:12 by apielasz          #+#    #+#              #
#    Updated: 2022/09/14 20:49:35 by apielasz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I -pthread -g -fsanitize=address

SRC = $(SRC_DIR)init.c \
		$(SRC_DIR)main.c \
		$(SRC_DIR)philo.c \
		$(SRC_DIR)threads.c \
		$(SRC_DIR)time.c \
		$(SRC_DIR)utils.c

# takes all named source files and converts them to .o files in the /obj directory
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# prevents rules from being considered as files
.PHONY: all clean fclean re

all: $(NAME) # credit

# creates subdirectory /obj
# makes sure to make a /obj dir before compiling .o files
$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# compiles all object files and builds executable file
# $^ is a list of all the prerequisites of the rule, including the names of the 
# directories in which they were found, and the value of ‘$@’ is the target.
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)>>>SUCCESSFULLY COMPILED!<<<$(UNDO_COL)"

# removes all object files and the /obj directory and cleans libft
clean:
	rm -r $(OBJ_DIR)

# calls 'clean' and removes the executable
fclean: clean
	rm -f $(NAME)

# re-makes the whole compilation from scratch
re: fclean all

# credit:
# 	@echo "\n"
# 	@echo "                        #%%%%/,..*#%%%%.                              "
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
# 	@echo
	                                                              
#                                  #%%%%/,..*#%%%%.                              
#                                %%,                %%%                           
#                             *%#                      %%                         
#                            %%                         .%,                       
#                           %%                        .  .%,                      
#                          .%.                ,%%%/   %,  %%                      
#                          *%   .%%%#       %%  (%   .%.  %%                      
#                          %%   *%    &%%  %% %%     %%   %%                      
#                         %%     %% %%% %% %%%      %%   %%                       
#                        %%       %%%*.#%% %%%%%%%%,    %%                        
#                        #%%%(           %%%           %.                         
#                            %.          (%,          %%                          
#                            %%          ,%           %%                          
#                            /%         #%/           %%                          
#                              ,#######.              &%                          
                                                          