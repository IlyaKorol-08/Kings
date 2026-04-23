#ifndef STACK_H    
#define STACK_H

#define SIZE(stack) (sizeof(stack) / sizeof((stack)[0]))

void Proverka (int count);
void Add(int Stek[], int *count, int *number_of_elements, int new);
void Delete(int Stek[], int *number_of_elements);

#endif
