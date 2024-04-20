#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int count;
	struct Trie* children[26];	
};

// Initializes a trie structure
struct Trie *createTrie()
{
	struct Trie *pTrie = (struct Trie*) malloc(sizeof(struct Trie));

	for(int i = 0; i< 26; i++){
		pTrie->children[i] = NULL;
	}
	pTrie->count = 0;
	return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	struct Trie* tmp = pTrie;
    
    for (int i = 0; i < strlen(word); i++){

        int index = word[i] - 'a';

        if (tmp->children[index] == NULL){
			tmp->children[index] = createTrie();
        }
        tmp = tmp->children[index];
    }
    tmp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	 for (int i = 0; i < strlen(word); i++){

        int index = word[i] - 'a';

        if (pTrie->children[index] == NULL){
            return 0;
        }

        pTrie = pTrie->children[index];
    }
    return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	if (pTrie == NULL){
		return NULL;
	}

	else if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i] != NULL) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE* file;
    int count = 0;
    char words[256];

    file = fopen(filename, "r");
    if (file == NULL) {
        exit(1);
    }

    fscanf(file, "%d", &count);

    for (int i = 0; i < count; ++i) {
        fscanf(file, "%s", words);
        pInWords[i] = strdup(words);
    }

    fclose(file);
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