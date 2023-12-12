#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

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

int main()
{
    char filename[200];

    printf("Please enter a file name: ");
    scanf("%s", filename);

    size_t len = strlen(filename);
    if (len >= 4 && strcmp(filename + len - 4, ".csv") == 0) {
        printf("File successfully loaded.\n");
    } else {
        printf("Error: Could not find or open the file.\n");
        return 1;
    }

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
    
    while (fgets(line,sizeof(line),filename))
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