#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER struct stack1
#define SIGN struct stack2

NUMBER {
    long long int value;
    NUMBER * nextN;
};

SIGN {
    char sign;
    SIGN * nextS;
};

void makeStackElementsNullS(SIGN * S){
    SIGN * runnerS = S->nextS;
    while(runnerS) {
        SIGN *next = runnerS->nextS;
        free(runnerS);
        runnerS = next;
    }
    S->nextS = NULL;
}

void makeStackElementsNullN(NUMBER * N){
    NUMBER * runnerN = N->nextN;
    while(runnerN) {
        NUMBER *next = runnerN->nextN;
        free(runnerN);
        runnerN = next;
    }
    N->nextN = NULL;
}

void syntaxError(NUMBER * N, SIGN * S){
    printf("%s", "syntax error");
    makeStackElementsNullS(S);
    makeStackElementsNullN(N);
    exit(0);
}

void pushN(NUMBER * N, NUMBER * n){
    NUMBER * numberFrst = N->nextN;
    n->nextN = numberFrst;
    N->nextN = n;
}

void pushS(SIGN * S, SIGN * s){
    SIGN * sgnFrst = S->nextS;
    s->nextS = sgnFrst;
    S->nextS = s;
}

int popN(NUMBER * N){
    int value = 0;
    NUMBER * DELETE_ELN =  NULL;
    if(N->nextN){
        value = N->nextN->value;
        DELETE_ELN = N->nextN;
        N->nextN = N->nextN->nextN;
    }
    free(DELETE_ELN);

    return value;
}

char popS(SIGN * S){
    char value = 0;
    SIGN * DELETE_ELS = NULL;
    if(S->nextS){
        value = S->nextS->sign;
        DELETE_ELS = S->nextS;
        S->nextS = S->nextS->nextS;
    }
    free(DELETE_ELS);

    return value;
}

int isEmptyN(NUMBER * N){
    return !(N->nextN);
}

int isEmptyS(SIGN * S){
    return !(S->nextS);
}

int operationDo(NUMBER * N, char sign, SIGN * S){
    switch (sign) {
        case '+' :
            return popN(N->nextN) + popN(N);
        case '-' :
            return popN(N->nextN) - popN(N);
        case '*' :
            return popN(N->nextN) * popN(N);
        case '/' :
            if (N->nextN->value == 0) {
                printf("%s", "division by zero");
                makeStackElementsNullS(S);
                makeStackElementsNullN(N);
                exit(0);
            }
            return popN(N->nextN) / popN(N);
        default:
            syntaxError(N, S);
            return 1;
    }
}

int priority(char sign){

    switch (sign) {
        case '+' :
            return 1;
        case '-' :
            return 1;
        case '*' :
            return 2;
        case '/' :
            return 2;
        default:
            return 0;
    }

}

char findSign(char sign){
    return (sign == '+' || sign == '-' || sign == '*' || sign == '/' || sign == '(' || sign == ')');
}

char findNumber(char number){
    int numASCII = number;
    return numASCII>47 && numASCII<58;
}

void checkSingleNumber(NUMBER * N, SIGN * S){
    if(N->nextN != NULL  && N->nextN->nextN != NULL){
        return;
    }
    syntaxError(N, S);
}

NUMBER* createNewElementN(long long int number){
    NUMBER * elem = (NUMBER*)malloc(sizeof(NUMBER));
    elem->value = number;
    return elem;
}

SIGN* createNewElementS(char sign){
    SIGN * elem = (SIGN*)malloc(sizeof(SIGN));
    elem->sign = sign;
    return elem;
}

void findOpenBracket(SIGN * S, char sign, NUMBER * N){
    SIGN * Sgn = S->nextS;
    while(Sgn && Sgn->sign != '('){
        Sgn = Sgn->nextS;
    }
    if(Sgn == NULL || sign == '('){
        syntaxError(N, S);
    }
}

void calculate(NUMBER * numberStack, SIGN * signStack, char * string, int stringLength){
    for(int i = 0; i < stringLength; i++){

        if(findNumber(string[i])){
            int num = string[i] - '0';
            while(i<stringLength && findNumber(string[++i])){
                num = num * 10 + (string[i]-'0');
            }
            i--;
            pushN(numberStack, createNewElementN(num));
        } else if(findSign(string[i])){
            if(isEmptyS(signStack) && string[i] != '(' && string[i] != ')'){
                pushS(signStack, createNewElementS(string[i]));
            } else {
                if(string[i] == '('){
                    pushS(signStack, createNewElementS(string[i]));
                } else if (string[i] == ')'){
                    if(i==0){
                        syntaxError(numberStack, signStack);
                    }
                    findOpenBracket(signStack, string[--i], numberStack);
                    i++;
                    while (signStack->nextS->sign != '('){
                        checkSingleNumber(numberStack, signStack);
                        pushN(numberStack, createNewElementN(operationDo(numberStack, signStack->nextS->sign, signStack)));
                        popS(signStack);
                    }
                    popS(signStack);
                } else if(priority(signStack->nextS->sign) < priority(string[i])){
                    pushS(signStack, createNewElementS(string[i]));
                } else {
                    if(!isEmptyN(numberStack)){
                        checkSingleNumber(numberStack, signStack);
                        pushN(numberStack, createNewElementN(operationDo(numberStack, signStack->nextS->sign, signStack)));
                        popS(signStack);
                        pushS(signStack, createNewElementS(string[i]));
                    } else {
                        syntaxError(numberStack, signStack);
                    }
                }
            }
        } else {
            syntaxError(numberStack, signStack);
        }

    }

    if(isEmptyN(numberStack)){
        printf("%s", "syntax error");
    } else {
        while(!isEmptyS(signStack)){
            checkSingleNumber(numberStack, signStack);
            pushN(numberStack, createNewElementN(operationDo(numberStack, signStack->nextS->sign, signStack)) );
            popS(signStack);
        }
        printf("%lld", numberStack->nextN->value);
        popN(numberStack);
    }
}

int main(void) {

    char * scanned;

    NUMBER * numberStack = (NUMBER*) malloc(sizeof(NUMBER));
    SIGN * signStack = (SIGN*) malloc(sizeof(SIGN));
    numberStack->nextN = NULL;
    signStack->nextS = NULL;

    int size = 1003;
    char string[size];

    scanned = fgets(string, size-1, stdin);
    if(scanned == NULL){
        printf("%s", "reading error");
    }

    int stringLength = strlen(string)-1;

    calculate(numberStack, signStack, string, stringLength);

    makeStackElementsNullN(numberStack);
    makeStackElementsNullS(signStack);

    free(numberStack);
    free(signStack);

    return EXIT_SUCCESS;
}
