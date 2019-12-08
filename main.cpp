#include "Termio.h"
#include "Cell.h"

int main()
{
    Term::IO io;
    Cell test;
    io << Term::clear;
    test.spawn();
    test.print();
    test.next();
    test.print();
    test.kill();
    test.print();
    test.next();
    test.print();
    io << Term::Point(0,0);
    test.spawn();
    test.next();
    test.print();
}