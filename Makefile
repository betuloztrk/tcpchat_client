CC = gcc
CFLAGS = -Wall -g 
TARGET = clientapp
PWD = $(shell pwd)

SRCS = 	$(PWD)/clientapp.c\
		$(PWD)/msgprotocol/msgprotocol.c\
		$(PWD)/sendrecv/sendrecv.c\
		$(PWD)/userbase/userbase.c\

OBJS = $(SRCS:.c=.o)

INCLUDES = -I/$(PWD)/msgprotocol/\
	       -I/$(PWD)/sendrecv/\
	       -I/$(PWD)/userbase/
		   

all: clean $(TARGET) 
	@echo  Simple compiler named clientapp has been compiled
	
$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) -lpthread
	
clean:
	$(RM) clientapp *.o *~ $(OBJS)