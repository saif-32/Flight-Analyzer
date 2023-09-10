/*
    Function: createRecords
    ------------------------
    This function goes through the CSV file and counts the amount of records.
    It also dynamically allocates an array for RouteRecords based on the amount
    of records, as well as initalizing the passengers array for the struct objects.
        File* FileIn: This paramater passes in the csv file.
    Returns: The return value is the pointer to the dynamically allocated array.    

*/

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

/*
    Function: printMenu
    ------------------------
    This function prints out a menu that enables the user to see options for their input.
    Returns: The return value is nothing.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "route-records.h"

RouteRecord* createRecords (FILE* fileIn)
{
    int records = 0;
    char line[1000];
    while (fgets(line, 1000, fileIn) != NULL) // Counts each line until file is closed.
    {
        records++;
    }
    records = records -1; // Subtract the header.
    RouteRecord *RouteRecords = (RouteRecord*)malloc((records) * sizeof(RouteRecord)); // Allocate an array based on file size.
    for (int i = 0; i < records; i++) // For loop to initialize each array of 6 integers for struct object
    {
        for (int j = 0; j < 6; j++)
        {
            RouteRecords[i].passengers[j] = 0;
        }
    }
    rewind(fileIn); // Rewinds the file pointer.
    return RouteRecords; // Returns the array.
}



int fillRecords(RouteRecord* r, FILE* fileIn)
{
    char line[1000];
    char *sp;
    
    int month;
    char origin[4];
    char destination[4];
    char airline[4];
    char flightType[20];
    int passengers;
    
    int length = 0;
    int index = 0;
    int flightIndex = 0;
    
    while(fgets(line, 1000, fileIn) != NULL)
    {
        // Parses through the CSV file
        if (line[0] == 'M') continue; // Skips header line.
        sp = strtok(line, ",");
        month = atoi(sp);
        sp = strtok(NULL, ",");
        strcpy(origin, sp);
        sp = strtok(NULL, ",");
        strcpy(destination, sp);
        sp = strtok(NULL, ",");
        strcpy(airline, sp);
        sp = strtok(NULL, ",");
        strcpy(flightType, sp);
        sp = strtok(NULL, ",");
        passengers = atoi(sp);

        // Checks to see if the route has already been added to array
        flightIndex = findAirlineRoute(r, length, origin, destination, airline, index);
        
        if (flightIndex == -1) // If route was not found, add it to the array.
        {
            strcpy(r[length].origin, origin);
            strcpy(r[length].destination, destination);
            strcpy(r[length].airline, airline);
            r[length].passengers[month - 1] = passengers;
            length++;
        }
        else // If route was found already, add the passenger count for that month.
        {
           r[flightIndex].passengers[month - 1] = passengers;
        }
      
    }
    
    return length; // Returns unique records
    
}

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx)
{
    // 2 Base cases
    if(curIdx == length) return -1; // If the array does not include the route
    if (strcmp (r[curIdx].origin, origin) == 0 && strcmp (r[curIdx].destination, destination) == 0 && strcmp (r[curIdx].airline, airline) == 0)
    {
        return curIdx; // If the array includes the route
    }
    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1); // Call until base case
}

void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st )
{
    // Variables
    int count = 0;
    int total = 0;
    int average = 0;
    int savedPassengers[6] = { 0, 0, 0, 0, 0, 0 };
    
    // Traverses through the array to compare against user input
    for (int i = 0; i < length; i++)
    {
        if (st == ORIGIN)
        {
                if (strcmp(r[i].origin, key1) == 0)
                {
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    
                    for(int j = 0; j < 6; j++){
                        savedPassengers[j] += r[i].passengers[j];
                    }
                    count++;
                }
                
            }
            
            
        else if (st == DESTINATION)
        {
                if (strcmp(r[i].destination, key1) == 0)
                {
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    
                    for(int j = 0; j < 6; j++)
                    {
                        savedPassengers[j] += r[i].passengers[j];
                    }
                    count++;
                }
        }  
                
        else if (st == AIRLINE)
        {
                if (strcmp(r[i].airline, key1) == 0)
                {
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    
                    for(int j = 0; j < 6; j++)
                    {
                        savedPassengers[j] += r[i].passengers[j];
                    }
                    count++;
                }        
        }
        
        
        else if (st == ROUTE)
            {
                if (strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0)
                {
                    printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
                    
                    for(int j = 0; j < 6; j++)
                    {
                        savedPassengers[j] += r[i].passengers[j];
                    }
                    count++;
                }
            }
    }
    
    // Adds up the total passengers and gets the average
    for (int z = 0; z < 6; z++)
    {
        total += savedPassengers[z];
    }
    average = total / 6;
    
    // Prints out the statistics
    printf("\n%d matches were found.\n", count);
    printf("\n\nStatistics");
    printf("\nTotal Passengers: %d\n", total);
    printf("Total Passangers in Month 1: %d\n", savedPassengers[0]);
    printf("Total Passangers in Month 2: %d\n", savedPassengers[1]);
    printf("Total Passangers in Month 3: %d\n", savedPassengers[2]);
    printf("Total Passangers in Month 4: %d\n", savedPassengers[3]);
    printf("Total Passangers in Month 5: %d\n", savedPassengers[4]);
    printf("Total Passangers in Month 6: %d\n", savedPassengers[5]);
    printf("\nAverage Passengers per Month: %d \n", average);
}

void printMenu()
{
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
    printf( "1. Search by Route\n" );
    printf( "2. Search by Origin Airport\n" );
    printf( "3. Search by Destination Airport\n" );
    printf( "4. Search by Airline\n" );
    printf( "5. Quit\n" );
    printf( "Enter your selection: " );
}



