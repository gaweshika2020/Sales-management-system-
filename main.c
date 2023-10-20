#include <stdio.h>
#include <stdlib.h>
#include "xyz.h"

vehicles vehicleList[MAX_VEHICLES];
int vehicleListCount;
items itemList[MAX_ITEMS];
int itemListCount;
stocks stockList[MAX_ITEMS];
int stockListCount;
load loadList[MAX_VEHICLES][MAX_ITEMS];
int loadListCount[MAX_VEHICLES];
char vehicleLoadIdMap[MAX_VEHICLES][100];
int rowId;
int loadListRecordCount;
int loadQuantity;

int main()
{
	int i, j;
	vehicleListCount = 0;
	itemListCount = 0;
	stockListCount = 0;
	rowId = 0;

	for (i = 0; i < MAX_VEHICLES; i++){
		loadListCount[i] = 0;
	}

	char username[15];
	char password[12];
	int option;

	printf("------------------------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("-----------------------------------  XYZ Distributors  -----------------------------------\n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------\n");

	/* Login */

	printf("\nEnter your username:\n");
	scanf("%s",&username);

	printf("\nEnter your password:\n");
	scanf("%s",&password);

	if (strcmp(username,"xyz") == 0) {
		if (strcmp(password,"123") == 0) {
			printf("Welcome. Login Success!\n\n");
		}
		else {
			printf("wrong password!\n");
			return 0;
		}
	}
	else {
		printf("User doesn't exist!\n");
		return 0;
	}

	//read files and initialize variables
	read_all_files();
    Sleep(2500);
	system("cls");

	do {
		/* User Options */
		printf("\n---------\n");
		printf("HOME PAGE\n");
		printf("---------\n\n");

		printf("[1]:Managing Vehicles\n");
		printf("[2]:Managing Sales Items\n");
		printf("[3]:Managing Stock Items\n");
		printf("[4]:Facilitating Loading\n");
		printf("[5]:Facilitating Unloading\n");
		printf("[6]:Producing report\n");
		printf("[0]:Exit\n\n");
		printf("\nEnter your choice:\n");
		scanf("%d",&option);

		Sleep(2500);
		system("cls");


		switch(option) {
			case 1:
			    printf("Entered to managing vehicle page");
				manage_vehicles();
				break;
			case 2:
			    printf("Entered to managing sales item page\n");
				manage_items();
				break;
			case 3:
			     printf("Entered to managing stock item page\n");
				 manage_stocks();
				break;
			case 4:
			    printf("Entered to Facilitating loading page\n");
				manage_loads();
				break;
			case 5:
			    printf("Entered to Facilitating unloading page\n");
				unload_items();
				break;
			case 6:
			    printf("Entered to Producing report page\n");
				report();
				break;
            case 0:
                printf("Thank you!!!");
                break;
		}
	} while (option != 0);

//read files and initialize variables
	read_all_files();

	write_all_files();

	return 0;

}

/*
 * Reading all files and initialzing global variables.
 */
void read_all_files()
{


	FILE *fptrVehicles;
	FILE *fptrItems;
	FILE *fptrStocks;
	FILE *fptrloads;

	char vehicleId[100];

	char prev_vehicleId[100] = {0};
	char itemId[10];
	int quantity;

	fptrVehicles = fopen("VEHICLES.txt","r");
	fptrItems = fopen("ITEMS.txt","r");
	fptrStocks = fopen("STOCKS.txt","r");
	fptrloads = fopen("LOADS.txt","r");



// vehicles
	if (fptrVehicles == NULL) {
		printf("File not found!");
	}
	else {
		while (fscanf(fptrVehicles, "%s\t%s\t%s\n", vehicleList[vehicleListCount].vehicleId, vehicleList[vehicleListCount].vehicleName, vehicleList[vehicleListCount].salesmanId)!=EOF) {
			vehicleListCount++;
		}
	}
	fclose(fptrVehicles);

// items
	if (fptrItems == NULL) {
		printf("File not found!");
	}
	else {
		while (fscanf(fptrItems, "\n%s\t%s\t%f\t\n", itemList[itemListCount].itemId, itemList[itemListCount].itemName, &itemList[itemListCount].unitPrice)!=EOF) {
			itemListCount++;
		}
	}
	fclose(fptrItems);

// stocks
	if (fptrStocks == NULL) {
		printf("File not found!");
	}
	else {
		while (fscanf(fptrStocks, "%s\t%d\t\n", stockList[stockListCount].itemId, &stockList[stockListCount].quantity)!=EOF) {
			stockListCount++;
		}
	}
	fclose(fptrStocks);

// loads
	if (fptrloads == NULL) {
		printf("File not found!");
	}
	else {
		while (fscanf(fptrloads, "%s\t%s\t%d\t\n", vehicleId, itemId, &loadQuantity)!=EOF) {

			printf("load: %s\t%s\t%d\t\n", vehicleId , itemId, loadQuantity);
			if (strcmp(prev_vehicleId, vehicleId) != 0) {
				strcpy(prev_vehicleId, vehicleId); //STRING COPY
				rowId++;
			}
			strcpy(loadList[rowId - 1][loadListCount[rowId - 1]].itemId, itemId);
			loadList[rowId - 1][loadListCount[rowId - 1]].loadQuantity = quantity;
			strcpy(vehicleLoadIdMap[rowId - 1], vehicleId);
			loadListCount[rowId - 1]++;
            loadListRecordCount=sizeof(loadListCount);
		}
	}
	fclose(fptrloads);

}

/*
 * Write to files VEHICLE.txt, ITEM.txt,  STOCKS.txt , & LOADS.txt
 */
void write_all_files()
{
	FILE *fptrVehicles;
	FILE *fptrItems;
	FILE *fptrStocks;
	FILE *fptrloads;
	int i, j;

	fptrVehicles = fopen("VEHICLES.txt","w");
	fptrItems = fopen("ITEMS.txt","w");
	fptrStocks = fopen("STOCKS.txt","w");
	fptrloads = fopen("LOADS.txt","w");
//vehicles
	if (fptrVehicles == NULL) {
		printf("File not found!");
	}
	else {
		for (i = 0; i < vehicleListCount; i++) {
			fprintf (fptrVehicles, "%s\t%s\t%s\n", vehicleList[i].vehicleId, vehicleList[i].vehicleName, vehicleList[i].salesmanId);
		}
	}
	fclose(fptrVehicles);

//items
    if (fptrItems == NULL) {
		printf("File not found!");
	}
	else {
		for (i = 0; i < itemListCount; i++) {
			fprintf (fptrItems, "%s\t%s\t%f\n", itemList[i].itemId, itemList[i].itemName, itemList[i].unitPrice);
		}
	}
	fclose(fptrItems);

//stocks
	if (fptrStocks == NULL) {
		printf("File not found!");
	}
	else {
        for(i = 0; i < itemListCount; i++) {
		fprintf(fptrStocks, "%s\t%d\t\n", stockList[stockListCount].itemId, &stockList[stockListCount].quantity);

	       }
	}
	fclose(fptrStocks);

//loads
	if (fptrloads == NULL) {
		printf("File not found!");
	}
	else {
		for (i = 0; i < rowId; i++) {
			for (j = 0; j < loadListRecordCount; j++)
				fprintf(fptrloads,"%s %s %d \n",vehicleLoadIdMap[i], loadList[i][j].itemId, loadList[i][j].loadQuantity);
		}
	}
	fclose(fptrloads);
}


/*
 * VEHICLE PAGE
 */
void manage_vehicles()
{
    Sleep(2500);
    system("cls");
	printf("------------\n");
	printf("VEHICLE PAGE\n");
	printf("----------\n\n");

	printf("[1]:Display vehicle list:  \n");
	printf("[2]:Add new vehicle:  \n");
	printf("[3]:Delete an entry: \n");

	int option;
	printf("\nEnter your choice:\n");
	scanf("%d",&option);

	Sleep(2500);
	system("cls");

	switch(option){

		case 1:
		    printf("\n  Vehicle List :  \n\n");
			display_vehicles();
			break;
		case 2:
			add_vehicle();
			break;
		case 3:
			delete_vehicle();
			break;

	}

  //system("cls");
}

/*
 * ITEM PAGE
 */

void manage_items()
{
	//Sleep(250);
    //system("cls");
	printf("------------\n");
	printf("ITEMS PAGE\n");
	printf("----------\n\n");

	printf("[1]:Display Item list:  \n");
	printf("[2]:Add new Item:  \n");
	printf("[3]:Delete an entry: \n");

	int option;
	printf("\nEnter your choice:\n");
	scanf("%d",&option);

	Sleep(2500);
	system("cls");

	switch(option){

		case 1:
		    printf("\n  Item List :  \n\n");
		    printf("Items\n\n");
			display_items();

			break;
		case 2:
			add_item();
			break;
		case 3:
			delete_item();
			break;

	}

  //system("cls");
}

/*
 * STOCK PAGE
 */
void manage_stocks()
{
    //Sleep(250);
    //system("cls");
	printf("------------\n");
	printf("STOCK PAGE\n");
	printf("----------\n\n");

	printf("[1]:Display Stock list:  \n");
	printf("[2]:Add new Stock:  \n");
	printf("[3]:Delete a Stock: \n");

	int option;
	printf("\nEnter your choice:\n");
	scanf("%d",&option);

	Sleep(250);
	system("cls");

	switch(option){

		case 1:
		    printf("\n  Stock List :  \n\n");
			display_stocks();
			break;
		case 2:
			add_stock();
			break;
		case 3:
			delete_stock();
			break;

	}

  //system("cls");
}

/*
 * LOAD PAGE
 */

void manage_loads()
{
    //Sleep(250);
    //system("cls");
	printf("------------\n");
	printf("LOAD PAGE\n");
	printf("----------\n\n");

	printf("[1]:Display Load list:  \n");
	printf("[2]:Add new Load:  \n");
	printf("[3]:Delete a Load: \n");

	int option;
	printf("\nEnter your choice:\n");
	scanf("%d",&option);

	Sleep(2500);
	system("cls");

	switch(option){

		case 1:
		    printf("\n  Load List :  \n\n");
			//display_loads();
			break;
		case 2:
			//add_load();
			break;
		case 3:
			//delete_load();
			break;

	}

  //system("cls");
}

void unload_items()
{
	// TODO:
}

void report()
{
	// TODO:
}



/* **************** */
/* Vehicles related */
/* **************** */

/*
 * Displays the vehicle list
 */
void display_vehicles()
{
	int i;
	printf("VehicleID\tName\t\tSalesmanID\n");
	for (i = 0; i < vehicleListCount; i++) {
		printf("%s\t\t%s\t\t%s\n", vehicleList[i].vehicleId, vehicleList[i].vehicleName, vehicleList[i].salesmanId);
	}
}

/*
 * Add an entry to the vehicle list
 */
void add_vehicle()
{
	printf("Add \"vehicle ID\" \"Vehicle Name\" \"salesman ID\": \n");
	scanf("%s %s %s", vehicleList[vehicleListCount].vehicleId, vehicleList[vehicleListCount].vehicleName, vehicleList[vehicleListCount].salesmanId);
	printf ("Entry %s\t%s\t%s\n successfull added!\n",vehicleList[vehicleListCount].vehicleId, vehicleList[vehicleListCount].vehicleName, vehicleList[vehicleListCount].salesmanId);
	vehicleListCount++;
}

/*
 * Delete an existing entry
 */
void delete_vehicle()
{
	char ID[2500];
	int i, j = -1;
	printf("Entry List:\n");
	display_vehicles();
	printf("Enter the vehicle ID to delete that entry:\n");
	scanf("%s", ID);
	for (i = 0; i < vehicleListCount; i++) {
		if (strcmp(ID,vehicleList[i].vehicleId) == 0) {
			j = i;
			break;
		}
	}

	if (j != -1) {
		printf ("Deleting entry %s\t\t%s\t\t%s\n...\n",vehicleList[j].vehicleId, vehicleList[j].vehicleName, vehicleList[j].salesmanId);

		for(i = j; i < vehicleListCount - 1; i++){
			vehicleList[i] = vehicleList[i+1];
		}
		vehicleListCount--;
	}
	else {
		printf ("No such entry");
	}
}

/* **************** */
/* Items related */
/* **************** */

/*
 * Displays the Item list
 */
void display_items()
{
	int i;
	printf("ItemID\tName\t\tUnitprice\n");
	for (i = 0; i < itemListCount; i++) {
		printf("%s\t%s\t%f\n", itemList[i].itemId, itemList[i].itemName, itemList[i].unitPrice);
	}
}

/*
 * Add an entry to the item list
 */
void add_item()
{
	printf("Add \"Item ID\" \"Item Name\" \"UnitPrice\": \n");
	scanf("%s %s %f", itemList[itemListCount].itemId, itemList[itemListCount].itemName, itemList[itemListCount].unitPrice);
	printf ("Entry %s\t%s\t%f\n successfull added!\n",itemList[itemListCount].itemId, itemList[itemListCount].itemName, itemList[itemListCount].unitPrice);
	vehicleListCount++;
}

/*
 * Delete an existing entry
 */
void delete_item()
{
	char ID[2500];
	int i, j = -1;
	printf("Entry List:\n");
	display_items();
	printf("Enter the item ID to delete that entry:\n");
	scanf("%s", ID);
	for (i = 0; i < itemListCount; i++) {
		if (strcmp(ID,itemList[i].itemId) == 0) {
			j = i;
			break;
		}
	}

	if (j != -1) {
		printf ("Deleting entry %s\t%s\t%f\n...\n",itemList[j].itemId, itemList[j].itemName, itemList[j].unitPrice);

		for(i = j; i < itemListCount - 1; i++){
			itemList[i] = itemList[i+1];
		}
		itemListCount--;
	}
	else {
		printf ("No such entry");
	}
}

/* **************** */
/* Stocks related */
/* **************** */

/*
 * Displays the Stock list
 */
void display_stocks()
{
	int i;
	printf("ItemID\tQuantity\n");
	for (i = 0; i < stockListCount; i++) {
		printf("%s\t%d\t\n", stockList[i].itemId, stockList[i].quantity);
	}
}

/*
 * Add an entry to the stock list
 */
void add_stock()
{
	printf("Add \"Item ID\" \"Quantity\": \n");
	scanf("%s %d", stockList[stockListCount].itemId, stockList[stockListCount].quantity);
	printf ("Entry %s\t%d\t\n successfull added!\n",stockList[stockListCount].itemId, stockList[stockListCount].quantity);
	stockListCount++;
}

/*
 * Delete a stock entry
 */

void delete_stock()
{
	char ID[2500];
	int i, j = -1;
	printf("Entry List:\n");
	display_stocks();
	printf("Enter the Item ID to delete that entry:\n");
	scanf("%s", ID);
	for (i = 0; i < stockListCount; i++) {
		if (strcmp(ID,stockList[i].itemId) == 0) {
			j = i;
			break;
		}
	}

	if (j != -1) {
		printf ("Deleting entry %s\t%d\t\n...\n",stockList[j].itemId, stockList[j].quantity);

		for(i = j; i < stockListCount - 1; i++){
			stockList[i] = stockList[i+1];
		}
		stockListCount--;
	}
	else {
		printf ("No such entry");
	}
}

/* **************** */
/* LOAD related */
/* **************** */


 //* Displays the Load list
/*
void display_loads()
{
	int i;
	printf("VehicleID\tItemID\t\tQuantity\n");
	for (i = 0; i < loadListRecordCount; i++) {
		printf("%s\t\t%s\t\t%d\n", loadList[i]->vehicleId, loadList[i]->itemId, loadList[i]->loadQuantity);
	}
}*/

/*
 * Add an entry to the load list
 */
/*
void add_load()
{
	printf("Add \"vehicle ID\" \"ItemID\" \"Quantity\": \n");
	scanf("%s %s %d", loadList[loadListRecordCount].vehicleId, loadList[loadListRecordCount].itemId, loadList[loadListRecordCount].loadQuantity);
	printf ("Entry %s\t%s\t%d\n successfull added!\n",loadList[loadListRecordCount].vehicleId, loadList[loadListRecordCount].itemId, loadList[loadListRecordCount].loadQuantity);
	loadListRecordCount++;
}*/

/*
 * Delete an existing entry
 */
/*
void delete_load()
{
	char ID[2500];
	int i, j = -1;
	printf("Entry List:\n");
	display_loads();
	printf("Enter the vehicle ID to delete that entry:\n");
	scanf("%s", ID);
	for (i = 0; i < loadListRecordCount; i++) {
		if (strcmp(ID,loadList[i].vehicleId) == 0) {
			j = i;
			break;
		}
	}

	if (j != -1) {
		printf("Deleting entry %s\t\t%s\t\t%s\n...\n",loadList[j].vehicleId, loadList[j].itemId, loadList[j].loadQuantity);

		for(i = j; i < loadListRecordCount - 1; i++){
			loadList[i] = loadList[i+1];
		}
		loadListRecordCount--;
	}
	else {
		printf("No such entry");
	}
}*/

