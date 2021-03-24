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

int accept_connection(int server_socket){
int client_socket; /* Socket descriptor for client */
struct sockaddr_in client_address; /* Client address */
unsigned int client_length; /* Length of client address data structure */

/* Set the size of the in-out parameter */
client_length = sizeof(client_address);

/* Wait for a client to connect */
if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address,
&client_length)) < 0)
printf("accept() failed");

/* client_socket is connected to a client! */
printf("Handling client %s\n", inet_ntoa(client_address.sin_addr));

return client_socket;
}

void handle_client (int client_socket){
char buffer [BUFFSIZE]; /* Buffer for incomming data */
int msg_size; /* Size of received message */
int bytes, all_bytes;

do {
alarm (60);
msg_size = read (client_socket, buffer, BUFFSIZE);
alarm (0);

if ( msg_size <= 0 ){
printf ( " %i ", msg_size );
printf ( "End of data\n" );
}
} while ( msg_size > 0 );
printf ("Data received: %s", buffer);
bytes = 0;
}

int main(){
int clnt_sock;
int sock = make_socket(ADRESS_PORT, SERVER_SOCKET, "none");
clnt_sock = accept_connection (sock);
handle_client(clnt_sock);
close_socket(sock);
}
