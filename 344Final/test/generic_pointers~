 // Generic Pointers

 #include <iostream>
 #include <iomanip>
 using namespace std;

 void q(void *a, void *b, int n) {

     unsigned char *ca = (unsigned char *)a;
     unsigned char *cb = (unsigned char *)b;
     unsigned char c;

     for (int i = 0; i < n; i++) {
         c     = ca[i];
         ca[i] = cb[i];
         cb[i] = c;
     }
 }

 int main() {

     int a = 4, b = 7;
     float x = 2.5f, y = 3.5f;

     q(&a, &b, sizeof(int));
     q(&x, &y, sizeof(float));

     cout << setprecision(1) << fixed;
     cout << "(a,b) = (" << a << ',' << b << ')' << endl;
     cout << "(x,y) = (" << x << ',' << y << ')' << endl; 
 }
