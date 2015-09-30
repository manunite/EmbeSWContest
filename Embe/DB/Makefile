DB_DIR = usr/include/cppconn

libDBCon.a : DBConnect.o
	ar rv libDBCon.a DBConnect.o

DBConnect.o : DBConnect.cpp
	g++ -c DBConnect.cpp -I/$(DB_DIR)

clean :
	rm -rf *.o *.a
