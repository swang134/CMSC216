#include<stdio.h>
#include "machine.h"

/* Shuyao Wang 9/10/19
 * ID number: 115935327
 * This project is to write some functions that manipulate the instructions of
 * a fictional CPU code named the Coffee Cake
 */

/* This function is passed a Word instruction 
 * If the insturction is not valid it will just return 0
 * If the instruction is valid it will return 1 after print the instruction's
 * components on a single line 
 */
int print_instruction(Word instruction) {

  /* check wheter instruction is valid for Coffe Cake*/
  if(!(is_valid_instruction(instruction)))
    return 0;
  else{
  
    /* opcode = first 4 bit of insturction, so shift 32-28 bit to get opcode8*/
    int opera = instruction >> 28;
    /* reg1 = the bit between last 6 to last 9 of instuction*/
    int reg1 = ( instruction >> 6 ) & 0x7;
    /* reg2 = the bit between last 3 to last 6 of instuction*/
    int reg2 = ( instruction >> 3 ) & 0X7;
    /* reg3 = the last 3 bit of instuction*/
    int reg3 = ( instruction >> 0 ) & 0x7;
    /* memory = the bit between positon 9 to 28 of instuction*/
    int memory = ( instruction >> 9 ) & 0x7ffff;

    /* Use value of the opcode field to find the enum balue and return 1 after
     * it
     */
    switch( opera ) {
    case PLUS:
      printf( "plus\tR%d\tR%d\tR%d", reg1, reg2, reg3 );
      break;
      
    case DIFF:
      printf( "diff\tR%d\tR%d\tR%d", reg1, reg2, reg3 );
      break;

    case MULT:
      printf( "mult\tR%d\tR%d\tR%d", reg1, reg2, reg3 );
      break;

    case QUOT:
      printf( "quot\tR%d\tR%d\tR%d", reg1, reg2, reg3 );
      break;

    case MOD:
      printf( "mod\tR%d\tR%d\tR%d", reg1, reg2, reg3 );
      break;

    case AND:
      printf( "and\tR%d\tR%d\tR%d", reg1, reg2, reg3 );
      break;

    case OR:
      printf( "or\tR%d\tR%d\tR%d", reg1, reg2, reg3 );
      break;

    case NOT:
      printf( "not\tR%d\tR%d", reg1, reg2 );
      break;

    case BR:
      printf( "br\tR%d\t%05d", reg1, memory );
      break;

    case READ:
      printf( "read\tR%d", reg1 );
      break;

    case WRT:
      printf( "wrt\tR%d", reg1 );
      break;

    case MOVE:
      printf( "move\tR%d\tR%d", reg1, reg2 );
      break;

    case LW:
      printf( "lw\tR%d\t%05d", reg1, memory );
      break;

    case SW:
      printf( "sw\tR%d\t%05d", reg1, memory );
      break;

    case LI:
      printf( "li\tR%d\t%d", reg1, memory );
      break;
    }
  }
      return 1;
}

/* This function will convert machine language to assembly language for 
 * Coffee Cake program by applying print_instruction()
 */
int disassemble(const Word program[], unsigned int instr_num,
                unsigned int data_num) {

  /* The parameters would be invalid if array is NULL. The two unsigned 
   * in parameters' value would be invalid if the size of the code is not
   * at least one word. If (data_num + instr_num)*4 greater than the number
   * of words in the Coffe Cake's memory , the parameter would be invalid
   * return 0 without producing any output if parameter are invalid
   */
  if( program == NULL )  
    return 0;
  
  if( instr_num < 1 || (data_num + instr_num)*4 > 12288 )
    return 0;
   
  else {
      int pos=0; 
      int add=0; 

      /* Calling print_instruction() on each element of array representing 
       * part of the code segment
       */
      while( pos < instr_num ){

	/* if any element of the code segment represents a invalid Coffe Cake
	 * instruction, all valid insturction before the first invalid 
	 * insturction will be printed, and return 0
	 */
	if( is_valid_instruction( program[pos] ) ) {
	  printf( "%04x: ", add );
	  print_instruction( program[pos] );
	  printf( "\n" );
	  pos++; 
	  add+=4;
	} else
	  return 0;
      }

      /* Print the contents of the words in the data segment, in hexadecimal
       * using exactly eight place
       */
      while( pos < instr_num +  data_num ){
	printf( "%04x: ", add );
	printf( "%08x", program[pos] );
	printf( "\n" );
	pos++;
	add+=4;
      }
      return 1;
 }
}

/* This function should return 1 if the value of its parameter Word word is a
 * valid machine insturction and 0 if it is not valid 
 */
int is_valid_instruction(Word word){
  
  /* opcode = first 4 bit of insturction, so shift 32-28 bit to get opcode8*/
  int opera = word >> 28;
   /* reg1 = the bit between last 6 to last 9 of instuction*/
  int reg1 = ( word >> 6 ) & 0x7;
   /* reg1 = the bit between last 3 to last 6 of instuction*/
  int reg2 = ( word >> 3 ) & 0X7;
   /* reg1 = the bit between last 0 to last 3 of instuction*/
  int reg3 = ( word >> 0 ) & 0x7;
   /* reg1 = the bit between position 9 to 28 of instuction*/
  int memory = ( word >> 9) & 0x7ffff;

  /* There is one bit pattern in the opcode part of word that doesn't represent
   * an opcode which is opera == 15
   */
  if( opera<0 || opera>14 ) 
    return 0;

  /* The three register operands are 3 bit each but there are only numbers 0-6
   * so there is one bit pattern that could be in a register operand field that
   * does not represent a vaild register number
   */
  if( opera <= 6 ){
    if( reg1 <0 || reg2 < 0 || reg3 < 0 || reg1 > 6 || reg2 >6 || reg3 >6 )
       return 0;
  } else if( opera == 7 || opera == 11 ){
    if( reg1 <0 || reg2 < 0 || reg1 > 6 || reg2 > 6 )
       return 0;
  } else {
    if( reg1 < 0 || reg1 > 6 )
      return 0;
  }

  /* The momery address/immediate field in Coffe Cake instructions is 19 bits
   * but the Coffe Cake has 12288 bytes of memory, with 0-12287, we need make 
   * sure that the memory address < max memary
   * everything must begin at an address that is divisible by 4
   * LI instruction can be any value that can be store in 19 bits
   */
  if( opera == 8 || opera == 12 || opera == 13 ){
    if( memory < 0 || memory > 12287)
       return 0;
    if( memory%4 !=0 )
      return 0;
  }

  /* The instructions that use the first register operand and would modify it 
   * are all instructions except for br, wrt, and sw, any instruction that has
   * the effect of modifying the first register operand and it uses either of
   * the special unmodifiable register R0 or R6 for the first operand
   */
  if( !( opera == 8 || opera == 10 || opera == 13 ) ){
    if( reg1 == 0 || reg1 == 6)
      return 0;
  }
  return 1;
}

/* This function will move the instructions in program to relocated_ program
 * Instructions that only use operands in registers would not be affected if 
 * a program was placed in memory starting at different address, but 
 * instructions that use memory addresses would have to have their memory 
 * addresses adjusted
 */
int relocate(const Word program[], unsigned int instr_num,
             unsigned int data_num, int offset, Word relocated_program[],
             unsigned short *const instrs_changed){

  /* if program is NULL or if instr_num < 1 or (data_num + instr_num) * 4 >
   * 12288 or offset is not divisible by 4 or instrs_changed is NULL, it will
   * just return 0
   */
  if( program == NULL|| instr_num < 1 || offset%4 != 0 ||
      instrs_changed == NULL ||  (data_num + instr_num) * 4 > 12288 )
    return 0;
  
  else{ 
    int pos = 0;
    int opera = 0;
    int memory = 0;
    int modify = 0;
    
     while( pos < instr_num ){

       /* check whether the instruction in program is valid*/
       if( is_valid_instruction(program[pos]) ) {
	   opera = program[pos] >> 28;
	   memory = ( program[pos] >> 9 ) & 0x7ffff;

	   /* Instructions that only use operands in registers would not be
	    * affected
	    */
	   if( opera != 8 && opera < 12 )
	     relocated_program[pos] = program[pos];
	   else{

	     /* if adding offset to any instruction's memory address eould be 
	      * less than zero or larger than the Coffe Cake's max memory 
	      * address, the function will return to 0*/
	     if( memory + offset > 12288 || memory + offset < 0)
	       return 0;
	     
	     /* All instructions that do use the memory address/constant
	      * field for storing a memory address should have their memory
	      * address modified when copied to relocated_program by having
	      * the value of offset added to the address
	      */ 
	     relocated_program[pos] = program[pos] + (offset << 9);
	     modify++;
	   }
	} else
	  return 0;
       pos++;
    }
     
    while( pos < instr_num + data_num ){
      relocated_program[pos] = program[pos];
      pos++;
    }
    return 1;
  }
}



