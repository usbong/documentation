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
  @last updated: 20210324

  Notes:
  1) Execute Commands in sequence:
  1.1) ./server_halimbawa
  1.2) ./client_halimbawa
  
  2) Execute Compile Commands:
  2.1) Server example: gcc network.c server.c -o server_halimbawa
  2.2) Client example: gcc network.c client.c -o client_halimbawa

  3) Add the following "include" files in your .h files
  	#include <netinet/in.h>
	#include <netdb.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>

	#include <stdlib.h>
	#include <stdio.h>
	
	#include <string.h>

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

//added by Mike, 20210324
//TO-DO: -reverify: this
//#include <unistd.h> 

#define ADRESS_PORT 10203
#define ADRESS_IP "127.0.0.1"
#define MAXPENDING 5
//edited by Mike, 20210324
//#define BUFFSIZE 21
//edited by Mike, 20210324
#define MAX_INPUT_TEXT_PER_LINE 10241//100
#define BUFFSIZE MAX_INPUT_TEXT_PER_LINE

#define SERVER_SOCKET 1
#define CLIENT_SOCKET 0

#define TRUE 1
#define FALSE 0
#define START 11
#define DIVIDER ":"

//added by Mike, 20210324; edited by Mike, 20210326
#define MAX_INPUT_LINE_ROW 1 //316
char cImageMapContainer[MAX_INPUT_LINE_ROW][MAX_INPUT_TEXT_PER_LINE];
