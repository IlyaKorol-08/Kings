#include "LinkedList.h"
#include <assert.h>

#define Add_To_Start_test_SUCCESS 0
#define Add_To_End_test_SUCCESS 0
#define Add_To_Pos_test_SUCCESS 0
#define Del_By_Pos_test_SUCCESS 0
#define Del_By_Val_test_SUCCESS 0

int Add_To_Start_test() {
  Clear_List();

  Add_To_Start(24);
  assert(F_Count() == 1);
  assert(Find_By_Pos(1) == 24); // 24

  Add_To_Start(312); // 312, 24
  assert(F_Count() == 2);
  assert(Find_By_Pos(1) == 312);
  assert(Find_By_Pos(2) == 24);

  Add_To_Start(42); // 42, 312, 24
  assert(F_Count() == 3);
  assert(Find_By_Pos(1) == 42);
  assert(Find_By_Pos(2) == 312);
  assert(Find_By_Pos(3) == 24);
  return Add_To_Start_test_SUCCESS;
}
int Add_To_End_test() {
  Clear_List();
  Add_To_Start(24);
  Add_To_Start(312);
  Add_To_Start(42); // 42, 312, 24

  Add_To_End(51); // 42, 312, 24, 51
  assert(F_Count() == 4);
  assert(Find_By_Pos(4) == 51);
  assert(Find_By_Pos(3) == 24);

  Add_To_End(95); // 42, 312, 24, 51, 95
  assert(F_Count() == 5);
  assert(Find_By_Pos(5) == 95);
  assert(Find_By_Pos(4) == 51);

  Add_To_End(1245); // 42, 312, 24, 51, 95, 1245
  assert(F_Count() == 6);
  assert(Find_By_Pos(6) == 1245);
  assert(Find_By_Pos(5) == 95);
  return Add_To_End_test_SUCCESS;
}

int Add_To_Pos_test() {
  Clear_List();

  Add_To_Start(24);
  Add_To_Start(312);
  Add_To_Start(42);
  Add_To_End(51);
  Add_To_End(95);
  Add_To_End(1245); // 42, 312, 24, 51, 95, 1245

  Add_To_Pos(1, 783); // 783, 42, 312, 24, 51, 95, 1245
  assert(Find_By_Pos(1) == 783);
  assert(Find_By_Pos(2) == 42);
  assert(F_Count() == 7);

  Add_To_Pos(5, 294); // 783, 42, 312, 24, 294, 51, 95, 1245
  assert(Find_By_Pos(5) == 294);
  assert(Find_By_Pos(6) == 51);
  assert(F_Count() == 8);

  Add_To_Pos(
      100, 132); // игнорируем, если пытаемся добавить в слишком большую позицию
  assert(F_Count() == 8);
  return Add_To_Pos_test_SUCCESS;
}

int Del_By_Pos_test() {
  Clear_List();

  Add_To_End(10);
  Add_To_End(20);
  Add_To_End(30);
  Add_To_End(40);
  Add_To_End(50); // 10, 20, 30, 40, 50

  Del_By_Pos(3); // 10, 20, 40, 50
  assert(F_Count() == 4);
  assert(Find_By_Pos(1) == 10);
  assert(Find_By_Pos(2) == 20);
  assert(Find_By_Pos(3) == 40);
  assert(Find_By_Pos(4) == 50);

  Del_By_Pos(1); // 20, 40, 50
  assert(F_Count() == 3);
  assert(Find_By_Pos(1) == 20);
  assert(Find_By_Pos(2) == 40);
  assert(Find_By_Pos(3) == 50);

  Del_By_Pos(3); // 20, 40
  assert(F_Count() == 2);
  assert(Find_By_Pos(1) == 20);
  assert(Find_By_Pos(2) == 40);
  return Del_By_Pos_test_SUCCESS;
}

int Del_By_Val_test() {
  Clear_List();

  Add_To_End(10);
  Add_To_End(20);
  Add_To_End(30);
  Add_To_End(20);
  Add_To_End(40); // 10, 20, 30, 20, 40

  Del_By_Val(20); // 10, 30, 20, 40
  assert(F_Count() == 4);
  assert(Find_By_Pos(1) == 10);
  assert(Find_By_Pos(2) == 30);
  assert(Find_By_Pos(3) == 20);
  assert(Find_By_Pos(4) == 40);

  Del_By_Val(10); // 30, 20, 40
  assert(F_Count() == 3);
  assert(Find_By_Pos(1) == 30);
  assert(Find_By_Pos(2) == 20);
  assert(Find_By_Pos(3) == 40);

  Del_By_Val(40); // 30, 20
  assert(F_Count() == 2);
  assert(Find_By_Pos(1) == 30);
  assert(Find_By_Pos(2) == 20);

  Del_By_Val(999); //  Попытка удалить несуществующее
  assert(F_Count() == 2);
  return Del_By_Val_test_SUCCESS;
}
int main() {
  Add_To_Start_test();
  Add_To_End_test();
  Add_To_Pos_test();
  Del_By_Pos_test();
  Del_By_Val_test();
  return 0;
}
