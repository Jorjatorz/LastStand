#pragma once

#include <assert.h>

/*
* Base class. It applies the Singleton pattern to subclasses.
*/

template <class T>
class Singleton
{
private:
	Singleton(const Singleton<T> &); 
	Singleton& operator=(const Singleton<T> &);

protected:
	static T* _singleton; //static instance

public:
	Singleton(void) //Default constructor that is in charge of saving just one reference of the class
	{
		assert(!_singleton); //just created once
		_singleton = static_cast<T*>(this); //allocate the singleton
	}

	~Singleton(void) //Default destructor that is in charge of erasing the singleton reference
	{
		assert(_singleton);
		_singleton = 0;
	}

	static T* getSingleton(void) //Return a pointer to the singleton object
	{
		assert(_singleton); //check it exists
		return _singleton;
	}


};

//initiate the singleton
template <typename T>
T* Singleton<T>::_singleton = 0;