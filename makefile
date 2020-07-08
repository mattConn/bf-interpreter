bf: *.c
	gcc -std=c11 $^ -o $@

check:
	./bf
