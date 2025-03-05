#include "blockchain.h"
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int saveBlockchainToLedger(Block* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    Block* tmp = head;
    while (tmp) {
        LedgerEntry entry;
        entry.index = tmp->index;
        entry.timestamp = tmp->timestamp;
        strncpy(entry.data, tmp->data, sizeof(entry.data) - 1);
        entry.data[sizeof(entry.data) - 1] = '\0';
        strncpy(entry.hash, tmp->hash, sizeof(entry.hash) - 1);
        entry.hash[sizeof(entry.hash) - 1] = '\0';
        entry.nonce = tmp->nonce;

        if (fwrite(&entry, sizeof(LedgerEntry), 1, file) != 1) {
            perror("Erreur lors de l'écriture dans le fichier");
            fclose(file);
            return 0;
        }

        tmp = tmp->next;
    }

    fclose(file);
    return 1;
}


Block* loadBlockchainFromLedger(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    Block* head = NULL;
    Block* tmp = NULL;
    LedgerEntry entry;

    while (fread(&entry, sizeof(LedgerEntry), 1, file) == 1) {
        Block* newBlock = (Block*)malloc(sizeof(Block));
        if (!newBlock) {
            perror("Erreur d'allocation mémoire");
            fclose(file);
            return NULL;
        }

        newBlock->index = entry.index;
        newBlock->timestamp = entry.timestamp;
        strncpy(newBlock->data, entry.data, sizeof(newBlock->data) - 1);
        newBlock->data[sizeof(newBlock->data) - 1] = '\0';
        strncpy(newBlock->hash, entry.hash, sizeof(newBlock->hash) - 1);
        newBlock->hash[sizeof(newBlock->hash) - 1] = '\0';
        newBlock->nonce = entry.nonce;
        newBlock->next = NULL;

        if (head == NULL) {
            head = newBlock;
        } else {
            tmp->next = newBlock;
        }
        tmp = newBlock;
    }

    fclose(file);
    return head;
}