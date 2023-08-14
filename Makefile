# Variables
CXXFLAGS := -Wall -Werror -Wextra
LIBRARY_NAME := libSockets.a
SRC_DIR := src
BUILD_DIR := build/obj
INCLUDE_DIR := include

# Check if cross compile variable is set
ifeq ($(CROSS_COMPILE),)
	CXX := g++
else
	CXX := $(CROSS_COMPILE)g++
endif

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Targets
$(LIBRARY_NAME): $(OBJ_FILES)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(LIBRARY_NAME)
