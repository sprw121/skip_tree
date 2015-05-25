all:
	gcc -O3 -std=c99 -Werror -Wall skip_tree.c main.c -o main
