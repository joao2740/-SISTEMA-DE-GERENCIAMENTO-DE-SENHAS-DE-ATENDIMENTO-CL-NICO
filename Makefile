CC = gcc

sistema_senhas: main.c
	$(CC) main.c -o sistema_senhas

clean:
	rm -f sistema_senhas sistema_senhas.exe
