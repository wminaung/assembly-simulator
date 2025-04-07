#pragma onece

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUB 31
#define DIV 32
#define MUL 33
#define JUMP 40
#define JUMPNEG 41
#define JUMPZERO 42
#define HALT 43
#define COMBINE(op, addr) ((op)*100 + (addr))