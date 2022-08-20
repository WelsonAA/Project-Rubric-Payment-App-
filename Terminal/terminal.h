//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_TERMINAL_H
#define UNTITLED3_TERMINAL_H

#include <stdint.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#include "E:\untitled3\top.h"
/*typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;*/

typedef enum EN_terminalError_t
{
    OK_t, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;
int isleap(int y) {
    if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
        return 1;
    else
        return 0;
}
int isvalid(int d, int m, int y) {
    if(y < 2000 || y > 2100)
        return 0;
    if(m < 1 || m > 12)
        return 0;
    if(d < 1 || d > 31)
        return 0;
    //Now we will check date according to month
    if( m == 2 ) {
        if(isleap(y)) {
            if(d <= 29)
                return 1;
            else
                return 0;
        }
    }
    //April, June, September and November are with 30 days
    if ( m == 4 || m == 6 || m == 9 || m == 11 )
        if(d <= 30)
            return 1;
        else
            return 0;
    return 1;
}
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){

    strcpy(termData->transactionDate,get_string(NULL,"Enter Transaction Date:\n"));
    int n= strlen(termData->transactionDate);
    if(termData->transactionDate[0]=='\0') return WRONG_DATE;
    if (n!=10) return WRONG_DATE;
    for(int i=0;i<n;i++){
        if(i!=2 && i!=5 && isdigit(termData->transactionDate[i])==0)return WRONG_DATE;
        if(i==2 || i==5){
            if(termData->transactionDate[i]!='/') return WRONG_DATE;
        }
    }
    string expdate;
    strcpy(expdate,&termData->transactionDate);
    int date[3];
    char* token = strtok(expdate, "/");
    int i=0;
    while (token != NULL && i<3) {
        date[i]= atoi(token);

        token = strtok(NULL, "/");
        i++;
    }
    if(isvalid(date[0],date[1],date[2])==0) return WRONG_DATE;
    else return OK_t;

};
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    int exp[2];
    int trans[2];
    char seps[]="/";
    int var;
    string expiry,transaction;
    strcpy(expiry,cardData.cardExpirationDate);
    strcpy(transaction,termData.transactionDate);
    if((exp[1]+2000)<trans[1]){
        return EXPIRED_CARD;
    }
    else if(exp[1]==trans[1]){
        if(exp[0]<trans[0]){
            return EXPIRED_CARD;
        }
    }
};
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

        int n = strlen(cardData->primaryAccountNumber);

        int nSum = 0, isSecond = false;
        for (int i = n - 1; i >= 0; i--) {


            int d= cardData->primaryAccountNumber[i]-'0';
            if (isSecond == true)
                d = d * 2;

            // We add two digits to handle
            // cases that make two digits after
            // doubling
            nSum += d / 10;
            nSum += d % 10;

            isSecond = !isSecond;
        }
    if(nSum % 10 ==0) {
        return OK_t;}
    else return INVALID_CARD;


};
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    float in= get_float("Enter Transaction Amount:\n");
    if(in<=0) {
        termData->transAmount=in;
        return INVALID_AMOUNT;
    }
    return OK_t;
};
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount>termData->maxTransAmount) return EXCEED_MAX_AMOUNT;
    else return OK_t;
};
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    float in= get_float("Enter Max Amount:\n");
    if(in>0){
        termData->maxTransAmount=in;
        return OK_t;
    }
    return INVALID_AMOUNT;
};
#endif //UNTITLED3_TERMINAL_H
