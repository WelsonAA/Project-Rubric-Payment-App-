//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_APP_H
#define UNTITLED3_APP_H
#include "E:\untitled3\Card\card.h"
#include "E:\untitled3\Server\server.h"
#include "E:\untitled3\Terminal\terminal.h"

void appStart(void){
    ST_transaction transaction1;
    if(getCardHolderName(&transaction1.cardHolderData)!=OK_c){
        printf("Invalid Name\n");
        return;
    };
    if(getCardExpiryDate(&transaction1.cardHolderData)!=OK_c){
        printf("Invalid Expiry Date\n");
        return;
    };
    if(getCardPAN(&transaction1.cardHolderData)!=OK_c){
        printf("Invalid Primary Account Number\n");
        return;
    };
    if(getTransactionDate(&transaction1.terminalData)!=OK_t){
        printf("Wrong Date\n");
        return;
    };
    if(setMaxAmount(&transaction1.terminalData)!=OK_t){
        printf("Invalid Max Amount\n");
        return;
    };
    if(isValidCardPAN(&transaction1.cardHolderData)!=OK_t) {
        printf("Declined Invalid Primary Account Number\n");
        return;
    }
    if(isCardExpired(transaction1.cardHolderData,transaction1.terminalData)!=OK_t) {
        printf("Declined Expired Card\n");
        return;
    }
    if(getTransactionAmount(&transaction1.terminalData)!=OK_t){
        printf("Declined Invalid Amount\n");
        return;
    };
    if(isBelowMaxAmount(&transaction1.terminalData)!=OK_t) {
        printf("Declined Amount Exceeding Limit\n");
        return;
    }
    switch (receiveTransactionData(&transaction1)){
        case DECLINED_STOLEN_CARD:
            printf("Declined Stolen Card\n");
            return;
        case DECLINED_INSUFFECIENT_FUND:
            printf("Declined Insufficient Fund\n");
            return;
        case INTERNAL_SERVER_ERROR:
            printf("Internal Server Error\n");
            return;
        default:
            printf("Approved\n");
    }
    switch (getTransaction(get_int("Enter Transaction Sequence Number\n"),&transaction1)){
        case TRANSACTION_NOT_FOUND:
            printf("Transaction Not Found\n");
            return;
        case OK:
            printf("Transaction Found\n");
            return;
    }

}
#endif //UNTITLED3_APP_H
