
#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Helper function prototypes
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);
void ReadFile(char *filename);
int Number_of_records(char *filename);
int Mean_step_count(char *filename);
int Largest_step_counter(char *filename, FITNESS_DATA *largest_data);
int Smallest_Steps(char *filename, FITNESS_DATA *smallest_data);
int Longest_Above_500_Steps(char *filename, FITNESS_DATA *longest_data);



#endif // FITNESS_DATA_STRUCT_H