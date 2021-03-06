/*
Copyright (c) 2006 by Svetoslav P. Chukov.
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.2
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover
Texts. A copy of the license is included in the section entitled "GNU
Free Documentation License".
*/

/*
  Copyright 2020~2021 USBONG SOCIAL SYSTEMS, INC. (USBONG)
  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You ' may obtain a copy of the License at
  http://www.apache.org/licenses/LICENSE-2.0
  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, ' WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing ' permissions and limitations under the License.
  
  @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
  @author: SYSON, MICHAEL B.
  @date created: 20201119
  @last updated: 20210429

  Notes:
  1) Execute Commands in sequence:
  1.1) ./server_halimbawa
  1.2) ./client_halimbawa
  
  2) Execute Compile Commands:
  2.1) Server example: g++ network.cpp server.cpp -o server_halimbawa
  2.2) Client example: g++ network.cpp client.cpp -o client_halimbawa

  3) Add the following "include" files in your .h files
  	#include <netinet/in.h>
	#include <netdb.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>

	#include <stdlib.h>
	#include <stdio.h>
	
	#include <string.h>
	
	4) Set "ADDRESS_IP" value to be the computer to connect to from this computer;
	--> Reminder: with local computer, i.e. "127.0.0.1", value is equal with the sender and receiver computers.
	--> where: sender = client; receiver = server
	--> Examples: 
	--> Receiving computer's IP Address: 192.168.1.110
	--> Sending computer's IP Address: 192.168.1.50
	--> We send image file to receiving computer.
	--> We as Client send image file to receiving computer, i.e. Server, at address 192.168.1.110.
	--> Additional Note: We update the receiving computer "ADDRESS_IP" to be the sender's IP address.

  Reference: 
  1) https://www.linuxquestions.org/linux/answers/Programming/BSD_Sockets_programming_in_C_with_examples; 
  last accessed: 20201119; answer by: By nhydra, 2006-11-11T08:44 
*/

#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>

//added by Mike, 20201119
#include <string.h>

//added by Mike, 20210425
#include <unistd.h> //used in cpp

//edited by Mike, 20210428
/*
#define ADRESS_PORT 10203
#define ADRESS_IP "127.0.0.1"
*/
#define ADDRESS_PORT 10203

//added by Mike, 20210428
//We as Client send image file to receiving computer, i.e. Server, at address 192.168.1.110.
//Additional Note: We update the receiving computer "ADDRESS_IP" to be the sender's IP address.
//edited by Mike, 20210429
//#define ADDRESS_IP "192.168.1.110"
#define ADDRESS_IP "127.0.0.1"

#define MAXPENDING 5
//edited by Mike, 20210324
//#define BUFFSIZE 21
//edited by Mike, 20210324
#define MAX_INPUT_TEXT_PER_LINE 10241//100
//edited by Mike, 20210427
//#define BUFFSIZE MAX_INPUT_TEXT_PER_LINE
//TO-DO: -remove this
#define BUFFSIZE 54

#define BUFFER_SIZE 54
#define HEADER_BUFFER_SIZE 54

#define SERVER_SOCKET 1
#define CLIENT_SOCKET 0

#define TRUE 1
#define FALSE 0
#define START 11
#define DIVIDER ":"

//added by Mike, 20210324; edited by Mike, 20210326
#define MAX_INPUT_LINE_ROW 1 //316

/* //removed by Mike, 20210425
//edited by Mike, 20210425
//char cImageMapContainer[MAX_INPUT_LINE_ROW][MAX_INPUT_TEXT_PER_LINE];
//extern keyword for Global variables
extern char cImageMapContainer[MAX_INPUT_LINE_ROW][MAX_INPUT_TEXT_PER_LINE];

//added by Mike, 20210425; edited by Mike, 20210425
//unsigned char * cImageMapContainerData;		
//edited by Mike, 20210425
//char * cImageMapContainerData;		
//extern keyword for Global variables
extern char * cImageMapContainerData;		
*/

//added by Mike, 20210425
int make_socket ( uint16_t port, int type, const char * server_IP );
void close_socket (int socket);
//char * clean_data( unsigned char * data );
//char * clean_data( const char * data );
char * clean_data( char * data );
//int send_data(int socket, unsigned char *data, FILE *file);
//int send_data(int socket, const char *data, FILE *file);
//edited by Mike, 20210426
//int send_data(int socket, char *data);
//int send_data(int socket, unsigned char *data, unsigned int dataSize);
int send_data(int socket, unsigned char *data);
