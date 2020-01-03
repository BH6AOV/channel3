all : table.txt

table.txt : objtotable
	./objtotable > table.txt

objtotable : objtotable.c
	gcc -o $@ $^

clean :
	rm -rf *.o *~ objtotable table.txt

