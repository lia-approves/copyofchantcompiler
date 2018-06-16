#include <iostream>
using std::cout;
using std::endl;
int main() {

  int *a; //a = null
  int b; //b=null
  a = &b; //a=0x45
  *a = 1; //(0x45)=1
  int c;
  c = *a;
  cout << c;
  return 0;
}
