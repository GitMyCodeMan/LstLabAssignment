#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int isWord;
    struct Trie* nextChar[26];
};

struct Trie* createTrieNode() {
    struct Trie* newNode = (struct Trie*)malloc(sizeof(struct Trie));
    for (int i = 0; i < 26; i++) {
        newNode->nextChar[i] = NULL;
    }
    
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* currentNode = pTrie;

    int i;
    for(i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';

        if(currentNode->nextChar[index] == NULL){
            currentNode->nextChar[index] = createTrieNode();
        }
        currentNode = currentNode->nextChar[index];
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* currentNode = pTrie;
    
    int i;
    for(i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if(currentNode->nextChar[index] != NULL){
            return 0;
        }
        currentNode = currentNode->nextChar[index];
    }

    return currentNode->isWord;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie){
        int i;

        for(i = 0; i < 26; i++){
            if(pTrie->nextChar[i]){
                deallocateTrie(pTrie->nextChar[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* tree = (struct Trie*) malloc(sizeof(struct Trie));
    
    int i;
    for(int i = 0; i < 26; i++){
        tree->nextChar[i] = NULL;
        tree->isWord = 0;
    }

    return tree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* fp;
    int numWords = 0;
    char word[256];

    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error opening file");
        exit;
    }

    fscanf(fp, "%d", numWords);

    int i;
    for(i = 0; i < numWords; i++){
        fscanf(fp, "%s", word);
        pInWords[i] = strdup(word);
    }

    fclose(fp);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}