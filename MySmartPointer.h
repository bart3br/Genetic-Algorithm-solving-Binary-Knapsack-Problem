#pragma once
#include "RefCounter.h"

template <typename T>
class MySmartPointer
{
public:
	MySmartPointer(T* pcPointer);
	MySmartPointer(const MySmartPointer& other);
	MySmartPointer(MySmartPointer&& other) noexcept;
	~MySmartPointer();

	T& operator*();
	T* operator->();
	MySmartPointer& operator=(const MySmartPointer& other);
	MySmartPointer& operator=(MySmartPointer&& other) noexcept;

private:
	T* pointer;
	RefCounter* counter;

	void deleteFields();
	void copy(const MySmartPointer& other);
};

#include "MySmartPointer.tpp"