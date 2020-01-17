#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
	int value;
	Node* next;
};

struct LinkedList {
	struct Node* last;
       	struct Node* first;
};

struct LinkedList* createLinkedList (int firstNodeValue) {
	struct Node* firstNode = (struct Node*) malloc(sizeof(struct Node));
	firstNode->value = firstNodeValue;
	firstNode->next = NULL;

	struct LinkedList* list = (struct LinkedList*) malloc(sizeof(struct LinkedList));
	list->first = list->last = firstNode;
	return list;
}

void addLast (struct LinkedList* list, int toAdd) {
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->value = toAdd;
	newNode->next = list->last;
	list->last = newNode;
	return;
}

void addFirst (struct LinkedList* list, int toAdd) {
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->value = toAdd;
	newNode->next = NULL;

	list->first->next = newNode;
	list->first = newNode;
	return;
}

Node* getFirst(struct LinkedList* list) {
	return (list->first);
}

void removeFirst (struct LinkedList* list) {
	struct Node* oldFirstNode = list->first;
	struct Node* nextNode = list->last;

	while(1) {
		if (nextNode->next == list->first) {
			nextNode->next = NULL;
			list->first = nextNode;
			free(oldFirstNode);
			break;
		}
		nextNode = nextNode->next;
	}
}

void removeLast (struct LinkedList* list) {
	struct Node* toRemove = list->last;
	list->last = list->last->next;
	free(toRemove);
}


Node* getLast (struct LinkedList* list) {
	return (list->last);
}

int nodeIsLast (struct Node* node) {
	return (node->next == NULL);
}

int size (struct LinkedList* list) {
	int size = 0;
	struct Node* nextNode = list->last;
	while (1) {
		size++;
		if (nextNode->next == NULL)
			break;
		else
			nextNode = nextNode->next;
	}
	return size;
}


void printList (struct LinkedList* list) {
	struct Node* nextNode = list->last;
	while (1) {
		printf("%d", nextNode->value);
		if (nextNode->next == NULL) {
			printf("\n");
			break;
		} else {
			printf(" - ");
		}
		nextNode = nextNode->next;
	};
		}


int main () {
	struct LinkedList* list = createLinkedList(5);
	addLast(list, 17);
	addLast(list, 29);
	addLast(list, 58);
	printf("%d FIRST ITEM\n", getFirst(list)->value);
	printf("%d LAST ITEM\n", getLast(list)->value);
	printList(list);
	
	printf("REMOVING FIRST\n");
	removeFirst(list);
	printList(list);

	printf("REMOVING LAST\n");
	removeLast(list);
	printList(list);

	printf("Adding new first!\n");
	addFirst(list, 19);
	printList(list);

	printf("Adding new last!\n");
	addLast(list, 2);
	printList(list);

	printf("SIZE: %d\n", size(list));
	}
