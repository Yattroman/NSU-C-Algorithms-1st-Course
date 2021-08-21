#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

void numToB2Int(long long int intPart, int b2, int period){

    char resultArr[period];
    int i = period-1;

    while(intPart >= b2){
        resultArr[i] = intPart%b2;
        intPart /= b2;
        i--;
    }

    resultArr[0] = intPart;

    for(int k = 0; k<period; k++){
        printf("%x", resultArr[k]);
    }

}

void numToB2Fract(double fractPart, int b2){
    int length = 12;
    char resultArr[length];
    int i = 0;

    while(i < 12 && fractPart*b2 != 0){
        fractPart *= b2;

        resultArr[i] = fractPart/1;
        fractPart -= (int) fractPart/1;
        i++;

    }

    if(i != 0) { printf("%c", '.'); }
    for(int k = 0; k<i; k++){
        printf("%x", resultArr[k]);
    }
}

void numToDecimalInt(char* b1Num, int numLong, int b1, int b2, int start){
    long long int number = 0;
    long long int numberForPeriod = 0;
    int period = 0;
    for(int i = start; i<numLong; i++){
        int asciiCode = b1Num[i];
        switch (asciiCode){
            case 48: number += 0*pow(b1, numLong-1-i); break;
            case 49: number += 1*pow(b1, numLong-1-i); break;
            case 50: number += 2*pow(b1, numLong-1-i); break;
            case 51: number += 3*pow(b1, numLong-1-i); break;
            case 52: number += 4*pow(b1, numLong-1-i); break;
            case 53: number += 5*pow(b1, numLong-1-i); break;
            case 54: number += 6*pow(b1, numLong-1-i); break;
            case 55: number += 7*pow(b1, numLong-1-i); break;
            case 56: number += 8*pow(b1, numLong-1-i); break;
            case 57: number += 9*pow(b1, numLong-1-i); break;
            case 65: number += 10*pow(b1, numLong-1-i); break;
            case 66: number += 11*pow(b1, numLong-1-i); break;
            case 67: number += 12*pow(b1, numLong-1-i); break;
            case 68: number += 13*pow(b1, numLong-1-i); break;
            case 69: number += 14*pow(b1, numLong-1-i); break;
            case 70: number += 15*pow(b1, numLong-1-i); break;
            case 97: number += 10*pow(b1, numLong-1-i); break;
            case 98: number += 11*pow(b1, numLong-1-i); break;
            case 99: number += 12*pow(b1, numLong-1-i); break;
            case 100: number += 13*pow(b1, numLong-1-i); break;
            case 101: number += 14*pow(b1, numLong-1-i); break;
            case 102: number += 15*pow(b1, numLong-1-i); break;
        }
    }
    numberForPeriod = number;
    while(numberForPeriod>0){
        period++;
        numberForPeriod = numberForPeriod/b2;
    }

    if(number == 0){
        period = 1;
    }

    numToB2Int(number ,b2, period);
}

void numToDecimalFract(char* b1Num, int numLong, int b1, int start, int b2){
    double number = 0;
    int period = 0;
    for(int i = start; i<numLong; i++){
        int asciiCode = b1Num[i];
        switch (asciiCode){
            case 48: period++; number += 0*pow(b1, (-1) * period); break;
            case 49: period++; number += 1*pow(b1, (-1) * period); break;
            case 50: period++; number += 2*pow(b1, (-1) * period); break;
            case 51: period++; number += 3*pow(b1, (-1) * period); break;
            case 52: period++; number += 4*pow(b1, (-1) * period); break;
            case 53: period++; number += 5*pow(b1, (-1) * period); break;
            case 54: period++; number += 6*pow(b1, (-1) * period); break;
            case 55: period++; number += 7*pow(b1, (-1) * period); break;
            case 56: period++; number += 8*pow(b1, (-1) * period); break;
            case 57: period++; number += 9*pow(b1, (-1) * period); break;
            case 65: period++; number += 10*pow(b1, (-1) * period); break;
            case 66: period++; number += 11*pow(b1, (-1) * period); break;
            case 67: period++; number += 12*pow(b1, (-1) * period); break;
            case 68: period++; number += 13*pow(b1, (-1) * period); break;
            case 69: period++; number += 14*pow(b1, (-1) * period); break;
            case 70: period++; number += 15*pow(b1, (-1) * period); break;
            case 97: period++; number += 10*pow(b1, (-1) * period); break;
            case 98: period++; number += 11*pow(b1, (-1) * period); break;
            case 99: period++; number += 12*pow(b1, (-1) * period); break;
            case 100: period++; number += 13*pow(b1, (-1) * period); break;
            case 101: period++; number += 14*pow(b1, (-1) * period); break;
            case 102: period++; number += 15*pow(b1, (-1) * period); break;
        }
    }

    numToB2Fract(number, b2);
}

int numCheck(char* b1Num, int b1, int numLong, int start){
    int value = 0;
    for(int i = start; i<numLong; i++){
        int asciiCode = b1Num[i];
        switch (asciiCode){
            case 48: if(b1>0){value++;} break;
            case 49: if(b1>1){value++;} break;
            case 50: if(b1>2){value++;} break;
            case 51: if(b1>3){value++;} break;
            case 52: if(b1>4){value++;} break;
            case 53: if(b1>5){value++;} break;
            case 54: if(b1>6){value++;} break;
            case 55: if(b1>7){value++;} break;
            case 56: if(b1>8){value++;} break;
            case 57: if(b1>9){value++;} break;
            case 65: if(b1>10){value++;} break;
            case 66: if(b1>11){value++;} break;
            case 67: if(b1>12){value++;} break;
            case 68: if(b1>13){value++;} break;
            case 69: if(b1>14){value++;} break;
            case 70: if(b1>15){value++;} break;
            case 97: if(b1>10){value++;} break;
            case 98: if(b1>11){value++;} break;
            case 99: if(b1>12){value++;} break;
            case 100: if(b1>13){value++;} break;
            case 101: if(b1>14){value++;} break;
            case 102: if(b1>15){value++;} break;
        }
    }

    return (value == numLong-start) ? 0 : 1;
}

int findPoint(char* b1Num, int b1Long){
    int pointLocation = -1;
    int ptTimes = 0;
    for(int i = 0; i<b1Long; i++){
        if(b1Num[i] == '.'){
            ptTimes++;
            pointLocation = i;
        }
    }
    if(ptTimes > 1 || pointLocation == 0 || pointLocation == b1Long-1){
        return -2;
    } else if(pointLocation == -1){
        return -1;
    } else {
        return pointLocation;
    }
}

int main() {
    int b1, b2, ptLc, b1Long, checkResult;
    //char digits[] = "0123456789abcdef";
    //char digits_B[] = "0123456789ABCDEF";

    char *b1Num;
    b1Num = (char*)malloc(15);

    int scannedCount = scanf("%d %d\n %14s", &b1, &b2, b1Num);

    b1Long = strlen(b1Num);
    ptLc = findPoint(b1Num, b1Long);
    checkResult = 0;

    if (scannedCount != 3) {
        printf("not enough input data\n");
        free(b1Num);
        return 1;
    }
    if(b1<2 || b1>16 || b2<2 || b2>16 ){
        checkResult = -1;
    }
    if(ptLc == -1 && numCheck(b1Num, b1, b1Long, 0)){
        checkResult = -1;
    }
    if(ptLc > 0 && ( numCheck(b1Num, b1, b1Long, ptLc+1) || numCheck(b1Num, b1, ptLc, 0) ) ) {
        checkResult = -1;
    }
    if(ptLc == -2) {
        checkResult = -1;
    }

    if(checkResult<0){
        printf("%s\n", "bad input");
    } else if(ptLc == -1){
        numToDecimalInt(b1Num, b1Long, b1, b2, 0);
    } else {
        numToDecimalInt(b1Num, ptLc, b1, b2, 0);
        numToDecimalFract(b1Num, b1Long, b1, ptLc+1, b2);
    }

    free(b1Num);

    return 0;
}
