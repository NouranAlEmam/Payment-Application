#define _CRT_SECURE_NO_WARNINGS
#include "server.h"

ST_accountsDB_t accountsDB[255]={0};
ST_transaction_t transaction[255] = { 0 };
int m = 0;
uint8_t store = 0;

ST_transaction_t test_trans;
ST_cardData_t test_card;
ST_terminalData_t test_term;
ST_accountsDB_t test_db;
uint8_t p[25];

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	
	if (isValidAccount(&transData->cardHolderData,&accountsDB) == ACCOUNT_NOT_FOUND) {
		printf("ACCOUNT NOT FOUND\n");
		return FRAUD_CARD;
	}
	if (isAmountAvailable(&transData->terminalData, &accountsDB) == LOW_BALANCE) {
		printf("DECLINED INSUFFECIENT FUND\n");
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (isBlockedAccount(&accountsDB) == BLOCKED_ACCOUNT) {
		printf("BLOCKED ACCOUNT\n");
		return DECLINED_STOLEN_CARD;
	}
	if (saveTransaction(transData) != SERVER_OK) {
		printf("INTERNAL SERVER ERROR\n");
		return INTERNAL_SERVER_ERROR;
	}
	return APPROVED;
}

void recieveTransactionDataTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name: recieveTransactionData\n");

	strcpy(accountsDB->primaryAccountNumber, "79927398713834267");
	accountsDB->state = RUNNING;
	accountsDB->balance = 500.0;

	printf("Test Case 1:\n\
		Input Data: No input data\n\
		Expected Result: INTERNAL SERVER ERROR\n\
		Actual Result: ");
	strcpy(test_trans.cardHolderData.cardExpirationDate, "\0");
	strcpy(test_trans.cardHolderData.cardHolderName, "\0");
	strcpy(test_trans.cardHolderData.primaryAccountNumber, "\0");
	strcpy(test_trans.terminalData.transactionDate, "\0");
	test_trans.terminalData.maxTransAmount = 0.0;
	test_trans.terminalData.transAmount = 0.0;
	test_trans.transactionSequenceNumber = NULL;
	recieveTransactionData(&test_trans);

	printf("Test Case 2 :\
		\nInput Data : \
		\nCard Holder Name: Nouran Osama Farouk Al\n \
		Card PAN: 79927398713834267 (As in DB & it isn't blocked)\n \
		Card Expiry Date:12/12\n \
		Transaction Date:11/10/2012\n \
		Max Amount:1000\n \
		Transaction Amount:200 (Less than blance)\n \
		Transaction Sequence Number:23\n \
		Transaction State: Approved	\n \
		Expected Result : SERVER OK\n \
		Actual Result :\n");

	strcpy(test_trans.cardHolderData.cardHolderName, "Nouran Osama Farouk Al");
	strcpy(test_trans.cardHolderData.primaryAccountNumber, "79927398713834267");
	strcpy(test_trans.cardHolderData.cardExpirationDate, "12/12");
	strcpy(test_trans.terminalData.transactionDate, "11/10/2012");
	test_trans.terminalData.maxTransAmount = 1000;
	test_trans.terminalData.transAmount = 200;
	test_trans.transactionSequenceNumber = 23;
	recieveTransactionData(&test_trans);

	printf("Test Case 3 :\
		\nInput Data : \
		\nCard Holder Name: Nouran Osama Farouk Al\n \
		Card PAN: 9494597446994899 (Not as in DB & it isn't blocked)\n \
		Card Expiry Date:12/12\n \
		Transaction Date:11/10/2012\n \
		Max Amount:1000\n \
		Transaction Amount:200 (Less than blance)\n \
		Transaction Sequence Number:23\n \
		Transaction State: Approved	\n \
		Expected Result : ACCOUNT NOT FOUND\n \
		Actual Result : ");

	strcpy(test_trans.cardHolderData.cardHolderName, "Nouran Osama Farouk Al");
	strcpy(test_trans.cardHolderData.primaryAccountNumber, "9494597446994899");
	strcpy(test_trans.cardHolderData.cardExpirationDate, "12/12");
	strcpy(test_trans.terminalData.transactionDate, "11/10/2012");
	test_trans.terminalData.maxTransAmount = 1000;
	test_trans.terminalData.transAmount = 200;
	test_trans.transactionSequenceNumber = 23;
	recieveTransactionData(&test_trans);

	printf("Test Case 4 :\
		\nInput Data : \
		\nCard Holder Name: Nouran Osama Farouk Al\n \
		Card PAN:79927398713834267 (As in DB & it isn't blocked)\n \
		Card Expiry Date:12/12\n \
		Transaction Date:11/10/2012\n \
		Max Amount:1000\n \
		Transaction Amount:700 (More than blance)\n \
		Transaction Sequence Number:23\n \
		Transaction State: Approved	\n \
		Expected Result : DECLINED INSUFFECIENT FUND\n \
		Actual Result : ");

	strcpy(test_trans.cardHolderData.cardHolderName, "Nouran Osama Farouk Al");
	strcpy(test_trans.cardHolderData.primaryAccountNumber, "79927398713834267");
	strcpy(test_trans.cardHolderData.cardExpirationDate, "12/12");
	strcpy(test_trans.terminalData.transactionDate, "11/10/2012");
	test_trans.terminalData.maxTransAmount = 1000;
	test_trans.terminalData.transAmount = 700;
	test_trans.transactionSequenceNumber = 23;
	recieveTransactionData(&test_trans);

	printf("Test Case 5 :\
		\nInput Data : \
		\nCard Holder Name: Nouran Osama Farouk Al\n \
		Card PAN:79927398713834267 (As in DB & it is blocked)\n \
		Card Expiry Date:12/12\n \
		Transaction Date:11/10/2012\n \
		Max Amount:1000\n \
		Transaction Amount:500 (More than blance)\n \
		Transaction Sequence Number:23\n \
		Transaction State: Approved	\n \
		Expected Result : BLOCKED ACCOUNT\n \
		Actual Result : ");

	strcpy(test_trans.cardHolderData.cardHolderName, "Nouran Osama Farouk Al");
	strcpy(test_trans.cardHolderData.primaryAccountNumber, "79927398713834267");
	strcpy(test_trans.cardHolderData.cardExpirationDate, "12/12");
	strcpy(test_trans.terminalData.transactionDate, "11/10/2012");
	test_trans.terminalData.maxTransAmount = 1000;
	test_trans.terminalData.transAmount = 500;
	test_trans.transactionSequenceNumber = 23;
	accountsDB->state = BLOCKED;
	recieveTransactionData(&test_trans);
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	int i = 0;
	while (i<255)
	{
		if (accountRefrence[i].primaryAccountNumber !=NULL) {
			if (strcmp(accountRefrence[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
				store = 1;
		}
		i++;
	}
	if (store == 1) 
	{
		store = 0;
		return SERVER_OK;
	}
	else
	{
		//printf("ACCOUNT NOT FOUND\n");
		return ACCOUNT_NOT_FOUND;
	}
}

void isValidAccountTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name: isValidAccount\n");

	//Happy case
	printf("Test Case 1 :\n \
			Input Data :79927398713834267 (Account Found)\n \
			Expected Result :SERVER OK\n \
			Actual Result :");
	strcpy(test_card.primaryAccountNumber, "79927398713834267");
	strcpy(test_db.primaryAccountNumber, "79927398713834267");
	isValidAccount(&test_card, &test_db);

	//Worst case
	printf("\nTest Case 2 :\n \
			Input Data :88888888888888888 (Account not Found)\n \
			Expected Result :ACCOUNT NOT FOUND\n \
			Actual Result :");
	strcpy(test_card.primaryAccountNumber, "88888888888888888");   
	strcpy(test_db.primaryAccountNumber, "79927398713834267");
	isValidAccount(&test_card, &test_db);
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state==RUNNING) {
	//	printf("SERVER OK");
		return SERVER_OK ;
	}
	else {
	//	printf("BLOCKED ACCOUNT");
		return BLOCKED_ACCOUNT;
	}
}

void isBlockedAccountTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name: isBlockedAccount\n");

	printf("Test Case 1 :\n \
			Input Data :BLOCKED ACCOUNT\n \
			Expected Result :BLOCKED ACCOUNT\n \
			Actual Result :");
	test_db.state = BLOCKED;
	isBlockedAccount(&test_db);
	
	printf("\nTest Case 2 :\n \
			Input Data :NOT Blocked ACCOUNT\n \
			Expected Result :SERVER OK\n \
			Actual Result :");
	test_db.state = RUNNING;
	isBlockedAccount(&test_db);
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	accountsDB[m] = accountRefrence[m];
	m++;
	if (termData->transAmount > accountRefrence->balance) {
		//printf("LOW BALANCE\n");
		return LOW_BALANCE;
	}
	else {
		//printf("SERVER OK\n");
		return SERVER_OK;
	}
}

void isAmountAvailableTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name: isAmountAvailable\n");

	printf("Test Case 1 :\n \
			Input Data :Transaction Amount=100 , DB Balance=10\n \
			Expected Result :LOW BALANCE\n \
			Actual Result :");
	test_term.transAmount =100 ;
	test_db.balance = 10;
	isAmountAvailable(&test_term,&test_db);

	printf("Test Case 2 :\n \
			Input Data :Transaction Amount=10 , DB Balance=100\n \
			Expected Result :SERVER OK\n \
			Actual Result :");
	test_term.transAmount = 10;
	test_db.balance = 100;
	isAmountAvailable(&test_term, &test_db);
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	if(transData->transactionSequenceNumber != NULL)
	{
		transaction->cardHolderData = transData->cardHolderData;
		transaction->terminalData = transData->terminalData;
		transaction->transState = transData->transState;
		transaction->transactionSequenceNumber = transData->transactionSequenceNumber;
		listSavedTransactions();
		printf("Successful Operation.\n");
		return SERVER_OK;
	}
	else
	{
		printf("SAVING FAILED\n");
		return SAVING_FAILED;
	}
}

void saveTransactionTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name: saveTransaction\n");

	printf("Test Case 1:\n\
			Input Data: No input data \n\
			Expected Result: SAVING FAILED\n\
			Actual Result: ");

	saveTransaction(&test_trans);

	printf("Test Case 2 :\
			\nInput Data : \n \
			Card Holder Name: Nouran Osama Farouk Al\n \
			Card PAN:79927398713834267 \n \
			Card Expiry Date:12/12\n \
			Transaction Date:11/10/2012\n \
			Max Amount:1000\n \
			Transaction Amount:200\n \
			Transaction Sequence Number:23\n \
			Transaction State: Approved	\n \
			Expected Result :Successful Operation \
			\nActual Result :\n");

	strcpy(test_trans.cardHolderData.cardHolderName, "Nouran Osama Farouk Al");
	strcpy(test_trans.cardHolderData.primaryAccountNumber, "79927398713834267");
	strcpy(test_trans.cardHolderData.cardExpirationDate, "12/12");
	strcpy(test_trans.terminalData.transactionDate, "11/10/2012");
	test_trans.terminalData.maxTransAmount = 1000;
	test_trans.terminalData.transAmount = 200;
	test_trans.transactionSequenceNumber = 23;
	saveTransaction(&test_trans);
}

void listSavedTransactions(void) {
	int i = 0;
	while ( i < 255)
	{
		if (transaction[i].transactionSequenceNumber < 255)
		{
			if (transaction[i].transactionSequenceNumber != NULL)
			{
				if (transaction[i].transState == INTERNAL_SERVER_ERROR)
				{
					strcpy(p, "INTERNAL SERVER ERROR");
				}
				else if (transaction[i].transState == FRAUD_CARD)
				{
					strcpy(p, "FRAUD CARD");
				}
				else if (transaction[i].transState == DECLINED_INSUFFECIENT_FUND)
				{
					strcpy(p, "DECLINED INSUFFECIENT FUND");
				}
				else if (transaction[i].transState==DECLINED_STOLEN_CARD) {
					strcpy(p, "DECLINED STOLEN CARD");
				}
				else
				{
					strcpy(p, "APPROVED");
				}
				printf("#########################\n");
				printf("Transaction Sequence Number : %d\n", transaction[i].transactionSequenceNumber);
				printf("Transaction Date :%s\n", transaction[i].terminalData.transactionDate);
				printf("Transaction Amount :%f\n", transaction[i].terminalData.transAmount);
				printf("Transaction State :%s\n", p);
				printf("Terminal Max Amount :%f\n", transaction[i].terminalData.maxTransAmount);
				printf("Cardholder Name :%s\n", transaction[i].cardHolderData.cardHolderName);
				printf("PAN:%s\n", transaction[i].cardHolderData.primaryAccountNumber);
				printf("Card Expiration Date :%s\n", transaction[i].cardHolderData.cardExpirationDate);
				printf("#########################\n");
			
			}
		}
		 i++;
	}
}

void listSavedTransactionsTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name: listSavedTransactions\n");

	printf("Test Case 1:\n\
	Input Data: No input data \n\
	Expected Result: Nothing will be printed\n\
	Actual Result: \n");
	listSavedTransactions();

	printf("Test Case 2 :\
			\nInput Data : \
			\nCard Holder Name: Nouran Osama Farouk Al\n \
			Card PAN:79927398713834267 \n \
			Card Expiry Date:12/12\n \
			Transaction Date:11/10/2012\n \
			Max Amount:1000\n \
			Transaction Amount:200\n \
			Transaction Sequence Number:23\n \
			Transaction State: Approved	\n \
			Expected Result : OK \
			\nActual Result :\n");

	strcpy(transaction[1].cardHolderData.cardHolderName, "Nouran Osama Farouk Al");
	strcpy(transaction[1].cardHolderData.primaryAccountNumber, "79927398713834267");
	strcpy(transaction[1].cardHolderData.cardExpirationDate, "12/12");
	strcpy(transaction[1].terminalData.transactionDate, "11/10/2012");
	transaction[1].terminalData.maxTransAmount = 1000;
	transaction[1].terminalData.transAmount = 200;
	transaction[1].transactionSequenceNumber = 23;
	transaction[1].transState = APPROVED;
	listSavedTransactions();
}
