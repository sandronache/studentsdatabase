#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Tree initNode(char* last_name, char* first_name, int id, char* group, float average_grade) {
    Tree node = malloc(sizeof(struct tree));

    node->height = 0;
    node->left = NULL;
    node->right = NULL;

    node->data.id = id;
    node->data.average_grade = average_grade;
    int length;

    length = strlen(last_name) + 1;
    node->data.last_name = malloc(length * sizeof(char));
    strcpy(node->data.last_name, last_name);

    length = strlen(first_name) + 1;
    node->data.first_name = malloc(length * sizeof(char));
    strcpy(node->data.first_name, first_name);

    length = strlen(group) + 1;
    node->data.group = malloc(length * sizeof(char));
    strcpy(node->data.group, group);

    return node;
}

int max(int id1, int id2) {
	if(id1 > id2)
		return id1;
    return id2;
}

int height(Tree tree) {
	if(tree == NULL)
		return -1;
	return tree->height;
}

int balancedFactor(Tree tree) {
	if(tree == NULL)
		return 0;
	return height(tree->right) - height(tree->left);
}

void updateHeight(Tree tree) {
	if(tree == NULL)
		return;
	tree->height = max(height(tree->left), height(tree->right))	+ 1;
}

Tree leftRotation(Tree x) {
	if(x == NULL)
		return NULL;
	Tree y = x->right;
	x->right = y->left;
	y->left = x;
	x = y;
	updateHeight(x);
	updateHeight(y);
	return y;
}

Tree rightRotation(Tree y) {
	if(y == NULL)
		return NULL;
	Tree x = y->left;
	y->left = x->right;
	x->right = y;
	y = x;
	updateHeight(y);
	updateHeight(x);
	return x;
}

Tree fixingTree(Tree tree, int id) {
	updateHeight(tree);
	int bf = balancedFactor(tree);
	// Left left
	if(bf < -1 && id < tree->left->data.id)
		return rightRotation(tree);
	
	// Right right
	if(bf > 1 && id > tree->right->data.id)
		return leftRotation(tree);

	// left right
	if(bf < -1 && id > tree->left->data.id){
		tree->left = leftRotation(tree->left);	
		return rightRotation(tree);
	}

	// right left
	if(bf > 1 && id < tree->right->data.id){
		tree->right =  rightRotation(tree->right);
		return leftRotation(tree);
	}
		
	return tree;
}

Tree insert(Tree tree, char* last_name, char* first_name, int id, char* group, float average_grade) {
	if(tree == NULL) {
		tree = initNode(last_name, first_name, id, group, average_grade);
		return tree;
	}

	if(id < tree->data.id){
		tree->left = insert(tree->left, last_name, first_name, id, group, average_grade);
	}else if(id > tree->data.id){
		tree->right = insert(tree->right, last_name, first_name, id, group, average_grade);
	}else{
		return tree;
	}

	return fixingTree(tree, id);
}


Tree minimum(Tree tree) {
	if(tree == NULL)
		return NULL;
	while(tree->left != NULL){
		tree = tree->left;
	}
	return tree;
}

Tree delete(Tree tree, int id) {
	if(tree == NULL)
		return NULL;

	if(id < tree->data.id) {
		tree->left = delete(tree->left, id);
	} else if(id > tree->data.id) {
		tree->right = delete(tree->right, id);
	} else {
	    if((tree->left == NULL) || (tree->right == NULL)) {
			Tree z = tree->left ? tree->left : tree->right;
	    	if(z == NULL){
	    		z = tree;
	    		tree = NULL;
	    	}else {
	    		*tree = *z;
	    		}
	    	free(z);
	    } else {
	    	Tree successor = minimum(tree->right);
	    	tree->data.id = successor->data.id;
	    	tree->right = delete(tree->right, successor->data.id);
	    	}
	    }

    if(tree == NULL) return NULL;

    return fixingTree(tree, id);
}

void printFromLastName(Tree tree, char* last_name) {
	if(tree == NULL) return;
	if(strcmp(tree->data.last_name, last_name) == 0) {
		printNode(tree);
		printf("\n");
	}
	printFromLastName(tree->left, last_name);
	printFromLastName(tree->right, last_name);
}

void printFromFirstName(Tree tree, char* first_name) {
	if(tree == NULL) return;
	if(strcmp(tree->data.first_name, first_name) == 0) {
		printNode(tree);
		printf("\n");
	}
	printFromFirstName(tree->left, first_name);
	printFromFirstName(tree->right, first_name);
}

void printFromFirstandLastName(Tree tree, char* last_name, char* first_name) {
	if(tree == NULL) return;
	if(strcmp(tree->data.last_name, last_name) == 0 && strcmp(tree->data.first_name, first_name) == 0) {
		printNode(tree);
		printf("\n");
	}
	printFromFirstandLastName(tree->left, last_name, first_name);
	printFromFirstandLastName(tree->right, last_name, first_name);
}

void printFromId(Tree tree, int id) {
	if(tree == NULL) return;
	if(tree->data.id == id) {
		printNode(tree);
		printf("\n");
	}
	printFromId(tree->left, id);
	printFromId(tree->right, id);
}

void printFromGroup(Tree tree, char* group) {
	if(tree == NULL) return;
	if(strcmp(tree->data.group, group) == 0) {
		printNode(tree);
		printf("\n");
	}
	printFromGroup(tree->left, group);
	printFromGroup(tree->right, group);
}

void replaceLastName(Tree tree, int id, char* last_name) {
	if(tree == NULL) return;
	if(tree->data.id == id) {
		strcpy(tree->data.last_name, last_name);
		return;
	}
	replaceLastName(tree->left, id, last_name);
	replaceLastName(tree->right, id, last_name);
}

void replaceFirstName(Tree tree, int id, char* first_name) {
	if(tree == NULL) return;
	if(tree->data.id == id) {
		strcpy(tree->data.first_name, first_name);
		return;
	}
	replaceFirstName(tree->left, id, first_name);
	replaceFirstName(tree->right, id, first_name);
}

void replaceGroup(Tree tree, int id, char* group) {
	if(tree == NULL) return;
	if(tree->data.id == id) {
		strcpy(tree->data.group, group);
		return;
	}
	replaceGroup(tree->left, id, group);
	replaceGroup(tree->right, id, group);
}

void replaceAverageGrade(Tree tree, int id, float average_grade) {
	if(tree == NULL) return;
	if(tree->data.id == id) {
		tree->data.average_grade = average_grade;
		return;
	}
	replaceAverageGrade(tree->left, id, average_grade);
	replaceAverageGrade(tree->right, id, average_grade);
}

float calculateSumOfStudentsAverages(Tree tree) {
	if(tree == NULL) 
		return 0;
	return tree->data.average_grade + calculateSumOfStudentsAverages(tree->left) + calculateSumOfStudentsAverages(tree->right);
}

int calculateNumberOfStudents(Tree tree) {
	if(tree == NULL)
		return 0;
	return 1 + calculateNumberOfStudents(tree->left) + calculateNumberOfStudents(tree->right);
}

int calculateNumberOfStudentsWithGradeI(Tree tree, int i) {
	if(tree == NULL)
		return 0;
	if(tree->data.average_grade >= i && tree->data.average_grade < i + 1)
		return 1 + calculateNumberOfStudentsWithGradeI(tree->left, i) + calculateNumberOfStudentsWithGradeI(tree->right, i);
	else return calculateNumberOfStudentsWithGradeI(tree->left, i) + calculateNumberOfStudentsWithGradeI(tree->right, i);
}

int calculateNumberOfStudentsPromoted(Tree tree) {
	if(tree == NULL)
		return 0;
	if(tree->data.average_grade >= 5)
		return 1 + calculateNumberOfStudents(tree->left) + calculateNumberOfStudents(tree->right);
	else return calculateNumberOfStudents(tree->left) + calculateNumberOfStudents(tree->right);
}

int verifyId(Tree tree, int id) {
	if(tree == NULL) return 0;
	if(tree->data.id == id) {
		return 1 + verifyId(tree->left, id) + verifyId(tree->right, id);
	}
	return verifyId(tree->left, id) + verifyId(tree->right, id);
}

int verifyLastName(Tree tree, char* last_name) {
	if(tree == NULL) return 0;
	if(strcmp(tree->data.last_name, last_name) == 0) {
		return 1 + verifyLastName(tree->left, last_name) + verifyLastName(tree->right, last_name);
	}
	return verifyLastName(tree->left, last_name) + verifyLastName(tree->right, last_name);
}

int verifyFirstName(Tree tree, char* first_name) {
	if(tree == NULL) return 0;
	if(strcmp(tree->data.first_name, first_name) == 0) {
		return 1 + verifyFirstName(tree->left, first_name) + verifyFirstName(tree->right, first_name);
	}
	return verifyFirstName(tree->left, first_name) + verifyFirstName(tree->right, first_name);
}

int verifyGroup(Tree tree, char* group) {
	if(tree == NULL) return 0;
	if(strcmp(tree->data.group, group) == 0) {
		return 1 + verifyGroup(tree->left, group) + verifyGroup(tree->right, group);
	}
	return verifyGroup(tree->left, group) + verifyGroup(tree->right, group);
}

void printNodeFILE(Tree tree, FILE* fout) {
    fprintf(fout, "%s\n%s\n%d\n%s\n%0.2f\n", tree->data.last_name, tree->data.first_name, tree->data.id, tree->data.group, tree->data.average_grade);
}

void printNode(Tree tree) {
    printf("%s\n%s\n%d\n%s\n%0.2f\n", tree->data.last_name, tree->data.first_name, tree->data.id, tree->data.group, tree->data.average_grade);
}

void printAscending(Tree tree, FILE* fout) {
    if (tree == NULL) {
        return;
    }

    printAscending(tree->left, fout);
    printNodeFILE(tree, fout);
    printAscending(tree->right, fout);
}

void freeTree(Tree tree) {
	if(tree == NULL) return;
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree->data.last_name);
	free(tree->data.first_name);
	free(tree->data.group);
	free(tree);
}