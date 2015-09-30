#include <iostream>
#include <cstdlib>

int Heart_client(int BPM,int Id);

//int main(void)
int Heart_Main(int first_BPM,int first_Id)
{
	//srand((unsigned int)time(NULL));
	//Heart_client(rand()%20 + 1,1);
	Heart_client(first_BPM,first_Id);
}
