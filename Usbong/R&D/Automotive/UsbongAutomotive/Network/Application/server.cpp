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
  
  Recommended Reading:
  1) https://www.php.net/manual/en/function.fopen.php;
  last accessed: 20210324
  
  2) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/;
  last accessed: 20210425  
*/

//TO-DO: -execute code refactoring, i.e. delete excess instructions, et cetera

#include "network.h"

//added by Mike, 20210324
int isFileMessageDone=FALSE;
int iCount=0;
//added by Mike, 20210325
int iTotalMessageSize=0;

//added by Mike, 20210324; edited by Mike, 20210326
//void write(char *outputFilename, char *cOutputTextLine) {
//void writeOutputImageFile(char *outputFilename, unsigned char *cOutputTextLine) {
//edited by Mike, 20210427
//void writeOutputImageFile(char *outputFilename, char *cOutputTextLine) {
void writeOutputImageFile(char *outputFilename, unsigned char *cOutputTextLine) {

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
/*	//removed by Mike, 20210427
//note: byte, instead of String of characters
		printf("\n");
		printf("\n");
		printf("dito: %s",cOutputTextLine);
		printf("\n");
*/	
	
//	size_t num = fwrite(array, sizeof(int), arraySize, file);
	int cOutputTextLineSize = sizeof(cOutputTextLine);	
	
//	printf("cOutputTextLineSize: %i",cOutputTextLineSize); 
//	printf("size of char: %li",sizeof(char)); 

	//edited by Mike, 20210325
	//TO-DO: -reverify: output size
	//TO-DO: -reverify: using .txt file, instead of .png file for input and output
//	size_t num = fwrite(cOutputTextLine, sizeof(int), cOutputTextLineSize, file);
//	size_t num = fwrite(cOutputTextLine, sizeof(char), BUFFSIZE*cOutputTextLineSize, file);
//	size_t num = fwrite(cOutputTextLine, cOutputTextLineSize, cOutputTextLineSize*iTotalMessageSize, file);
//	size_t num = fwrite(cOutputTextLine, cOutputTextLineSize, 3584, file);
//	size_t num = fwrite(cOutputTextLine, sizeof(char), iTotalMessageSize, file);
	size_t num = fwrite(cOutputTextLine, 1, iTotalMessageSize, file);
	
	//added by Mike, 20210325
	//outputs: 
	//num=16266
	//iTotalMessageSize=16266
	
/*	//removed by Mike, 20210427	
	printf("\nnum: %zu",num);
*/
	
	printf("\niTotalMessageSize: %i\n",iTotalMessageSize);

/*	//removed by Mike, 20210427
//	if ( num != cOutputTextLineSize*iTotalMessageSize )
//	if ( num != sizeof(char)*ciTotalMessageSize )
	if ( num != iTotalMessageSize )
	{
		//error
		printf("Error: num != cOutputTextLineSize*iTotalMessageSize");
	}
*/
	
	//added by Mike, 20210324
	fclose(file);	
}

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

//added by Mike, 20210426
void handle_clientPrev (int client_socket){
	//edited by Mike, 20210324
//	char buffer [BUFFSIZE]; /* Buffer for incoming data */
	char buffer [BUFFSIZE]; /* Buffer for incoming data */
	
/*	//removed by Mike, 20210324; 
	//segmenation fault error, buffer only 100*100, i.e. 10,000
	char buffer [MAX_INPUT_LINE_ROW*BUFFSIZE]; //Buffer for incoming data
*/
	
	int msg_size; /* Size of received message */
	int bytes, all_bytes;
	
	//added by Mike, 20210426
	char *cImageMapContainerDataOutput;

	do {
		//added by Mike, 20210325
		bytes = 0;		
//		strcpy(buffer, clean_data(buffer));
		//we execute zero-initialize to char array container
		//due to copied string may be 
		//shorter than the previous one, et cetera
		memset(buffer, '\0', BUFFSIZE);
		strcpy(buffer, "");	
		
		alarm (60);
		//edited by Mike, 20210324
		msg_size = read (client_socket, buffer, BUFFSIZE);
		
/*		//removed by Mike, 20210324; 
		//segmenation fault error, buffer only 100*100, i.e. 10,000		
		msg_size = read (client_socket, buffer, MAX_INPUT_LINE_ROW*BUFFSIZE);
*/		
		alarm (0);
		
		if ( msg_size <= 0 ){
//			printf ( " %i ", msg_size );
			printf ( "End of data\n" );
		}
		else {
			//added by Mike, 20210324
			printf ("Count: %i; ", iCount);
			printf ("Message Size: %i; ", msg_size);
			printf ("Data received: %s", buffer);

			iTotalMessageSize=iTotalMessageSize+msg_size;
			
			//TO-DO: -reverify: received data due multiple iCount data in one packet
			//iCount not increased due to msg_size > 0
			//edited by Mike, 20210325
			//strcpy(cImageMapContainer[iCount],buffer);	
			//edited by Mike, 20210426
//			strcat(cImageMapContainer[iCount],buffer);
			strcat(cImageMapContainerDataOutput,buffer);

			printf("\n");
		}		
	} while ( msg_size > 0 );
	
	//added by Mike, 20210324; removed by Mike, 20210324
	//clean_data(buffer);

/* //removed by Mike, 20210325
	//added by Mike, 20210324
	//if buffer is ""
	if (strcmp(buffer,"")==0) {
		
		printf ("Data received: %s", cImageMapContainer[0]);
		
		isFileMessageDone=TRUE;
		return;
	}
*/
	
/* //removed by Mike, 20210324	
	printf ("Data received: %s", buffer);
	printf("\n"); //added by Mike, 20210324
*/	
	
	//added by Mike, 20210324
	//write(inputFilename, char *cInputTextLine);
	//TO-DO: -update: write instructions after verifying all data received
	//write("outputImageSample.png", buffer);
	
	printf("\n"); //added by Mike, 20210324
	//edited by Mike, 20210426
//	printf ("All data received: %s", cImageMapContainer[0]);
	printf ("All data received: %s", cImageMapContainerDataOutput);
		
	//added by Mike, 20210325
	printf("\n");
	printf ("SERVER iTotalMessageSize: %i", iTotalMessageSize);
	
	//edited by Mike, 20210325; edited by Mike, 2021326
//	write("outputImageSample.png", cImageMapContainer[0]);
//	fwrite("outputImageSample.png", cImageMapContainer[0]);
//	write("outputHalimbawa.txt", cImageMapContainer[0]);

	//edited by Mike, 20210326; edited by Mike, 20210425
	//edited by Mike, 20210426
//	write("outputImageSample.bmp", cImageMapContainer[0]);
	//edited by Mike, 20210426
//	write("outputImageSample.bmp", cImageMapContainerDataOutput);
	//removed by Mike, 202104027
	//writeOutputImageFile("outputImageSample.bmp", cImageMapContainerDataOutput);
			
//	fwrite(cImageMapContainer[0], 1, iTotalMessageSize, "outputImageSample.bmp");		
//	write("outputImageSample.png", cImageMapContainer[0]);

	
	bytes = 0;
		
	strcpy(buffer, "");	
	
	isFileMessageDone=TRUE;
}

//added by Mike, 20210427
void handle_client (int client_socket){
	//edited by Mike, 20210427
	//char buffer [BUFFSIZE]; // Buffer for incoming data	
//	unsigned char headerBuffer [HEADER_BUFFER_SIZE]; // Buffer for incoming data		
	//BUFFER_SIZE=54 bytes
	unsigned char buffer [BUFFER_SIZE]; // Buffer for incoming data		
	
	int msg_size; // Size of received message
	int bytes, all_bytes;

	//edited by Mike, 20210427
//	char *cImageMapContainerDataOutput;
	unsigned char *cImageMapContainerDataOutput;

	//added by Mike, 20210427
	int iByteCount=0;

	printf("Header\n");
	printf("Reading received byte...\n");
	
	do {
		bytes = 0;		
//		strcpy(buffer, clean_data(buffer));
		//we execute zero-initialize to char array container
		//due to copied string may be 
		//shorter than the previous one, et cetera
//		memset(headerBuffer, '\0', HEADER_BUFFER_SIZE);
		memset(buffer, '\0', BUFFER_SIZE);
		
		//removed by Mike, 20210427
//		strcpy(buffer, "");	
		
		alarm (60);
		//edited by Mike, 20210324; edited by Mike, 20210427
//		msg_size = read (client_socket, headerBuffer, HEADER_BUFFER_SIZE);
		msg_size = read (client_socket, buffer, BUFFER_SIZE);
		
/*		//removed by Mike, 20210324; 
		//segmenation fault error, buffer only 100*100, i.e. 10,000		
		msg_size = read (client_socket, buffer, MAX_INPUT_LINE_ROW*BUFFSIZE);
*/		
		alarm (0);
		
		if ( msg_size <= 0 ){
//			printf ( " %i ", msg_size );
			printf ( "End of data\n" );
		}
		else {
/*			//removed by Mike, 20210427
//note: buffer value is of type byte
			//added by Mike, 20210324
			printf ("Count: %i; ", iCount);
			printf ("Message Size: %i; ", msg_size);
			printf ("Data received: %s", buffer);
*/			
			iTotalMessageSize=iTotalMessageSize+msg_size;
			
			//TO-DO: -reverify: received data due multiple iCount data in one packet
			//iCount not increased due to msg_size > 0
			//edited by Mike, 20210325
			//strcpy(cImageMapContainer[iCount],buffer);	
			//edited by Mike, 20210426
//			strcat(cImageMapContainer[iCount],buffer);
			//removed by Mike, 20210427			
//			strcat(cImageMapContainerDataOutput,buffer);
			
			//printf("sizeof headerBuffer: %i\n",sizeof(headerBuffer));

			unsigned int imageSize;   // = width*height*3

			//added by Mike, 20210428
			//TO-DO: -reverify: input imageSample.bmp's image size: 78,538Bytes; output image size: 78,400Bytes
			//note: sent data only 78,400Bytes
			
			//edited by Mike, 20210427
			//init cImageMapContainerDataOutput 
			if (iByteCount==0) {
				//removed by Mike, 20210428
//				unsigned char buffer[54]; // Each BMP file begins by a 54-bytes header
				unsigned int dataPos;     // Position in the file where the actual data begins
				unsigned int width, height;
//				unsigned int imageSize;   // = width*height*3
				
				dataPos    = *(int*)&(buffer[0x0A]);
				imageSize  = *(int*)&(buffer[0x22]);

								printf("imageSize: %i\n",imageSize);

				width      = *(int*)&(buffer[0x12]);
				height     = *(int*)&(buffer[0x16]);				
				// Some BMP files are misformatted, guess missing information
				if (imageSize==0) { imageSize=width*height*3;}// 3 : one byte for each Red, Green and Blue component			
				
				cImageMapContainerDataOutput = new unsigned char [imageSize];					
				
				printf(">>imageSize: %i\n",imageSize);
				
			}			
			
//			cImageMapContainerDataOutput=headerBuffer;		
			//cImageMapContainerDataOutput[iByteCount]=buffer[iByteCount];
//			cImageMapContainerDataOutput=buffer;		
//			strcat(cImageMapContainerDataOutput,buffer);
			int iSizeOfBuffer=sizeof(buffer);
/*		//removed by Mike, 20210428
			printf("iSizeOfBuffer: %i\n",iSizeOfBuffer);
			printf("iByteCount: %i\n",iByteCount);
//			printf("imageSize: %i\n",imageSize);
*/
			
			size_t iBufferCount=0;
			for (iBufferCount = 0; iBufferCount < iSizeOfBuffer; iBufferCount++) {
//				printf("buffer count i: %i; 0x%02x\n",i,buffer[i]);
				
				//edited by Mike, 20210428
				int iTempImageMapContainerDataOutputPos=iByteCount+iBufferCount;
				
				int iImageMapContainerDataOutputPos=iTempImageMapContainerDataOutputPos;
				
				if (iTempImageMapContainerDataOutputPos>=imageSize) {				
					iImageMapContainerDataOutputPos=iByteCount+(iTempImageMapContainerDataOutputPos-imageSize);
				}
//				printf("iImageMapContainerDataOutputPos: %i",iImageMapContainerDataOutputPos);
				
/*				
				//if negative due 
				if ((iImageMapContainerDataOutputPos<0) {									
					break;
				}
*/					
/*		
				if ((iByteCount+iBufferCount)<imageSize) {									
*/		
//					cImageMapContainerDataOutput[iByteCount+iBufferCount]=buffer[iBufferCount];
					cImageMapContainerDataOutput[iImageMapContainerDataOutputPos]=buffer[iBufferCount];

/* //removed by Mike, 20210428				
					fprintf(stdout, "0x%02x ", buffer[iBufferCount]);

					if ((iBufferCount + 1) % 8 == 0) {
						fputc('\n', stdout);
					}				
*/				
				
/*				}
				else {
					break;
				}
*/		
			}	
			iByteCount=iByteCount+iBufferCount;//iSizeOfBuffer;
			
/*	//removed by Mike, 20210428
printf("\n>>iByteCount: %i\n",iByteCount);
*/			
			
//			break;
			
/*	//removed by Mike, 20210427		
	//print hex value
			if (iByteCount<54) {
    			fprintf(stdout, "0x%02x ", cImageMapContainerDataOutput[iByteCount]);
				printf("iByteCount: %i",iByteCount);				
				break;
			}
				
iByteCount=iByteCount+1;
*/
			
/*			
for (size_t i = 0 ; i < 54 ; ++i) {
	cImageMapContainerDataOutput[i]=buffer[i];
}				
*/
//			printf("iTotalMessageSize: %i\n",iTotalMessageSize);

			//removed by Mike, 20210427
			//printf("\n");
		}		
	} while ( msg_size > 0 );
	
	printf("\n"); //added by Mike, 20210324
	//edited by Mike, 20210427	
/*	printf ("All data received: %s", cImageMapContainerDataOutput);
*/
	
fprintf(stdout, "DITO 0x%02x \n", cImageMapContainerDataOutput[0]);
fprintf(stdout, "sizeof received data: %i\n", sizeof(cImageMapContainerDataOutput));

	
	//added by Mike, 20210427
	//----------	
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
	printf("@server.cpp\n");
	printf("-----\n");
//header	
printf("header\n");	

//edited by Mike, 20210427
//for (size_t i = 0 ; i < 54 ; ++i) {
for (int i = 0 ; i < 54 ; ++i) {
	header[i]=cImageMapContainerDataOutput[i];

	//print hex value
    fprintf(stdout, "0x%02x ", cImageMapContainerDataOutput[i]);
	
    if ((i + 1) % 8 == 0) {
        fputc('\n', stdout);
    }
}		
	
	
	
//printf("\n>>>> %d\n",strlen((char*)data));	
//printf("\n>>>> %d\n",size_t(header));	
printf("\n>>>> 0x%02x\n",cImageMapContainerDataOutput[0]);
	
	
	printf("header size: %i\n",sizeof(header));
	
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

	//removed by Mike, 20210427
//	sendstrlen = imageSize;

	
//Reference: https://stackoverflow.com/questions/40813492/fread-into-buffer-is-blank-despite-non-empty-file;
//answered by: Iharob Al Asimi, 20161125T2339
//note: we do not use printf and %s with binary

//edited by Mike, 20210427
/*	
//for (size_t i = 0 ; i < 256 ; ++i) {
for (size_t i = 54 ; i < 256 ; ++i) {	
	//print hex value
    fprintf(stdout, "0x%02x ", cImageMapContainerDataOutput[i]);
    if ((i + 1) % 8 == 0) {
    }
}	
*/
	
	
/* //removed by Mike, 20210428				
printf(">>Message Body");
for (size_t i = 0 ; i < imageSize ; ++i) {	
	//print hex value
    fprintf(stdout, "0x%02x ", cImageMapContainerDataOutput[i]);
    if ((i + 1) % 8 == 0) {
        fputc('\n', stdout);
    }	
}	
*/
	
	
	
	//----------	
	
	
	//added by Mike, 20210325
	printf("\n");
	printf ("SERVER iTotalMessageSize: %i", iTotalMessageSize);
	
	//added by Mike, 20210427
	writeOutputImageFile("outputImageSample.bmp", cImageMapContainerDataOutput);
/*
	for (size_t i = 0 ; i < 256 ; ++i) {		
		writeOutputImageFile("outputImageSample.bmp", cImageMapContainerDataOutput[i]);
	}
*/	
	bytes = 0;

	//removed by Mike, 20210427
//	strcpy(buffer, "");	
	
	isFileMessageDone=TRUE;
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

	//added by Mike, 20210325; removed by Mike, 20210426
	//strcpy(cImageMapContainer[0],"");		
	
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


