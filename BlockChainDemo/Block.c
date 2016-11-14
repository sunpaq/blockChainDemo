
#include "Block.h"

//copy form << The C Programming language >>
//BKDR Hash Function
static unsigned hash(const char *s) {
    unsigned hashval;
    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval & 0x7fffffff;
}

static void BlockChainInsert(BlockChain* chain, Block* block) {
    if (chain->tail == NULL) {
        chain->tail = block;
    }else{
        Block* b = chain->tail;
        while (b->previous!=NULL) {
            b=b->previous;
        }
        b->previous = block;
    }
}

static int Balance(BlockChain* chain, char id) {
    int balance = 0;
    Block* b = chain->tail;
    while (b!=NULL) {
        if (b->transaction->src == id)
            balance -= b->transaction->value;
        if (b->transaction->dest == id)
            balance += b->transaction->value;
        b=b->previous;
    }
    return balance;
}

static Block* BlockCreate(Transaction* transaction) {
    Block* b = (Block*)malloc(sizeof(Block));
    b->previous = NULL;
    b->transaction = transaction;
    return b;
}

static char* BlockContentAppendNonce(Block* b, char* buff, size_t size, int nonce) {
    sprintf(buff, "%ld_%c_%c_%d_%d", b->timestamp, b->transaction->src,
            b->transaction->dest, b->transaction->value, nonce);
    buff[size-1] = '\0';
    return buff;
}

static int Validation(BlockChain* chain, Transaction* tran) {
    if (tran->src == tran->dest) {
        return -1;
    }
    if (tran->value > Balance(chain, tran->src)) {
        return -2;
    }
    return 0;
}

void Mining(BlockChain* chain, Transaction* tran, const unsigned HLimit) {
    if(!chain) return;
    int err = 0;
    if ((err=Validation(chain, tran)) != 0) {
        if (err == -1) printf("VALIDATION ERROR! %c=>%c $%d\n", tran->src, tran->dest, tran->value);
        if (err == -2) printf("BALANCE WARNING! %c=>%c $%d\n", tran->src, tran->dest, tran->value);
    }
    
    Block* block = BlockCreate(tran);
    
    char content[LINE_MAX];
    unsigned H=HLimit+1;
    
    //Proof of Work
    while (H > HLimit) {
        int X = rand();
        H = hash(BlockContentAppendNonce(block, content, LINE_MAX, X));
    }
    
    block->hash = H;
    block->timestamp = time(0);
    
    BlockChainInsert(chain, block);
    printf("Block:%04x\n", block->hash);
}

void LedgerPrint(Block* block) {
    if(block->previous) {
        LedgerPrint(block->previous);
    }
    printf("----------------------------------\n");
    printf("transaction[T:%ld H:%04x] %c=>%c $%d\n", block->timestamp, block->hash,
           block->transaction->src, block->transaction->dest, block->transaction->value);
}

void BalancePrint(BlockChain* chain, char id) {
    printf("balance of %c: %d\n", id, Balance(chain, id));
}

void HashPrint(const char* s) {
    printf("hash(%s) -> %u(%04x)\n", s, hash(s), hash(s));
}
