#include <iostream>

#include "mraa.hpp"
#include <unistd.h>
#include <thread>

using namespace std;

int Pos_main(int _X,int _Y,int _Z,int first_Id);
int Heart_Main(int first_BPM,int first_Id);

class pulseSensor
{
private :
   mraa::Aio* adc_a0 = NULL;               // 심박 센서의 아날로그 값을 읽어 들이기 위한 변수
   volatile unsigned int Signal;            // 심박 센서를 통해 들어오는 raw data를 저장. 매 2ms 마다
   volatile int IBI;                     // beat 사이의 시간 간격을 저장하는 변수. 2mS resolution. 분해능?
   volatile bool Pulse;                  // heartbeat가 감지되면 True. Pulse wave가 high일 때 True / low일 때 false
   volatile int BPM;                     // heart rate(심박수)를 저장하는 변수. 이전 10개의 IBI값의 평균으로부터 구해진 비트 값
   volatile bool QS;                     // BPM을 찾았을 경우 True. 사용자에 의해 리셋 되어야 함
   volatile int rate[10];
   volatile unsigned long sampleCounter;
   volatile unsigned long lastBeatTime;
   volatile int P;
   volatile int T;
   volatile int thresh;
   volatile int amp;
   volatile bool firstBeat;
   volatile bool secondBeat;

   std::thread* t;

public :

   pulseSensor()
   {
      Signal = 0;
      IBI = 600;
      Pulse = false;
      BPM = 0;
      QS = false;
      adc_a0 = new mraa::Aio(0);
      sampleCounter = 0;
      lastBeatTime = 0;
      P = 512;
      T = 512;
      thresh = 525;
      amp = 100;
      firstBeat = true;
      secondBeat = false;
      t = nullptr;
   }

 

   void pulseCheck()
   {
      while(true){
	 //cout <<"rhrhrhr "<<endl;
         this_thread::sleep_for(std::chrono::milliseconds(500));
         Signal = adc_a0->read();
         sampleCounter += 2;
         int N = sampleCounter - lastBeatTime;
         int i = 0;
 
         if(Signal < thresh && N > (IBI/5)*3){
            if(Signal < T){
               T = Signal;
            }
         }

 

         if(Signal > thresh && Signal > P){
               P = Signal;
         }

 

         if (N > 250){

            if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){
               Pulse = true;
               //mraa_gpio_write(d_pin, 1);
               IBI = sampleCounter - lastBeatTime;
               lastBeatTime = sampleCounter;

 
               if(secondBeat){
                  secondBeat = false;
                  for(i=0; i<=9; i++){
                     rate[i] = IBI;
                  }
               }

 

            if(firstBeat){
               firstBeat = false;
               secondBeat = true;
               continue;
            }

            int runningTotal = 0;

 

            for(i=0; i<=8; i++){
               rate[i] = rate[i+1];
               runningTotal += rate[i];
            }

 

            rate[9] = IBI;
            runningTotal += rate[9];
            runningTotal /= 10;
            BPM = 60000/runningTotal;
            QS = true;
            }
         }

 

         if (Signal < thresh && Pulse == true){
            //mraa_gpio_write(d_pin, 0);            // turn off pin 13 LED
            Pulse = false;
            amp = P - T;
            thresh = amp/2 + T;
            P = thresh;
            T = thresh;
         }

 

         if (N > 2500){
            thresh = 512;
            P = 512;
            T = 512;
            lastBeatTime = sampleCounter;
            firstBeat = true;
            secondBeat = false;
         }

         //this_thread::sleep_for(std::chrono::milliseconds(2));
	//cout << N << endl;
	Heart_Main(N,1);
      }

   }

 

   int getBPM()
   {
      return BPM;
   }

 

   int getIBI()
   {
      return IBI;
   }

   bool getQS()
   {
      return QS;
   }

 

   void setQS(bool _QS)
   {
      QS = _QS;
   }

 

   int getSignal()
   {
      return Signal;
   }

   void test()
   {
      while(true){
      //std::cout<< "hi\n";
         pulseCheck();
         this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
   }

 

   void run()
   {
      t = new thread(&pulseSensor::test, this);
      //t = new thread(&pulseSensor::pulseCheck, this);
      t->detach();
   }
};

 

int main() {
   mraa_platform_t platform = mraa_get_platform_type();
   mraa::Gpio* d_pin = NULL;
cout << "A" <<endl;

   pulseSensor* ps = new pulseSensor();
   ps->run();


  /* Code in this loop will run repeatedly

   */

   for (;;) {

     // printf("SIGNAL : %d\n", ps->getSignal());
    //  printf("BPM : %d\n",ps->getBPM());
	//sleep(1);

      if (ps->getQS() == true)
      {
	//Heart_Main(ps->getBPM(),1);     
	printf("B%d\n",ps->getBPM());   // send heart rate with a 'B' prefix
         printf("Q%d\n",ps->getIBI());   // send time between beats with a 'Q' prefix
         ps->setQS(false);                   // reset the Quantified Self flag for next time
      }

 

   }
  return 0;
}

