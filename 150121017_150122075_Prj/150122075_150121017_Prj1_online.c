// Ata Selçuk 150122075
// Eren Ahmet Yeþiltaþ 150121017

// Online

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

// This variable is used to determine if the rotation cycle is over or not
int isRotate = 0;

// Preorder function
void preorder(BTNodePtr ptr) {
	
	if (ptr != NULL) {
		if (isPutComma == 0) {
			printf("(%d,%d)",ptr->key,ptr->frequency);
		}
		else {
			printf(",(%d,%d)",ptr->key,ptr->frequency);
		}
		isPutComma++;
		preorder(ptr->left);
		preorder(ptr->right);
	}
	
}

// Insert function for the binary search tree
BTNodePtr insert(int key,int frequency, BTNodePtr ptr) {
					
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
		
		BTNodePtr tempPtr = malloc(sizeof(struct BTNode));
		if (tempPtr == NULL) {
			printf("No heap space in avaliable.");
		}
		
		// Copy our values to the temporary pointer
		tempPtr->key = key;
		tempPtr->frequency = frequency;
		
		// If key is greater than our ptr's key then we put the values at the left child
		if (key > ptr->key) {
			tempPtr->left = ptr;
			tempPtr->right = NULL;
			ptr = tempPtr;
			
		}
		// If key is less than our ptr's key then we put the values at the right child
		else if (key < ptr->key) {
			tempPtr->right = ptr;
			tempPtr->left = NULL;
			ptr = tempPtr;
		}
		
	}
	// If the frequency is less we keep inserting as if it's a normal bst
	else if (frequency <= ptr->frequency) {
		if (key > ptr->key) {
			ptr->right = insert(key,frequency,ptr->right);
		}
		else if (key < ptr->key) {
			ptr->left = insert(key,frequency,ptr->left);
		}
	}
	
	return ptr;
	
}

// This block increases the frequency of the node that was searched
BTNodePtr increaseFrequency(int key,BTNodePtr ptr) {
	
	if (key > ptr->key) {
		ptr->right = increaseFrequency(key,ptr->right);
	}
	else if (key < ptr->key) {
		ptr->left = increaseFrequency(key,ptr->left);
	}
	else if (key == ptr->key) {
		ptr->frequency++;
		return ptr;
	}
	return ptr;
}

// This block rotates the binary search tree to prioritize greater frequency nodes
void rotation(BTNodePtr ptr) {
	// These variables are used to determine if our current node has NULL poointers for right and left nodes
	int rightChild = 1;
	int leftChild = 1;
	
	// If the right pointer is NULL then we assign 0 to rightChild variable
	if (ptr->right == NULL) {
		rightChild = 0;
	}
	
	// If the left pointer is NULL then we assign 0 to leftChild variable
	if (ptr->left == NULL) {
		leftChild = 0;
	}
	
	// If leftChild is not NULL then we check the frequencies
	if (leftChild == 1) {
		
		// If current frequency is greater than the children's frequency then we keep checking and don't do a rotation
		if(ptr->frequency >= ptr->left->frequency) {
			rotation(ptr->left);
		}
		
		// If current frequency is less than the children's frequency then we do the rotation
		else if(ptr->frequency < ptr->left->frequency) {
			
			// We assign our current values to the temporary pointer
			BTNodePtr tempPtr = malloc(sizeof(BTNode));
			tempPtr->key = ptr->key;
			tempPtr->frequency = ptr->frequency;
			tempPtr->right = ptr->right;
			tempPtr->left = ptr->left->right;
			
			// Rotation block
			ptr->key = ptr->left->key;
			ptr->frequency = ptr->left->frequency;
			ptr->left = ptr->left->left;
			ptr->right = tempPtr;
			
			ptr = tempPtr;
			
			// isRotate is set to 1 as we did a rotation and we need to check again if we need to do another rotation
			isRotate = 1;
		}
	}
	
	// Same thing as the upper block but for the right child of our current node
	if (rightChild == 1) {
		if (ptr->frequency >= ptr->right->frequency) {
			rotation(ptr->right);
		}
		else if (ptr->frequency < ptr->right->frequency) {
			
			BTNodePtr tempPtr = malloc(sizeof(BTNode));
			tempPtr->key = ptr->key;
			tempPtr->frequency = ptr->frequency;
			tempPtr->left = ptr->left;
			tempPtr->right = ptr->right->left;
			
			ptr->key = ptr->right->key;
			ptr->frequency = ptr->right->frequency;
			ptr->right = ptr->right->right;
			ptr->left = tempPtr;
			
			ptr = tempPtr;
			
			isRotate = 1;
		}
	}
	
}

int main(int argc, char *argv[]) {
	
	// Create a file pointer to find the number of node in the input file.
	FILE *fptr;
	fptr = fopen(argv[1],"r");
	
	// Create a file pointer to get the data from it.
	FILE *fptr2;
	fptr2 = fopen(argv[1],"r");
	
	
	// Compute the number of nodes
	int lineCounter = 0;
	
	char *line[5];
	while (fgets(line, sizeof(line), fptr) != NULL) {
		lineCounter++;
    }
    
    // Get the nodes' data to an 2D array
    int keyFreq[lineCounter][2];
    
    int i = 0;
    while (fgets(line, sizeof(line), fptr2) != NULL) {
	    keyFreq[i][0] = atoi(line);
	    keyFreq[i][1] = 0;
		i++; 
    }
    
    // Create a BST
    BTNodePtr newBTNode = NULL;
    
    for (i = 0; i<lineCounter; i++) {
    	newBTNode = insert(keyFreq[i][0],keyFreq[i][1],newBTNode);
	}

	printf("Pre-order traversal of constructed tree : ");
	preorder(newBTNode);
	
	// Operations
 	while (1 > 0) {
 		isPutComma = 0;
 		int number;
 		
 		printf("\nEnter a value to search: ");
		scanf("%d", &number);
		
		int numberControl = 0;
			
		for (i = 0; i < lineCounter; i++) {
			if (number == keyFreq[i][0]) {
				numberControl = 1;
			}
		}
		
		if (numberControl == 0) {
			printf("The value entered (%d) does not exist in the binary search tree. ", number);
			continue;
		}
		
		increaseFrequency(number,newBTNode);
		
		rotation(newBTNode);
		
		// We check for isRotate variable to see if we need to check for a rotation or not,
		// if isRotate is 0 then the rotation cycle is over, if not we check 
		while (isRotate == 1) {
			isRotate = 0;
			rotation(newBTNode);
		}
		
		printf("Pre-order traversal of constructed tree : ");
		preorder(newBTNode);
	}	
	 
}
