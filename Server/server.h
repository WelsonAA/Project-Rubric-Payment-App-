//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_SERVER_H
#define UNTITLED3_SERVER_H

#include <stdint.h>

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
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    enum EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction;
ST_accountsDB_t accglobal[255]={
        {
        8000.0,"600802538951367588"
        },
        {
            755.0,"51714505293369193"
        },
        {
            4563.4,"51714505293369140"
        }

};
ST_transaction_t tranansactionglobal[255]={
        {
                {"0","0","0"},{0.0,0.0,"0"},APPROVED,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},APPROVED,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},APPROVED,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},APPROVED,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},APPROVED,0
        },{
                {"0","0","0"},{0.0,0.0,"0"},APPROVED,0
        }
};
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    for(int i=0;i<255;i++){
        if(cardData->primaryAccountNumber==accglobal[i].primaryAccountNumber){
            return OK;
        }
    }
    return DECLINED_STOLEN_CARD;
};

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    if(termData->transAmount==termData.)


    /*
     This function will take terminal data and validate these data.
    It checks if the transaction's amount is available or not.
    If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return OK
     */
};
EN_serverError_t saveTransaction(ST_transaction_t *transData){
    static int generator=1000;
    generator++;
    transData->transactionSequenceNumber=generator;

    for(int i=0;i<255;i++){
        if(tranansactionglobal[i].transactionSequenceNumber==0){
            tranansactionglobal[i]=*transData;//check again
            return OK;
        }
    }
    return SAVING_FAILED;
    /*
     This function will take all transaction data into the transactions database.
    It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
    If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
    If transaction can't be saved will return SAVING_FAILED, else will return OK */
};
EN_transState_t receiveTransactionData(ST_transaction_t *transData){
    if(isValidAccount(&transData->cardHolderData)==DECLINED_STOLEN_CARD){
        transData->transState=DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    if(isAmountAvailable(&transData->terminalData)==LOW_BALANCE){
        transData->transState= DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
}
    if(saveTransaction(&transData)==SAVING_FAILED){
        transData->transState=INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }
    for(int i=0;i<255;i++){
        if(transData->cardHolderData.primaryAccountNumber==accglobal[i].primaryAccountNumber){
            accglobal[i].balance-=transData->terminalData.transAmount;
            saveTransaction(transData);
            return APPROVED;
        }
    }
    //update the database with new balance and return APPROVED
};



EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    /*
    This function will take a transaction sequence number and search for this transaction in the database.
    If the transaction can't be found will return TRANSACTION_NOT_FOUND, else will return OK and store the transaction in a structure
     */
    for(int i=0;i<255;i++){
        if(transactionSequenceNumber==tranansactionglobal[i].transactionSequenceNumber) return OK;
    }
    return TRANSACTION_NOT_FOUND;
};

#endif //UNTITLED3_SERVER_H
