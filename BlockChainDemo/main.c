
#include "Block.h"

Transaction trans[] = {
    {'A','B',10},
    {'B','A',5},
    {'C','A',10},
    {'B','A',6},
    {'A','C',3},
    {'B','C',1},
    {'C','A',10},
    {'B','A',2},
    {'B','C',1},
    {'A','C',8}
    //{'A','A',8}
};

BlockChain Chain = {NULL, 0};

int main(int argc, char* argv[]) {
    
    HashPrint("1234567");
    HashPrint("salt1234567");
    //return 0;
    
    int count = sizeof(trans)/sizeof(Transaction);
    for (int i=0; i<count; i++) {
        Mining(&Chain, &trans[i], 10000);
    }
    
    LedgerPrint(Chain.tail);
    BalancePrint(&Chain, 'A');
    BalancePrint(&Chain, 'B');
    BalancePrint(&Chain, 'C');
    
    return 0;
}

