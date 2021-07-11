# Template Virtual Machine for C Language

* ### Registers 
   - PC : Program Counter is used for pointing instruction in the memory executing the instruction and then incrementing itself
   - SP : Stack Pointer is used to point top of the stack
   - FP : Frame Pointer is used to access values(arguments and locals of subroutine) within the stack.
   
 * ### Memory 
    - Memory is used for **Code**,**Data** and **Stack**
    - vm_create(page) take page as argument one page contains 256 Blocks of Memory
    - Example 1024 KB will have 4 Pages which is default

* ### Stack
    - Stack will start from ```max_memory```
    - Stack will grows upwards
    - ```push(value) -> Decrement SP by 1 and Insert the Value at Memory[SP]```
    - ```pop() -> Take out the value From Memory[SP] and Increment SP by 1``` 

* ### Instructions
    - ```[Number of operands: 0] HALT -> Halt the Virtual Machine```
    - ```[Number of operands: 0] NOP   -> Do Nothing```
    - ```[Number of operands: 1] OP1 <operand1> -> Performs Operations on <operand1>```
    - ```[Number of operands: 2] OP2 <operand1> <operand2> -> Performs Operations on <operand1> and  <operand2>```
    - ```[Number of operands: 3] OP3 <operand1> <operand2> <operand3> -> Performs Operations on <operand1> <operand2> and  <operand3>```
    - ```[Number of operands: 4] OP4 <operand1> <operand2> <operand3> <operand4> -> Performs Operations on <operand1> <operand2> <operand3> and  <operand4>```
