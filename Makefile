TARGET = ransac

CC = g++ -std=c++11

CFLAGS = -Wno-deprecated-declarations -fpermissive  

all: $(TARGET)

$(TARGET): $(TARGET).cpp $(AUX)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp  
