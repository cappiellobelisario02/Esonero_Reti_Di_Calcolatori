#ifndef OPERATIONS_H
#define OPERATIONS_H

#if defined WIN32
	#include <winsock2.h>
#else
	#define closesocket close
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>

#define NO_ERROR 0
#define BUFFERSIZE 512
#define PROTOPORT 60001
#define SERVER_ADDRESS "127.0.0.1"

void clearwinsock();
void errorhandler(char *);
void tokenizer(char * tokens[4], char *);
int checkChar(char *);
int isNumber(char *);

#endif
