CC = clang
LD = clang
CC_FLAGS = -O2 -Wall -Wextra -c -Iqr-Code-generator/c
LD_FLAGS = -Wall -Wextra -lpng
OBJ = obj
LIB_SRC = qr-Code-generator/c/qrcodegen.c
LIB_OBJ = $(OBJ)/qrcodegen.o

qr-gen: $(OBJ) $(OBJ)/qr-gen.o $(LIB_OBJ)
	$(CC) $(LD_FLAGS) $(OBJ)/qr-gen.o $(LIB_OBJ) -o qr-gen

$(OBJ):
	mkdir $(OBJ)

$(OBJ)/qr-gen.o: qr-gen.c
	$(CC) $(CC_FLAGS) qr-gen.c -o $(OBJ)/qr-gen.o

$(LIB_OBJ): $(LIB_SRC)
	$(CC) $(CC_FLAGS) $(LIB_SRC) -o $(LIB_OBJ)

.PHONY: clean
clean:
	rm -rf $(OBJ) qr-gen