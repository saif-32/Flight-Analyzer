#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "route-records.h"

int main(int argc, char *argv[])
{
    // Variables
    int unique = 0;
    int contloop = 1;
    int user_input;
    FILE* FileIn = NULL;

    if (argc != 2) // Checks to see if command line arguments are present
    {
        printf("ERROR: Missing file name.");
        return 1;

    }

    printf("Opening %s...\n", argv[1]);
    FileIn = fopen(argv[1], "r"); // Attempts to open the file

    if (FileIn == NULL) // If file cannot be opened
    {
        printf("ERROR: Could not open file");
        return 1;
    }

    RouteRecord *r; // Creates struct object
    r = createRecords(FileIn); // Calls function to return array
    unique = fillRecords(r, FileIn); // Calls function to fill records, variable represents unique records
    fclose(FileIn); // Closes the file

    printf("Unique routers operated by airlines: %d\n", unique); // Prints out unique records
    
    // Infinite loop until user exits
    while(contloop == 1)
    {
        // User variables
        printMenu();
        char user_origin[4];
        char user_destination[4];
        char user_airline[3];
        int check_input = 0;

        check_input = scanf("%d", &user_input); // Asks user for input

        // Checks for invalid inputs
        while (check_input != 1)
        {
            printf("Invalid input.\n");
            scanf("%*[^\n]");
            printMenu();
            check_input = scanf("%d", &user_input);
        }

        // Switch case to handle all menu options
        switch(user_input)
        {
            case 1: 
                printf("Enter origin: ");
                scanf("%s", user_origin);
                printf("Enter destination: ");
                scanf("%s", user_destination);
                printf("\nSearching by route...\n");
                searchRecords(r, unique, user_origin, user_destination, ROUTE);
                break;
            case 2:
                printf("Enter origin: ");
                scanf("%s", user_origin);
                printf("\nSearching by origin...\n");
                searchRecords(r, unique, user_origin, user_destination, ORIGIN);
                break;
            case 3:
                printf("Enter destination: ");
                scanf("%s", user_destination);
                printf("\nSearching by destination...\n");
                searchRecords(r, unique, user_destination, user_origin, DESTINATION);
                break;
            case 4:
                printf("Enter airline: ");
                scanf("%s", user_airline);
                printf("\nSearching by airline...\n");
                searchRecords(r, unique, user_airline, user_destination, AIRLINE);
                break;
            case 5:
                printf("Good-bye! ");
                free(r);
                contloop = 0;
                break;
            default:
                printf("Invalid choice.");
                break;
        }
            
    }


    return 0;
}
