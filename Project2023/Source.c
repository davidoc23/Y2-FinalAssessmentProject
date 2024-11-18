#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cfloat> //Allows you to use DBL_MAX which helps you find the minimum value of a set of numbers.

//For the username and password
#define MAX_USERS 3

#define MAX_LEN 6

// Define a structure to hold accommodation details
typedef struct Accommodation
{
	int property_id;
	char owner_first_name[50];
	char owner_last_name[50];
	int year_built;
	int num_rooms;
	float monthly_rental;
	char email_address[50];
	int accommodationType;
	int petsAllowed;
	int duration;

	//Reference to next node
	struct Accommodation* next;
}accommodationL;


// Function prototypes
void add_accommodation(accommodationL** head);
void display_all_accommodation(accommodationL* head);
void update_accommodation(accommodationL* head);
void delete_accommodation(accommodationL** head);
void print_accommodation_report(accommodationL* head);
void display_accommodation_details(accommodationL** head);
void generate_statistics_details(accommodationL* head);
void list_by_monthly_rental(accommodationL* head);

int main()
{
	//Start with an empty list
	accommodationL* head = NULL;

	//Declare Variables
	int choice;
	char usernames[MAX_USERS][MAX_LEN+1]; //array to store username
	char savedPasswords[MAX_USERS][MAX_LEN+1]; //array to store password
	char password[MAX_LEN+1];
	char username[MAX_LEN+1];
	int loginSuccess = 0;
	int p = 0, ch; //Used for masking the password

	//Used to read the file that stores the passwords.
	FILE* FP = fopen("login.txt", "r");

	for (int i = 0; i < MAX_USERS; i++)
	{
		fscanf(FP, "%s %s", usernames[i], savedPasswords[i]);
	}
	
	do
	{
		/*One small problem i have is that if the first user enters wrong details that it expects you to enter the next users detailsand i cannot figure out how to get it to ask for the first users details again.
		So i just made the program exit when the username and password dont match. */

		printf("\nPlease enter the username: ");
		scanf("%s", username);

		printf("\nPlease enter the password: ");
		while ((ch = getch()) != 13) //13 is the ascii code for the Enter key
		{
			if (ch == 8) //Check for backspace character
			{
				if (p > 0) //Make sure there are characters to delete
				{
					p--;
					printf("\b \b"); //Move cursor back, print space and move cursor back again
				}
			}
			else
			{
				password[p] = ch;
				p++;
				printf("*");
			}
		}
		password[p] = '\0';

		//Comparing the username and passwords with the .txt file values
		for (int i = 0; i < MAX_USERS; i++)
		{
			if (strcmp(username, usernames[i]) == 0 && strcmp(password, savedPasswords[i]) == 0)
			{
				loginSuccess = 1;
				break;
			}
		}

		//Displays a message to user if the details were incorrect and asks them to try again.
		if (!loginSuccess)
		{
			printf("\n\nThose details were incorrect, please relaunch the program to try again!\n");
			printf("\nExiting the program now.\n");
			exit(0); //Exits the program so you have to relaunch the program to try again.
		}
	

	}while(!loginSuccess); //Will keep looping if the wrong details have been entered.


	if (loginSuccess) //If the entered username and password are correct continue.
	{
		do
		{
			printf("\n\n\t\tXYZ ACCOMMODATION LTD\n\n");
			printf("\nMenu:\n");
			printf("\n1. Add Accommodation\n");
			printf("2. Display all accommodation to screen\n");
			printf("3. Display an accommodation Details\n");
			printf("4. Update Accommodation parameters\n");
			printf("5. Delete accommodation\n");
			printf("6. Generate Statistics \n");
			printf("7. Print all accommodation into a report file \n");
			printf("8. List all the accommodation in order of monthly rental\n");
			printf("-1. Exit\n\n");
			printf("Enter your choice: ");
			scanf("%d", &choice);

			switch (choice)
			{
				case 1:
					add_accommodation(&head);
					break;
				case 2:
					display_all_accommodation(head);
					break;
				case 3:
					display_accommodation_details(head);
					break;
				case 4:
					update_accommodation(head);
					break;
				case 5:
					delete_accommodation(&head);
					break;
				case 6:
					generate_statistics_details(head);
					break;
				case 7:
					print_accommodation_report(head);
					generate_statistics_details(head);
					break;
				case 8:
					list_by_monthly_rental(head);
					break;
				case -1:
					printf("Exiting program...\n");
					break;
				default:
					printf("Invalid choice!\n");
			}
		} while (choice != -1);

		exit(0); //Exits the program so you have to relaunch the program to try again.	}
	}
	//close the file
	fclose(FP);
}

void add_accommodation(accommodationL** head)
{
	accommodationL* new_node = (accommodationL*)malloc(sizeof(accommodationL));

	printf("\nEnter Property Identification Number: ");
	scanf("%d", &new_node->property_id);
	printf("Enter Name of owner: ");
	scanf("%s", new_node->owner_first_name);
	printf("Enter Last Name of Owner: ");
	scanf("%s", new_node->owner_last_name);
	printf("Enter Year Built: ");
	scanf("%d", &new_node->year_built);
	printf("Enter Email Address: ");
	scanf("%s", new_node->email_address);
	printf("Enter new Accommodation Type:\n");
	printf("1. Single Room\n");
	printf("2. Apartment\n");
	printf("3. Bungalow\n");
	printf("4. Two Story\n");
	scanf("%d", &new_node->accommodationType);
	printf("Enter Number of rooms: \n");
	printf("1. 1 Bedroom\n");
	printf("2. 2 Bedrooms\n");
	printf("3. 3 Bedrooms\n");
	printf("4. 4 Bedrooms\n");
	printf("5. More than 4 Bedrooms\n");
	scanf("%d", &new_node->num_rooms);
	printf("Enter Monthly Rental Price: ");
	scanf("%f", &new_node->monthly_rental);
	printf("Are pets allowed? (1 for No, 2 for Yes): ");
	scanf("%d", &(new_node->petsAllowed));
	printf("Enter the average duration of stay:\n");
	printf("1. One day\n");
	printf("2. Less than 3 days\n");
	printf("3. Less than 7 days\n");
	printf("4. More than 7 days\n");
	scanf("%d", &(new_node->duration));


	new_node->next = NULL;

	if (*head == NULL)
	{
		// If the list is empty or the new node has the smallest property ID, insert at the beginning
		*head = new_node;
	}
	else
	{
		// Insert the new node in sorted order
		accommodationL* temp = *head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = new_node;
	}

	printf("\nAccommodation with Property Identification Number %d has been added.\n", new_node->property_id);

}

void display_all_accommodation(accommodationL* head)
{
	accommodationL* current = head;

	if (head == NULL)
	{
		printf("\nSorry the list is empty.\n");
		return;
	}
	
	while (current != NULL) 
	{
		printf("ACCOMMODATION REPORT:\n");
		printf("\nProperty ID: %d\n", current->property_id);
		printf("Owner Name: %s %s\n", current->owner_first_name, current->owner_last_name);
		printf("Year Built: %d\n", current->year_built);
		printf("Email Address: %s\n", current->email_address);
		
		printf("Number of Rooms: ");
		if (current->num_rooms == 1) 
		{
			printf("1 Bedroom\n");
		}
		else if (current->num_rooms == 2) 
		{
			printf("2 Bedrooms\n");
		}
		else if (current->num_rooms == 3) 
		{
			printf("3 Bedrooms\n");
		}
		else if (current->num_rooms == 4) 
		{
			printf("4 Bedrooms\n");
		}
		else 
		{
			printf("More than 4 Bedrooms\n");
		}

		printf("Monthly Rental Price: $%.2f\n", current->monthly_rental);
		printf("Pets Allowed: %s\n", (current->petsAllowed == 2) ? "Yes" : "No");
		
		printf("Average Duration of Stay: ");
		if (current->duration == 1) {
			printf("One day\n");
		}
		else if (current->duration == 2) {
			printf("Less than 3 days\n");
		}
		else if (current->duration == 3) {
			printf("Less than 7 days\n");
		}
		else {
			printf("More than 7 days\n");
		}


		printf("Accommodation Type: ");
		if (current->accommodationType == 1) 
		{
			printf("Single Room\n");
		}
		else if (current->accommodationType == 2) 
		{
			printf("Apartment\n");
		}
		else if (current->accommodationType == 3) 
		{
			printf("Bungalow\n");
		}
		else if (current->accommodationType == 4) 
		{
			printf("Two Story\n");
		}
		else 
		{
			printf("Unknown Type\n");
		}


		printf("-------------------------------------------\n");
		current = current->next;
	}
}

void delete_accommodation(accommodationL** head)
{
	//Declare Variables
	int property_id;

	accommodationL* temp = *head;
	accommodationL* prev = NULL;

	printf("\nEnter the Property Identification Number of the accommodation to delete: ");
	scanf("%d", &property_id);

	if (*head == NULL)
	{
		printf("\nNo accommodations found.\n");
		return;
	}

	while (temp != NULL && temp->property_id != property_id)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL)
	{
		printf("\nAccommodation with Property Identification Number %d not found.\n", property_id);
		return;
	}

	if (prev == NULL)
	{
		*head = temp->next;
	}
	else
	{
		prev->next = temp->next;
	}

	free(temp);
	printf("\nAccommodation with Property Identification Number %d has been deleted successfully.\n", property_id);
}

void update_accommodation(accommodationL* head)
{
	//Declare Variables
	int property_id;
	float new_monthly_rental;
	int new_num_rooms;

	printf("\nEnter the Property Identification Number of the accommodation to update: ");
	scanf("%d", &property_id);

	accommodationL* temp = head;

	while (temp != NULL && temp->property_id != property_id)
	{
		temp = temp->next;
	}

	if (temp == NULL)
	{
		printf("\nAccommodation with Property Identification Number %d not found.\n", property_id);
		return;
	}

	// Asks the user to update each of the details.
	printf("Enter new Name of owner: ");
	scanf("%s", temp->owner_first_name);
	printf("Enter new Last Name of Owner: ");
	scanf("%s", temp->owner_last_name);
	printf("Enter new Year Built: ");
	scanf("%d", &temp->year_built);
	printf("Enter new Email Address: ");
	scanf("%s", temp->email_address);
	printf("Enter new Accommodation Type:\n");
	printf("1. Single Room\n");
	printf("2. Apartment\n");
	printf("3. Bungalow\n");
	printf("4. Two Story\n");
	scanf("%d", &(temp->accommodationType));
	printf("Enter new Number of rooms: \n");
	printf("1. 1 Bedroom\n");
	printf("2. 2 Bedrooms\n");
	printf("3. 3 Bedrooms\n");
	printf("4. 4 Bedrooms\n");
	printf("5. More than 4 Bedrooms\n");
	scanf("%d", &temp->num_rooms);
	printf("Enter new Monthly Rental Price: ");
	scanf("%f", &temp->monthly_rental);
	printf("Are pets allowed? (1 for No, 2 for Yes): ");
	scanf("%d", &(temp->petsAllowed));
	printf("Enter new average duration of stay:\n");
	printf("1. One day\n");
	printf("2. Less than 3 days\n");
	printf("3. Less than 7 days\n");
	printf("4. More than 7 days\n");
	scanf("%d", &(temp->duration));

	printf("\nAccommodation with Property Identification Number %d has been updated successfully.\n", property_id);
}

void print_accommodation_report(accommodationL* head)
{
	accommodationL* temp = head;
	
	FILE* fp; //Used for the file access

	//Open the file in write mode.
	fp = fopen("accommodation.txt", "w");

	if (head == NULL)
	{
		printf("\nNo accommodations found.\n");
		return;
	}

	if (fp == NULL)
	{
		printf("\nError: Unable to create report file.\n");
		return;
	}

	fprintf(fp, "ACCOMMODATION REPORT\n\n");

	while (temp != NULL)
	{
		fprintf(fp, "-------------------------------------------\n");
		fprintf(fp, "\nProperty ID: %d\n", temp->property_id);
		fprintf(fp, "Owner Name: %s %s\n", temp->owner_first_name, temp->owner_last_name);
		fprintf(fp, "Year Built: %d\n", temp->year_built);
		fprintf(fp, "Email Address: %s\n", temp->email_address);
		
		fprintf(fp, "Number of Rooms: ");
		if (temp->num_rooms == 1) 
		{
			fprintf(fp, "1 Bedroom\n");
		}
		else if (temp->num_rooms == 2) 
		{
			fprintf(fp, "2 Bedrooms\n");
		}
		else if (temp->num_rooms == 3)
		{
			fprintf(fp, "3 Bedrooms\n");
		}
		else if (temp->num_rooms == 4)
		{
			fprintf(fp, "4 Bedrooms\n");
		}
		else 
		{
			printf("More than 4 Bedrooms\n");
		}

		fprintf(fp, "Monthly Rental Price: €%.2f\n", temp->monthly_rental);
		fprintf(fp, "Pets Allowed: %s\n", (temp->petsAllowed == 2) ? "Yes" : "No");
		
		fprintf(fp, "Average Duration of Stay: ");
		if (temp->duration == 1) 
		{
			fprintf(fp, "One day\n");
		}
		else if (temp->duration == 2) 
		{
			fprintf(fp, "Less than 3 days\n");
		}
		else if (temp->duration == 3) 
		{
			fprintf(fp, "Less than 7 days\n");
		}
		else 
		{
			fprintf(fp, "More than 7 days\n");
		}


		fprintf(fp, "Accommodation Type: ");
		if (temp->num_rooms == 1)
		{
			fprintf(fp, "1 Bedroom\n");
		}
		else if (temp->num_rooms == 2)
		{
			fprintf(fp, "2 Bedrooms\n");
		}
		else if (temp->num_rooms == 3)
		{
			fprintf(fp, "3 Bedrooms\n");
		}
		else if (temp->num_rooms == 4)
		{
			fprintf(fp, "4 Bedrooms\n");
		}
		else 
		{
			printf("More than 4 Bedrooms\n");
		}


		fprintf(fp, "-------------------------------------------\n");

		temp = temp->next;

	}

	//Closing the file once finished with it.
	fclose(fp);

	printf("\nAccommodation report generated successfully.\n");

}

void display_accommodation_details(accommodationL** head)
{
	//Declare Variables
	int choice;

	printf("Please choose how you would like to search for the accommodation:\n");
	printf("1. Search by Property Identification Number\n");
	printf("2. Search by Owner Name\n");
	scanf("%d", &choice);

	if (choice == 1)
	{
		//Declare Variables
		int property_id;

		printf("Please enter the Property Identification Number: ");
		scanf("%d", &property_id);

		accommodationL* current = head;

		if (property_id == NULL)
		{
			printf("\nAccommodation with Property Identification Number %d not found.\n", property_id);
		}
		while (current != NULL)
		{
			//Checking if the id entered is the same as whats on file already.
			if(current->property_id == property_id)
			{
				printf("\nACCOMMODATION REPORT:\n");
				printf("Property ID: %d\n", current->property_id);
				printf("Owner Name: %s %s\n", current->owner_first_name, current->owner_last_name);
				printf("Year Built: %d\n", current->year_built);
				printf("Email Address: %s\n", current->email_address);

				printf("Number of Rooms: ");
				if (current->num_rooms == 1)
				{
					printf("1 Bedroom\n");
				}
				else if (current->num_rooms == 2)
				{
					printf("2 Bedrooms\n");
				}
				else if (current->num_rooms == 3)
				{
					printf("3 Bedrooms\n");
				}
				else if (current->num_rooms == 4)
				{
					printf("4 Bedrooms\n");
				}
				else
				{
					printf("More than 4 Bedrooms\n");
				}

				printf("Monthly Rental Price: €%.2f\n", current->monthly_rental);
				printf("Pets Allowed: %s\n", (current->petsAllowed == 2) ? "Yes" : "No");

				printf("Average Duration of Stay: ");
				if (current->duration == 1)
				{
					printf("One day\n");
				}
				else if (current->duration == 2)
				{
					printf("Less than 3 days\n");
				}
				else if (current->duration == 3)
				{
					printf("Less than 7 days\n");
				}
				else
				{
					printf("More than 7 days\n");
				}

			}
		 current = current->next;
		}
	}
	else if (choice == 2)
	{
		//Declare Variables
		char owner_first_name[MAX_LEN], owner_last_name[MAX_LEN];


		printf("\nEnter the first name and last name of the owner for the accommodation: ");
		scanf("%s %s", owner_first_name, owner_last_name);

		accommodationL* temp = head;

		if (temp == NULL)
		{
			printf("\nAccommodation with Owner Name %s %s not found.\n", owner_first_name, owner_last_name);
			return;
		}

		while (temp != NULL)
		{
			//Checking if the first and last name entered is the same as the ones that have been entered previously.
			if (strcmp(temp->owner_first_name, owner_first_name) == 0 || strcmp(temp->owner_last_name, owner_last_name) == 0)
			{

				printf("\nACCOMMODATION DETAILS:\n");
				printf("\nProperty ID: %d\n", temp->property_id);
				printf("Owner Name: %s %s\n", temp->owner_first_name, temp->owner_last_name);
				printf("Year Built: %d\n", temp->year_built);
				printf("Email Address: %s\n", temp->email_address);

				printf("Number of Rooms: ");
				if (temp->num_rooms == 1)
				{
					printf("1 Bedroom\n");
				}
				else if (temp->num_rooms == 2)
				{
					printf("2 Bedrooms\n");
				}
				else if (temp->num_rooms == 3)
				{
					printf("3 Bedrooms\n");
				}
				else if (temp->num_rooms == 4)
				{
					printf("4 Bedrooms\n");
				}
				else
				{
					printf("More than 4 Bedrooms\n");
				}


				printf("Monthly Rental Price: €%.2f\n", temp->monthly_rental);
				printf("Pets Allowed: %s\n", (temp->petsAllowed == 2) ? "Yes" : "No");

				printf("Average Duration of Stay: ");
				if (temp->duration == 1)
				{
					printf("One day\n");
				}
				else if (temp->duration == 2)
				{
					printf("Less than 3 days\n");
				}
				else if (temp->duration == 3)
				{
					printf("Less than 7 days\n");
				}
				else
				{
					printf("More than 7 days\n");
				}


				printf("-------------------------------------------\n");
			}
			temp = temp->next;
		}
	}

}

void generate_statistics_details(accommodationL* head) 
{
	//Declare Variables
	int singleRooms = 0, apartments = 0, bungalows = 0, twoStories = 0;
	double maxRental = 0.0, minRental = DBL_MAX, totalRental = 0.0;
	int count = 0;

	// Traverse the linked list and count the number of each type of accommodation
	accommodationL* current = head;

	while (current != NULL) 
	{

		if (current->accommodationType == 1) 
		{
			singleRooms++;
		}
		else if (current->accommodationType == 2) 
		{
			apartments++;
		}
		else if (current->accommodationType == 3) 
		{
			bungalows++;
		}
		else if (current->accommodationType == 4) 
		{
			twoStories++;
		}


		// Calculate rental statistics
		if (current->monthly_rental > maxRental) 
		{
			maxRental = current->monthly_rental;
		}
		if (current->monthly_rental < minRental) 
		{
			minRental = current->monthly_rental;
		}

		totalRental += current->monthly_rental;

		count++;

		current = current->next;
	}

	// Calculate percentages
	double total = singleRooms + apartments + bungalows + twoStories;
	double singleRoomsPercent = singleRooms / total * 100;
	double apartmentsPercent = apartments / total * 100;
	double bungalowsPercent = bungalows / total * 100;
	double twoStoriesPercent = twoStories / total * 100;

	// Output statistics to console
	printf("\nAccommodation Statistics:\n\n");
	printf("A. %d Single Rooms (%.2f%%)\n", singleRooms, singleRoomsPercent);
	printf("B. %d Apartments (%.2f%%)\n", apartments, apartmentsPercent);
	printf("C. %d Bungalows (%.2f%%)\n", bungalows, bungalowsPercent);
	printf("D. %d Two Stories (%.2f%%)\n", twoStories, twoStoriesPercent);
	printf("E. Max Rental Amount: €%.2f\n", maxRental);
	printf("F. Min Rental Amount: €%.2f\n", minRental);
	printf("G. Average Rental Amount: €%.2f\n", totalRental / count);


	//For printing to the accommodation.txt file as used above previous
	FILE* fptr;

	fptr = fopen("accommodation.txt", "a"); //Open the file in append mode and adds the data to the end of the previous details that have been printed to the file already.
	
	if (fptr == NULL) 
	{
		printf("Error opening file.\n");
		return;
	}

	fprintf(fptr, "\nAccommodation Statistics:\n");
	fprintf(fptr, "A. Percentage of Single Room Accommodation: %.2f%%\n", singleRoomsPercent);
	fprintf(fptr, "B. Percentage of Apartment Accommodation: %.2f%%\n", apartmentsPercent);
	fprintf(fptr, "C. Percentage of Bungalow Accommodation: %.2f%%\n", bungalowsPercent);
	fprintf(fptr, "D. Percentage of Two Story Accommodation: %.2f%%\n", twoStoriesPercent);
	fprintf(fptr, "E. Maximum Rental Amount: €%.2f\n", maxRental);
	fprintf(fptr, "F. Minimum Rental Amount: €%.2f\n", minRental);
	fprintf(fptr, "G. Average Rental Amount: €%.2f\n", totalRental / count);

	fclose(fptr); //Close the file once finished with it

}

void list_by_monthly_rental(accommodationL* head)
{
	accommodationL* temp = head;

	//Declare variables
	int count = 0;

	if (head == NULL)
	{
		printf("\nSorry the list is empty.\n");
		return;
	}

	// Count the number of nodes in the list
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}

	// Create an array to store the pointers to nodes
	accommodationL** arr = (accommodationL**)malloc(count * sizeof(accommodationL*));
	
	if (arr == NULL)
	{
		printf("\nMemory allocation failed.\n");
		return;
	}

	// Populate the array with the pointers to nodes
	temp = head;
	for (int i = 0; i < count; i++)
	{
		arr[i] = temp;
		temp = temp->next;
	}

	// Sort the array of nodes by monthly rental
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (arr[j]->monthly_rental > arr[j + 1]->monthly_rental)
			{
				accommodationL* temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	// Print the sorted list of nodes
	printf("\nACCOMMODATION LIST BY MONTHLY RENTAL:\n");
	for (int i = 0; i < count; i++)
	{
		printf("\nProperty ID: %d\n", arr[i]->property_id);
		printf("Owner Name: %s %s\n", arr[i]->owner_first_name, arr[i]->owner_last_name);
		printf("Year Built: %d\n", arr[i]->year_built);
		printf("Email Address: %s\n", arr[i]->email_address);
		
		printf("Number of Rooms: ");
		switch (arr[i]->num_rooms)
		{
			case 1:
				printf("1 Bedroom\n");
				break;
			case 2:
				printf("2 Bedrooms\n");
				break;
			case 3:
				printf("3 Bedrooms\n");
				break;
			case 4:
				printf("4 Bedrooms\n");
				break;
			default:
				printf("More than 4 Bedrooms\n");
				break;
		}

		printf("Monthly Rental Price: €%.2f\n", arr[i]->monthly_rental);
		printf("Pets Allowed: %s\n", (arr[i]->petsAllowed == 2) ? "Yes" : "No");
		
		printf("Average Duration of Stay: ");
		switch (arr[i]->duration)
		{
			case 1:
				printf("One day\n");
				break;
			case 2:
				printf("Less than 3 days\n");
				break;
			case 3:
				printf("Less than 7 days\n");
				break;
			default:
				printf("More than 7 days\n");
				break;
		}

		printf("-------------------------------------------\n");
	}

	free(arr);
}
