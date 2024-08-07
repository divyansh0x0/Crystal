OUT := build
#lists all .c files in src directory
SRC_FILES := $(wildcard crystal/src/*.cpp) $(wildcard crystal/src/util/*.cpp) $(wildcard crystal/src/core/*.cpp)  $(wildcard crystal/src/core/geometry/*.cpp) $(wildcard crystal/src/ui/*.cpp)
#$(VARIABLE:OLD_SUFFIX=NEW_SUFFIX) changes extension of all .c files to .obj
#creates object file names from .cpp file names and stores them
O_FILES = $(addprefix $(OUT)/,$(notdir $(SRC_FILES:.cpp=.obj)))
NAME := $(OUT)/crystal
CXX := g++
C := gcc

PROJECT_INCLUDE_FILES := crystal/include/

EXTERNAL_INCLUDE_FILES := include
# LIB := ../MUI/lib
EXTERNAL_LIBS := lib

COMPILATION_ARGS = -pedantic -Wall -Wlogical-op -Wmissing-include-dirs -Werror -Wno-unused
CFLAGS := -g -I$(EXTERNAL_INCLUDE_FILES) -I$(PROJECT_INCLUDE_FILES)

LIBS_SRC := -L $(EXTERNAL_LIBS) 

ifeq ($(OS),Windows_NT)
    # Windows settings
    LINKER_FLAGS := -w -lglfw3 -lgdi32  -lopengl32 -lfreeglut
else
    # Assume Linux settings
    LINKER_FLAGS := -w -lglfw3  -lopengl32 -lfreeglut
endif



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



build: $(NAME) $(SPIRV_FILES)
	@echo --------------------------------------- EXECUTING $(NAME).exe ------------------------------------------------------------
	$(NAME).exe

	


#build objects	
vpath %.cpp $(dir $(SRC_FILES))
$(OUT)/%.obj: %.cpp 
	@echo --------------------------------------- COMPILING CPP TO OBJs ------------------------------------------------------------
	@echo [CREATING] $@ file from $<
	$(CXX) $(CFLAGS) $(COMPILATION_ARGS) -c $< -o $@ 
	


#build exe
$(NAME) : $(O_FILES)
	@echo --------------------------------------- BUILDING EXECUTABLE ------------------------------------------------------------
# @echo $(CXX) -o $(NAME) $(addprefix $(OUT)/,$(notdir $(O_FILES))) $(LIBS_SRC) $(LINKER_FLAGS)
	$(CXX) -o $(NAME) $(O_FILES) $(LIBS_SRC) $(LINKER_FLAGS)


debug:$(NAME)
	gdb $(NAME).exe




.PHONY:  build, debug, shaders