/*
Josh Caney
10/22/2020 10:45 PM
This program performs various actions including math operations
and assignment operators involving arrays.
Input: myArray objects, indices, and values.
Output: various outputs including booleans, streams, and arrays
*/
#include "myArray.h"

myArray::myArray()
{
	size = 0; 
	arr = new float[size];
}
 
myArray::myArray(int _size, float _num)
{
	size = _size; 
	arr = new float[_size]; 
	for(int i = 0; i < size; i++)
	{
		arr[i] = _num;
	}
}
myArray::myArray(float* _arr, int _size)
{
	size = _size; 
	arr = new float[_size]; 
	for(int i = 0; i < size; i++)
	{
		arr[i] = _arr[i];
	}
}
myArray::myArray(const myArray& obj2) //copy constructor
{
      size = obj2.size; 
      arr = new float[size]; 
      for(int i = 0; i < size; i++) 
      {
           arr[i] = obj2.arr[i]; 
      }
}
myArray::~myArray()
{
	delete [] arr;
}
		
void myArray::insert(int _index,float _num)
{
	float *temp; 
	temp = arr;
	arr= new float[size+1];
	for(int i = 0; i < _index; i++) 
	{
		arr[i] = temp[i]; 
	}
	arr[_index] = _num; 
	for(int i = _index+1; i < size+1; i++) 
	{
		arr[i] = temp[i-1]; 
	}
	size = size +1;
	delete [] temp;
}
void myArray::remove(int _index)
{
	float *temp; 
	temp = arr; 
	arr = new float[size-1]; 
	for(int i = 0; i < size-1; i++) 
	{
		if(i != _index && i < _index)
		{
			arr[i] = temp[i]; 
		}
		else
		{
			arr[i] = temp[i+1]; 
		}
	}
	delete [] temp;
	size = size -1;
}

float myArray::get(int _index)
{
	if(_index >=0 && _index < size)
	{
		return arr[_index];
	}
	cout << "Error, index out of bounds" << endl;
	return -1;
}

void myArray::clear()
{
	delete [] arr;
	arr = new float[0];
	size = 0;
} 

int myArray::find(float _num)
{
	int ret = -1; 
	for(int i = 0; i < size; i++)
	{
		if(arr[i] == _num) 
		{
			ret = i; 
			break;
		}
	}
	return ret;
}

bool myArray::equals(myArray& obj2)
{
	bool ret = true; 
	for(int i = 0; i < size; i++)
	{
		if(arr[i] != obj2.arr[i]) 
		{
			ret = false; 
			break;
		}
	}
	return ret;
}
 
void myArray::init()
{
	cout << "Enter " << size << " elements." << endl; 
	for(int i = 0; i < size; i++)
	{
		cin >> arr[i]; 
	}
} 

void myArray::print()
{
	for(int i = 0; i < size; i++)
	{
		cout << arr[i] << " "; 
	}
	cout << endl; 
}

bool myArray::operator!=(myArray& obj2) //operator overload for not equal
{
    if (&obj2 == this) //if the calling object and parameter are equal, return false
    {
        return false;
    }
    else //if not equal
    {
	return true;
    }
}

float myArray::operator[](int index) //returning index
{
	//return get(index);
	if(index >= size || index < 0) //make sure index is within array
	{
	  cout << "Index out of bounds" << endl;
	  return -1;
	}	
	else
	{
	  return get(index);
	}
}

void myArray::operator()(int index, float num) //change value of array at index
{
	if(index >= size || index < 0)
	{
	   cout << "Index out of bounds" << endl;
	   return;
	}
	arr[index] = num; //sets arr[index] equal to the number that was passed in
}
 
myArray& myArray::operator=(myArray obj2) //sets arr equal to other array
{
	delete [] arr; //clears arr
	size = obj2.size; //sets local variable 
	arr = new float[size]; //creates array of equal size
	for(int i=0; i<size; i++)
	{
		arr[i] = obj2[i]; //loop thru the size, setting arr = obj2;
	}
	return *this;
}

myArray myArray::operator+(myArray& obj2) //add the two arrays by index
{
	int n = obj2.size; //local variable
	for (int i=0; i<n; i++)
	{
		arr[i] = arr[i] + obj2[i]; 
	}
	return *this;
}

void myArray::operator+=(myArray& obj2) //change arr to arr plus obj2 at each index
{
	int thisSize = size; //local variable for arr size
	int newSize = thisSize + obj2.size; //size of the final array
	float temp [newSize] = {0}; //temporary array to save values before passing back to arr
	for(int i=0; i<newSize; i++) //looping thru final size
	{
		if(i<thisSize) //for the first part of the array
		{
			temp[i] = arr[i]; //set equal at each index to arr[i]
		}
		else //when done with the first array
		{
		  temp [i] = obj2[i-thisSize]; //i-thisSize to start at index 0 and work up.
		}
	}
	delete [] arr; //clear arr to reassign
    size = newSize; // have to reset size for whole array to print, due to print method relying on size for a loop.
	arr = new float [newSize]; //resizing
	for (int i=0; i<newSize; i++) //set arr equal to temp to pass back
	{
	   arr[i] = temp[i];
	}
}

istream& operator>>(istream& in, myArray& rhs) //fills array based on user input
{
	int n = rhs.size; //allow user to input numbers up to the array size
	cout << "Enter " << n << " floats." << endl;
	for(int i=0; i<n; i++)
	{
		in >> rhs.arr[i]; //input each float as a new index
	}
	return in;
}

ostream& operator<<(ostream& out, myArray& rhs)
{
	if (rhs.size == 0) //make sure there is an array to output
	{
		cout << "NULL" << endl;
	}
	else
	{
		for(int i=0; i<rhs.size; i++)
		{
			out << rhs.arr[i] << " "; //print array one index at time.
		}
	}
	return out;
}
