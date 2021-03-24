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

#include "network.h"

int make_socket ( uint16_t port, int type, const char * server_IP ){
int sock;
struct hostent * hostinfo = NULL;
struct sockaddr_in server_address;

/* Create the socket. */
sock = socket ( PF_INET, SOCK_STREAM, IPPROTO_TCP );
if (sock < 0){
perror ( "socket" );
exit ( 1 );
}

/* Give the socket a name. */
memset(&server_address, 0, sizeof(server_address));
server_address.sin_family = AF_INET;
server_address.sin_port = htons ( port );

if ( type == SERVER_SOCKET ){
server_address.sin_addr.s_addr = htonl(INADDR_ANY);
if ( bind ( sock, ( struct sockaddr * ) &server_address, sizeof ( server_address ) ) < 0 ){
perror ( "bind" );
exit ( 1 );
}

if ( listen(sock, MAXPENDING) < 0 )
printf("listen() failed");
} else if ( type == CLIENT_SOCKET ){
server_address.sin_addr.s_addr = inet_addr(server_IP);

/* Establish the connection to the server */
if (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
printf("connect() failed\n");
}
return sock;
}

void close_socket (int socket){
	close (socket);
}

char * clean_data( const char * data ){
int count;
char * ptr_data = NULL;
char * result_data = NULL;
char * temp_ptr_data = NULL;
int len;
int write_info, ifone;

ptr_data = strstr (data, DIVIDER);
ptr_data =& ptr_data[strlen(DIVIDER)];

temp_ptr_data = (char *) malloc ( strlen (ptr_data) );
strcpy (temp_ptr_data, ptr_data);
result_data = (char *) strsep (&temp_ptr_data, DIVIDER);
printf ("%i, %i, %s", strlen (data), strlen (ptr_data), result_data);
return result_data;
}

void send_data (int socket, const char * data ){
int sent_bytes, all_sent_bytes;
int err_status;
int sendstrlen;

sendstrlen = strlen ( data );
all_sent_bytes = 0;

sent_bytes = send ( socket, data, sendstrlen, 0 );
all_sent_bytes = all_sent_bytes + sent_bytes;
printf ("\t !!! Sent data: %s --- \n", data);
}
