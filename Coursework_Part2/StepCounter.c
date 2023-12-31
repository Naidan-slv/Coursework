#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"



// Global variables
char filename[200]; // Moved filename to a global variable

int main()
{
    char choice;
    char filename[200];
    int counter;

    do
    {
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");
        printf("\n");
        printf("Please enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'A':
            printf("Please enter a file name: ");
            scanf("%s", filename);

            size_t len = strlen(filename);
            if (len >= 4 && strcmp(filename + len - 4, ".csv") == 0) {
                printf("File successfully loaded.\n");
            } else {
                printf("Error: Could not find or open the file.\n");
                return 1;
            }
            break;
        case 'B':
            printf("The number of records is: %d\n", Number_of_records(filename));
            counter = Number_of_records(filename);
            break;
        case 'C':
            {
                FITNESS_DATA smallest_data;
                int smallestSteps = Smallest_Steps(filename, &smallest_data);
                printf("Fewest Steps: %s %s\n", smallest_data.date, smallest_data.time);
            }
            break;
        case 'D':
            {
                FITNESS_DATA largest_data;
                int largestSteps = Largest_step_counter(filename, &largest_data);
                printf("Largest Steps: %d\n", largestSteps);
                printf("Largest Steps: %s %s\n", largest_data.date, largest_data.time);
            }
            break;
        case 'E':
            printf("The mean is: %d steps\n", Mean_step_count(filename));
            break;
        case 'F':
            findLongestPeriod(filename);
            break;
        case 'Q':
            printf("Quitting the program.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 'Q');

    return 0;
}