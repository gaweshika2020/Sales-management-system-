#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VEHICLES 25
#define MAX_ITEMS 20
#define MAX_SALESMEN 25

typedef struct vehicles
{
	char vehicleId[100];
	char vehicleName[100];
	char salesmanId[100];
} vehicles;

typedef struct items
{
	char itemId[10];
	char itemName[20];
	float unitPrice;
} items;

typedef struct stocks
{
	char itemId[10];
	int quantity;
} stocks;

typedef struct load
{   char vehicleId[100];
	char itemId[10];
	int loadQuantity;
} load;

//Home page functions
void manage_vehicles(void);
void manage_items(void);
void manage_stocks(void);
void load_items(void);
void unload_items(void);
void report(void);

//file reading and writing
void read_all_files(void);
void write_all_files(void);

// related to vehicle page
void display_vehicles(void);
void add_vehicle(void);
void delete_vehicle(void);


// related to items page
void display_items(void);
void add_item(void);
void delete_item(void);


// related to stocks page
void display_stocks(void);
void add_stock(void);
void delete_stock(void);

// related to loads page
void display_loads(void);
void add_load(void);
void delete_load(void);

