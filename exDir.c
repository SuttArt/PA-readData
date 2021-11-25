#include "exDir.h"

int main(void)
{
    DIR* dir;
    char x [80]; //string in C => char* x; => dann malloc() benutzen
    struct dirent* d_pntr;


    dir = opendir("./A");
    if(dir != NULL)
    {
        while ((d_pntr = readdir(dir)) != NULL)
        {
            //strcpy(x,d_pntr -> d_name);
            strcpy(x,(*d_pntr).d_name);
            printf("\nName: %s",x);
            if (strcmp(x, ".") == 1 && strcmp(x,"..") == 1) //(x[0] != '.' || (x[0] != '.' && x[1] != '.'))
            {
                makeList(x);
            }

            iterateListAndCopy();

        }
        closedir(dir);
        iterateList();
        deleteList();
    }
    return 0;
}

//TODO: 1) List mit Dateinamen aufbauen.
//TODO: 2) Diese Liste durchgehen und Dateien von ./A nach ./B zu kopieren.
void makeList(char* nameOfFile)
{
    DataList* current = NULL; //current/working Node of the List

    int gDataListsize = sizeof (DataList);

    current = (DataList*) malloc(gDataListsize);//Storage reservation
    strcpy(current -> name, nameOfFile);
    current -> mutex = 0;
    current -> threadNr = 0;
    current -> next = NULL;
    //list is empty
    if (gFirstData == NULL)
    {
        gFirstData = current;
    }
    else
    {
        gLastData -> next = current;
    }
    gLastData = current;
}

void iterateList(void)
{
    DataList* current = gFirstData; //current/working Node of the List

    while (current != NULL)
    {
        printf("\n== my address: %p == name of file: %s == address of next: %p",current ,current->name, current->next);
        current = current->next;

    }
}

void iterateListAndCopy(void)
{
    DataList* current = gFirstData; //current/working Node of the List
    char name_in[80]; // full name of source name
    char name_out[80]; //full name of target file
    FILE* in; // handler
    FILE* out;
    char ch;

    while (current != NULL)
    {
        strcpy(name_in, "./A/");
        strcpy(name_out, "./B/");
        strcat(name_in, current -> name); // "./A/dat01.txt"
        strcat(name_out, current -> name);

        in = fopen(name_in,"rb"); //rb ?! Byte? Binary??
        out = fopen(name_out,"wb");

        while ((ch=fgetc(in)) != EOF) //EOF - End Of File
        {
            fputc(ch,out);
        }
//            while ((ch=fgetc(in)) != EOF) //EOF - End Of File
//                fputc(ch,out); //Geht auch, weil wir nur 1 Anweisung hier haben
        fclose(in);
        fclose(out);

        current = current->next;
    }
}

void deleteList(void)
{
    DataList* current = gFirstData; //current/working Node of the List
    DataList* x = NULL; //temporary Node of the List

    while (current != NULL)
    {
        printf("\nFreigabe: %s", current->name);
        x = current->next;
        free(current);
        current = x;
    }
}