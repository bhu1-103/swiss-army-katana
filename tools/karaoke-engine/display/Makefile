CC = gcc

CFLAGS = -Wall -O1 -std=c99 -Wno-missing-braces -I/usr/local/include

LDFLAGS = -L/usr/local/lib -lraylib -lm -ldl -lpthread -lX11

TARGET = display

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
