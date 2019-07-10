#include "assignment 3.c"

int main() {
    int numbers[10], stp_index = 0;
    stp_index = ScanFunction(numbers, 10);
    int max_number = Maximium(numbers, stp_index);
    int min_number = Minimium(numbers, stp_index);
    printf("Max: %d, Min: %d", max_number, min_number);
    getchar();
    return 0;
}
