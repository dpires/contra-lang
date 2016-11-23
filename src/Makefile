program_NAME := contra

program_C_SRCS := $(wildcard *.c)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_OBJS := $(program_C_OBJS)

.PHONY: all clean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.c) $(program_OBJS) -o $(program_NAME)

clean:
	$(RM) $(program_NAME)


