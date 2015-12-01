/*
    Simple udp client
    Silver Moon (m00n.silv3r@gmail.com)
*/
/*
#include<stdio.h>
#include<winsock2.h>
#include <thread>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
 
#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data


void ReceiveThread(int s) {
  struct sockaddr_in si_other;
  int slen=sizeof(si_other);
  char buf[BUFLEN];

  while(1) {
    if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
      {
	printf("recvfrom() failed with error code : %d" , WSAGetLastError());
	system("PAUSE");
	exit(EXIT_FAILURE);
      }
         
    puts(buf);
    fflush(stdout);
  }
}

int main(void)
{
  struct sockaddr_in si_other;
  int s, slen=sizeof(si_other);
  char buf[BUFLEN];
  char message[BUFLEN];
  WSADATA wsa;

  
    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d\n",WSAGetLastError());
		system("PAUSE");
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");
     
    //create socket
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        printf("socket() failed with error code : %d" , WSAGetLastError());
		system("PAUSE");
        exit(EXIT_FAILURE);
    }
     
    //setup address structure
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);


    std::thread recthr(ReceiveThread, s);

    //start communication
    while(1)
    {
        printf("Enter message : ");
        gets(message);
         
        //send the message
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d" , WSAGetLastError());
			system("PAUSE");
            exit(EXIT_FAILURE);
        }         
    }
 
    closesocket(s);
    WSACleanup();
	system("PAUSE");
    return 0;
}
*/