CC = gcc
CFLAGS = -Wall -Wextra -g -I${PGHOME}/include
LIBS = -L${PGHOME}/lib -lpq

ALL: hello simple_query cursor

cursor: cursor.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

cursor.o: cursor.c
	$(CC) $(CFLAGS) -c -o $@ $<

simple_query: simple_query.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

simple_query.o: simple_query.c
	$(CC) $(CFLAGS) -c -o $@ $<

hello: hello.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

hello.o: hello.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f hello hello.o simple_query simple_query.o cursor cursor.o
