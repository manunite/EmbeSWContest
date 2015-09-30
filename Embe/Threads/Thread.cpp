#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int Pos_main(int _X,int _Y,int _Z,int first_Id);
int Heart_Main(int first_BPM,int first_Id);

class test

{

private :

   int a = 1;
   thread *t;

 

public:

   test()

   {

//      cout << "init" << "\n";

//      cout <<"a = " <<a << "\n";

      t = nullptr;

   }

 

   void aaa()

   {

      while (true) {

         a++;

         cout << "\na = " << a << "Thread" << "\n";
	 srand((unsigned int)time(NULL));
	Pos_main(rand()%20 + 1,rand()%20 + 1,rand()%20 + 1,1);
	Heart_Main(rand()%20 + 1,1);
	Pos_main(rand()%20 + 1,rand()%20 + 1,rand()%20 + 1,2);
	Heart_Main(rand()%20 + 1,2);
	Pos_main(rand()%20 + 1,rand()%20 + 1,rand()%20 + 1,3);
	Heart_Main(rand()%20 + 1,3);
	Pos_main(rand()%20 + 1,rand()%20 + 1,rand()%20 + 1,4);
	Heart_Main(rand()%20 + 1,4);
	Pos_main(rand()%20 + 1,rand()%20 + 1,rand()%20 + 1,5);
	Heart_Main(rand()%20 + 1,5);
	
	sleep(1);
	


         this_thread::sleep_for(std::chrono::seconds(1));

 

      }

   }

 

   void run()
   {
	//cout <<"aaaaa";

      t = new thread(&test::aaa, this);


      t->detach();

   }

};

 

int main() {

test* a = new test();
a->run();
   for (;;) {

 //cout << "A";

  }

 

  return 0;

}

