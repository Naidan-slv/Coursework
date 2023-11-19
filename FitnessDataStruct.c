#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255
#define MAX_SENTENCES 500

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

    char buffer[BUFFER_SIZE];
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

    char buffer[BUFFER_SIZE];
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

    char buffer[BUFFER_SIZE];
    int sentence_count = 0;
    int sentences_max = MAX_SENTENCES; 
    FITNESS_DATA sentences[MAX_SENTENCES]; 

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

    char buffer[BUFFER_SIZE];
    int sentence_count = 0;
    int sentences_max = MAX_SENTENCES; 
    FITNESS_DATA sentences[MAX_SENTENCES]; 

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

    int x = 1000000; 
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

int Longest_Above_500_Steps(char *filename, FITNESS_DATA *longest_data)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open this File");
        return -1; 
    }

    char buffer[BUFFER_SIZE];
    int sentence_count = 0;
    int sentences_max = MAX_SENTENCES; 
    FITNESS_DATA sentences[MAX_SENTENCES]; 
    int longest_duration = 0;
    int current_duration = 0;
    int start_index = -1;
    int end_index = -1;

    while (fgets(buffer, sizeof(buffer), file))
    {
        char date[11];
        char time[6];
        char steps[1000];

        tokeniseRecord(buffer, ",", date, time, steps);

        int current_steps = atoi(steps);

        if (current_steps > 500)
        {
            if (start_index == -1)
            {
                start_index = sentence_count;
            }

            current_duration++;
        }
        else
        {
            if (current_duration > longest_duration)
            {
                longest_duration = current_duration;
                end_index = sentence_count - 1;
            }

            current_duration = 0;
            start_index = -1;
        }

        if (sentence_count < sentences_max)
        {
            sentences[sentence_count].steps = current_steps;
            strcpy(sentences[sentence_count].date, date);
            strcpy(sentences[sentence_count].time, time);
            sentence_count++;
        }
    }

    fclose(file); 

    // Check if the last period was the longest
    if (current_duration > longest_duration)
    {
        end_index = sentence_count - 1;
    }

    if (start_index != -1 && end_index != -1)
    {
        int longest_steps = 0;

        for (int i = start_index; i <= end_index; i++)
        {
            if (sentences[i].steps > longest_steps)
            {
                longest_steps = sentences[i].steps;
            }
        }

        *longest_data = sentences[end_index];
        return longest_steps;
    }
    else
    {
        return -1; 
    }
}