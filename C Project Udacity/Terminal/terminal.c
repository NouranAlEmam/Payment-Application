#define _CRT_SECURE_NO_WARNINGS
#include "terminal.h"

ST_terminalData_t termtest;
ST_cardData_t expired_test;
ST_cardData_t pan;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Please enter transaction date: ");
	scanf("%s", &termData->transactionDate);
	if (termData->transactionDate == NULL || strlen(termData->transactionDate) < 10 || strlen(termData->transactionDate) > 10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/' || isdigit(termData->transactionDate[0]) == 0 || isdigit(termData->transactionDate[1]) == 0 || isdigit(termData->transactionDate[3]) == 0 || isdigit(termData->transactionDate[4]) == 0 || isdigit(termData->transactionDate[6]) == 0 || isdigit(termData->transactionDate[7]) == 0 || isdigit(termData->transactionDate[8]) == 0 || isdigit(termData->transactionDate[9]) == 0 || months_terminal(&termData->transactionDate) == WRONG_DATE || days_terminal(&termData->transactionDate) == WRONG_DATE) {
		printf("Wrong Data.\n"); 
		return WRONG_DATE;
	}
	else {
	//	printf("TERMINAl OK.\n");
		return	TERMINAL_OK;
	}
}

EN_terminalError_t months_terminal (uint8_t* termonth) {
	if ((termonth[3]-'0') * 10 + (termonth[4]-'0') > 12) {
		return WRONG_DATE;
	}
	else {
		return	TERMINAL_OK;
	}
}
EN_terminalError_t days_terminal(uint8_t* termday) {
	if ((termday[0]-'0') * 10 + (termday[1]-'0') > 31) {
		return WRONG_DATE;
	}
	else {
		return	TERMINAL_OK;
	}
}

/*void getTransactionDateTest(void) {
		printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name : getTransactionDate");
	
		printf("Test Case 1 :\n \
			Input Data :11/12/2020\n \
			Expected Result :TERMINAl OK\n \
			Actual Result :");
		strcpy(termtest.transactionDate,"11/12/2020");
		getTransactionDate(&termtest);

		printf("Test Case 2 :\n \
			Input Data :11/55/2020\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "11/55/2020");
		getTransactionDate(&termtest);

		printf("Test Case 3 :\n \
			Input Data :1/06/2020\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "1/06/2020");
		getTransactionDate(&termtest);

		printf("Test Case 4 :\n \
			Input Data :40/10/2020\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "40/10/2020");
		getTransactionDate(&termtest);

		printf("Test Case 5 :\n \
			Input Data :11/11/203\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "11/11/203");
		getTransactionDate(&termtest);

		printf("Test Case 6 :\n \
			Input Data :11/6/2020\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "11/6/2020");
		getTransactionDate(&termtest);

		printf("Test Case 7 :\n \
			Input Data :11.10/2020\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "11.10/2020");
		getTransactionDate(&termtest);

		printf("Test Case 8 :\n \
			Input Data :11/10.2020\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "11/10.2020");
		getTransactionDate(&termtest);

		printf("Test Case 9 :\n \
			Input Data :11/d3/2020\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
		strcpy(termtest.transactionDate, "11/d3/2020");
		getTransactionDate(&termtest);
}*/

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	uint8_t c[5] = {0};
	for (int i = 0; i < 5; i++) {
		if (i < 3) {
			c[i] = termData.transactionDate[i + 3];
		}
		else {
			c[i] = termData.transactionDate[i + 5];
		}
	}
	
	if (strcmp(cardData.cardExpirationDate,c)<0) {
		printf("EXPIRED CARD.\n"); 
		return EXPIRED_CARD;
	}
	else {
	//	printf("TERMINAL OK.\n");
		return TERMINAL_OK;
	}
}

/*void isCardExpriedTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name : isCardExpried\n");

	printf("Test Case 1 :\n \
			Input Data :11/12  ,  11/09/2022\n \
			Expected Result :TERMINAl OK\n \
			Actual Result :");
	strcpy(termtest.transactionDate, "11/09/2022");
	strcpy(expired_test.cardExpirationDate, "11/12");
	isCardExpired(expired_test, termtest);

	printf("Test Case 2 :\n \
			Input Data :11 / 22  ,  11 / 12 / 2022\n \
			Expected Result :EXPIRED CARD\n \
			Actual Result :");
	strcpy(termtest.transactionDate, "11/12/2022");
	strcpy(expired_test.cardExpirationDate, "11/22");
	isCardExpired(expired_test,termtest);
}*/

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Please enter transaction amount: ");
	scanf("%f", &termData->transAmount);
	if(termData->transAmount<=0){
		printf("INVALID AMOUNT.\n");
		return INVALID_AMOUNT;
	}
	else {
	//	printf("TERMINAL OK.\n");
		return	TERMINAL_OK;
	}
}

/*void getTransactionAmountTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name : getTransactionAmount\n");

	printf("Test Case 1 :\n \
			Input Data :0\n \
			Expected Result :INVALID AMOUNT\n \
			Actual Result :");
	termtest.transAmount= 0;
	getTransactionAmount(&termtest);

	printf("Test Case 3 :\n \
			Input Data :-11\n \
			Expected Result :INVALID AMOUNT\n \
			Actual Result :");
	termtest.transAmount = -11;
	getTransactionAmount(&termtest);

	printf("Test Case 3 :\n \
			Input Data :60\n \
			Expected Result :TERMINAL_OK\n \
			Actual Result :");
	termtest.transAmount = 60;
	getTransactionAmount(&termtest);
}*/

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		printf("EXCEED MAX AMOUNT\n");
		return EXCEED_MAX_AMOUNT;
	}
	else {
	//	printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}
}

/*void isBelowMaxAmountTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name : isBelowMaxAmount\n");

	printf("Test Case 1 :\n \
			Input Data :10,20\n \
			Expected Result :INVALID AMOUNT\n \
			Actual Result :");
	termtest.transAmount = 10;
	termtest.maxTransAmount = 20;
	isBelowMaxAmount(&termtest);

	printf("Test Case 2 :\n \
			Input Data :30,30\n \
			Expected Result :INVALID AMOUNT\n \
			Actual Result :");
	termtest.transAmount = 30;
	termtest.maxTransAmount = 30;
	isBelowMaxAmount(&termtest);

	printf("Test Case 3 :\n \
			Input Data :20,10\n \
			Expected Result :INVALID AMOUNT\n \
			Actual Result :");
	termtest.transAmount = 20;
	termtest.maxTransAmount = 10;
	isBelowMaxAmount(&termtest);

}*/

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Please enter the maximum allowed amount: ");
	scanf("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount<=0){
		printf("INVALID MAX AMOUNT\n");
		return INVALID_MAX_AMOUNT;
	}
	else {
	//	printf("TERMINAL OK\n");
		return	TERMINAL_OK;
	}
}

/*void setMaxAmountTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name : setMaxAmount\n");

	printf("Test Case 1 :\n \
			Input Data :0\n \
			Expected Result :INVALID AMOUNT\n \
			Actual Result :");
	setMaxAmount(&termtest, 0);

	printf("Test Case 3 :\n \
			Input Data :-36\n \
			Expected Result :INVALID AMOUNT\n \
			Actual Result :");
	setMaxAmount(&termtest,-36);

	printf("Test Case 3 :\n \
			Input Data :85\n \
			Expected Result :TERMINAL_OK\n \
			Actual Result :");
	setMaxAmount(&termtest,85);
}*/

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	int j = 0, sum = 0, l = 0 ;
	int k[19] = {0};
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++) { 
		k[i] = (cardData->primaryAccountNumber[i]-'0');
		if (j == 1) {
			j = 0;
			l = k[i] * 2;
			if (l > 9) {
				sum += l % 10;
				sum += l / 10;
				
			}
			else {
				sum += l;
				
			}
		}
		else {
			j = 1;
			sum += k[i];
		}
	}
	if (sum % 10 != 0) {
		printf("INVALID CARD\n");
		return INVALID_CARD;
	}
	else {
	//	printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}
}

/*void isValidCardPANTest(void) {
	printf("Tester Name : Nouran Osmam Farouk Al Emam\n \
			Function Name: isValidCardPAN\n");

	printf("Test Case 1 :\n \
			Input Data :112\n \
			Expected Result :INVALID CARD\n \
			Actual Result :");  //False PAN Number
	strcpy(&pan.primaryAccountNumber, "112");
	isValidCardPAN(&pan);

	printf("Test Case 2 :\n \
			Input Data :79927398713834268\n \
			Expected Result :INVALID CARD\n \
			Actual Result :");  //False PAN Number
	strcpy(&pan.primaryAccountNumber, "79927398713834268");
	isValidCardPAN(&pan);

	printf("Test Case 3 :\n \
			Input Data :79927398713834267\n \
			Expected Result :TERMINAL OK\n \
			Actual Result :");  //True PAN Number
	strcpy(&pan.primaryAccountNumber, "79927398713834267");
	isValidCardPAN(&pan);
}*/