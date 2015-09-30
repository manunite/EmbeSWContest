#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

using namespace std;

int DBcon(int value,int job,int Id,int Pos_X,int Pos_Y,int Pos_Z);

int main( void)
{
   int   server_socket;
   int   client_socket;
   int   client_addr_size;

   struct sockaddr_in   server_addr;
   struct sockaddr_in   client_addr;

   char   buff_rcv[BUFF_SIZE+5];
   char   buff_snd[BUFF_SIZE+5];



   server_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == server_socket)
   {
      printf( "server socket 생성 실패n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons( 4000);
   server_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	//htonl(INADDR_ANY);
   if(-1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
   {
      printf( "bind() 실행 에러n");
      exit( 1);
   }

		

   while( 1)
   {
      if( -1 == listen(server_socket, 5))
      {
         printf( "대기상태 모드 설정 실패n");
         exit( 1);
      }

      client_addr_size  = sizeof(client_addr);
      client_socket     = accept(server_socket, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);

      if ( -1 == client_socket)
      {
         printf( "클라이언트 연결 수락 실패n");
         exit( 1);
      }

      read (client_socket, buff_rcv, BUFF_SIZE);
      cout << buff_rcv << endl;
      
      if(buff_rcv[0] == 'H')      
      {
	cout << "before" << endl;
	//sleep(1);
	cout << "after" << " " <<buff_rcv << endl;
      	printf( "receive: %s\n", buff_rcv);
        char num[20];
	memset(num,0x00,sizeof(num));
	for(int i=2;buff_rcv[i]!=0;i++) num[i-2] = buff_rcv[i];
	printf("make str : %s\n",num);
	cout << num << endl;
	int BPM = atoi(num);
	char temp = buff_rcv[1];
	int Id = temp-48;
	printf("BPM : %d , Id : %d\n",BPM,Id);
      	DBcon(BPM,1,Id,0,0,0);
      }
      else if(buff_rcv[0] == 'P')      
      {
	int PX=0;
	int PY=0;
	int PZ=0;
	cout << "before" << endl;
	cout << "after" << " " <<buff_rcv << endl;
      	printf( "receive: %s\n", buff_rcv);
        char num[100];
	int cnt = 0;
	int j=0;
	memset(num,0x00,sizeof(num));
	//for(int i=1;buff_rcv[i]!=NULL;i++) num[i-2] = buff_rcv[i];
	for(int i=2;buff_rcv[i]!=0;i++)
	{
		int k=0;
		memset(num,0x00,sizeof(num));
		if(buff_rcv[i] == 'J' && cnt == 0)
		{
			for(j=i+1;buff_rcv[j]!='J';j++)
			{
				num[k++] = buff_rcv[j];
			}
			PX = atoi(num);
			i=j-1;cnt++;
		}
		else if(buff_rcv[i] == 'J' && cnt == 1)
		{
			for(j=i+1;buff_rcv[j]!='J';j++)
			{
				num[k++] = buff_rcv[j];
			}
			PY = atoi(num);
			i=j-1; cnt++;
		}
		else if(buff_rcv[i] == 'J' && cnt == 2)
		{
			for(j=i+1;buff_rcv[j]!=0;j++)
			{
				num[k++] = buff_rcv[j];
			}
			PZ = atoi(num);
			i=j; cnt++;
		}
	}
	cnt = 0;
	char temp = buff_rcv[1];
	int Id = temp-48;
	printf("PX : %d , PY : %d , PZ :%d \n",PX,PY,PZ);
      	DBcon(0,2,Id,PX,PY,PZ);
      }

      
	printf("%s\n",inet_ntoa(client_addr.sin_addr));
	printf("%d\n",ntohs(client_addr.sin_port));

      sprintf( buff_snd, "%d : %s", strlen( buff_rcv), buff_rcv);
      write( client_socket, buff_snd, strlen( buff_snd)+1);          // +1: NULL까지 포함해서 전송
      close( client_socket);
   }
}

