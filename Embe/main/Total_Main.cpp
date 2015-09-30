#include <iostream>
#include <cstdlib>
int Pos_main(int _X,int _Y,int _Z,int first_Id);
int Heart_Main(int first_BPM,int first_Id);

int main(void)
{
	srand((unsigned int)time(NULL));
	Pos_main(rand()%20 + 1,rand()%200 + 1,rand()%20 + 1,1);
	Heart_Main(rand()%20 + 1,1);
	Pos_main(rand()%20 + 1,rand()%200 + 1,rand()%20 + 1,2);
	Heart_Main(rand()%20 + 1,2);
	Pos_main(rand()%20 + 1,rand()%200 + 1,rand()%20 + 1,3);
	Heart_Main(rand()%20 + 1,3);
	Pos_main(rand()%20 + 1,rand()%200 + 1,rand()%20 + 1,4);
	Heart_Main(rand()%20 + 1,4);
	Pos_main(rand()%20 + 1,rand()%200 + 1,rand()%20 + 1,5);
	Heart_Main(rand()%20 + 1,5);
}
