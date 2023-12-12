
#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) 
{
    char *inputCopy = strdup(input);
    
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    free(inputCopy);
}


int Number_of_records(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open this File");
        return 0; 
    }

    char buffer[100];
    int counter = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        counter += 1;
    }
    fclose(file);

    return counter;
}

int Mean_step_count(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open this File");
        return 0; 
    }

    char buffer[100];
    int sentence_count = 0;
    int sum = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        char date[11];
        char time[6];
        char steps[1000];

        tokeniseRecord(buffer, ",", date, time, steps);
        sum += atoi(steps);
        sentence_count++;
    }

    fclose(file);

    int mean;
    if (sentence_count > 0)
    {
        mean = sum / sentence_count;
    }
    else
    {
        mean = 0;
    }
    return mean;
}

int Largest_step_counter(char *filename, FITNESS_DATA *largest_data)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open this File");
        return -1; 
    }

    char buffer[100];
    int sentence_count = 0;
    int sentences_max = 100; 
    FITNESS_DATA sentences[100]; 

    while (fgets(buffer, sizeof(buffer), file))
    {
        char date[11];
        char time[6];
        char steps[1000];

        tokeniseRecord(buffer, ",", date, time, steps);

        if (sentence_count < sentences_max)
        {
            sentences[sentence_count].steps = atoi(steps);
            strcpy(sentences[sentence_count].date, date);
            strcpy(sentences[sentence_count].time, time);
            sentence_count++;
        }
    }

    fclose(file); 

    int x = -1; 
    int index_x = -1;

    for (int i = 0; i < sentence_count; i++)
    {
        if (sentences[i].steps > x)
        {
            x = sentences[i].steps;
            index_x = i;
        }
    }

    if (index_x != -1) {
        *largest_data = sentences[index_x];
    }

    return x;
}

int Smallest_Steps(char *filename, FITNESS_DATA *smallest_data)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open this File");
        return -1; 
    }

    char buffer[100];
    int sentence_count = 0;
    int sentences_max = 100; 
    FITNESS_DATA sentences[100]; 

    while (fgets(buffer, sizeof(buffer), file))
    {
        char date[11];
        char time[6];
        char steps[1000];

        tokeniseRecord(buffer, ",", date, time, steps);

        if (sentence_count < sentences_max)
        {
            sentences[sentence_count].steps = atoi(steps);
            strcpy(sentences[sentence_count].date, date);
            strcpy(sentences[sentence_count].time, time);
            sentence_count++;
        }
    }

    fclose(file); 

    int x = 10000; 
    int index_x = -1;

    for (int i = 0; i < sentence_count; i++)
    {
        if (sentences[i].steps < x)
        {
            x = sentences[i].steps;
            index_x = i;
        }
    }

    if (index_x != -1) {
        *smallest_data = sentences[index_x];
    }

    return x;
}

void findLongestPeriod(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open this file");
        return;
    }

    FITNESS_DATA data[100];
    char buffer[100];

    int dataSize = 0;
    while (fgets(buffer, 100, file) != NULL && dataSize < 100) {
        char date[11], time[6], steps[10];
        tokeniseRecord(buffer, ",", date, time, steps);
        strcpy(data[dataSize].date, date);
        strcpy(data[dataSize].time, time);
        data[dataSize].steps = atoi(steps);
        dataSize++;
    }

    fclose(file);

    if (dataSize > 0) {
        int longestPeriod = 0;
        int currentPeriod = 0;
        int startIndex = 0;
        int endIndex = 0;
        
        for (int i = 0; i < dataSize; ++i) {
            if (data[i].steps > 500) {
                currentPeriod++;
                if (currentPeriod > longestPeriod) {
                    longestPeriod = currentPeriod;
                    startIndex = i - currentPeriod + 1;
                    endIndex = i;
                }
            } else {
                currentPeriod = 0;
            }
        }
        
        if (longestPeriod > 0) {
            printf("Longest period start: %s %s\n", data[startIndex].date, data[startIndex].time);
            printf("Longests period end : %s %s\n", data[endIndex].date, data[endIndex].time);
        } else {
            printf("No continuous period with steps > 500 found.\n");
        }
    } else {
        printf("No data found in the file.\n");
    }
}



#endif // FITNESS_DATA_STRUCT_H