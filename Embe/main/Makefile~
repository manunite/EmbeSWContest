DIR_Client = /home/heo/fairi/Embe/Client
CC = g++ -std=C++11
H_C = $(DIR_Client)/Fin_Heart_Client.o
P_C = $(DIR_Client)/Fin_Pos_Client.o

Final_Main : Final_Main.cpp $(H_C) $(P_C)
	$(CC) Final_Main.cpp -o Final_Main -pthread -lmraa $(H_C) $(P_C) 

clean : 
	rm -rf Final_Main
