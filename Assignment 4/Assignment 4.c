#include "Assignment 2.h"

typedef struct{
        unsigned char Operation_Select: 4;
        unsigned char Operation_Start : 1;
        unsigned char Operation_Counter: 4;
        unsigned char OperandA : 1;
        unsigned char OperandB : 1;
        unsigned char dot_in : 1;
        unsigned char OperandA_Counter: 6;
        unsigned char OperandB_Counter: 6;
} Selector;

double Operation_Doer(double operandA, double operandB, char operation){
    switch (operation){
        case 0:
            return operandA + operandB;
        case 1:
            return operandA - operandB;
        case 2:
            return operandA * operandB;
        case 3:
            return operandA / operandB;
        case 4:
            return (long)operandA & (long)operandB;
        case 5:
            return (long)operandA | (long)operandB;
        case 6:
            return ((~(long)operandA) & (long)operandB) | ((long)operandA & (~(long)operandB));
        case 7:
            return (long)operandA % (long)operandB;
        case 8:
            return ~((long)operandA);
        case 9:
            return (operandA + 1);
        case 10:
            return (operandA - 1);
    }
}

void Calculator(void){
    char *operations[12] = {"Add",  "Subtract", "Multiply", "Divide", "And", "Or", "Xor", "Remainder", "Not", "Increment", "Decrement", "Q"};
    Selector select;
    select.OperandB = select.OperandA = select.Operation_Select
                    = select.Operation_Counter = select.Operation_Start
                    = select.dot_in = select.OperandB_Counter = select.OperandA_Counter = 0;
    unsigned char dot_counter = 1;
    char operation[10] = {0}, c;
    double operandA = 0, operandB = 0;
    void cleaner(void){
        for(int i = 0; i < select.Operation_Counter; operation[i] = '\0', i++);
        select.Operation_Counter = 0;
    }
    printf("Please enter Operation: ");
    while((c = getchar()) != EOF){
        if (c == '\n'){
            if (!select.Operation_Start){
                for(int i = 0; i < 12; i++){
                    if (!strcmp(operations[i], operation)) {
                        select.Operation_Select = i;
                        select.Operation_Start = 1;
                        cleaner();
                    }
                }
                if (!select.Operation_Start){
                    cleaner();
                    printf("Please enter Operation: ");
                }else{
                    if (select.Operation_Select == 11){exit(0);}
                    printf("Please enter Operand A: ");
                }
            }else if (!select.OperandA_Counter){
                printf("Please enter Operand A: ");
            }else if (select.OperandA_Counter && !select.OperandA) {
                if (select.Operation_Select >= 8) {
                    printf("The Result Of Operation: %lf", Operation_Doer(operandA, 0, select.Operation_Select));
                    return;
                }
                operandA /= dot_counter;
                dot_counter = 1;
                select.OperandA = 1;
                select.dot_in = 0;
                printf("Please enter Operand B: ");
            }else if(select.OperandB_Counter){
                operandB /= dot_counter;
                printf("The Result Of Operation: %f", Operation_Doer(operandA, operandB, select.Operation_Select));
                return;
            }
        }
        else if (!select.Operation_Start && select.Operation_Counter < 16){
            operation[select.Operation_Counter++] = c;
        }else if(c == '.'){
            select.dot_in = 1;
        }else if(!select.OperandA && isdigit(c)){
            if (select.dot_in){dot_counter *= 10;}
            operandA = operandA * 10 + (c - '0');
            select.OperandA_Counter += 1;
        }else if(!select.OperandB && isdigit(c)){
            if (select.dot_in){dot_counter *= 10;}
            operandB = operandB * 10 + (c - '0');
            select.OperandB_Counter += 1;
        }else if(c == 8){
            if (select.OperandB_Counter)
                select.OperandB_Counter -= 1;
            else if(select.OperandA_Counter)
                select.OperandA_Counter -= 1;
            else
                select.Operation_Counter -= 1;
        }
    }
}
