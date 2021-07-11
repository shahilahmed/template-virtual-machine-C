#include "defs.h"

// Compile: >gcc data.c vm.c fileXXXXX.c -o fileXXXXX.exe

// Run: >fileXXXXX

const int MAX_PAGE = TO_PAGE(TO_KB(MAX_KB));

int can_vm_run = 1;
type_vm *vm;
int address_main = 0;

void init_vm(void) {
	vm = create_vm(MAX_PAGE);
}

void init_data(void) {
}

void init(void) {
	init_vm();
	init_data();
}

void load_main(void) {
	address_main = 128;
	int code[] = {
		DATA,876,
		DATA,567,
		DATA,-569,
		OP3,9,8,-2,
		OP2,45,67,
		ORG,512,
		NOP,
		OP3,1,2,3,
		NOP,
		
		ORG,128,
		NOP,
		NOP,
		NOP,
		OP1,1,
		OP3,1,-2,45,
		OP2,1,2,
		OP4,1,2,3,4,
		HALT,
		
		ORG,64,
		DATA,12,
		DATA,13,
		DATA,0,
		DATA,78,
		DATA,1
	};
	vm_load(vm,code,((sizeof(code)) / sizeof(int)));
	print_memory(vm->memory,0,vm->max_memory);
	if(!can_vm_run) {
		print_disassembly(code,((sizeof(code)) / sizeof(int)));
	}
}


void load(void) {
	load_main();
	if(!can_vm_run) {
		print_memory(vm->memory,0,vm->max_memory);
	}
}

void run(void) {
	init();
	load();	
	if(can_vm_run) {
		printf("\n");
		printf("Output:\n");
		printf("\n");
		vm_run(vm,address_main);
		//print_memory(vm->data,0,vm->max_memory_data);
		printf("\n");
	} else {
		print_vm(vm);
		print_stack(vm);
	}
	/*
	print_vm(vm);
	print_stack(vm);
	push(vm,0);
	push(vm,1);
	push(vm,2);
	push(vm,3);
	push(vm,4);
	vm->fp = vm->sp;
	print_vm(vm);
	print_stack(vm);
	push(vm,5);
	push(vm,6);
	pop(vm);
	pop(vm);
	pop(vm);
	pop(vm);
	vm->fp = vm->sp;
	print_vm(vm);
	print_stack(vm);
	*/
}

void vm_info() {
	printf("\n");
	printf("%s %s by %s (Copyright 2021)\n",NAME,VERSION,AUTHOR);
	printf("\n");
}

int main() {
	vm_info();
	run();	
	printf("\n");
	return 0;
}




