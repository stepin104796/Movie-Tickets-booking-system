# Name of the project
PROJECT_NAME = Movie

# Output directory
BUILD = build

# All source code files
SRC = main.c\
src/movieList.c

# All test source files
#TEST_SRC = src/calculator_operations.c\
#test/test_calculator_operations.c\
#unity/unity.c\

#TEST_OUTPUT = $(BUILD)/Test_$(PROJECT_NAME).out

# All include folders with header files
INC	= -Iinc


# Project Output name
PROJECT_OUTPUT = $(BUILD)/$(PROJECT_NAME).out


# Default target built
$(PROJECT_NAME):all

# Run the target even if the matching name exists
.PHONY: run clean test doc all

all: $(SRC) $(BUILD)
	gcc $(SRC) $(INC) -o $(PROJECT_OUTPUT).out

# Call `make run` to run the application
run:$(PROJECT_NAME)
	./$(PROJECT_OUTPUT).out





# Remove all the built files, invoke by `make clean`
clean:
	rm -rf $(BUILD) 

# Create new build folder if not present
$(BUILD):
	mkdir build
