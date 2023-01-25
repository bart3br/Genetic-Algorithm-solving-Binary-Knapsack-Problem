#pragma once
class RefCounter
{
public:
	RefCounter();
	int iAdd();
	int iDec();
	int iGet();

private:
	int count;
};

