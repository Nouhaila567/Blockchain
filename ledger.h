#ifndef LEDGER_H
#define LEDGER_H
#include <time.h>
#include "blockchain.h"

typedef struct {
    int index;
    time_t timestamp;
    char data[256];
    char hash[65];
    int nonce;
} LedgerEntry;

int saveBlockchainToLedger(Block* head, const char* filename);
Block* loadBlockchainFromLedger(const char* filename);

#endif