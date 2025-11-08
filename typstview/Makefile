CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.0)

TARGET = typstview
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(GTK_CFLAGS) -o $(TARGET) $(SRC) $(GTK_LIBS)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -D $(TARGET) $(DESTDIR)/usr/local/bin/$(TARGET)

.PHONY: all clean install
