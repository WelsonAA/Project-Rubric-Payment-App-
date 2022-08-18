//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_CARD_H
#define UNTITLED3_CARD_H

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "E:\untitled3\top.h"
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    OK_c, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    strcpy(cardData->cardHolderName ,get_string(NULL,"Enter Card Holder Name:\n"));


    int n=strlen(cardData->cardHolderName)-1;
    for(int i=0;i<n;i++){
        if(isalpha(cardData->cardHolderName[i])==0 && cardData->cardHolderName!=' '){
            return WRONG_NAME;
        }
    }
    if(cardData->cardHolderName[0]=='\0')
        return WRONG_NAME;;
    if( n<20 || n>24 ){

        return WRONG_NAME;
    }
    else{
        return OK_c;
    }
};
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    strcpy(cardData->cardExpirationDate ,get_string(NULL,"Enter Card Expiration Date:\n"));
    int n=strlen(cardData->cardExpirationDate)-1;
    if(n!=5 || cardData->cardExpirationDate[0]=='\0') return WRONG_EXP_DATE;
    int flag=0;
    for(int i=0;i<(n-1);i++){
        if(i!=2 && isdigit(cardData->cardExpirationDate[i])==0){
            flag =1;
            break;
        }
        if(cardData->cardExpirationDate[2]!='/') {
            flag =1;
            break;
        }
    }

    int date[2];
    char* token = strtok(cardData->cardExpirationDate, "/");
    int i=0;
    while (token != NULL && i<2) {
        date[i]= atoi(token);

        token = strtok(NULL, "/");
        i++;
    }
    if(date[0]>12 || date[0]<1) return WRONG_EXP_DATE;
    if(date[1]>99 || date[1]<0) return WRONG_EXP_DATE;
    if(flag ==1){
        return WRONG_EXP_DATE;
    }
    else return OK_c;
};
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    strcpy(cardData->primaryAccountNumber ,get_string(NULL,"Enter Primary Account Number:\n"));
    int n=strlen(cardData->primaryAccountNumber);

    if(n<16 || n> 19 || cardData->primaryAccountNumber[0]=='\0'){
        return WRONG_PAN;
    }
    int flag =0;
    for(int i=0;i<n;i++){
        if(isalnum(cardData->primaryAccountNumber[i])==0){
            flag=1;
            break;
        }
    }
    if(flag==0)
    return OK_c;
    else return WRONG_PAN;
};

#endif //UNTITLED3_CARD_H
