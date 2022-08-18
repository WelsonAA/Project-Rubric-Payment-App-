//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_APP_H
#define UNTITLED3_APP_H
#include "E:\untitled3\Card\card.h"
#include "E:\untitled3\Server\server.h"
#include "E:\untitled3\Terminal\terminal.h"

void appStart(void){
    //ST_cardData_t card1;
    //ST_terminalData_t term1;
    ST_transaction transaction1;
    getCardHolderName(&transaction1.cardHolderData);
    getCardExpiryDate(&transaction1.cardHolderData);
    getCardPAN(&transaction1.cardHolderData);
    getTransactionDate(&transaction1);
    setMaxAmount(&transaction1.terminalData);
    if(isValidCardPAN(&transaction1.terminalData)!=OK_t) {
        printf("Declined Invalid Primary Account Number\n");
    }
    if(isCardExpired(transaction1.cardHolderData,transaction1.terminalData)!=OK_t) {
        printf("Declined Expired Card\n");
        return;
    }
    getTransactionAmount(&transaction1.terminalData);
    if(isBelowMaxAmount(&transaction1.terminalData)!=OK_t) {
        printf("Declined Amount Exceeding Limit\n");
        return;
    }
    if(isValidAccount(&transaction1.terminalData)!=OK){
        printf("Declined Invalid Account\n");
        return;
    };
    receiveTransactionData(&transaction1);
    getTransaction(get_int("Enter Transaction Sequence Number\n"),&transaction1);
}
;
#endif //UNTITLED3_APP_H
