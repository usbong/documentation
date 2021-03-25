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
  @last updated: 20210325

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

/* //removed by Mike, 20210324; added in network.h
//added by Mike, 20210324
//#define MAX_INPUT_TEXT_PER_LINE 100 //removed by Mike, 20210324 to network.h
#define MAX_INPUT_LINE_ROW 316
char cImageMapContainer[MAX_INPUT_LINE_ROW][MAX_INPUT_TEXT_PER_LINE];
*/

int main(){
	//edited by Mike, 20201119
	//int sock = make_socket(ADRESS_PORT, CLIENT_SOCKET, "10.35.43.41");
	int sock = make_socket(ADRESS_PORT, CLIENT_SOCKET, "127.0.0.1");
	int iTotalMessageSize = 0; //added by Mike, 20210325
	
	//edited by Mike, 20210325
//	read("imageSample.png");
//	read("inputHalimbawa.txt");	
	read("inputImageSample.png");
		
	//edited by Mike, 20210323
	//send_data (sock, "Some data to be sent");
	//edited by Mike, 20210324
//	send_data(sock, "Kumusta!");

	//edited by Mike, 20210324
//	send_data(sock, cImageMapContainer[316]);
//	send_data(sock, cImageMapContainer[300]);

	//edited by Mike, 20210324	
	for (int iCount=0; iCount<MAX_INPUT_LINE_ROW; iCount++) {
		//edited by Mike, 20210325
		//send_data(sock, cImageMapContainer[iCount]);
		if (strcmp(cImageMapContainer[iCount],"")==0) {
			//if blank
		}
		else {
			iTotalMessageSize = iTotalMessageSize + send_data(sock, cImageMapContainer[iCount]);
		}		
	}
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
	//TO-DO: -reverify: cause output .png image file is less than input .png image file
	//file size (input): 25612B
	//file size (output): 16266B
	//iTotalMessageSize output: 16266 = with SERVER's iTotalMessageSize
	printf ("CLIENT iTotalMessageSize: %i", iTotalMessageSize);
	
	close_socket(sock);
}


//added by Mike, 20210324
void read(char *inputFilename) {
	int c;
	FILE *file;
	
	int iCount=0;
	
	//note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
	//I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
	//where memory leaks = not deallocated storage in memory, albeit not used by software application
	//identifying not deallocated storage in memory becomes more difficult with increasing use
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
}