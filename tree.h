#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    char* last_name;
    char* first_name;
    int id;
    char* group;
    float average_grade;
} Data;

typedef struct tree {
    Data data;
    int height;
    struct tree* left;
    struct tree* right;
} *Tree;


Tree initNode(char* last_name, char* first_name, int id, char* group, float average_grade);
int max(int id1, int id2);
int height(Tree tree);
int balancedFactor(Tree tree);
void updateHeight(Tree tree);
Tree leftRotation(Tree x);
Tree rightRotation(Tree y);
Tree fixingTree(Tree tree, int id);
Tree insert(Tree tree, char* last_name, char* first_name, int id, char* group, float average_grade);
Tree minimum(Tree tree);
Tree delete(Tree tree, int id);
void printFromLastName(Tree tree, char* last_name);
void printFromFirstName(Tree tree, char* first_name);
void printFromFirstandLastName(Tree tree, char* last_name, char* first_name);
void printFromId(Tree tree, int id);
void printFromGroup(Tree tree, char* group);
void replaceLastName(Tree tree, int id, char* last_name);
void replaceFirstName(Tree tree, int id, char* first_name);
void replaceGroup(Tree tree, int id, char* group);
void replaceAverageGrade(Tree tree, int id, float average_grade);
float calculateSumOfStudentsAverages(Tree tree);
int calculateNumberOfStudents(Tree tree);
int calculateNumberOfStudentsPromoted(Tree tree);
int calculateNumberOfStudentsWithGradeI(Tree tree, int i);
int verifyLastName(Tree tree, char* last_name);
int verifyFirstName(Tree tree, char* first_name);
int verifyGroup(Tree tree, char* group);
void printNodeFILE(Tree tree, FILE* fout);
int verifyId(Tree tree, int id);
void printNode(Tree tree);
void printAscending(Tree tree, FILE* fout);
void freeTree(Tree tree);