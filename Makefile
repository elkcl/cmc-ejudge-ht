.PHONY: all clean

CC = gcc
CFLAGS = -O2 -std=gnu2x -Wall -Werror -Wno-pointer-sign -Werror=vla
LD = gcc
LDFLAGS = -lm -ldl -rdynamic
CCMD = $(CC) $(CFLAGS) -c -o $@ $<

all: printrandom

clean:
	rm -f my_utility.o linear.o random.o main.o printrandom

my_utility.o: my_utility.c my_utility.h
	$(CCMD)

linear.o: linear.c random_source.h my_utility.h
	$(CCMD)

random.o: random.c random_source.h my_utility.h
	$(CCMD)

main.o: main.c random_source.h my_utility.h
	$(CCMD)

printrandom: my_utility.o linear.o random.o main.o
	$(LD) $(LDFLAGS) -o $@ $^
