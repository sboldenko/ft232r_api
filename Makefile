include Rules.make

SRC=sources/main.c
SRC+=sources/ft232_api.c
APP = ft232_api

all:
	$(CC) $(SRC) -o $(APP) $(CFLAGS)

clean:
	-rm -f *.o ; rm $(APP)
