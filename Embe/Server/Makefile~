DIR_DB = home/heo/fairi/Embe/DB

Fin_Server.o : Fin_Server.cpp
	g++ Fin_Server.cpp -o Fin_Server -L/$(DIR_DB) -L/usr/lib -lDBCon -lmysqlcppconn

clean : 
	rm -rf *.o *.a Fin_Server
