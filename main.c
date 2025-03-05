#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "blockchain.h"
#include "ledger.h"

int main() {
    // Step 1: Testing Linked List
    printf("=== Linked List Test ===\n");
    node *head = NULL;
    head = insertNode(head, 10);
    head = insertNode(head, 20);
    head = insertNode(head, 30);
    printf("Linked List after insertion: ");
    displayList(head);

    head = deleteNode(head, 20);
    printf("Linked List after deleting 20: ");
    displayList(head);
    printf("\n");

    // Step 2: Testing Blockchain
    printf("=== Blockchain Test ===\n");

    // Initialize blockchain with a genesis block
    Block *blockchain = initializeBlockchain("Genesis Block");
    if (!blockchain) {
        fprintf(stderr, "Failed to initialize blockchain.\n");
        return 1;
    }

    // Insert new blocks into the blockchain
    blockchain = insertBlock(blockchain, "Second Block");
    blockchain = insertBlock(blockchain, "Third Block");

    // Display the blockchain
    printf("Blockchain after inserting new blocks:\n");
    displayBlockchain(blockchain);

    // Step 3: Mining a block
    printf("=== Mining Block ===\n");
    Block *newBlock = createBlock(3, "Fourth Block");
    mineBlock(newBlock, blockchain->hash);  // Mine the block based on the previous block's hash
    blockchain = insertBlock(blockchain, "Fourth Block");

    // Display the blockchain after mining
    printf("Blockchain after mining new block:\n");
    displayBlockchain(blockchain);

    // Step 4: Validate Blockchain
    printf("=== Blockchain Validation ===\n");
    if (validateChain(blockchain)) {
        printf("Blockchain is valid.\n");
    } else {
        printf("Blockchain is invalid.\n");
    }

    // Step 5: Save the blockchain to a ledger file
    const char *ledgerFile = "blockchain.ledger";
    printf("=== Saving Blockchain to Ledger ===\n");
    if (saveBlockchainToLedger(blockchain, ledgerFile)) {
        printf("Blockchain successfully saved to ledger file.\n");
    } else {
        printf("Failed to save blockchain to ledger file.\n");
    }

    // Step 6: Load the blockchain from the ledger file
    printf("=== Loading Blockchain from Ledger ===\n");
    Block *loadedBlockchain = loadBlockchainFromLedger(ledgerFile);
    if (loadedBlockchain) {
        printf("Blockchain successfully loaded from ledger file:\n");
        displayBlockchain(loadedBlockchain);
    } else {
        printf("Failed to load blockchain from ledger file.\n");
    }

    // Step 7: Cleanup (Free the memory)

    // Free linked list memory
    node *current = head;
    while (current) {
        node *temp = current;
        current = current->next;
        free(temp);
    }

    // Free blockchain memory
    Block *currentBlock = blockchain;
    while (currentBlock) {
        Block *temp = currentBlock;
        currentBlock = currentBlock->next;
        free(temp);
    }

    return 0;
}
