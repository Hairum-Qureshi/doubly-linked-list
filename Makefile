CC = gcc

slist: slist.o
	$(CC) -o slist -g slist.o

slist.o: main.c
	$(CC) -c -g main.c -o slist.o

tests: slist
	@echo "Running test1: adding students, then printing"
	./slist < test1 > test1.stdout
	@echo "Running test2: deleting students from different positions"
	./slist < test2 > test2.stdout
	@echo "Running test3: deleting multiple students, then the rest"
	./slist < test3 > test3.stdout

clean:
	rm -f *.o
