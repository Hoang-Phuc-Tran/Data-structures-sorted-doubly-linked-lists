/*
 * Project:	    Major 1
 * Author:	    Hoang Phuc Tran
 * Student ID:  8789102
 * Date:		June 01, 2022
 * Description: a program that takes in information about flights and stores the destination, date
				and fare in  sorted doubly-linked lists to be displayed. Dynamic memory allocation
				is used to store the strings in the linked list data structure FlightNode.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma warning(disable: 4996)


#define STRING_LENGTH 30


// Prototype
struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date);
int fillFlightInfo(struct FlightNode** headFare, struct FlightNode** tailFare, struct FlightNode** headDest, struct FlightNode** tailDest);
int insertByFare(struct FlightNode** headFare, struct FlightNode** tailFare, char destinationInput[], char dateInput[], double fareInput);
int insertByDest(struct FlightNode** headDest, struct FlightNode** tailDest, char destinationInput[], char dateInput[], double fareInput);
int deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail);
void printFlightInfo(struct FlightNode* head);
void freeAll(FlightNode* head);



 // Define a struct called FlightNodes
struct FlightNode {
	char* destination;
	char* date;
	double fare;
	struct FlightNode* prev;
	struct FlightNode* next;
};




int main()
{
	struct FlightNode* headFare = NULL;
	struct FlightNode* tailFare = NULL;
	struct FlightNode* headDest = NULL;
	struct FlightNode* tailDest = NULL;

	struct FlightNode* foundNode = NULL;

	// these string will contain information from user's input to find destination and date in the list
	char findDest[STRING_LENGTH] = { 0 };
	char findDate[STRING_LENGTH] = { 0 };
	
	int checkReturnValue = 0;

	// Check return value from fillFlightInfo function
	while (checkReturnValue != -1)
	{

		checkReturnValue = fillFlightInfo(&headFare, &tailFare, &headDest, &tailDest);

	}

	printf("\nSorted By Fare:\n");
	printFlightInfo(headFare);

	printf("\nSorted By Destination:\n");
	printFlightInfo(headDest);

	printf("\nDestination: ");
	fgets(findDest, sizeof(findDest), stdin);
	
	// Get rid of newline character
	findDest[strcspn(findDest, "\n")] = '\0';

	printf("Date: ");
	fgets(findDate, sizeof(findDate), stdin);

	// Get rid of newline character
	findDate[strcspn(findDate, "\n")] = '\0';

	/* returns a pointer to the node containing a flight, if both the destination and date
	are matched then assign it to foundNode variable */ 
	foundNode = findFlight(headDest, findDest, findDate);	

	// check if foundNode is NULL
	if (foundNode == NULL)
	{
		printf("Flight not found.\n");
	}
	else
	{
		char newDest[STRING_LENGTH] = { 0 };
		char newDate[STRING_LENGTH] = { 0 };
		double newFare = 0;
		char fareInput[STRING_LENGTH] = { 0 };

		printf("Old fare: $%.2lf\n", foundNode->fare);
		printf("\nNew fare: ");
		
		// Get new fare
		fgets(fareInput, sizeof(fareInput), stdin);

		// Get rid of newline character
		fareInput[strcspn(fareInput, "\n")] = '\0';

		if (sscanf(fareInput, "%lf", &newFare) != 1)
		{
			/* if the user did not enter a number recognizable by
			 * the system, set the fare 0 */
			newFare = 0;
		}
		// Compare new fare to old fare
		if (foundNode->fare == newFare)
		{
			printf("Old fare and new fare are identical.\n");
		}
		else
		{
			// Copy destination and date from the deleted node
			strcpy(newDest, foundNode->destination);
			strcpy(newDate, foundNode->date);

			// Update new fare in  the destination-sorted linked lis
			foundNode->fare = newFare;

			// Delete the flight from the fare-sorted linked list
			deleteNode(foundNode, &headFare, &tailFare);

			// Reinsert it
			insertByFare(&headFare, &tailFare, newDest, newDate, newFare);

			printf("\nSorted By Fare:\n");

			printFlightInfo(headFare);

			printf("\nSorted By Destination:\n");

			printFlightInfo(headDest);
		}

		
	}

	// Free all the sorted doubly-linked lists
	freeAll(headDest);
	freeAll(headFare);
	// Set two heads and tails to NULL
	headDest = tailDest = NULL;
	headFare = tailFare = NULL;

	return 0;
}


/*
* Function: fillFlightInfo()
* Description: This function will prompt a user to get the destination, date, and fare and then put it into 
				the destination-sorted linked list and the fare-sorted linked list.
* Parameters: 4 parameters (FlightNode** headFare: start of the linked list of fare - FlightNode** tailFare: 
							the end of the linked list of fare).
*						   (FlightNode** headDest: start of the linked list of Destination - FlightNode** tailDest: 
							the end of the linked list of Destination)
* Returns: int: -1 if the allocation is out of memory or user's input is a '.' character, 0 otherwise
*/
int fillFlightInfo(struct FlightNode** headFare,struct FlightNode** tailFare,struct FlightNode** headDest,struct FlightNode** tailDest)
{
	char strDestination[STRING_LENGTH] = { 0 };
	char strDate[STRING_LENGTH] = { 0 };
	char strFare[STRING_LENGTH] = { 0 };
	double fare = 0;
	int checkCompare = 1;
	// Get a flight destination from the user
	printf("Destination: ");
	fgets(strDestination, sizeof(strDestination), stdin);

	// Get rid of newline character
	strDestination[strcspn(strDestination, "\n")] = '\0';

	checkCompare = strcmp(strDestination, ".");
	// Check if user's input contains '.' character
	if (checkCompare == 0)
	{
		return -1;
	}
	// Get a flight date from the user
	printf("Date: ");
	fgets(strDate, sizeof(strDate), stdin);

	// Get rid of newline character
	strDate[strcspn(strDate, "\n")] = '\0';

	checkCompare = strcmp(strDate, ".");
	// Check if user's input contains '.' character
	if (checkCompare == 0)
	{
		return -1;
	}

	// Get a flight fare from the user
	printf("Fare: ");
	fgets(strFare, sizeof(strFare), stdin);

	strFare[strcspn(strFare, "\n")] = '\0';

	checkCompare = strcmp(strFare, ".");
	// Check if user's input contains '.' character
	if (checkCompare == 0)
	{
		return -1;
	}

	if (sscanf(strFare, "%lf", &fare) != 1)
	{
		/* if the user did not enter a number recognizable by
		 * the system, set the fare 0 */
		fare = 0;
	}


	checkCompare = insertByDest(headDest, tailDest, strDestination, strDate, fare);
	
	// Check the return value from the insertByDest function
	if (checkCompare == -1)
	{
		return -1;
	}

	checkCompare = insertByFare(headFare, tailFare, strDestination, strDate, fare);

	// Check the return value from the insertByFare function
	if (checkCompare == -1)
	{
		return -1;
	}

	return 0;
}

/*
* Function: insertByFare()
* Description: This function will allocate memory for the destination, and date, then put it into
				the fare-sorted linked list in ascending way.
* Parameters: 5 parameters (FlightNode** headFare: start of the linked list of fare - FlightNode** tailFare:
							the end of the linked list of fare) - (a pointer to char contains the destination
							- a pointer to char contains the date - and a double contains fare)
* Returns: int: -1 if the allocation is out of memory, 0 otherwise
*/
int insertByFare(struct FlightNode** headFare, struct FlightNode** tailFare, char destinationInput[], char dateInput[], double fareInput)
{
	FlightNode* newBlock = NULL;
	FlightNode* beforeElement = NULL;
	FlightNode* afterElement = NULL;

	size_t maxLengthOfDestination = 0;
	size_t maxLengthOfDate = 0;

	// maxLengthOfDestination adds one for the null-termination
	maxLengthOfDestination = strlen(destinationInput) + 1;

	// maxLengthOfDate adds one for the null-termination
	maxLengthOfDate = strlen(dateInput) + 1;

	// allocate a block of memory for new block
	newBlock = (FlightNode*)malloc(sizeof(FlightNode));

	if (newBlock == NULL)
	{
		printf("Error! No more memory!\n");
		return -1;
	}

	// Allocate a block of memory to cantain the destination string
	newBlock->destination = (char*)malloc(maxLengthOfDestination * sizeof(char));

	// Check if the allocation fails
	if (newBlock->destination == NULL)
	{
		printf("Error! No more memory!\n");
		return -1;
	}

	// Copy the destination to new block
	strcpy(newBlock->destination, destinationInput);

	// Allocate a block of memory to cantain the date string
	newBlock->date = (char*)malloc(maxLengthOfDate * sizeof(char));

	// Check if the allocation fails
	if (newBlock->date == NULL)
	{
		printf("Error! No more memory!\n");
		return -1;
	}

	// copy the date to new block
	strcpy(newBlock->date, dateInput);

	// Set fare to new block
	newBlock->fare = fareInput;

	// Set prev and next pointer to NULL
	newBlock->prev = newBlock->next = NULL;

	// Check if headFare is NULL
	if (*headFare == NULL)
	{
		// empty list, so set head and tail
		*headFare = *tailFare = newBlock;
	}
	// Special case - inserting at the front of the list
	else if ((*headFare)->fare > fareInput)
	{
		// Set the next pointer of newBlock points to the headFare
		newBlock->next = *headFare;
		// Set the previous pointer of headFare points to newBlock
		(*headFare)->prev = newBlock;
		// set head to point to the new start of the list
		*headFare = newBlock;
	}
	else
	{
		// first item in list
		beforeElement = *headFare;
		// second item in list 
		afterElement = (*headFare)->next;

		while (afterElement != NULL)
		{
			// Check if the fareInput is larger than the fare of afterElement
			if (afterElement->fare > fareInput)
			{
				// we've found a name in the list that is either equal to or greater 
				// than the one we're entering now
				break;
			}
			// Check if the fareInput is equal the fare of afterElement
			if (afterElement->fare == fareInput)
			{
				// Move these pointers one step forward
				beforeElement = afterElement;
				afterElement = afterElement->next;
				break;
			}
			beforeElement = afterElement;
			afterElement = afterElement->next;
		}	/* end while */

		// add the new node here, between beforeElement and afterElement
		newBlock->prev = beforeElement;
		newBlock->next = afterElement;
		beforeElement->next = newBlock;

		// Check if we are end of the list
		if (afterElement == NULL)
		{
			*tailFare = newBlock;
		}
		else
		{
			afterElement->prev = newBlock;
		}
	}

	return 0;
}


/*
* Function: insertByDest()
* Description: This function will allocate memory for the destination, and date, then put it into
				the destination-sorted linked list in ascending way.
* Parameters: 5 parameters (FlightNode** headDest: start of the linked list of fare - FlightNode** tailDest:
							the end of the linked list of fare) - (a pointer to char contains the destination
							- a pointer to char contains the date - and a double contains fare)
* Returns: int: -1 if the allocation is out of memory, 0 otherwise
*/
int insertByDest(struct FlightNode** headDest, struct FlightNode** tailDest, char destinationInput[], char dateInput[], double fareInput)
{
	FlightNode* newBlock = NULL;
	FlightNode* beforeElement = NULL;
	FlightNode* afterElement = NULL;

	size_t maxLengthOfDestination = 0;
	size_t maxLengthOfDate = 0;

	// maxLengthOfDestination adds one for the null-termination
	maxLengthOfDestination = strlen(destinationInput) + 1;

	// maxLengthOfDate adds one for the null-termination
	maxLengthOfDate = strlen(dateInput) + 1;

	// allocate a block of memory for new block
	newBlock = (FlightNode*)malloc(sizeof(FlightNode));

	if (newBlock == NULL)
	{
		printf("Error! No more memory!\n");
		return -1;
	}

	// Allocate a block of memory to cantain the destination string
	newBlock->destination = (char*)malloc(maxLengthOfDestination * sizeof(char));

	// Check if the allocation fails
	if (newBlock->destination == NULL)
	{
		printf("Error! No more memory!\n");
		return -1;
	}

	// Copy the destination to new block
	strcpy(newBlock->destination, destinationInput);

	// Allocate a block of memory to cantain the date string
	newBlock->date = (char*)malloc(maxLengthOfDate * sizeof(char));

	// Check if the allocation fails
	if (newBlock->date == NULL)
	{
		printf("Error! No more memory!\n");
		return -1;
	}

	// copy the date to new block
	strcpy(newBlock->date, dateInput);

	// Set the fareInput to newBlock
	newBlock->fare = fareInput;

	// Set the previous and next pointer of newBlock to NULL
	newBlock->prev = newBlock->next = NULL;

	if (*headDest == NULL)
	{
		// empty list, so set head and tail
		*headDest = *tailDest = newBlock;
	}
	// Special case - inserting at the front of the list
	else if (strcmp((*headDest)->destination, destinationInput) > 0)
	{
		// Set the next pointer of newBlock points to the headDest
		newBlock->next = *headDest;
		// Set the previous pointer of headDest points to newBlock
		(*headDest)->prev = newBlock;
		// set head to point to the new start of the list
		*headDest = newBlock;
	}
	else 
	{
		// first item in list
		beforeElement = *headDest;	
		// second item in list
		afterElement = (*headDest)->next;

		while (afterElement != NULL)
		{
			if (strcmp(afterElement->destination, destinationInput) > 0)
			{
				// we've found a name in the list that is either equal to or greater 
				// than the one we're entering now
				break;
			}
			// Check if the fareInput is equal the fare of afterElement
			if (strcmp(afterElement->destination, destinationInput) == 0)
			{
				// Move these pointers one step forward
				beforeElement = afterElement;
				afterElement = afterElement->next;
				break;
			}
			beforeElement = afterElement;
			afterElement = afterElement->next;
		}	/* end while */

		// add the new node here, between beforeElement and afterElement
		newBlock->prev = beforeElement;
		newBlock->next = afterElement;
		beforeElement->next = newBlock;

		// Check if we are end of the list
		if (afterElement == NULL)
		{
			*tailDest = newBlock;
		}
		else
		{
			afterElement->prev = newBlock;
		}
	}

	return 0;

}


/*
* Function: deleteNode()
* Description : This function will delete a specified node 
* Parameters : 3 parameter(FlightNode *head: start of the linked list - FlightNode *tail: the end
				FlightNode *node: node to delete).
* Returns : void
*/
int deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail)
{
	FlightNode* curr = NULL;
	FlightNode* next = NULL;

	curr = *head;

	// traverse the list, being careful to not access freed blocks
	while (curr != NULL)
	{
		// found it?
		//strcmp(node->destination, curr->destination) == 0 && strcmp(node->date, curr->date) == 0 && node->fare == curr->fare
		if (strcmp(node->destination, curr->destination) == 0 && strcmp(node->date, curr->date) == 0 )
		{


			if ((curr == *head) && (curr == *tail))
			{
				// this is the only item in the list
				*head = *tail = NULL;
				free(curr);
				return 1;
			}

			// are we deleting the first of many items?
			if (curr == *head)
			{
				FlightNode* secondElement = curr->next;
				// we're deleting the first item
				*head = curr->next;
				// null out the prev pointer for what used to be the second item
				secondElement->prev = NULL;
			}
			else
			{
				// make the following prev pointer point to the element before this one, 
				// as long as we're not deleting the last item
				if (curr == *tail)
				{
					FlightNode* secondlastElement = curr->prev;
					// adjust the tail
					*tail = curr->prev;
					// null out the next pointer for what used to be the second-last item
					secondlastElement->next = NULL;
				}
				else
				{
					FlightNode* precedingElement = curr->prev;
					FlightNode* followingElement = curr->next;

					// set the following element's prev pointer to point to the item before this one
					followingElement->prev = precedingElement;
					// set the preceding element's next pointer to point to the item after this one
					precedingElement->next = followingElement;
				}
			}

			// finally, free the desired element
			free(curr->destination);
			free(curr->date);
			free(curr);

			return 1;
		}

		curr = curr->next;
	}

	// didn't find the item to delete
	return 0;
}

/*
* Function: FlightNode* findFlight()
* Description : This function will return NULL if a flight is not found or it returns a
pointer to the node containing a flight, if both the destination and date are matched
* Parameters : 3 parameter(FlightNode *head: start of the linked list - char *destination: pointer 
to null-terminated string containing destination - char *date: pointer to null-terminated string containing date).
* Returns : A node 
*/
struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date)
{
	FlightNode* curr = NULL;
	curr = head;

	while (curr != NULL)
	{
		// found it?
		if (strcmp(curr->destination, destination) == 0 && strcmp(curr->date, date) == 0)
		{
			return curr;
		}
		curr = curr->next;

	}

	return NULL;
}

/*
* Function: printFlightInfo()
* Description : This function will prints all of the information contained within the list
* Parameters : 1 parameter(FlightNode *head: start of the linked list).
* Returns : a found node
*/
void printFlightInfo(struct FlightNode* head)
{
	FlightNode* ptr = head;


	while (ptr != NULL)
	{
		// Displayed destination and date information in the next 35 characters of the line (left-justified)
		printf("%-35s", ptr->destination);
		printf("%-35s", ptr->date);
		printf("$%-35.2lf\n", ptr->fare);
		ptr = ptr->next;
	}

}

/*
 * Function: freeAll(phoneInfo *head)
 * Description: This function will free all allocated memory in the linked list.
 * Parameter: FlightNode **head(a double pointer): start of the linked list
 * Returns: void
 */
void freeAll(FlightNode* head)
{
	FlightNode* curr = NULL;
	FlightNode* next = NULL;

	curr = head;

	// traverse the list, being careful to not access freed blocks
	while (curr != NULL)
	{
		// keep a pointer to the next block so we can go there after it's freed
		next = curr->next;
		free(curr->destination);
		free(curr->date);
		free(curr);
		curr = next;
	}

}