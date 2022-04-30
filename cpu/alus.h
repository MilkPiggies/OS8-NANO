#pragma once
#include <regs.h>

int e;			// ALU A
int f;			// ALU B
int g;			// ALU C
	
e = 0x05		// ALU A = 0x01 +-*/ 0x02
f = 0x06		// ALU B = 0x03 +-*/ 0x04
g = 0x07		// ALU C = 0x05 +-*/ 0x06

int e1 = ALU_A_ADDITION
int e2 = ALU_A_SUBTRACTION
int e3 = ALU_A_MULTIPLICATION
int e4 = ALU_A_DIVISION

int f1 = ALU_B_ADDITION
int f2 = ALU_B_SUBTRACTION
int f3 = ALU_B_MULTIPLICATION
int f4 = ALU_B_DIVISION

int g1 = ALU_C_ADDITION
int g2 = ALU_C_SUBTRACTION
int g3 = ALU_C_MULTIPLICATION
int g4 = ALU_C_DIVISION

e1 = 0x08
e2 = 0x09
e3 = 0x10
e4 = 0x11

f1 = 0x12
f2 = 0x13
f3 = 0x14
f4 = 0x15

g1 = 0x16
g2 = 0x17
g3 = 0x18
g4 = 0x19


// ALU Addition
	// ALU A
	e1 = 0x01 + 0x02 {
		for (i = 0x01; i <= 10; i = 0x02 + 1)
		{
			printf(" %d \t 0xe1 \n", i);
		}
		
	// ALU B
	f1 = 0x03 + 0x04 {
		for (i = 0x03; i <= 10; i = 0x04 + 1)
		{
			printf(" %d \t 0xf1 \n", i);
		}

	// ALU C
	g1 = 0x05 + 0x06 {
		for (i = 0x05; i <= 10; i = 0x06 + 1)
		{
			printf(" %d \t 0xg1 \n", i);
		}

// ALU Subtraction
	// ALU A
	e2 = 0x01 - 0x02 {
		for (i = 0x01; i <= 10; i = 0x02 - 1)
		{
			printf(" %d \t 0xe2 \n", i);
		}

	// ALU B
	f1 = 0x03 - 0x04 {
		for (i = 0x03; i <= 10; i = 0x04 - 1)
		{
			printf(" %d \t 0xf2 \n", i);
		}

	// ALU C
	g1 = 0x05 - 0x06 {
		for (i = 0x05; i <= 10; i = 0x06 - 1)
		{
			printf(" %d \t 0xg2 \n", i);
		}

// ALU Multiplication
	// ALU A
	
	// ALU B
	
	// ALU C
	 
	 
// ALU Division
	// ALU A

	// ALU B

	// ALU C