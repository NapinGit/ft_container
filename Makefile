NAME1	=	Container_test
NAME2	=	Container_test_std
CC = clang++
OBJ_DIR = obj/
#-Werror -Wextra -Wall -std=c++98
FLAGS	= -Werror -Wextra -Wall -std=c++98
OBJ		=  main.cpp
OBJ2	=  mainStd.cpp
SUPP_DIR = rm -rf $(OBJ_DIR)
SUPP_NAME = rm -f $(NAME1) $(NAME2)

OBJ_PREFIX =	$(addprefix $(OBJ_DIR),$(OBJ:%.cpp=%.o))
OBJ_PREFIX2 =	$(addprefix $(OBJ_DIR),$(OBJ2:%.cpp=%.o))

all :	$(NAME1) $(NAME2)



$(NAME1) : $(INCLUDE) $(OBJ_PREFIX)
	$(CC) $(FLAGS) $(OBJ_PREFIX) -o $(NAME1)

$(NAME2) : $(INCLUDE) $(OBJ_PREFIX2)
	$(CC) $(FLAGS) $(OBJ_PREFIX2) -o $(NAME2)

$(OBJ_DIR)%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(SUPP_DIR)

fclean : clean
	$(SUPP_NAME)

re : fclean all