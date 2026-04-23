#include "LinkedList.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
struct LL {
  int Value;
  struct LL *Next;
};
struct LL *Start = NULL;
void Add_To_Start(int Val) {
  struct LL *newLL = (struct LL *)malloc(sizeof(struct LL));
  newLL->Value = Val;
  newLL->Next = Start;
  Start = newLL;
}
void Add_To_End(int Val) {
  struct LL *newLL = (struct LL *)malloc(sizeof(struct LL));
  newLL->Value = Val;
  newLL->Next = NULL;
  if (Start == NULL) {
    Start = newLL;
    return;
  }
  struct LL *Current = Start;
  while (Current->Next != NULL) {
    Current = Current->Next;
  }
  Current->Next = newLL;
}
void Add_To_Pos(int Pos, int Val) {
  if (Pos < 1) {
    return;
  }
  if (Pos == 1) {
    Add_To_Start(Val);
    return;
  }
  struct LL *newLL = (struct LL *)malloc(sizeof(struct LL));
  newLL->Value = Val;

  struct LL *Current = Start;
  for (int i = 1; i < Pos - 1; i++) {
    if (Current == NULL) {
      free(newLL);
      return;
    }
    Current = Current->Next;
  }
  if (Current == NULL) {
    free(newLL);
    return;
  }
  newLL->Next = Current->Next;
  Current->Next = newLL;
}
void Del_By_Pos(int Pos) {
  if (Start == NULL) {
    return;
  }
  if (Pos < 1) {
    return;
  }
  struct LL *Temp = Start;
  if (Pos == 1) {
    Start = Start->Next;
    free(Temp);
    return;
  }
  struct LL *Current = Start;
  for (int i = 1; i < Pos - 1; i++) {
    if (Current->Next == NULL) {
      return;
    }
    Current = Current->Next;
  }
  if (Current->Next == NULL) {
    return;
  }
  Temp = Current->Next;
  Current->Next = Temp->Next;
  free(Temp);
}
void Del_By_Val(int Val) {
  if (Start == NULL) {
    return;
  }
  struct LL *Current = Start;
  struct LL *Prev = NULL;
  if (Current->Value == Val) {
    Start = Current->Next;
    free(Current);
    return;
  }
  while (Current != NULL && Current->Value != Val) {
    Prev = Current;
    Current = Current->Next;
  }
  if (Current == NULL) {
    return;
  }
  Prev->Next = Current->Next;
  free(Current);
}
int Find_By_Pos(int Pos) {
  if (Start == NULL) {
    return -1;
  }
  if (Pos < 1) {
    return -1;
  }
  struct LL *Current = Start;
  int CurrentPos = 1;
  while (Current != NULL) {
    if (CurrentPos == Pos) {
      return Current->Value;
    }
    Current = Current->Next;
    CurrentPos++;
  }
  return -1;
}
int F_Count() {
  int Count = 0;
  struct LL *Current = Start;
  while (Current != NULL) {
    Count++;
    Current = Current->Next;
  }
  return Count;
}
void Clear_List() {
  while (F_Count() > 0) {
    Del_By_Pos(1);
  }
}
