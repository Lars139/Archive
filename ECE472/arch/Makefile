CC = /usr/local/common/gcc-4.9.0/bin/gcc 
CFLAGS = -Wall -O0 -std=c99
DEPS = part2.h part3.h part4.h
OBJ = part2.o part3.o part4.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

default: $(OBJ)
	 $(CC) $(CFLAGS) main.c -o hw4 $^

clean:
	rm *.o hw4 


