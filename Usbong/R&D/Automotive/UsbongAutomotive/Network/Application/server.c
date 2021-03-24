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
  
  Recommended Reading:
  1) https://www.php.net/manual/en/function.fopen.php;
  last accessed: 20210324
*/

#include "network.h"

//added by Mike, 20210324
int isFileMessageDone=FALSE;
int iCount=0;

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
	//edited by Mike, 20210324
	char buffer [BUFFSIZE]; /* Buffer for incoming data */
/*	//removed by Mike, 20210324; 
	//segmenation fault error, buffer only 100*100, i.e. 10,000
	char buffer [MAX_INPUT_LINE_ROW*BUFFSIZE]; //Buffer for incoming data
*/
	
	int msg_size; /* Size of received message */
	int bytes, all_bytes;

	do {
		alarm (60);
		//edited by Mike, 20210324
		msg_size = read (client_socket, buffer, BUFFSIZE);
		
/*		//removed by Mike, 20210324; 
		//segmenation fault error, buffer only 100*100, i.e. 10,000		
		msg_size = read (client_socket, buffer, MAX_INPUT_LINE_ROW*BUFFSIZE);
*/		
		alarm (0);
		
		//added by Mike, 20210324
		printf ("Count: %i; ", iCount);
		printf ("Message Size: %i; ", msg_size);
		printf ("Data received: %s", buffer);

		//TO-DO: -reverify: received data due multiple iCount data in one packet
		//iCount not increased due to msg_size > 0
		strcpy(cImageMapContainer[iCount],buffer);		

		printf("\n");
		
		if ( msg_size <= 0 ){
//			printf ( " %i ", msg_size );
			printf ( "End of data\n" );
		}
	} while ( msg_size > 0 );
	
	//added by Mike, 20210324; removed by Mike, 20210324
	//clean_data(buffer);
	
	//added by Mike, 20210324
	//if buffer is ""
	if (strcmp(buffer,"")==0) {
		isFileMessageDone=TRUE;
		return;
	}

/* //removed by Mike, 20210324	
	printf ("Data received: %s", buffer);
	printf("\n"); //added by Mike, 20210324
*/	
	
	//added by Mike, 20210324
	//write(inputFilename, char *cInputTextLine);
	//TO-DO: -update: write instructions after verifying all data received
	//write("outputImageSample.png", buffer);
	
	bytes = 0;
		
	strcpy(buffer, "");	
}

int main(){
	int clnt_sock;
	int sock = make_socket(ADRESS_PORT, SERVER_SOCKET, "none");
	
	//edited by Mike, 20210324
/*	
	clnt_sock = accept_connection (sock);
	handle_client(clnt_sock);
*/
	clnt_sock = accept_connection(sock);

	//edited by Mike, 20210324
//	while (1) {
	while (!isFileMessageDone) {
		handle_client(clnt_sock);
		iCount=iCount+1;
	}		
	
	close_socket(sock);
	
	//added by Mike, 20210324
	return 0;
}

//added by Mike, 20210324
//TO-DO: -add: write whole input cImageMapContainer
void write(char *outputFilename, char *cOutputTextLine) {
	FILE *file;
	
	//note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
	//I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
	//where memory leaks = not deallocated storage in memory, albeit not used by software application
	//identifying not deallocated storage in memory becomes more difficult with increasing use
	char output[MAX_INPUT_TEXT_PER_LINE]; //max size
	
	strcpy(output, "output/");
	strcat(output, outputFilename); //already includes .png, .txt, et cetera
	
	//edited by Mike, 20210324	
//	file = fopen(output, "w"); //.png file
	file = fopen(output, "wb"); //.png file

	//Reference: https://stackoverflow.com/questions/27630855/fwrite-function-in-c;
	//last accessed: 20210324
	//answered by: R Sahu, 20141224T0304
	//edited by: paxdiablo, 20141224T0309
	
//	size_t num = fwrite(array, sizeof(int), arraySize, file);
	int cOutputTextLineSize = sizeof(cOutputTextLine);	
	size_t num = fwrite(cOutputTextLine, sizeof(int), cOutputTextLineSize, file);
	
	if ( num != cOutputTextLineSize )
	{
		//error
	}	
	
	//added by Mike, 20210324
	fclose(file);	
}
