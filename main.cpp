#include "Termio.h"
#include "Cell.h"

int main()
{
    Cell test;
    test.spawn();
    test.print();
    test.next();
    test.print();
    test.kill();
    test.print();
    test.next();
    test.print();
}