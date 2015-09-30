#include <iostream>
#include <cstdlib>

int Position_client(int X,int Y,int Z,int Id);

int Pos_main(int _X,int _Y,int _Z,int first_Id)
{
	//srand((unsigned int)time(NULL));
	//Position_client(rand()%20 + 1,rand()%20 + 1,rand()%20 + 1,1);
	Position_client(_X,_Y,_Z,first_Id);
}
