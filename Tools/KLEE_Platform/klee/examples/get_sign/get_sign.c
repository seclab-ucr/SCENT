/*
 * First KLEE tutorial: testing a small function
 */

#include <klee/klee.h>
int get_sign(int x, int y) {
  if (x == -10){
      printf("hello\n");
     return 0;
  }
  
  if (y < 0)
     return -1;
  else 
     return 1;
}
/*
int get_sign(short x){
    if (x== 10)
        return 0;
    return -1;
}
*/
int x, y;
void Model0_Symbolize(){
    int a;
    klee_make_symbolic(&a, sizeof(a), "a");
    x = a;
    int b;
    klee_make_symbolic(&b, sizeof(b), "b");
    y = b;
}
int main() {
/*
  int x, y, a, b;
  klee_make_symbolic(&a, sizeof(a), "a");
  klee_make_symbolic(&b, sizeof(b), "b");
  x = a;
  y = b;
  x = -8;
*/
  Model0_Symbolize();
  x = -10;
  //a = 3;
  //b = a+2;
  //printf("%d\n", a);
  //return get_sign((int)a, 1);
  return get_sign(x, y);
} 
