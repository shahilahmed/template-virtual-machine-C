#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/timeb.h>


/***************
DEFINATION PART
	- This part is used to define.

***************/
#define NAME    "Template Virtual Machine"
#define VERSION "v0.3.0"
#define AUTHOR  "Md Shahil Ahmed"

#define TO_KB(value) (value * 1024) 
#define TO_MB(value) (value * 1024 * 1024) 

#define TO_MEMORY(page) (page * 256)
#define TO_PAGE(value)  (value / 256)

#define MAX_KB 1

#define DEBUG_TRACE 0

enum {	
	HALT = 0,
	NOP  = 1,
	
	OP1  = 2,
	OP2  = 3,
	OP3  = 4,
	OP4  = 5,
	
	MAX_INSTRUCTION = OP4 + 1,
	
	DATA    = -3,
	ORG     = -2,
	INVALID = -1
};

typedef struct {
	int  opcode;
	char str[30];
	int  nargs;
}type_instruction;

typedef struct {
	int *memory;
	int max_memory;
	int pc;
	int sp;
	int fp;
	int is_running;
}type_vm;

/***************
GLOBAL DATA PART
	- This part is used to declare global variables and static functions.
***************/
extern type_instruction instructions[MAX_INSTRUCTION];
/***************
MACRO PART
	- This part is used for macro.
***************/
/***************
PROTOTYPE PART
	- This part is used to define prototypes of function.
***************/
/* - vm.c - */
extern void push(type_vm *vm,int value);
extern int  pop(type_vm *vm);
extern void vm_clear(type_vm *vm);
extern type_vm *create_vm(int page);
extern void vm_load(type_vm *vm,int *memory,int length);
extern void vm_execute(type_vm *vm);
extern void vm_run(type_vm *vm,int address);
extern void print_instruction(int *memory,int index,int pc);
extern void print_disassembly(int *memory,int length);
extern void print_memory(const int *memory,int page,int max_memory);
extern void print_stack(const type_vm *vm);
extern void print_vm(const type_vm *vm);


#endif






























