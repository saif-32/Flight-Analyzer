#ifndef ROUTE_RECORDS
#define ROUTE_RECORDS


typedef struct RouteRecord
{
  char origin[4];
  char destination[4];
  char airline[3];
  int passengers[6];


} RouteRecord;

typedef enum SearchType
{ ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

/*
    Function: createRecords
    ------------------------
    This function goes through the CSV file and counts the amount of records.
    It also dynamically allocates an array for RouteRecords based on the amount
    of records, as well as initalizing the passengers array for the struct objects.
        File* FileIn: This paramater passes in the csv file.
    Returns: The return value is the pointer to the dynamically allocated array.    

*/
RouteRecord* createRecords(FILE* fileIn);

/*
    Function: fillRecords
    ------------------------
    This function goes through the CSV file and parses through the airline records.
    After parsing through each airline record, it calls the findAirlineRoute function
    and checks to see if the specific route has already been added to the array. If not,
    the function will add. If it has been added, it will add the passenger number for that route.
        Routerecord *r: This paramater passes in the dynamically allocated array.
        File* FileIn: This paramater passes in the csv file.
    Returns: The return value is the length of the unique routes.

*/
int fillRecords(RouteRecord* r, FILE* fileIn); 

/*
    Function: findAirlineRoute
    RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx
    ------------------------
    This recursive function goes through the RouteRecords array and checks to see if the origin, destination
    and airline specific route has been found. If it is not in the route, it returns -1. Otherwise,
    it returns the current index on where its found.
        Routerecord *r: This paramater passes in the dynamically allocated array.
        int length: This paramater passes in the unique route amounts.
        const char* origin: This paramater passes in the origin to check.
        const char* destination: This paramater passes in the destination to check.
        const char* airline: This paramater passes in the airline to check.
        int curIdx: This paramater passes in the index it needs to check in the array.
        File* FileIn: This paramater passes in the csv file.
    Returns: The return value is -1, if not found. Current Index if found.

*/
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);

/*
    Function: searchRecords
    ------------------------
    This function takes in user input and compares the input with data in the routeRecords array.
    If the user input has been found, the function lists statistics regarding the input such as
    statistics about the AA airline monthly passengers.
        Routerecord *r: This paramater passes in the dynamically allocated array.
        int length: This paramater passes in the unique route amounts.
        const char* key1: This paramater passes in the user's input
        const char* key2: This paramater passes in the user's input
        SearchType st: This paramater passes in the Searchtype enum.
    Returns: The return value is nothing.

*/
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st); 

/*
    Function: printMenu
    ------------------------
    This function prints out a menu that enables the user to see options for their input.
    Returns: The return value is nothing.

*/
void printMenu();




#endif
