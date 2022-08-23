//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_SERVER_H
#define UNTITLED3_SERVER_H

#include <stdint.h>
#include <string.h>

#include "../Card/card.h"

typedef enum EN_transState_t
{
APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
    OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t ;

typedef struct ST_accountsDB_t
{
    float balance;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    enum EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction;

ST_accountsDB_t accglobal[255]={
    {
    8000.0,"7502289947808108"
    },{
    755.0,"51714505293369193"
    }
};

struct ST_transaction_t transactionglobal[255]={
        {
                {"0","0","0"},{0.0,0.0,"0"},0,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},0,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},0,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},0,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},0,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},0,0
        }
};

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    for(int i=0;i<255;i++){
        if(strcmp(cardData->primaryAccountNumber,accglobal[i].primaryAccountNumber)==0){
            return OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t *accountsDb){
        if(termData->transAmount<=accountsDb->balance) return OK;
    return LOW_BALANCE;
}

EN_serverError_t saveTransaction(struct ST_transaction_t *transData){
    static int generator=1000;
    generator++;
    transData->transactionSequenceNumber=generator;

    for(int i=0;i<255;i++){
        if(transactionglobal[i].transactionSequenceNumber==0){
            transactionglobal[i]=*transData;
            return OK;
        }
    }
    return SAVING_FAILED;
}

enum EN_transState_t receiveTransactionData(struct ST_transaction_t *transData){
    if(isValidAccount(&transData->cardHolderData)==ACCOUNT_NOT_FOUND){
        transData->transState=DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    for(int i=0;i<255;i++) {
        if (strcmp(transData->cardHolderData.primaryAccountNumber, accglobal[i].primaryAccountNumber) == 0) {
            if (isAmountAvailable(&transData->terminalData, &accglobal[i]) == LOW_BALANCE) {
                transData->transState = DECLINED_INSUFFECIENT_FUND;
                return DECLINED_INSUFFECIENT_FUND;
            } else {
                accglobal[i].balance -= transData->terminalData.transAmount;
                if (saveTransaction(transData) == SAVING_FAILED) {
                    transData->transState = INTERNAL_SERVER_ERROR;
                    return INTERNAL_SERVER_ERROR;
                }
                return APPROVED;
            }
        }
    }
 }

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, struct ST_transaction_t *transData){

    for(int i=0;i<255;i++){
        if(transactionSequenceNumber==transactionglobal[i].transactionSequenceNumber) return OK;
    }
    transData->transactionSequenceNumber=transactionSequenceNumber;

    return TRANSACTION_NOT_FOUND;
}

#endif //UNTITLED3_SERVER_H
