#include <stdio.h>

#include "E:\untitled3\Card\card.h"
#include "E:\untitled3\Terminal\terminal.h"

int main() {
    ST_terminalData_t term1;
    getTransactionAmount(&term1);
    ST_cardData_t card1;


    getCardPAN(&card1);
    while ((getchar()) != '\n');
    isValidCardPAN(&card1);
    /*string s= get_string(NULL,"Enter\n");
    if(s[0]=='\0') printf("sorry");
    ST_terminalData_t data1;

    if(getTransactionDate(&data1)==OK_t){
        printf("OK");
    }else printf("NO");*/

}
