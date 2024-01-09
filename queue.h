#pragma once
#include<iostream>
using namespace std;
template<typename T>
class DynamicQueue {
private:
	int size;
	int capacity;
	T* arr;
	int Fi, Ri;
	int Pre_Ri;
public:
	DynamicQueue(int cap = 5)
	{
		capacity = cap;
		size = 0;
		arr = new T[capacity];
		Fi = 0, Ri = size;
	}

	T operator[](int index)
	{
		if (index >= 0 && index < size)
		{
			return arr[(Fi + index) % capacity];
		}
		//return T();
		throw std::out_of_range("Index out of bounds or empty queue");
	}

	bool isFull()
	{
		if (size == capacity)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int getsize()
	{
		return size;
	}
	void Push(T val)
	{
		/*if (isFull())
		{
			T* newArr = new T[capacity * 2];
			for (int i = 0, c = Fi; i < size; i++, c++)
			{
				if (c == capacity)
				{
					c = 0;
				}
				newArr[i] = arr[c];
			}
			delete[] arr;
			arr = newArr;
			capacity = capacity * 2;
			Fi = 0;
			size++;
			Ri = size;
		}
		arr[Ri] = val;
		Pre_Ri = Ri;
		size++;
		Ri = size;*/

		if (isFull()) 
		{
			T* newArr = new T[capacity * 2];
			for (int i = 0, c = Fi; i < size; i++, c++) 
			{
				if (c == capacity) 
				{
					c = 0;
				}
				newArr[i] = arr[c];
			}
			delete[] arr;
			arr = newArr;
			capacity = capacity * 2;
			Fi = 0;
			Ri = size - 1;  // Set Ri to the last valid index
		}

		arr[Ri] = val;
		Pre_Ri = Ri;
		size++;
		Ri = size - 1;  // Set Ri to the last valid index


	}

	bool isEmpty()
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Pop()
	{
		if (isEmpty())
		{
			cout << "Queue is Empty";
		}
		else
		{
			Fi = (Fi + 1) % capacity;
			size--;
		}
	}

	void PrintQueue()
	{
		for (int i = Fi; i < Ri; i++)
		{
			cout << arr[i] << endl;
		}
	}

	T getFrontIndex()
	{
		return arr[Fi];
	}

	T returnRear()
	{
		return arr[Pre_Ri];
	}
};
