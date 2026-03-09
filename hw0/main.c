#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char character;
    int count;
    struct Node *next;
} Node;

int main() {
    FILE *fp = fopen(__FILE__, "r");
    if (fp == NULL) return 1;

    Node *head = NULL;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        // Only process standard ASCII characters to avoid '?' symbols
        if (ch < 0 || ch > 127) continue;

        Node *current = head;
        Node *prev = NULL;
        int found = 0;

        while (current != NULL) {
            if (current->character == (char)ch) {
                current->count++;
                found = 1;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!found) {
            Node *newNode = (Node *)malloc(sizeof(Node));
            newNode->character = (char)ch;
            newNode->count = 1;
            newNode->next = NULL;
            if (head == NULL) head = newNode;
            else prev->next = newNode;
        }
    }
    fclose(fp);

    Node *temp = head;
    while (temp != NULL) {
        if (temp->character == '\n') printf("\\n:%d\n", temp->count);
        else if (temp->character >= 32) printf("%c:%d\n", temp->character, temp->count);
        
        Node *toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    return 0;
}
