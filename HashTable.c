#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define SIZE 20

typedef struct DataItem DataItem;

struct DataItem {
	char *key;
	DataItem  *next;
	char *value;
};



struct HashTable {
	int size;
	struct DataItem **table;
};

typedef struct HashTable HashTable;


/*
 * Create a hashtable instance
 */
HashTable *HashTable_create (int size) {
	HashTable *hashTable = NULL;
	int i;

	if (size < 1) return NULL;

	/*
	 * Allocate the table itself
	 */
	if ( (hashTable = malloc(sizeof(HashTable))) == NULL) {
		return NULL;
	}

	/*
	 * Allocate pointers to the head nodes
	 */
	if ( (hashTable->table = malloc(sizeof(DataItem) * size)) == NULL) {
			return NULL;
	}

	for (i = 0; i < size; i++) {
		hashTable->table[i] = NULL;
	}

	hashTable->size = size;

	return hashTable;
}

int HashTable_hash(HashTable *hashTable, char *key) {
	unsigned long int hashVal;
	int i = 0;

	while (hashVal < ULONG_MAX && i < strlen(key)) {
		hashVal = hashVal << 8;
		hashVal += key[i];
		i++;
	}

	return hashVal % hashTable->size;
}

DataItem *HashTable_newPair (char *key, char *value) {
	DataItem *newPair;
	
	if ( (newPair = malloc(sizeof(DataItem))) == NULL) {
		return NULL;
	}

	if ( (newPair->key = strdup(key)) == NULL) {
		return NULL;
	}

	if ( (newPair->value = strdup(value)) == NULL) {
		return NULL;
	}

	newPair->next = NULL;
	return newPair;
}

/*
 * Insert a key-value pair into hashtable
 */
void HashTable_set (HashTable *hashTable, char *key, char *value) {
	int bin = 0;
	DataItem *newPair = NULL;
	DataItem *next = NULL;
	DataItem *last = NULL;

	bin = HashTable_hash(hashTable, key);

	next = hashTable->table[bin];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		last = next;
		next = next->next;
	}

	// If there's already a pair, replace that string
	if (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		free(next->value);
		next->value = strdup(value);
	} else {
		newPair = HashTable_newPair(key, value);

		/* 
		 * We're at the start of the linked list in this bin
		 */
		if (next == hashTable->table[bin]) {
			newPair->next = next;

			hashTable->table[ bin ] = newPair;
	
		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newPair;
	
		/* We're in the middle of the list. */
		} else  {
			newPair->next = next;
			last->next = newPair;
		}
	}
}

/* Retrieve a key-value pair from a hash table. */
char *HashTable_get(HashTable *hashTable, char *key ) {
	int bin = 0;
	DataItem *pair;

	bin = HashTable_hash(hashTable, key);

	/* Step through the bin, looking for our value. */
	pair = hashTable->table[bin];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;

	} else {
		return pair->value;
	}
	
}


int main( int argc, char **argv ) {

	HashTable *hashtable = HashTable_create( 65536 );

	HashTable_set( hashtable, "january", "Remember to pick up your daughter" );
	HashTable_set( hashtable, "february", "Do homework." );
	HashTable_set( hashtable, "march", "Go on vacation." );
	HashTable_set( hashtable, "april", "Move to Italy" );

	printf( "January: %s\n", HashTable_get( hashtable, "january" ) );
	printf( "February: %s\n", HashTable_get( hashtable, "february" ) );
	printf( "March: %s\n", HashTable_get( hashtable, "march" ) );
	printf( "April: %s\n", HashTable_get( hashtable, "april" ) );

	return 0;
}
