#include "KGA_MyVector.h"
#include <stdexcept>
KGA_MyVector::KGA_MyVector(size_t count)
	: _container{new int[count]}, _size{count}, _capacity{count}
{
	for (int i = 0; i < _size; i++)
	{
		_container[i] = 0;
	}
}

KGA_MyVector::KGA_MyVector(const KGA_MyVector& other)
{
}

KGA_MyVector& KGA_MyVector::operator=(const KGA_MyVector& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

KGA_MyVector::KGA_MyVector(KGA_MyVector&& other)
{
}

KGA_MyVector& KGA_MyVector::operator=(KGA_MyVector&& other)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

KGA_MyVector::~KGA_MyVector()
{
}

int* KGA_MyVector::begin()
{
	return _container;	// 제일 처음 요소 반환
}

const int* KGA_MyVector::begin() const
{
	return _container;	// 제일 처음 요소 반환
}

int* KGA_MyVector::end()
{
	return _container + _size;  // _container[_size]
}

const int* KGA_MyVector::end() const
{
	return _container + _size;
}

bool KGA_MyVector::empty() const
{
	if (_size == 0)
	{
		return true;
	}
	return false;
}

size_t KGA_MyVector::size() const
{
	return _size;
}

size_t KGA_MyVector::capacity() const
{
	return _capacity;
}

int& KGA_MyVector::at(size_t pos)
{
	if (_size <= pos)
	{
		throw std::out_of_range("범위를 벗어났습니다.");
	}
	return _container[pos];
}

const int& KGA_MyVector::at(size_t pos) const
{
	if (_size <= pos)
	{
		throw std::out_of_range("범위를 벗어났습니다.");
	}
	return _container[pos];
}

int& KGA_MyVector::operator[](size_t pos)
{
	return _container[pos];
}

const int& KGA_MyVector::operator[](size_t pos) const
{
	return _container[pos];
}

int& KGA_MyVector::front()
{
	return _container[0];
	//return *begin();
}

const int& KGA_MyVector::front() const
{
	return _container[0];
}

int& KGA_MyVector::back()
{
	return _container[_size - 1];
}

const int& KGA_MyVector::back() const
{
	return _container[_size - 1];
}

void KGA_MyVector::clear()
{
	delete _container;
	_container = nullptr;
	_capacity = 0;
	_size = 0;
}

int* KGA_MyVector::insert(int* pos, int value)
{
	// 처음과 주소 사이의 거리
	int dist = pos - begin();

	if (_size == 0)
	{
		reserve(1);
		pos = begin() + dist;	// reserve 후 위치 초기화
	}

	if (_size == _capacity)
	{
		reserve(_capacity * 2);
		pos = begin() + dist;
	}

	for (int* iter = end(); iter != pos; --iter)
	{
		*iter = *(iter - 1);
	}
	*pos = value;	// 값 넣어주기
	_size++;
	return pos;
}

int* KGA_MyVector::erase(int* pos)
{
	if (_size == 0)
	{
		return end();
	}
	
	int* last = end() - 1;
	if (pos == last)
	{
		_size--;
		return end();
	}

	for (int* iter = pos; iter != end(); ++iter)
	{
		*iter = *(iter + 1);
	}
	_size--;
	return pos;
}

void KGA_MyVector::push_back(int value)
{
	insert(end(), value);
}

void KGA_MyVector::pop_back()
{
	erase(end() - 1);
}

bool KGA_MyVector::contains(int value)
{
	for (int i = 0; i < _size; i++)
	{
		if (_container[i] == value)
		{
			return true;
		}
	}
	return false;
}

void KGA_MyVector::reserve(size_t newCapacity)
{
	if (_capacity >= newCapacity)
	{
		return;
	}

	int* newContainer = new int[newCapacity];

	for (int i = 0; i < _size; i++)
	{
		newContainer[i] = _container[i];
	}

	delete _container;
	_container = newContainer;
	_capacity = newCapacity;
}
