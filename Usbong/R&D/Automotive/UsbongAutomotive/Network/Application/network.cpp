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
  @last updated: 20210427

  Notes:
  1) Execute Commands in sequence:
  1.1) ./server_halimbawa
  1.2) ./client_halimbawa
  
  2) Execute Compile Commands:
  2.1) Server example: g++ network.cpp server.cpp -o server_halimbawa
  2.2) Client example: g++ network.cpp client.cpp -o client_halimbawa

  2.Reminder) "gcc is the GCC compiler-driver for C programs, g++ is the one for C++ programs."
  --> https://stackoverflow.com/questions/27390078/gcc-compiling-c-code-undefined-reference-to-operator-newunsigned-long-lon;
  //last accessed: 20210425
  --> answered by: Deduplicator, 20141209T2244
  --> edited by: Matteo Italia, 20180607T1729
  
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
	//edited by Mike, 20210424
	close (socket);
	//pclose (socket);	
}

//edited by Mike, 20210425
//char * clean_data( const char * data ){
//char * clean_data( unsigned char * data ){	
char * clean_data( char * data ){
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

//edited by Mike, 20210325
//void send_data(int socket, const char * data){
//edited by Mike, 20210326
//int send_data(int socket, const char * data){
//edited by Mike, 20210425
//int send_data(int socket, const char *data, FILE *file){
//edited by Mike, 20210426
//int send_data(int socket, char *data){
int send_data(int socket, unsigned char *data){
//int send_data(int socket, unsigned char *data, unsigned int dataSize){
//int send_data(int socket, unsigned char *data, FILE *file){
	int sent_bytes, all_sent_bytes;
	int err_status;
	int sendstrlen;

	//edited by Mike, 20210426
	//note: binary data
//	sendstrlen = strlen ( data );
	//sendstrlen = strlen ( (char *)data );
		
	all_sent_bytes = 0;
	
	//added by Mike, 20210426
	//note: binary data
/*	printf("sendstrlen: %d\n",sendstrlen);
	printf("data: %s\n",data);
*/
	
	//added by Mike, 20210426
	//Reference: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/;
	//last accessed: 20210425
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	//edited by Mike, 20210425
	unsigned int imageSize;   // = width*height*3

	printf("-----\n");
	printf("@network.cpp\n");
	printf("-----\n");
//header	
printf("header\n");	

for (size_t i = 0 ; i < 54 ; ++i) {
	header[i]=data[i];

	//print hex value
    fprintf(stdout, "0x%02x ", data[i]);
	
    if ((i + 1) % 8 == 0) {
        fputc('\n', stdout);
    }
}		

//TO-DO: -reverify: this with output in client.cpp due to data[0] !='B'
	
//printf("\n>>>> %d\n",strlen((char*)data));	
//printf("\n>>>> %d\n",size_t(header));	
printf("\n>>>> 0x%02x\n",data[0]);
	
	printf("size: %i",sizeof(header));
	
//	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
//	if ( size_t(header)!=54 ){ // If not 54 bytes read : problem	
	//note: small letter "o" in "sizeof"
	if ( sizeof(header)!=54 ){ // If not 54 bytes read : problem			
		printf("Not a correct BMP file!\n");
//		return FALSE;
	}
	else {
		printf("OK! Correct BMP file!\n");
	}
	
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file based on Header!\n");
//		return 0;
	}	
	else {
		printf("OK! Correct BMP file based on Header!\n");
	}
	
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) { imageSize=width*height*3;}// 3 : one byte for each Red, Green and Blue component
	if (dataPos==0) {dataPos=54;} // The BMP header is done that way	
	
	printf("imageSize: %d\n",imageSize);	
	
	sendstrlen = imageSize;
	
//Reference: https://stackoverflow.com/questions/40813492/fread-into-buffer-is-blank-despite-non-empty-file;
//answered by: Iharob Al Asimi, 20161125T2339
//note: we do not use printf and %s with binary
//edited by Mike, 20210426
//for (size_t i = 0 ; i < 256 ; ++i) {
for (size_t i = 54 ; i < 256 ; ++i) {	
	//print hex value
    fprintf(stdout, "0x%02x ", data[i]);
    if ((i + 1) % 8 == 0) {
        fputc('\n', stdout);
    }
}	

	//added by Mike, 20210427
	//-----
	//header
	sent_bytes = send ( socket, header, 54, 0 );
	all_sent_bytes = all_sent_bytes + sent_bytes;
	//-----
	
	//edited by Mike, 20210326
	//-----
	//data
//	sent_bytes = send ( socket, data, sendstrlen, 0 );	
	sent_bytes = send ( socket, data, imageSize, 0 );	
	all_sent_bytes = all_sent_bytes + sent_bytes;
	//-----


	
	//edited by Mike, 20210324
	//printf ("\t !!! Sent data: %s --- \n", data);
	//removed by Mike, 20210426
/*	//data in bytes
	printf ("Data sent: %s", data);	
	printf("\n");
*/
	
	//added by Mike, 20210325; edited by Mike, 20210325
//	printf ("all_sent_bytes: %i\n", all_sent_bytes);
	printf ("Sent bytes for this packet: %i\n", all_sent_bytes);
	
	return all_sent_bytes;
}
