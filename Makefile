OUT := build
#lists all .c files in src directory
SOURCE_DIRECTORY = src
SRC_FILES := $(wildcard ${SOURCE_DIRECTORY}/*.cpp) $(wildcard ${SOURCE_DIRECTORY}/util/*.cpp) $(wildcard ${SOURCE_DIRECTORY}/core/*.cpp)  $(wildcard ${SOURCE_DIRECTORY}/core/geometry/*.cpp) $(wildcard ${SOURCE_DIRECTORY}/ui/*.cpp)
#$(VARIABLE:OLD_SUFFIX=NEW_SUFFIX) changes extension of all .c files to .obj
#creates object file names from .cpp file names and stores them
O_FILES = $(addprefix $(OUT)/,$(notdir $(SRC_FILES:.cpp=.obj)))
NAME := $(OUT)/crystal
CXX := g++
C := gcc

PROJECT_INCLUDE_FILES := include/

EXTERNAL_INCLUDE_FILES := external/include
# LIB := ../MUI/lib
EXTERNAL_LIBS := external/lib

COMPILATION_ARGS = -pedantic -Wall -Wlogical-op -Wmissing-include-dirs -Werror -Wno-unused
CFLAGS := -g -I$(EXTERNAL_INCLUDE_FILES) -I$(PROJECT_INCLUDE_FILES)

LIBS_SRC := -L $(EXTERNAL_LIBS) 

EXEC_SUFFIX := .exe

ifeq ($(OS),Windows_NT)
    # Windows settings
	EXEC_SUFFIX := .exe
    LINKER_FLAGS := -w -lglfw3 -lgdi32  -lopengl32
else
    # Assume Linux settings
    LINKER_FLAGS := -w -lglfw3  -lopengl32 
	EXEC_SUFFIX := 
endif


EXECUTABLE_NAME := $(NAME)$(EXEC_SUFFIX)

FRAG_SHADERS_SRC = $(wildcard shaders/*.frag) 
VERT_SHADERS_SRC = $(wildcard shaders/*.vert)
SHADER_OUT = $(OUT)/shaders
SHADER_COMPILER = glslc
COMPILED_SHADER_EXTENSION = .spirv
SPIRV_FILES = $(addprefix $(SHADER_OUT)/,$(notdir $(VERT_SHADERS_SRC:.vert=$(COMPILED_SHADER_EXTENSION)))) $(addprefix $(SHADER_OUT)/,$(notdir $(FRAG_SHADERS_SRC:.frag=$(COMPILED_SHADER_EXTENSION))))


#build vertex shaders rule	 
vpath %.vert $(dir $(VERT_SHADERS_SRC))

$(SHADER_OUT)/%$(COMPILED_SHADER_EXTENSION): %.vert
	@echo [CREATING] $@ file from vertex shader $<
	$(SHADER_COMPILER) $< -o $@ 

#build fragment shader rule
vpath %.frag $(dir $(FRAG_SHADERS_SRC))

$(SHADER_OUT)/%$(COMPILED_SHADER_EXTENSION): %.frag
	@echo [CREATING] $@ file from fragment shader $<
	$(SHADER_COMPILER) $< -o $@ 




#build objects	
vpath %.cpp $(dir $(SRC_FILES))
$(OUT)/%.obj: %.cpp 
	@echo --------------------------------------- COMPILING CPP TO OBJs ------------------------------------------------------------
	@echo [CREATING] $@ file from $<
	$(CXX) $(CFLAGS) $(COMPILATION_ARGS) -c $< -o $@ 
	
#build executable
$(NAME) : $(O_FILES)
	@echo --------------------------------------- BUILDING EXECUTABLE ------------------------------------------------------------
	$(CXX) -o $(NAME) $(O_FILES) $(LIBS_SRC) $(LINKER_FLAGS)



	
run: build
	@echo --------------------------------------- EXECUTING $(NAME).exe ------------------------------------------------------------
	$(EXECUTABLE_NAME)



build: $(NAME) $(SPIRV_FILES)
	@echo --------------------------------------- BUILD SUCCESSFUL ------------------------------------------------------------



debug:$(NAME)
	gdb $(NAME).exe




.PHONY: run build debug shaders