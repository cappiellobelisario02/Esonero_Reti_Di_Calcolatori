#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>

int checkChar(char * string){
	if(string[0] == '+' || string[0] == '-' || string[0] == 'x' || string[0] == '/'){
		return 1;
	}
	return 0;
}

int add(int first_operand, int second_operand){
	return first_operand + second_operand;
}

int sub(int first_operand, int second_operand){
	return first_operand - second_operand;
}

int mult(int first_operand, int second_operand){
	return first_operand * second_operand;
}

int division(int first_operand, int second_operand){
	return first_operand / second_operand;
}

#endif
