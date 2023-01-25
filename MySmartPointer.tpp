template <typename T>
MySmartPointer<T>::MySmartPointer(T* pcPointer) {
	pointer = pcPointer;
	counter = new RefCounter();
	counter->iAdd();
}

template <typename T>
MySmartPointer<T>::MySmartPointer(const MySmartPointer& other)
{
	copy(other);
}

template <typename T>
MySmartPointer<T>::MySmartPointer(MySmartPointer&& other) noexcept{
	copy(other);

	other.pointer = nullptr;
	other.counter = nullptr;
	counter->iDec();
}

template <typename T>
MySmartPointer<T>::~MySmartPointer()
{
	deleteFields();
}

template <typename T>
T& MySmartPointer<T>::operator*() {
	return (*pointer);
}

template <typename T>
T* MySmartPointer<T>::operator->() {
	return (pointer);
}

//operator=
template <typename T>
MySmartPointer<T>& MySmartPointer<T>::operator=(const MySmartPointer& other) {
	if (this == &other)
		return (*this);

	deleteFields();
	copy(other);
	return (*this);
}

template <typename T>
MySmartPointer<T>& MySmartPointer<T>::operator=(MySmartPointer&& other) noexcept
{
	if (this == &other)
		return (*this);

	deleteFields();
	copy(other);

	other.pointer = nullptr;
	other.counter = nullptr;
	counter->iDec();

	return (*this);
}


//private methods
template <typename T>
void MySmartPointer<T>::deleteFields() {

	if (counter != nullptr) {
		if (counter->iDec() == 0) {
			if (pointer != nullptr)
				delete pointer;

			delete counter;
		}
	}
}

template <typename T>
void MySmartPointer<T>::copy(const MySmartPointer& other) {
	pointer = other.pointer;
	counter = other.counter;
	counter->iAdd();
}