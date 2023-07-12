# Variables
CXX := g++
CXXFLAGS := -Wall -Werror -Wextra
LIBRARY_NAME := libSockets.a
SRC_DIR := src
INCLUDE_DIR := include

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(SRC_FILES))

# Targets
$(LIBRARY_NAME): $(OBJ_FILES)
	ar rcs $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(LIBRARY_NAME)
