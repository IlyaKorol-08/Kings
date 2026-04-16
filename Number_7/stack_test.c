#include <stdio.h>
#include "stack.h"
#include <assert.h>
void Test_1(){
    int Ster1 [10] = {1,2,3,4};
    int number_of_elements = 4;
    int n = SIZE(Ster1);
    Proverka(number_of_elements);
    assert(number_of_elements == 4);

    Add(Ster1,&n,&number_of_elements,10);
    assert(Ster1[4] == 10);      
    assert(number_of_elements == 5);  

    Delete(Ster1,&number_of_elements);
    assert(Ster1[4] == 0);
    assert(number_of_elements == 4); 
}
void Test_2() {
    int Ster2 [3] = {0};
    int number_of_elements = 0;
    int n = SIZE(Ster2);
    Proverka(number_of_elements);
    assert(number_of_elements == 0);

    Add(Ster2,&n,&number_of_elements,1);
    assert(Ster2[0] == 1);
    assert(number_of_elements == 1);

    Add(Ster2,&n,&number_of_elements,2);
    assert(Ster2[1] == 2);
    assert(number_of_elements == 2);

    Add(Ster2,&n,&number_of_elements,3);
    assert(Ster2[2] == 3);
    assert(number_of_elements == 3);

    Add(Ster2,&n,&number_of_elements,4);
    assert(number_of_elements == 3);

    Delete(Ster2,&number_of_elements);
    assert(Ster2[2] == 0);  
    assert(number_of_elements == 2);
}

int main() {
    Test_1();
    Test_2();
    return 0;
}
