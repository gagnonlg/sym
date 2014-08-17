sym: sym.c
	gcc -std=c99 sym.c -o sym

clean:
	rm -f sym
