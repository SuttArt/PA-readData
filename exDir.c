#include "exDir.h"

int main(void)
{
    DIR* dir;
    char x [80]; //string in C => char* x; => dann malloc() benutzen
    struct dirent* d_pntr;
    char name_in[80]; // full name of source name
    char name_out[80]; //full name of target file
    FILE* in; // handler
    FILE* out;
    char ch;

    dir = opendir("./A");
    if(dir != NULL)
    {
        while ((d_pntr = readdir(dir)) != NULL)
        {
            //strcpy(x,d_pntr -> d_name);
            strcpy(x,(*d_pntr).d_name);
            printf("\n%s",x);
            strcpy(name_in, "./A/");
            strcpy(name_out, "./B/");
            strcat(name_in, x); // "./A/dat01.txt"
            strcat(name_out, x);
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

        }
        closedir(dir);
    }
    return 0;
}

//TODO: 1) List mit Dateinamen aufbauen.
//TODO: 2) Diese Liste durchgehen und Dateien von ./A nach ./B zu kopieren.