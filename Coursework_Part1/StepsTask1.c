#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() 
{
     char filename [] = "FitnessData_2023.csv";
     FILE *file = fopen(filename, "r");
     if (file == NULL) 
     {
        perror("Error opening file \n");
        return 1;
     }
     
     int sentence_count = 0;
     int sentences_max = 500;
     char line[1000];
     FITNESS_DATA sentences[100];
     
     while (fgets(line,sizeof(line),file))
     {
        char date[11];
	    char time[6];
	    char steps [1000];

        tokeniseRecord(line, ",", date, time, steps);
        
        if (sentence_count < sentences_max)
        {
            sentences[sentence_count].steps = atoi(steps);
            strcpy(sentences[sentence_count].date,date);
            strcpy(sentences[sentence_count].time,time);
            sentence_count = sentence_count + 1;
        }
     }
        printf("Number of records in file: %d\n",sentence_count);
        for (int i = 0; i < 3; i++) {
            printf("%s/%s/%d\n",sentences[i].date, sentences[i].time, sentences[i].steps);
        
     }

    fclose(file);
    return 0;
}

// create a function to all 7 things
// read an input into it
// No need to create a function to read a file in
// Manipulate data which we've been given after storing it into an array
