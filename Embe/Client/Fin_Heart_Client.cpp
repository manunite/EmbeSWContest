#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int Heart_client(int BPM,int Id)
{
   int   client_socket;

   struct sockaddr_in   server_addr;

   char   buff[BUFF_SIZE+5];

   client_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if(-1 == client_socket)
   {
      printf( "socket 생성 실패\n");
      exit(1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons(4000);
   server_addr.sin_addr.s_addr= inet_addr("192.168.0.17");//linux ip작성
	// sizeof( server_addr))
   if(-1 == connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
   {printf("SSIBAL\n");
      printf("접속 실패n");
      exit(1);
   }
printf("SSIBALLLLL\n");
   printf("recive : %d\n",BPM);
   char str[20] = "H";
   char num[20];
   memset(num,0x00,sizeof(num));
   sprintf(num,"%d",Id);
   sprintf(num,"%s%d",num,BPM);
   strcat(str,num);
   printf("make is %s\n",str);
   write(client_socket, str, strlen(str)+1);      // +1: NULL까지 포함해서 전송
   read (client_socket, buff, BUFF_SIZE);
   printf("%s", buff);
   close(client_socket);
   
   return 0;
}
