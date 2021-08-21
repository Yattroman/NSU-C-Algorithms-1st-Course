#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PATTERN_SIZE 17
#define TABLE_SIZE 256
#define BUFFER_SIZE 65556

char* deleteN(char* string){
    if(string == NULL){
        return NULL;
    }
    if(string[strlen(string) - 1]=='\n'){
        string[strlen(string) - 1] = '\0';
    }
    return string;
}

int updateBuffer(char* buf, int j){
    int readSymb;

    readSymb = (int)fread(buf+j, sizeof(char), BUFFER_SIZE-j, stdin);

    return readSymb;
}

void boyerMoore(char* pattern, char* buf, int* Table, int patternLength, int bufLength){
    int pos = patternLength-1;
    int j;
    j=0;
    int readSymb = bufLength;
    int globalPos = patternLength-1;
    int sum = bufLength;

    while(1)
    {
        int repeats = 0;
        char lastSymb = 'c';
        int i = 0;
        while (i <= patternLength - 1) {
            if (pattern[patternLength - 1 - i] == buf[pos - i]) {
                if(globalPos - i + 1 <= sum) {
                    printf("%d ", globalPos - i + 1);
                }
                repeats++;
                i++;
            } else {
                lastSymb = buf[pos - i];
                if(globalPos - i + 1 <= sum) {
                    printf("%d ", globalPos - i + 1);
                }
                break;
            }
        }

        if (repeats == 0) {
            int index = lastSymb;
            pos = pos - i + Table[index];
            globalPos = globalPos - i + Table[index];
        } else if (repeats == patternLength) {
            pos = pos - i + patternLength + patternLength;
            globalPos = globalPos - i + patternLength + patternLength;
        } else if (repeats != 0) {
            int ind = pattern[patternLength - 1];
            pos = pos - i + Table[ind] + repeats;
            globalPos = globalPos - i + Table[ind] + repeats; // Norm
        }

        if(pos>bufLength-1){
            pos -= (patternLength-1);
            j = 0;
            for(int k = pos; k<bufLength; k++){
                buf[j] = buf[k];
                j++;
            }
            readSymb = updateBuffer(buf, j) ;
            if(readSymb == 0){
                break;
            }
            pos=patternLength-1;
            sum+=readSymb;
        }

    }
}

int* makeTable (int* Table ,char* pattern, int patternLength){
    int mv;
    mv = 0;

    // Заполняем таблицу длиной шаблона
    for(int i = 0; i < 256; i++){
        Table[i] = patternLength;
    }
    for(int j = patternLength-2; j >= 0; j--){
        int index = pattern[j];
        mv++;
        if(pattern[j] && Table[index] == patternLength){
            Table[index] = mv;
        }
    }
    return Table;
}

int main(void) {
    int table[TABLE_SIZE + 1] = {0};
    int* Table = table;

    char pattern[PATTERN_SIZE+1] = "";
    deleteN(fgets (pattern, PATTERN_SIZE+1, stdin));
    int patternLength = strlen(pattern);
    if(patternLength==0){
        printf("%s", "bad input");
        return 1;
    }

    char* buf;
    buf = (char*)malloc(BUFFER_SIZE * sizeof(char));
    int textLength = updateBuffer(buf, 0);

    if(textLength < patternLength){
        exit(0);
    }

    makeTable(Table, pattern, patternLength);
    boyerMoore(pattern, buf, Table, patternLength, textLength);

    free(buf);

    return 0;
}
