#pragma once

#include <assert.h>
#include <typeinfo>

#include "FLog.h"

template <class T>
class SingleInstance
{
	private:
		SingleInstance(const SingleInstance &);
		SingleInstance& operator=(const SingleInstance &);

		static bool _instantiated;

	public:
		SingleInstance()//Default constructor that is in charge of saving just one reference of the class
		{
			if (_instantiated)
			{
				FLog(FLog::FAILURE, "SingleInstance class already instantiated: %s", typeid(T).name());
				assert(0); //just created once
			}
			_instantiated = true;
		}

		~SingleInstance() //Default destructor that is in charge of erasing the SingleInstance
		{
			if (!_instantiated)
			{
				FLog(FLog::FAILURE, "SingleInstance class not instantiated, can't delete it: %s", typeid(T).name());
				assert(0); //just created once
			}

			_instantiated = false;
		}
};

template <class T>
bool SingleInstance<T>::_instantiated = false;