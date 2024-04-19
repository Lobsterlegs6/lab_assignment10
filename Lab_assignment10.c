#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Tri *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *tmp = pTrie;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        
        // Check if index is valid
        if (index < 0 || index >= 26)
        {
            printf("Invalid character in word: %c\n", word[i]);
            return;
        }
        
        if (tmp->children[index] == NULL)
        {
            tmp->children[index] = createTrieNode();
            if (tmp->children[index] == NULL)
            {
                printf("Memory allocation error\n");
                return;
            }
        }
        
        tmp = tmp->children[index];
    }
    tmp->count++;
}


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
     struct Trie *tmp = pTrie;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (tmp->children[index] == NULL)
        {
            return 0; 
        }
        tmp = tmp->children[index];
    }
    return tmp->count;
}


// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    struct Trie *tmp = pTrie;
     if (tmp == NULL) 
    {
        return NULL;
    }
    for (int i = 0; i < 26; i++) 
    {
        if (pTrie->children[i] != NULL) 
        {
            deallocateTrie(tmp->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *newNode = malloc(sizeof(struct Trie));
    newNode->count = 0;

    for(int i = 0; i<26; i++)  {
        newNode->children[i] = NULL;
    }

    return newNode;

}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) return -1;

    int count = 0;

    fscanf(fp, "%d\n", &count);
    char word[100];
    for (int i = 0; i<count; i++) {
        fscanf(fp, "%s\n", word);
        pInWords[i] = (char*)calloc(strlen(word), sizeof(char));
        strcpy(pInWords[i], word);
    }

    return count;
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