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
int main() {
  int a, b;
  klee_make_symbolic(&a, sizeof(a), "a");
  klee_make_symbolic(&b, sizeof(b), "b");
  a = -10;
  //a = 3;
  //b = a+2;
  //printf("%d\n", a);
  //return get_sign((int)a, 1);
  return get_sign(a, b);
} 
