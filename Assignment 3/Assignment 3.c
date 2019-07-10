#include "assignment 2.h"

int ScanFunction(int *numbers, int length){
    char c, counter = 0, temp_number_counter = 0;
    int temp_number = 0;
    printf("Enter Number [%d/%d]: ", counter+1, length);
    while((c = getchar()) != EOF && counter < length){
        if (isdigit(c)){
            temp_number = temp_number * 10 + (c - '0');
            temp_number_counter++;
        }else if (c == '\n'){
            if (temp_number_counter){
            numbers[counter++] = temp_number;
            temp_number = 0;
            temp_number_counter = 0;}
            printf("Enter Number [%d/%d]: ", counter+1, length);
        }else{
            continue;
        }
    }
    if (temp_number_counter && counter < length){*(numbers + counter) = temp_number;}
    return counter;
}

int Maximium(const int *numbers, int length){
    int max_number = numbers[0];
    for(int i = 1; i < length; max_number = max_number < numbers[i] ? numbers[i] : max_number, i++);
    return max_number;
}

int Minimium(const int *numbers, int length){
    int max_number = numbers[0];
    for(int i = 1; i < length; max_number = max_number < numbers[i] ? max_number : numbers[i], i++);
    return max_number;
}
