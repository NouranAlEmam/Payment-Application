#define _CRT_SECURE_NO_WARNINGS
#include "card.h"
ST_cardData_t test;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Please enter cardholder's name: ");
	scanf("%[^\n]s", &cardData->cardHolderName);
	if (cardData->cardHolderName==NULL || strlen(cardData->cardHolderName)>24||strlen(cardData->cardHolderName)<20) {
		printf("Wrong Name.\n");
		return WRONG_NAME;
	}
	else {
		printf("Accepted.\n");
		return	CARD_OK;
	}
}
/*void getCardHolderNameTest(void) {
	printf("Tester Name: Nouran Osama Farouk Al Emam\nFunction Name : getCardHolderName \n");
	printf("Test Case 1: \n \
		Input Data :Al Emam \n \
		Expected Result :Wrong Name\n \
		Actual Result :");
	strcpy(test.cardHolderName, "Al Emam");
	getCardHolderName(&test);

	printf("Test Case 2: \n \
		Input Data :Nouran Osama Farouk Al Emam \n \
		Expected Result :Wrong Name\n \
		Actual Result :");
	strcpy(test.cardHolderName, "Nouran Osama Farouk Al Emam");
	getCardHolderName(&test); 
	
	printf("Test Case 3: \n \
		Input Data :Nouran Osama Farouk Al \n \
		Expected Result :Accepted\n \
		Actual Result :");
	strcpy(test.cardHolderName, "Nouran Osama Farouk Al");
	getCardHolderName(&test);
}*/


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Please enter card expiry date: ");
	scanf("%s", &cardData->cardExpirationDate);
	if (cardData->cardExpirationDate == NULL || strlen(cardData->cardExpirationDate)<5 || strlen(cardData->cardExpirationDate)>5|| cardData->cardExpirationDate[2]!='/' || isdigit(cardData->cardExpirationDate[0]) == 0 || isdigit(cardData->cardExpirationDate[1]) == 0 || isdigit(cardData->cardExpirationDate[3]) == 0 || isdigit(cardData->cardExpirationDate[4]) == 0 || months(&cardData->cardExpirationDate)==WRONG_EXP_DATE ) {
		printf("Wrong Data.\n"); 
		return WRONG_EXP_DATE;
	}
	else {
		printf("ACCEPTED\n");
		return	CARD_OK;
	}
}
EN_cardError_t months(uint8_t* month) {
	if (((month[0] - '0') * 10 + (month[1]) - '0') > 12) {
		return WRONG_EXP_DATE;
	}
	else {
		return	CARD_OK;
	}
}
/*void getCardExpiryDateTest(void) {
	printf("Tester Name : Nouran Osama Farouk Al Emam\n \
			Function Name : getCardExpiryDate\n");

	printf("Test Case 1 :\n \
			Input Data :12/12\n \
			Expected Result :ACCEPTED\n \
			Actual Result :");
	strcpy(test.cardExpirationDate,"12/12");
	getCardExpiryDate(&test);

	printf("Test Case 2 :\n \
			Input Data :1/12\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
	strcpy(test.cardExpirationDate, "1/12");
	getCardExpiryDate(&test);

	printf("Test Case 3 :\n \
			Input Data :21/15\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
	strcpy(test.cardExpirationDate, "21/15");
	getCardExpiryDate(&test);

	printf("Test Case 4 :\n \
			Input Data :11/5\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
	strcpy(test.cardExpirationDate, "11/5");
	getCardExpiryDate(&test);

	printf("Test Case 5 :\n \
			Input Data :10.15\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
	strcpy(test.cardExpirationDate, "10.15");
	getCardExpiryDate(&test);

	printf("Test Case 6 :\n \
			Input Data :k0.15\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
	strcpy(test.cardExpirationDate, "k0.15");
	getCardExpiryDate(&test);

	printf("Test Case 7 :\n \
			Input Data :011/12\n \
			Expected Result :Wrong Data\n \
			Actual Result :");
	strcpy(test.cardExpirationDate, "10.15");
	getCardExpiryDate(&test);
}*/


EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Please enter Primary Account Number: ");
	scanf("%s", &cardData->primaryAccountNumber);
	if (cardData->primaryAccountNumber == NULL || strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16) {
		printf("Wrong Data.\n"); 
		return WRONG_PAN;
	}
	else {
		printf("CARD OK.\n");
		return	CARD_OK;
	}
}

/*void getCardPANTest(void) {
	printf("Tester Name : Nouran Osama Farouk Al Emam\n \
			Function Name : getCardPAN\n");

	printf("Test Case 1 :\n \
			Input Data :11122233344455566\n \
			Expected Result :CARD OK\n \
			Actual Result : ");
	strcpy(test.primaryAccountNumber,"11122233344455566"); //17 numbers
	getCardPAN(&test);

	printf("Test Case 2 :\n \
			Input Data :1112223334\n \
			Expected Result :Wrong Data\n \
			Actual Result : ");
	strcpy(test.primaryAccountNumber, "1112223334"); //10 numbers
	getCardPAN(&test);

	printf("Test Case 3 :\n \
			Input Data :1112223334445556667778\n \
			Expected Result :Wrong Data\n \
			Actual Result : ");
	strcpy(test.primaryAccountNumber, "1112223334445556667778"); //22 numbers
	getCardPAN(&test);
}*/
