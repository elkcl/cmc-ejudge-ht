.PHONY: all clean

CC = gcc
CFLAGS = -O2 --std=gnu2x -Wall -Werror -Wno-pointer-sign -Werror=vla
LD = gcc
LDFLAGS = -lm

all: printrandom

clean:
	rm -f my_utility.o linear.o random.o main.o printrandom

my_utility.o: my_utility.c my_utility.h
	$(CC) $(CFLAGS) -c -o $@ $<

linear.o: linear.c random_source.h my_utility.h
	$(CC) $(CFLAGS) -c -o $@ $<

random.o: random.c random_source.h my_utility.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c random_source.h my_utility.h
	$(CC) $(CFLAGS) -c -o $@ $<

printrandom: my_utility.o linear.o random.o main.o
	$(LD) $(LDFLAGS) -ldl -rdynamic -o $@ $^
