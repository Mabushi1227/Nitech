objects = token-test.o token_510.o

token-test : $(objects)
$(CC) $(objects) -o token-test.exe

.c.o : $< token.h keyword.h
$(CC) -c $< -o $@
