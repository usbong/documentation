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
  @last updated: 20210428

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

  References: 
  1) https://www.linuxquestions.org/linux/answers/Programming/BSD_Sockets_programming_in_C_with_examples; 
  last accessed: 20201119; answer by: By nhydra, 2006-11-11T08:44 
  
  2) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/;
  last accessed: 20210425
*/


#include "network.h"

/* //removed by Mike, 20210324; added in network.h
//added by Mike, 20210324
//#define MAX_INPUT_TEXT_PER_LINE 100 //removed by Mike, 20210324 to network.h
#define MAX_INPUT_LINE_ROW 316
char cImageMapContainer[MAX_INPUT_LINE_ROW][MAX_INPUT_TEXT_PER_LINE];
*/

//added by Mike, 20210324
//edited by Mike, 20210326
//void read(char *inputFilename) {
FILE* inputReadTextFile(char *inputFilename) {
	//added by Mike, 20210425
	char cImageMapContainer[MAX_INPUT_LINE_ROW][MAX_INPUT_TEXT_PER_LINE];
	
	int c;
	FILE *file;
	
	int iCount=0;
	
	//note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
	//I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
	//where memory leaks = not deallocated storage in memory, albeit not used by software application
	//identifying not deallocated storage in memory becomes more difficult with increasing use
	//added by Mike, 20210326
	//TO-DO: -update: max_size for input filename
	char input[MAX_INPUT_TEXT_PER_LINE]; //max size
	char inputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
	char tempInputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
	
	strcpy(input, "input/");
	strcat(input, inputFilename); //already includes .png, .txt, et cetera

//	file = fopen("input/inputHalimbawa.txt", "r"); //.txt file
	//edited by Mike, 20210324
//	file = fopen(input, "r"); //.txt file
	file = fopen(input, "rb"); //.txt file

	if (file) {				
		//added by Mike, 20210326
		//TO-DO: -reverify: this
		fseek(file, 0, SEEK_END);
		//size = ftell(picture);
		fseek(file, 0, SEEK_SET);
		
//		while ((c = getc(file)) != EOF) {
		while (fgets (input, MAX_INPUT_TEXT_PER_LINE, file)) { //read each line of input
			int iSscanfReturnValue = sscanf(input,"%[^\n]",inputTextLine);
			
//			printf("iSscanfReturnValue: %i",iSscanfReturnValue);
			printf("count %i: ",iCount);						
			
			if (iSscanfReturnValue!=0) { //if text before "\n" found
				//added by Mike, 20210325
				//add new line
				strcat(inputTextLine, "\n");

				//input text per line			
				printf("%s;",inputTextLine);

				strcpy(cImageMapContainer[iCount],inputTextLine);
			}
			//no text before "\n" match found using sscanf(...) command
			//example: only "\n", i.e. new line
			else {
				printf("%s","only new line found");
				strcpy(cImageMapContainer[iCount],"\n");				
			}

			iCount=iCount+1;

/*			
			strcpy(tempInputTextLine,inputTextLine);
	
			//note: add "-1" for empty
			//otherwise, comma as column is skipped
			char *ch = strtok(tempInputTextLine, ",");
*/							
			printf("\n");			
		}
		fclose(file);
	}	
	
	//added by Mike, 20210326
	return file;
}

//added by Mike, 20210326
//TO-DO: -update: this
//Reference: https://www.codeproject.com/Questions/1119117/How-can-read-image-with-fopen-using-C-language;
//last accessed: 20210326
//edited by Mike, 20210425
//FILE* inputReadImageFile(char *inputFilename) {
//edited by Mike, 20210426
//char* inputReadImageFile(char *inputFilename) {
unsigned char* inputReadImageFile(char *inputFilename) {
	
	int c;
	//edited by Mike, 20210326
	FILE *file, fTarget;
	
	int iCount=0;
	
	//note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
	//I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
	//where memory leaks = not deallocated storage in memory, albeit not used by software application
	//identifying not deallocated storage in memory becomes more difficult with increasing use
	//added by Mike, 20210326
	//TO-DO: -update: max_size for input filename
	char cbUpdatedInputFilename[MAX_INPUT_TEXT_PER_LINE]; //max size
	//edited by Mike, 20210326
	//char inputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
	//edited by Mike, 20210326
	//unsigned char inputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size

	//removed by Mike, 20210326
//	char tempInputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
	
	strcpy(cbUpdatedInputFilename, "input/");
	strcat(cbUpdatedInputFilename, inputFilename); //already includes .png, .txt, et cetera

	
	//printf("cbUpdatedInputFilename %s: ",cbUpdatedInputFilename);						
	
//	file = fopen("input/inputHalimbawa.txt", "r"); //.txt file
	//edited by Mike, 20210324
//	file = fopen(input, "r"); //.txt file
	//edited by Mike, 20210326
	file = fopen(cbUpdatedInputFilename, "rb"); //.txt file

//-----	
	//added by Mike, 20210425
	//Reference: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/;
	//last accessed: 20210425
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	//edited by Mike, 20210425
	unsigned int imageSize;   // = width*height*3
	//int imageSize;   // = width*height*3
	
	// Actual RGB data
	//removed by Mike, 20210424 to network.h file
//	unsigned char * data;		
	
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
		printf("Not a correct BMP file!\n");
		return FALSE;
	}
	else {
		printf("OK! Correct BMP file!\n");
	}
	
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file based on Header!\n");
		return 0;
	}	
	else {
		printf("OK! Correct BMP file based on Header!\n");
	}
	
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) { imageSize=width*height*3;}// 3 : one byte for each Red, Green and Blue component
	if (dataPos==0) {dataPos=54;} // The BMP header is done that way	
	
	printf("imageSize: %d\n",imageSize);
	printf("dataPos: %d\n",dataPos);

	// Create a buffer
	//edited by Mike, 20210425
//	data = new unsigned char [imageSize];
	
	//added by Mike, 20210425; edited by Mike, 20210426
//	char * cImageMapContainerData;			
	unsigned char * cImageMapContainerData;			
	
	//edited by Mike, 20210425
//	cImageMapContainerData = new unsigned char [imageSize];
	//edited by Mike, 20210426	
//	cImageMapContainerData = new char [imageSize];
	cImageMapContainerData = new unsigned char [imageSize];
	
	//added by Mike, 20210426
	fseek(file, 0, SEEK_END);
	fseek(file, 0, SEEK_SET);
	
//	strcpy((char *)cImageMapContainerData,"hallo");	
//	printf(">> DITO: cImageMapContainerData: %s\n",cImageMapContainerData);
		
	// Read the actual data from the file into the buffer
	int returnedStatus = fread((char *)cImageMapContainerData,1,imageSize,file);
//	fread(cImageMapContainerData,1,54,file);	

	//added by Mike, 20210426
	printf(">> imageSize: %d\n",imageSize);
	//removed by Mike, 20210426
//	printf(">> cImageMapContainerData: %s\n",cImageMapContainerData);
	
	printf(">> returnedStatus: %d\n",returnedStatus);

/* //removed by Mike, 20210428	
//Reference: https://stackoverflow.com/questions/40813492/fread-into-buffer-is-blank-despite-non-empty-file;
//answered by: Iharob Al Asimi, 20161125T2339
//note: we do not use printf and %s with binary
//update: 256 to actual size
//header	
printf("header\n");	
//for (size_t i = 0 ; i < 256 ; ++i) {
for (size_t i = 0 ; i < 54 ; ++i) {
	//print hex value
    fprintf(stdout, "0x%02x ", header[i]);
    if ((i + 1) % 8 == 0) {
        fputc('\n', stdout);
    }
}	

printf("\ndata\n");
	
//data
//edited by Mike, 20210428
//for (size_t i = 54 ; i < 256 ; ++i) {
for (size_t i = 54 ; i < imageSize ; ++i) {
	
	//print hex value
    fprintf(stdout, "0x%02x ", cImageMapContainerData[i]);
    if ((i + 1) % 8 == 0) {
        fputc('\n', stdout);
    }
}
*/
	
	
	//Everything is in memory now, the file can be closed
	fclose(file);	
//-----		

	//added by Mike, 20210326; edited by Mike, 20210425
	//return file;
	return cImageMapContainerData;
}

int main(){
	//edited by Mike, 20201119
	//int sock = make_socket(ADRESS_PORT, CLIENT_SOCKET, "10.35.43.41");
	//edited by Mike, 20210428
//	int sock = make_socket(ADRESS_PORT, CLIENT_SOCKET, "127.0.0.1");
	int sock = make_socket(ADDRESS_PORT, CLIENT_SOCKET, ADDRESS_IP);
	
	int iTotalMessageSize = 0; //added by Mike, 20210325
	
	//edited by Mike, 20210325
//	read("imageSample.png");
//	read("inputHalimbawa.txt");	
	//edited by Mike, 20210326
//	read("inputImageSample.png");
	//edited by Mike, 20210326
//	FILE *file = inputReadTextFile("inputImageSample.bmp");
//	FILE *file = inputReadImageFile("inputImageSample.png");
	//edited by Mike, 20210425
//	FILE *file = inputReadImageFile("inputImageSample.bmp");
	//edited by Mike, 20210425
//	FILE *file = inputReadImageFile("imageSample.bmp");
	//edited by Mike, 20210426
//	char *cImageMapContainerDataOutput = inputReadImageFile("imageSample.bmp");
	unsigned char *cImageMapContainerDataOutput = inputReadImageFile("imageSample.bmp");
			
	//edited by Mike, 20210323
	//send_data (sock, "Some data to be sent");
	//edited by Mike, 20210324
//	send_data(sock, "Kumusta!");

	//edited by Mike, 20210324
//	send_data(sock, cImageMapContainer[316]);
//	send_data(sock, cImageMapContainer[300]);

/*	//edited by Mike, 20210425	
	//edited by Mike, 20210324
	for (int iCount=0; iCount<MAX_INPUT_LINE_ROW; iCount++) {
		iTotalMessageSize = iTotalMessageSize + send_data(sock, cImageMapContainer[iCount], file);					
	}
*/	
	//edited by Mike, 20210426
//	iTotalMessageSize = iTotalMessageSize + send_data(sock, cImageMapContainerDataOutput);					
	iTotalMessageSize = iTotalMessageSize + send_data(sock, cImageMapContainerDataOutput);					

	
	//added by Mike, 20210325
//	send_data(sock,"\0");

//	send_data(sock, cImageMapContainer[0]);
	
/*	//removed by Mike, 20210324; segmentation fault error
	char cDataToSend[MAX_INPUT_LINE_ROW*BUFFSIZE];
	strcpy(cDataToSend, "");

	for (int iCount=0; iCount<MAX_INPUT_LINE_ROW; iCount++) {
		strcat(cDataToSend[iCount], cImageMapContainer[iCount]);
	}	
	send_data(sock, cDataToSend);
*/
	//edited by Mike, 20210428
	//output .png image file is less than input .png image file
	//reminder: compression technique is used with .png files
	//file size (input): 25612B
	//file size (output): 16266B
	//iTotalMessageSize output: 16266 = with SERVER's iTotalMessageSize
	printf ("CLIENT iTotalMessageSize: %i\n", iTotalMessageSize);
	
	close_socket(sock);
}


