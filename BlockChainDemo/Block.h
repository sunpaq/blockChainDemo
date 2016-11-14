
#ifndef Block_h
#define Block_h

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/syslimits.h>

typedef struct {
    char src;
    char dest;
    unsigned value;
} Transaction;

//in real blockchain previous use hash
typedef struct _Block {
    struct _Block *previous;
    Transaction* transaction;
    long timestamp;
    unsigned hash;
} Block;

//LinkedList A <- B <- C <- D
typedef struct {
    Block *tail;
    size_t count;
} BlockChain;

void Mining(BlockChain* chain, Transaction* tran, const unsigned HLimit);
void LedgerPrint(Block* block);
void BalancePrint(BlockChain* chain, char id);
void HashPrint(const char* s);

#endif /* Block_h */
