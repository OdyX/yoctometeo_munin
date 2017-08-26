OPTS_64 = -m64
OPTS_GENERIC = -O2 -g 
OPTS_LINK = -lyocto -lm -lpthread -lusb-1.0

ymeteo: main.cpp
	@g++ $(OPTS_GENERIC) -o $@ main.cpp $(OPTS_LINK)

clean:
	@rm -rf ymeteo
