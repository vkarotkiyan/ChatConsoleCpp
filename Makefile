TARGET = ChatConsoleCpp
PREFIX = /usr/local/bin

ChatConsoleCpp: main.cpp misc.h chat.h user.h message.h misc.cpp chat.cpp user.cpp message.cpp
	 g++ -std=c++17 -o $(TARGET) main.cpp misc.h chat.h user.h message.h misc.cpp chat.cpp user.cpp message.cpp

clean:
	rm -rf *.o *.a

install:
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
