//
// Created by George Welson on 14-Aug-22.
//

#ifndef UNTITLED3_APP_H
#define UNTITLED3_APP_H
#include "E:\untitled3\Card\card.h"
#include "E:\untitled3\Server\server.h"
#include "E:\untitled3\Terminal\terminal.h"

void appStart(void){
    ST_cardData_t card1;
    ST_terminalData_t term1;
    getCardHolderName(&card1);
    getCardExpiryDate(&card1);
    getCardPAN(&card1);
    getTransactionDate(&term1);
    setMaxAmount(&term1);
    if(isValidCardPAN(&card1)!=OK_t) {
        printf("Declined Invalid Primary Account Number\n");
    }
    if(isCardExpired(card1,term1)!=OK_t) {
        printf("Declined Expired Card\n");
        return;
    }
    getTransactionAmount(&term1);
    if(isBelowMaxAmount(&term1)!=OK_t) {
        printf("Declined Amount Exceeding Limit\n");
        return;
    }
    if(isValidAccount(&card1)!=OK){
        printf("Declined Invalid Account\n");
        return;
    };
    if(isAmountAvailable())
}
;
#endif //UNTITLED3_APP_H
