INCLUDES = $(shell pkg-config --cflags opencv)
LIBDIRS = $(shell pkg-config --libs opencv)

all:image_convolution

image_convolution:image_convolution.o
	g++ -o image_convolution image_convolution.o $(LIBDIRS) 
image_convolution.o:image_convolution.cpp
	g++ -c image_convolution.cpp $(INCLUDES)
clean:
	rm -f *.o image_convolution
