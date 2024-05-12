#output folder of compilation
OUT := lib
#lists all .c files in src directory
C_FILES := $(wildcard src/*.c) 
#$(VARIABLE:OLD_SUFFIX=NEW_SUFFIX) changes extension of all .c files to .o
#creates object file names from .c file names and stores
O_FILES =  $(addprefix $(OUT)/, $(notdir $(C_FILES:.c=.o))) 
NAME := $(OUT)/libMUI.a

CC := gcc

PROJECT_INCLUDE_FILES := include

EXTERNAL_INCLUDE_FILES := ../external_libs/include
LIB := ../external_libs/lib
LINKER_FLAGS := -lSDL2


all: $(NAME)
	echo "BUILD SUCCESS"

#compile all c files into object files
$(O_FILES): $(C_FILES)
	$(CC) -c $< -I $(EXTERNAL_INCLUDE_FILES) -I $(PROJECT_INCLUDE_FILES)  -L $(LIB) -w $(LINKER_FLAGS)  -o $@

#build static library. Preqreuisites are .o files and libMui.a is target
$(NAME): $(O_FILES)
	ar rcs $(NAME)  $(O_FILES) 



.PHONY:  all



#clean does not work
# fclean: clean 
# 	rm $(NAME)

# #clean static lib
# re: fclean $(NAME)
#clean all object files
# # clean house
# clean:$(O_FILES)
# 	for 


#targets that do not represent files but are actions that can be performed by make.
#Declaring a target as “.PHONY” informs make that it’s not associated with a file, so make won’t attempt to find a file with that name. 


#This is the target that compiles our executable
# all : $(SRC)
#	$(CC)  -c -I $(EXTERNAL_INCLUDE_FILES) -I $(PROJECT_INCLUDE_FILES)  -L $(LIB) -w $(LINKER_FLAGS)  $(SRC)
# muiLib.a:$(OBJ_FILES)
# 	ar rcs libMUI.a $(OBJ_FILES)
# %.o : %.c
# 	$(CC)  -c -I $(EXTERNAL_INCLUDE_FILES) -I $(PROJECT_INCLUDE_FILES)  -L $(LIB) -w $(LINKER_FLAGS)  $@



# buildStaticLibrary: $(OBJ_FILES)
# g++ -I src/include -L src/lib -o output/app src/app/main.cpp -lmingw32 -lSDL2main -lSDL2
