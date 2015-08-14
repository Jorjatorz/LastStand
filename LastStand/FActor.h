#pragma once

#include <vector>
#include <typeinfo>

#include "FObject.h"
#include "FSceneComponent.h"

class FInputComponent;

//fObject that can be placed in the world
class FActor : public FObject
{
public:
	FActor(std::string name);
	~FActor();

	//Transformation staff
	FSceneComponent* const getRootComponentPtr()
	{
		return &_rootComponent;
	}
	void setPosition(const Vector3& pos);
	virtual void translate(const Vector3& delta);

	void setOrientation(const Quaternion& quat);
	virtual	void rotate_WorldSpace(const Quaternion& delta);
	virtual void rotate_WorldSpace(float degrees, const Vector3& axisVector);
	virtual void rotate_LocalSpace(float degrees, const Vector3& axisVector);
	virtual void pitch(float degrees); //World space
	virtual void yaw(float degrees); //World space
	virtual void roll(float degrees); //World space
	

	void setScale(const Vector3& scale);
	virtual void scale(const Vector3& delta);
	
	//Add an already created scenecomponent to the rootComponent.
	void addComponent(FSceneComponent* component);
	//Creates and add a new component to the rootComponent
	template <typename T>
	T* addComponent(std::string name)
	{
		//Create the component (it will automatically register into the actor)
		T* newComponent = new T(name, this);
		if (!_rootComponent.addChildrenComponent(newComponent))
		{
			delete newComponent;
			return NULL; ///Change this to return the component with that name
		}

		return newComponent;
	}
	//Remove a component from the actor root component. Sames as removing directly from the root component itself
	void removeComponent(std::string name);
	//Return a constant direct reference to the components vector
	const std::vector<FComponent*>& getComponents() const
	{
		return _ownedComponents;
	}
	//Return a vector with the copy of the owned components.
	void getComponents(std::vector<FComponent*>& comp) const
	{
		comp = _ownedComponents;
	}


	//Adds a component to the _ownedComponents array.
	//Warning! This should only be called by the component
	void addOwnedComponent(FComponent* ownedComp);
	//Remove a owned component from the owned vector
	//Warning! This should only be called by the component
	void removeOwnedComponent(FComponent* ownedComp);

	//Allocates a new input component (if it doesnt already exists)
	FInputComponent* enableInput();
	//Deallocates the input component (if it does exists)
	void disableInput();
	//True if the input is enable
	bool isInputEnable()
	{
		return _inputComponent;
	}

protected:
	//Root component. Always a tranformationComponent
	FSceneComponent _rootComponent;
	//Input component. Its dynamically allocated when method enableInput is called;
	//By default its NULL at the beginning (input deactivated)
	FInputComponent* _inputComponent;

	//Vector with all the owned components by the actor
	std::vector<FComponent*> _ownedComponents;
};

