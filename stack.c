#include <stdio.h>
#include "stack.h"
void Proverka (int count)
{
    if (count != 0){
        printf("Количество элементов стека: %d\n", count);
    }
    else{
        printf("Стек пуст\n");
    }
}

void Add(int Stek[], int *count, int *number_of_elements, int new) {
    if (*number_of_elements < *count) {
        Stek[*number_of_elements] = new;
        (*number_of_elements)++;
        printf("Элемент добавлен\n");
    }
    else
    {
        printf("Стек заполнен!\n");
    }
}
void Delete(int Stek[], int *number_of_elements){
    if(*number_of_elements > 0){
        Stek[*number_of_elements - 1] = 0;
        (*number_of_elements)--;
         printf("Элемент удален\n");
    }
    else{
        printf("Все элементы удалены\n");
    }
} 
