#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


typedef int bool;
enum { false, true };
 
// element from list
typedef struct estructure {
    char letter;
    struct estructure *next;
} NODE;
 
NODE* createList(char word[]) {
    NODE *last = NULL;
    NODE *auxiliary = NULL;
    int counter;
 
    for (counter = 0; counter < strlen(word); counter++) {
        NODE *new_node = (NODE *) malloc(sizeof(NODE));
        new_node->letter = word[counter];
        new_node->next = NULL;
        if (last) {
            last->next = new_node;
        } else {
            auxiliary = new_node;
        }
        last = new_node;
    }
    return auxiliary;
}
 
void printList(NODE* p) {
    NODE* auxiliary = p;
    while(auxiliary) {
        printf("%c", auxiliary->letter);
        auxiliary = auxiliary->next;
    }
}

NODE* cloneList(NODE* p){
  NODE* response = (NODE*)malloc(sizeof(NODE)); 
  NODE *chain = p;
  //Use a previous node to conect elements
  NODE *previous = NULL; 
 
  while(chain){ 
    NODE *new_node = (NODE *) malloc(sizeof(NODE));
    new_node->letter = chain->letter;
    new_node->next = NULL;
 
    if (previous == NULL){ 
        response = new_node;
    }
    else { 
        previous->next = chain;
    }
 
    previous = new_node;
    chain = chain->next;
  }
 
  return response;
}
 
NO* invert(NODE* response){
    NODE* current = response;
    response = NULL;
 
    while (current != NULL){ 
        NODE* chain = current; 
        current = current->next; 
        current->next = response; 
        response = chain; 
    }
    return response;
}
 
void invertNonVowel(NODE* element, NODE* previous, NODE* end) {
    if (element != end) {
        invertNode(element->next, element, end);
    }
    element->next = previous;
}
 
bool checkSequence(NODE* value) {
    if (
        (
            value->letter != 'a' && 
            value->letter != 'A' && 
            value->letter != 'e' && 
            value->letter != 'E' && 
            value->letter != 'i' && 
            value->letter != 'I' && 
            value->letter != 'o' && 
            value->letter != 'O' && 
            value->letter != 'u' && 
            value->letter != 'U'
        )
    )
    {
        return true;
    }
    else{
        return false;
    }
}

NODE* decode(NODE* p) {
    NODE* auxiliary = cloneList(p);
    NODE* response = invert(auxiliary);
    NODE* firstNonVowel = NULL; 
    NODE* lastNonVowel = NULL; 
    NODE* current = response; 
    NODE* previous = NULL;
 
    while (current != NULL) {
        if (checkSequence(current)) {
            firstNonVowel = current;
            while (current->next != NULL && checkSequence(current->next)) {
                current = current->next;
            }
            // If the last letter found is a non-vowel,
            // so the end of sequence of non-vowels was reached
            lastNonVowel = current;
 
            // If there is a sequence of non-vowels,
            // In other words, firstNonVowel and lastNonVowel does not point to the same element
            // So the change of positions should be performed
            if (firstNonVowel != lastNonVowel) { 
                NODE* nextOriginal = lastNonVowel->next;
                invertNonVowel(firstNonVowel->next, firstNonVowel, lastNonVowel);
                firstNonVowel->next = nextOriginal;
                if (previous == NULL){
                    response = lastNonVowel;
                }
                else {
                    previous->next = lastNonVowel;
                }
                current = firstNonVowel;
            }
        }
        previous = current;
        current = current->next;
    }
    return response;
}
 
int main() {
    NODE* p = NULL;
    NODE* auxiliary = decode(p); 
    return 0;
}
