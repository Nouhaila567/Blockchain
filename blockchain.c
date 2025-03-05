#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Block* initializeBlockchain(const char* genesisData) {
    // The genesis block will always have index 0 and can have any data you want.
    Block* genesisBlock = createBlock(0, genesisData);
    if (!genesisBlock) {
        return NULL; // If the genesis block creation fails, return NULL.
    }
    return genesisBlock;
}

// Helper function to calculate a simple hash
void calculateHash(const Block* block, char* hashBuffer) {
    unsigned long hash = 0;
    const char* str = block->data;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    hash += block->index + block->timestamp + block->nonce;
    snprintf(hashBuffer, 65, "%lx", hash); // Convert hash to hexadecimal
}

// Create a new block
Block* createBlock(int index, const char* data) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    if (!newBlock) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    newBlock->index = index;
    newBlock->timestamp = time(NULL);
    strncpy(newBlock->data, data, sizeof(newBlock->data) - 1);
    newBlock->data[sizeof(newBlock->data) - 1] = '\0';
    newBlock->nonce = 0;
    calculateHash(newBlock, newBlock->hash);
    newBlock->next = NULL;
    return newBlock;
}

// Insert a block into the blockchain
Block* insertBlock(Block* head, const char* data) {
    if (!head) {
        return createBlock(0, data); // Create the genesis block
    }
    Block* tmp = head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    Block* newBlock = createBlock(tmp->index + 1, data);
    if (!newBlock) return head;
    mineBlock(newBlock, tmp->hash); // Mine the new block using the previous hash
    tmp->next = newBlock;
    return head;
}

// Mine a block by finding a hash with the required difficulty
void mineBlock(Block* block, const char* previousHash) {
    char hash[65];
    do {
        block->nonce++;
        calculateHash(block, hash);
    } while (strncmp(hash, "ee", 2) != 0); // Example condition: hash must start with "00"
    strncpy(block->hash, hash, 65);
}

// Validate the blockchain
int validateChain(Block* head) {
    if (!head) return 1; // An empty chain is valid
    Block* tmp = head;
    char previousHash[65] = "";
    char computedHash[65];

    while (tmp) {
        calculateHash(tmp, computedHash);
        if (strcmp(computedHash, tmp->hash) != 0) {
            return 0; // Invalid hash
        }
        strcpy(previousHash, tmp->hash);
        tmp = tmp->next;
    }
    return 1; // Blockchain is valid
}

// Display the blockchain
void displayBlockchain(Block* head) {
    Block* tmp = head;
    while (tmp) {
        printf("Block %d:\n", tmp->index);
        printf("  Timestamp: %s", ctime(&tmp->timestamp));
        printf("  Data: %s\n", tmp->data);
        printf("  Hash: %s\n", tmp->hash);
        printf("  Nonce: %d\n\n", tmp->nonce);
        tmp = tmp->next;
    }
}
