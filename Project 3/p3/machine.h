/* (c) Larry Herman, 2018.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

#define NUM_BYTES 12288
#define BYTES_PER_WORD 4
#define NUM_WORDS (NUM_BYTES / BYTES_PER_WORD)
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6

typedef unsigned int Word;

typedef enum { PLUS, DIFF, MULT, QUOT, MOD, AND, OR, NOT, BR, READ, WRT, MOVE,
               LW, SW, LI } Operation;

int print_instruction(Word instruction);
int disassemble(const Word program[], unsigned int instr_num,
                unsigned int data_num);
int is_valid_instruction(Word word);
int relocate(const Word program[], unsigned int instr_num,
             unsigned int data_num, int offset, Word relocated_program[],
             unsigned short *const instrs_changed);
