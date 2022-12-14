//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_TERMINAL_H
#define UNTITLED3_TERMINAL_H

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../top.h"
typedef enum EN_terminalError_t
{
    OK_t, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

int isleap(int x) {
    if((0==x%4) && (0!=x%100) && (0==x%400))
        return 1;
    else
        return 0;
}

int isvalid(int d, int m, int y) {
    if(2000>y || 2100<y)
        return 0;
    if(1>m || 12<m)
        return 0;
    if(1>d || 31<d)
        return 0;
    if( 2==m) {
        if(isleap(y)) {
            if(d <= 29)
                return 1;
            else
                return 0;
        }
    }
    if ( 4==m || 6==m || 9==m || 11==m )
        if(30>=d)
            return 1;
        else
            return 0;
    return 1;
}

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    string expdate;
    expdate=strcpy(termData->transactionDate,get_string(NULL,"Enter Transaction Date:\n"));
    int n= strlen(termData->transactionDate);
    if(termData->transactionDate[0]=='\0') return WRONG_DATE;
    if (n!=10) return WRONG_DATE;
    for(int i=0;i<n;i++){
        if(i!=2 && i!=5 && isdigit(termData->transactionDate[i])==0)return WRONG_DATE;
        if(i==2 || i==5){
            if(termData->transactionDate[i]!='/') return WRONG_DATE;
        }
    }



    int date[3];
    char* token = strtok(expdate, "/");
    int i=0;
    while (token != NULL && i<3) {
        date[i]= atoi(token);

        token = strtok(NULL, "/");
        i++;
    }
    for (int i=0;i<n;i++){
        if(expdate[i]=='\0'){
            expdate[i]='/';
        }
    }
    if(isvalid(date[0],date[1],date[2])==0) return WRONG_DATE;
    else return OK_t;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    int exp[2];
    int trans[2];
    char* tokene = strtok(cardData.cardExpirationDate, "/");
    int i=0;
    while (tokene != NULL && i<2) {
        exp[i]= atoi(tokene);

        tokene = strtok(NULL, "/");
        i++;
    }
    char* tokent= strtok(&termData.transactionDate[3],"/");
    int j=0;
    while(tokent!=NULL&&j<2){
        trans[j]=atoi(tokent);
        tokent = strtok(NULL, "/");
        ++j;
    }
    if((exp[1]+2000)<trans[1]){
        return EXPIRED_CARD;
    }
    else if(exp[1]==trans[1]){
        if(exp[0]<trans[0]){
            return EXPIRED_CARD;
        }
    }
    return OK_t;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

        int n = strlen(cardData->primaryAccountNumber);

        int nSum = 0, isSecond = false;
        for (int i = n - 1; i >= 0; i--) {
            int d= cardData->primaryAccountNumber[i]-'0';
            if (isSecond == true)
                d = d * 2;

            nSum += d / 10;
            nSum += d % 10;

            isSecond = !isSecond;
        }
    if(nSum % 10 ==0) {
        return OK_t;}
    else return INVALID_CARD ;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    float in= get_float("Enter Transaction Amount:\n");
    if(in<=0)return INVALID_AMOUNT;
    termData->transAmount=in;
    return OK_t;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount>termData->maxTransAmount) return EXCEED_MAX_AMOUNT;
    else return OK_t;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    float in= get_float("Enter Max Amount:\n");
    if(in>0){
        termData->maxTransAmount=in;
        return OK_t;
    }
    return INVALID_MAX_AMOUNT;
}

#endif //UNTITLED3_TERMINAL_H
