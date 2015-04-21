#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"
#define compare( a, b ) strcmp( ( a ), ( b ))
/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	/*Check whether a NULL value was passed as a parameter.*/
	if(ht == NULL)
    {
        printf("\nA bad parameter was passed from createMap to _initMap.\n");
        return;
    }

    /*Establish the number of buckets (table size) and links (0) in the new hash table.*/
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;

	/*Assign null values to each bucket for now*/
	for(index = 0; index < tableSize; index++)
    {
		ht->table[index] = NULL;
    }
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{
	/*write this*/
	 int i;
/*Loop through table and assign values to a temporary hashLink.*/
	 for(i = 0; i < ht->tableSize; i++)
        {
            hashLink* myLink = ht->table[i];
/*Free memory key and value memory*/
            while(myLink != NULL)
            {
                hashLink *nextLink = myLink->next;
                free(myLink->key);
                free(myLink);
                myLink = nextLink;
            }
        }
/*Set size and capacity to 0.*/
        ht->count = 0;
        ht->tableSize = 0;

/*Free the bucket*/
        free(ht->table);
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*write this*/
	int i;/*Initialize i for looping.  */

/*Assign and allocate memory for the table */
    struct hashLink **oldTable = ht->table;
    ht->table = (hashLink **)malloc(newTableSize * sizeof(hashLink *));
    ht->count = 0;

/* Assign variable to the table size and resize the table to the new size*/
    int prevSize = ht->tableSize;

    ht->tableSize = newTableSize;

    for(i = 0; i < ht->tableSize; i++)
    {
        ht->table[i] = NULL;
    }

/*Fill the new table with the values and free memory */
    for(i = 0; i < prevSize; i++)
    {
        struct hashLink *hLink = oldTable[i];
        struct hashLink *next;

        while(hLink)
        {
            next = hLink->next;

            insertMap(ht, hLink->key, hLink->value);

            free(hLink);
            hLink = next;
        }
    }
}
/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
    /*write this*/
    assert( ht != NULL );
/* Determine hashing function and apply it to the hashlink index. */
    int idx;
    if (HASHING_FUNCTION==1)
        idx= stringHash1(k) % ht->tableSize;
    else
        idx= stringHash2(k) % ht->tableSize;

/* If key exists replace the hashlink */
    if( containsKey(ht, k) == 1)
    {
        ht->table[idx]->value = v;
    }
/* Key doesn't exist, create new hashLink, assign values and add it to the table*/
    else
    {
        struct hashLink *new_lnk = malloc( sizeof( struct hashLink ) );

        new_lnk->value = v;
        new_lnk->key = k;
        new_lnk->next = ht->table[idx];

        ht->table[ idx ] = new_lnk;
        ht->count += 1;
    }
}
/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{
    /*write this*/
/* Determine hashing function and apply it to the hashlink index. */
    int idx;
    if (HASHING_FUNCTION==1)
        idx= stringHash1(k) % ht->tableSize;
    else
        idx= stringHash2(k) % ht->tableSize;

/*Search for a link match using the contains function and return the value if found, otherwise NULL*/
    struct hashLink *myLink = ht->table[idx];
    while (myLink!=NULL)
    {
        if (containsKey(ht,k)==1)
            return &(myLink->value);/*Value stored in memory address!*/

            myLink = myLink->next;
    }

    return NULL;
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
	/*write this*/
/* Determine hashing function and apply it to the hashlink index. */
     int idx;
     if (HASHING_FUNCTION==1)
        idx= stringHash1(k) % ht->tableSize;
    else
        idx= stringHash2(k) % ht->tableSize;

    hashLink *mylink = ht->table[idx];

	while (mylink != NULL)
	{

		if (strcmp(mylink->key, k) == 0)
		{
			return 1;
		}
		mylink = mylink->next;
	}
	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{
    /*write this*/

/* Determine hashing function and apply it to the hashlink index. */
    int idx;
    if (HASHING_FUNCTION==1)
        idx = stringHash1(k) % ht->tableSize;
    else
        idx = stringHash2(k) % ht->tableSize;

    hashLink *myLink = ht->table[idx];

/*If there is a key match, free the free the memory*/

    if( strcpy( myLink->key, k ) == 0 )
    {
        struct hashLink *myLink_tmp = myLink->next;

        free( myLink->key );
        free( myLink );

        ht->table[ idx ] = myLink_tmp;
        ht->count -= 1;

        return;
    }

/* Check all next links for the match and free the memory if found. */
    while( myLink->next != NULL )
    {
        if( compare( myLink->next->key, k ) == 0 )
        {
            struct hashLink *myLink_tmp = myLink->next->next;

            free( myLink->next->key );
            free( myLink->next );

            myLink->next = myLink_tmp;
            ht->count -= 1;

            return;
        }
        myLink = myLink->next;
    }
}


/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
	/*write this*/
	return (ht->count);

}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
	/*write this*/
	return (ht->tableSize);
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
	/*write this*/
    int i;
    int cnt = 0;

    /*Loop through the table checking for empty buckets. Add to count if found. */
    for(i = 0; i < ht->tableSize; i++)
    {
        if(ht->table[i] == NULL)
            cnt++;
    }

    return cnt;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
	/*write this*/
    return( (float)( ht->count ) / (float)( ht->tableSize ) );
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" ->");
			temp=temp->next;
		}
	}
}


