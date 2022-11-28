/*
 ============================================================================
 Name        : Client_esonero.c
 Author      : Belisario Cappiello
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "headers.h"

int main(){

	#if defined WIN32
		WSADATA wsa_data;
		int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		if (result != NO_ERROR)
		{
			printf("%s", "Start up failed");
			return -1;
		}
		printf("%s", "Start up done correctly\n");
	#endif

	// Socket creation
	int client_socket;
	client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket < NO_ERROR)
	{
		errorhandler("socket creation failed\n");
		closesocket(client_socket);
		clearwinsock();
		return -1;
	}
	printf("%s", "Socket created successfully\n");

	// Creating a struct for the server address
	char * address_to_connect = "127.0.0.1";
	int port = PROTOPORT;
	struct sockaddr_in server_ad;
	memset(&server_ad, 0, sizeof(server_ad));
	server_ad.sin_family = AF_INET;
	server_ad.sin_addr.s_addr = inet_addr(address_to_connect);
	server_ad.sin_port = htons(port);
	printf("%s %s %d\n", "Trying to establish connection with", address_to_connect, port);

	// Establish connection with the server
	int server_connect;
	server_connect = connect(client_socket, (struct sockaddr *)&server_ad, sizeof(server_ad));
	if (server_connect < NO_ERROR)
	{
		errorhandler("Failed to connect to the server\n");
		closesocket(client_socket);
		clearwinsock();
		return -1;
	}
	printf("%s", "Connected with the server\n");

	char * input_string = malloc(BUFFERSIZE);
//	char input_string[BUFFERSIZE];
	memset(input_string, 0, BUFFERSIZE);
//	strcpy(input_string, "- 23 45");
	//checkChar(input_string[0])
	while(1){
		memset(input_string, 0, BUFFERSIZE);
		printf("%s", "The server can do mathematical operations with integer numbers.\nThe options are:\n1. + for addition\n2. - for subtraction\n3. x for multiplication\n4. / for division\n");
		printf("%s\n", "If you want to close the connection, please enter only '=' character");
		printf("%s ", "Insert the operand and two numbers separated by a space\nThe server will send back the result -> ");
		fgets(input_string, BUFFERSIZE-1, stdin); //get the input string with size limit

		int string_len = strlen(input_string);

		// Remove the newline char, if there's one
		if ((string_len > 0) && (input_string[string_len - 1] == '\n'))
		{
			input_string[string_len - 1] = '\0';
		}

		char * string_tokens[4];
		char input_string_cpy[BUFFERSIZE];
		strcpy(input_string_cpy, input_string);
		tokenizer(string_tokens, input_string_cpy);
		int tokens_number = atoi(string_tokens[3]);
		if(tokens_number < 3 || tokens_number > 3 || (!checkChar(string_tokens[0])) || isNumber(string_tokens[1]) || isNumber(string_tokens[2])){
			if(strcmp(string_tokens[0], "=") == 0){
				send(client_socket, input_string, string_len, 0);
				printf("%s\n", "Closing connection with server\n");
				break;
			}
			printf("%s", "You must send to server a valid operation\n");
			Sleep(1500);
			system("CLS");
			continue;
		}else{
			// Send data to the server
			int data_sent;
			data_sent = send(client_socket, input_string, string_len, 0);
			if (data_sent != string_len)
			{
				errorhandler("Different number of bytes has been send to the server\n");
				closesocket(client_socket);
				clearwinsock();
				return -1;
			}
			printf("%s", "Data sent successfully\n");

			// Retrieve data from server
			int bytes_received = 0;
			char server_string[BUFFERSIZE];
			memset(server_string, 0, BUFFERSIZE);
			printf("Data retrieved from server: ");
			bytes_received = recv(client_socket, server_string, BUFFERSIZE - 1, 0);
			if (bytes_received <= 0){
				errorhandler("Retrieve failed or connection closed prematurely\n");
				closesocket(client_socket);
				clearwinsock();
				return -1;
			}
			printf("%s\n", server_string);
			Sleep(3000);
			system("CLS");
			printf("%s%s\n%s%s\n", "Previous operation -> ", input_string, "Result -> ", server_string);
		}
	}

//	free(input_string);
	closesocket(client_socket);
	clearwinsock();
	printf("%s", "\n");
	system("PAUSE");

	return 0;
}


void clearwinsock(){
	#if defined WIN32
		WSACleanup();
	#endif
}

void errorhandler(char * string){
	printf("%s", string);
}

void tokenizer(char * tokens[4], char * string){
	char * operation = string;
	short temp = 0;
	char * token_string;
	token_string = strtok(operation, " ");

	if(strcmp(token_string, "=") == 0){
		tokens[0] = "=";
		tokens[1] = NULL;
		tokens[2] = NULL;
		tokens[3] = "1";
	}else{
		while (token_string != NULL){
			tokens[temp] = token_string;
			temp++;
			token_string = strtok(NULL, " ");
		}
		if(temp == 3){
			int temp_var = temp;
			char str_temp_var[BUFFERSIZE];
			memset(str_temp_var, 0, BUFFERSIZE);
			itoa(temp_var, str_temp_var, 10);
			tokens[temp] = str_temp_var;
		}
	}
}

int checkChar(char * string){
	if(string[0] == '+' || string[0] == '-' || string[0] == 'x' || string[0] == '/'){
		return 1;
	}
	return 0;
}

int isNumber(char * string){
	int length = strlen(string);
	for (int i = 0; i < length; i++)
		if (!isdigit(string[i])){
			printf ("Entered input is not a number\n");
			return 1;;
		}

	return 0;
}
