#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <time.h>

typedef struct Block {
    int index;
    time_t timestamp;
    char data[256];
    char hash[65];
    int nonce;
    struct Block *next;
} Block;

Block* initializeBlockchain(const char* genesisData);
Block *createBlock(int index, const char *data);
Block *insertBlock(Block *head, const char *data);
void mineBlock(Block *block, const char *previousHash);
int validateChain(Block *head);
void displayBlockchain(Block *head);

#endif