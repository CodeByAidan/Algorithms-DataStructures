1.1 Write a class *charstring* for string manipulations, based on reference counting to avoid duplication of identical strings. Your class should at least provide the facilities required to run the following application program:

```c++
// Application, to be linked with charstring.cpp.
#include "charstring.h"

int main()
{  charstring s = "Smith ", t = s, u = t + s;
   s = t + "Johnson " + u;
   cout << t << endl << u << endl << s << endl;
   return 0;
}
```

Immediately after the above initalization of *t*, the variables *s* and *t* should refer to the same memory area containing the string "*Smith*". This program should produce the following output:

```
Smith
Smith Smith
Smith Johnson Smith Smith
```