libClient.a : Fin_Pos_Client.o Fin_Heart_Client.o
	ar rv libClients.a Fin_Pos_Client.o Fin_Heart_Client.o

Fin_Pos_Client.o : Fin_Pos_Client.cpp
	g++ -c Fin_Pos_Client.cpp

Fin_Heart_Client.o : Fin_Heart_Client.cpp
	g++ -c Fin_Heart_Client.cpp

clean :
	rm -rf *.o *.a


