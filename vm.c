#include "defs.h"

void push(type_vm *vm,int value) {
	vm->sp = vm->sp - 1;
	vm->memory[vm->sp] = value;
}

int  pop(type_vm *vm) {
	int value = INVALID;
	value = vm->memory[vm->sp];
	vm->sp = vm->sp + 1;
	return value;
}


void vm_clear(type_vm *vm) {
	int index;
	for(index = 0; index < vm->max_memory; index++) {
		vm->memory[index]  = INVALID;
	}
	vm->pc = INVALID;
	vm->sp = vm->max_memory;
	vm->fp = vm->max_memory;
	vm->is_running = 0;
}

type_vm *create_vm(int page) {
	page = (page) ? page : 1;
	type_vm *vm = (type_vm *)malloc(sizeof(type_vm));
	if(!vm) { 
		printf("Memory not available for vm.\n"); 
		exit(1); 
	}
	vm->max_memory = TO_MEMORY(page);
	vm->memory = (int *)malloc(vm->max_memory * sizeof(int));
	if(!vm->memory) { 
		printf("Memory not available for stack.\n"); 
		exit(1); 
	}
	vm_clear(vm);
	return vm;
}

void vm_load(type_vm *vm,int *memory,int length) {
	int index = 0, loc = 0, nargs = 0, opcode;
	while(index < length) {
		opcode = memory[index];
		if(opcode == ORG) {
			loc   = memory[index + 1];
			index = index + 2;
		} else if(opcode == DATA) {
			vm->memory[loc] = memory[index + 1];
			loc   = loc   + 1;
			index = index + 2;
		} else {
			if(opcode >= 0 && opcode <= MAX_INSTRUCTION - 1) {
				vm->memory[loc]  = opcode;
				loc   = loc   + 1;
				index = index + 1;
				nargs = index + instructions[opcode].nargs;
				while(index < nargs) {
					vm->memory[loc]  = memory[index];
					loc   = loc   + 1;
					index = index + 1;
				}
			} else {
				vm->memory[loc] = memory[index];
				loc   = loc   + 1;
				index = index + 1;
			}
		}
	}
}

void vm_execute(type_vm *vm) {
	int opcode, type, address, value, nlocals, nargs, noffsets, index;
	int *args;
	opcode = vm->memory[vm->pc];
	if(DEBUG_TRACE) {
		print_instruction(vm->memory,vm->pc,vm->pc);
	}
	switch(opcode) {
		case HALT:
			printf("Performing HALT\n");
			vm->is_running = 0;
			//vm->pc = vm->pc + 1;
			break;
		case  NOP:
			printf("Performing NOP\n");
			//vm->pc = vm->pc + 1;
			break;
		case  OP1:
			printf("Performing OP1\n");
			//vm->pc = vm->pc + 2;
			break;
		case  OP2:
			printf("Performing OP2\n");
			//vm->pc = vm->pc + 3;
			break;
		case  OP3:
			printf("Performing OP3\n");
			//vm->pc = vm->pc + 4;
			break;
		case  OP4:
			printf("Performing OP4\n");
			//vm->pc = vm->pc + 5;
			break;
		default:
			printf("Unkwown Opcode: %d at memory location %d.\n",opcode,vm->pc);
			exit(1);
			break;
	}
	vm->pc = vm->pc + instructions[opcode].nargs + 1;
}

void vm_run(type_vm *vm,int address) {
	if(!vm->is_running) {
		vm->is_running = 1;
		vm->pc = address;
		while(vm->is_running) {
			if(vm->pc >= vm->max_memory) vm->is_running = 0;
			vm_execute(vm);
			/*
			if(DEBUG_TRACE) {
				print_vm(vm);
				if(vm->sp != vm->max_memory) {
					print_stack(vm);
					printf("\n");
				}
			}
			*/
		}
	}
}

void print_instruction(int *memory,int index,int pc) {
	int opcode = memory[index], length;
	printf("    %4d %10s ",pc,instructions[opcode].str);
	index = index + 1;
	length = index + instructions[opcode].nargs;
	while(index < length) {
		printf("%6d ",memory[index]);
		index = index + 1;
	}
	printf("\n");				
}

void print_disassembly(int *memory,int length) {
	int opcode, index = 0, old_index;
	int pc = 0;
	printf("\n");
	printf("code disassemble:\n");
	printf("\n");
	while(index < length) {
		opcode = memory[index];
		if(opcode == HALT) {
			printf("    %4d %10s ",pc,instructions[opcode].str);
			printf("\n");
			break;
		} else {
			if(opcode == ORG) {
				pc = memory[index + 1];
				index = index + 2;
				printf("\n");
			} else {
				print_instruction(memory,index,pc);
				index = index + instructions[opcode].nargs + 1;
				pc    = pc    + instructions[opcode].nargs + 1;
				/*
				printf("    %4d %10s ",pc,instructions[opcode].str);
				index = index + 1;
				pc    = pc + 1;
				old_index = index;
				while(index < old_index + instructions[opcode].nargs) {
					printf("%6d ",memory[index]);
					index = index + 1;
					pc    = pc + 1;
				}
				printf("\n");
				*/	
			}
		}
	}
	printf("\n");
}


void print_memory(const int *memory,int page,int max_memory) {
	int start = page * 256;
	int max_page = (max_memory / 256);
	int index;
	if(page >= 0 && page <= max_page - 1) {
		printf("\n");
		printf("memory : 0 to %d\n",(max_memory - 1));
		printf("page   : %4d start : %4d end : %4d\n",page,start,((start + 256) - 1));
		printf("\n");
		for(index = 0; index < 256; index++) {
			if(!index) {
				printf("            0      1      2      3      4      5      6      7");
				printf("\n");
				printf("-----|--------------------------------------------------------");
			}
			if(!(index % 8)) {
				printf("\n");
				printf("%4d | ",(start + index));
			}
			if(memory[(start + index)] == INVALID) {
				printf("       ");
			} else {
				printf("%6d ",memory[(start + index)]);
			}
		}
		printf("\n");
	} else {
		printf("\n");
		printf("memory: 0 to %d\n",(max_memory - 1));
		printf("page must be between 0 and %d\n",(max_page - 1));
		printf("\n");
	}
	printf("\n");
}


void print_stack(const type_vm *vm) {
	int index;
	if(vm->sp == vm->max_memory) {
		printf("Stack is Empty.\n");
	} else {
		printf("Stack: [");
		for(index = vm->max_memory - 1; index >= vm->sp; index--) {
			if(index == vm->fp) printf("{");
			if(index == vm->sp) printf("(");
			printf("%d",vm->memory[index]);
			if(index == vm->sp) printf(")");
			if(index == vm->fp) printf("}");
			printf(" ");
		}
		printf("]");
	}
	printf("\n");
}


void print_vm(const type_vm *vm) {
	printf("\n");
	printf("vm->pc : %d\n",vm->pc);
	printf("\n");
	printf("vm->sp : %d\n",vm->sp);
	printf("vm->fp : %d\n",vm->fp);
	printf("\n");
}








