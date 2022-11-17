#define _CRT_SECURE_NO_WARNINGS
#include "app.h"
ST_transaction_t s={0};
ST_accountsDB_t y[255] = {0};
uint32_t n = 1;

void appStart(void) {
	getCardHolderName(&s.cardHolderData);
	getCardPAN(&s.cardHolderData);
	getCardExpiryDate(&s.cardHolderData);
	getTransactionDate(&s.terminalData);

	//79927398713834267
	strcpy(y[n].primaryAccountNumber, "66282542323526971");
	y[n].state = RUNNING;

	if (isCardExpired(s.cardHolderData,s.terminalData)==EXPIRED_CARD) {
		printf("Declined Expired Card.\n");
	}
	else {
	if (isValidCardPAN(&s.cardHolderData) == INVALID_CARD) {
		printf("Invalid Card Number.");
	 }
	else {
			getTransactionAmount(&s.terminalData);
			setMaxAmount(&s.terminalData);

			if (isBelowMaxAmount(&s.terminalData) == EXCEED_MAX_AMOUNT) {
				printf("Declined Amount Exceeding Limit.\n");
			}
			else {
				if (isValidAccount(&s.cardHolderData, &y[n]) == ACCOUNT_NOT_FOUND) {
					printf("Declined Invalid Account.\n");
				}
				else {
					if(isBlockedAccount(&y[n]) == BLOCKED_ACCOUNT)
					{
						printf("STOLEN!!");
					}
					else 
					{
						y[n].balance = 90000;
						if (isAmountAvailable(&s.terminalData, &y[n]) == LOW_BALANCE) {
							printf("Declined Insufecient funds.\n");
						}
					
						else {
							printf("Balance before transaction was %f\n",y[n].balance);
							y[n].balance -= s.terminalData.transAmount;
							printf("Balance after transaction is %f\n",y[n].balance);
							s.transactionSequenceNumber = n++;
							recieveTransactionData(&s);
						}
					}
				}
			}
		}
	}
//	getCardHolderNameTest();
//	getCardExpiryDateTest();
//	getCardPANTest();
//	getTransactionDateTest();
//	isCardExpriedTest();
//	getTransactionAmountTest();
//	isBelowMaxAmountTest();
//	setMaxAmountTest();
//	isValidCardPANTest();
//	recieveTransactionDataTest();
//	isValidAccountTest();
//	isBlockedAccountTest();
//	isAmountAvailableTest();
//	saveTransactionTest();	
//	listSavedTransactionsTest();
}