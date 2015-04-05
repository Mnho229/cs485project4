OBJECTS = main.o helperfunctions.o
HEADERS = helperfunctions.h

sish: $(OBJECTS)
	g++ $^ -o sish

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -f *.o sish

