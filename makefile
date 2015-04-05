OBJECTS = main.o althelperfunction.o
HEADERS = main.h helperfunction.h

proj4: $(OBJECTS)
	g++ $^ -o proj4

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -f *.o proj4

