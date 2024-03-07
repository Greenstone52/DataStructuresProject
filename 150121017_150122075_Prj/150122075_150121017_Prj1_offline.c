// Ata Selçuk 150122075
// Eren Ahmet Yeþiltaþ 150121017

// Offline

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creating the structure for binary search tree nodes
struct BTNode {
	int key;
	int frequency;
	struct BTNode *left;
	struct BTNode *right;
};

// typedef for easier writing and understanding
typedef struct BTNode* BTNodePtr;
typedef struct BTNode BTNode;

// Not to overwrite a comma after the preorder traversal is over
int isPutComma = 0;

// Preorder function
void preorder(BTNodePtr ptr) {
	
	if(ptr != NULL) {
		if(isPutComma == 0){
			printf("%d",ptr->key);
		}else{
			printf(", %d",ptr->key);
		}
		isPutComma++;
		preorder(ptr->left);
		preorder(ptr->right);
	}
	
}

// Insert function for the binary search tree
BTNodePtr insert(int key, int frequency, BTNodePtr ptr) {
	
	// If we don't have any more nodes, we insert new node with this block
	if (ptr == NULL) { 
		ptr = malloc(sizeof(BTNode));
		if (ptr == NULL) {
			printf("No heap space in avaliable.");
		}
		ptr->key = key;
		ptr->frequency = frequency;
		ptr->left = ptr->right = NULL;
		return ptr;
	}
	
	// If the frequency is greater we do a rotation with this block
	if (frequency > ptr->frequency) {
		
		BTNodePtr tempPtr = malloc(sizeof(BTNode));
		if (tempPtr == NULL) {
			printf("No heap space in avaliable.");
		}
		
		// Copy our values to the temporary pointer
		tempPtr->key = key;
		tempPtr->frequency = frequency;
		
		// If key is greater than our ptr's key then we put the values at the left child
		if(key > ptr->key) {
			tempPtr->left = ptr;
			tempPtr->right = NULL;
			ptr = tempPtr;
			
		}
		// If key is less than our ptr's key then we put the values at the right child
		else if(key < ptr->key) {
			tempPtr->right = ptr;
			tempPtr->left = NULL;
			ptr = tempPtr;
		}
		
	}
	
	// If the frequency is less we keep inserting as if it's a normal bst
	else if(frequency <= ptr->frequency) {
		if(key > ptr->key) {
			ptr->right = insert(key,frequency,ptr->right);
		}
		else if(key < ptr->key) {
			ptr->left = insert(key,frequency,ptr->left);
		}
	}
	return ptr;
}

int main(int argc, char *argv[]) {
	
	// Create a file pointer to find the number of nodes in the input file
	FILE *fptr;
	fptr = fopen(argv[1],"r");
	
	// Create a file pointer to get the data from it
	FILE *fptr2;
	fptr2 = fopen(argv[1],"r");
	
	
	// Compute the number of nodes
	int lineCounter = 0;
	
	char *line[5];
	while (fgets(line, sizeof(line), fptr) != NULL) {
		lineCounter++;
    }
    
    // Get the nodes' data to a 2D array
    int keyFreq[lineCounter][2];
    
    int i = 0;
    int j;
    char *line2[5];     	
        	
    while (fgets(line2, sizeof(line2), fptr2) != NULL) {
    	
    	// To separate two values (key, frequency) easier we used string token
    	char *tkn = strtok(line2,",");
    	
    	for(j = 0; j<2;j++){
    		keyFreq[i][j] = atoi(tkn);
    		tkn = strtok(NULL,",");
		}
		
    	i++;	 		
    }
	
	// Construct the BST
	BTNodePtr ptr = NULL;
	
	for(i = 0; i<lineCounter;i++){
		ptr = insert(keyFreq[i][0],keyFreq[i][1],ptr);
	}
	
	// Pre-order traversal of the bst
	printf("Pre-order traversal of constructed tree : ");
	preorder(ptr);
	
	
	// Close the file pointers
    fclose(fptr2);
    fclose(fptr);    
}
