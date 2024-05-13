#output folder of compilation
OUT := out
#lists all .c files in src directory
CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/MUI/*.cpp)
#$(VARIABLE:OLD_SUFFIX=NEW_SUFFIX) changes extension of all .c files to .o
#creates object file names from .c file names and stores
O_FILES =  $(addprefix $(OUT)/, $(notdir $(C_FILES:.cpp=.o))) 
NAME := $(OUT)/crystal


CXX := g++

PROJECT_INCLUDE_FILES := include

EXTERNAL_INCLUDE_FILES := ../external_libs/include
LIB := ../MUI/lib
EXTERNAL_LIBS := ../external_libs/lib
LINKER_FLAGS := -lSDL2


all: $(NAME)
	

	

#compile all c files into object files
$(O_FILES):

#build exe
$(NAME):  $(CPP_FILES)
	if exist $(OUT)\ (echo lib directory exists ) else (mkdir $(OUT)\)
	$(CXX) $(CPP_FILES)  -I $(EXTERNAL_INCLUDE_FILES) -I $(PROJECT_INCLUDE_FILES)  -L $(LIB) -L $(EXTERNAL_LIBS) -w $(LINKER_FLAGS) -o $(NAME)
	$(NAME).exe



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
