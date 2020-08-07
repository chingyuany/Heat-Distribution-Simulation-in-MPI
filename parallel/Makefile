TARGET = app
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(TARGET): $(OBJ_FILES)
	mpicc $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	mpicc -c $< -o $@

$(OBJ_DIR)/square.o: $(SRC_DIR)/square.c
	gcc -c $< -o $@

$(OBJ_DIR)/printcolors.o: $(SRC_DIR)/printcolors.c
	gcc -c $< -o $@

clean:
	rm $(OBJ_DIR)/*.o $(TARGET)