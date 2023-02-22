#include "client.h"

int main()
{
    client c;
    DerivedA a;
    a.add(5,2);
    a.getSum();
    DerivedB b;
    b.add(3,6);
    b.getSum();

    return 0;
}