build: main.c
	gcc -Wall -g main.c tree.c -o database

clean:
	rm database new_database.txt