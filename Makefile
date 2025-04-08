# === Configuration ===
BUILD_DIR = build
SRC_DIR = src
CXX = g++
CXXFLAGS = -std=c++17 -g

# === Auto-detect source and object files ===
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
EXEC = $(BUILD_DIR)/main.exe

# === Default target ===
.DEFAULT_GOAL := $(EXEC)

# === Link all object files into final executable ===
$(EXEC): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)
	@echo "Build complete!"

# === Compile each .cpp to .o ===
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# === Run the executable ===
run: $(EXEC)
	@echo "Running the program..."
	./$(EXEC) myasm.asm

# === Debug using GDB ===
debug: $(EXEC)
	@echo "Starting debugger..."
	gdb $(EXEC)

# === Clean build files ===
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)/*
	@echo "Clean complete!"

# === Declare non-file targets ===
.PHONY: run clean debug
