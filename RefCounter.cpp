#include "RefCounter.h"

RefCounter::RefCounter() { count = 0; }

int RefCounter::iAdd() { return (++count); }
int RefCounter::iDec() { return (--count); }
int RefCounter::iGet() { return (count); }