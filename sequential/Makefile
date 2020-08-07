TARGET = app  # 執行檔名稱app  慣例用target當變數名稱
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) # store all c filenames from dist as a single string
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES)) # convert each filename .c to .o  %對比 取檔案名稱 最後一個SRC_files是來源

#執行檔 ： 參照檔
$(TARGET): $(OBJ_FILES)
	# $^ stands for all of the prerequisites. i.e $(OBJ_FILES)
	# $@ is the current target. i.e $(TARGET)
	gcc $^ -o $@

# tell dependency of each .o file in ./obj with each .c file in ./src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	# $< is the first prerequisite file == %.c    -c compile  $@ == %.o    
	gcc -c $< -o $@

clean:
	rm $(OBJ_DIR)/*.o $(TARGET)