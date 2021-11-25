#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


//Precompiler-Variablen


//Datatypes
typedef struct DataList
{
    char name[80];
    int mutex;
    int threadNr;
    struct DataList* next; //address of the next node
}
DataList; //this is ONE node in the List


//Protorypen
void makeList(char* nameOfFile);
void iterateList(void);
void iterateListAndCopy(void);
void deleteList(void);

//global Variables
DataList* gFirstData = NULL;   // der 1. Knoten in der Liste
DataList* gLastData = NULL;    // der letzte Knoten in der Liste
int gDataListsize;   //Größe von DataList