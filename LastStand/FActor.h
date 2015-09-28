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
		return _rootComponent ? _rootComponent : NULL;
	}
	void setPosition(const Vector3& pos);
	void translate(const Vector3& delta);

	//Sets the Local rotation of the root component
	void setRotation(const Quaternion& quat);
	void setRotation(const FRotator& rotator);
	void setRotation(const Vector3& euler);
	//Sets the local direction of the root component. The direction must be normalized (Sets the corresponding rotation to face that direction) - like lookAt
	void setOrientation(const Vector3& direction);

	void rotate_WorldSpace(const Quaternion& delta);
	void rotate_WorldSpace(float degrees, const Vector3& axisVector);
	void rotate_LocalSpace(float degrees, const Vector3& axisVector);
	void pitch(float degrees); //World space
	void yaw(float degrees); //World space
	void roll(float degrees); //World space
	

	void setScale(const Vector3& scale);
	void scale(const Vector3& delta);
	
	//Add an already created scenecomponent to the rootComponent.
	void addComponent(FSceneComponent* component);
	//Creates and add a new component to the rootComponent
	template <typename T>
	T* addComponent(std::string name)
	{
		//Create the component (it will automatically register into the actor)
		T* newComponent = new T(name, this);
		if (!_rootComponent)
		{
			_rootComponent = newComponent;
			//We are attached to the actor (attached to null component) so call it
			_rootComponent->onAttachedToComponent();
		}
		//Add it to the root component if it doesn't exists
		else if (!_rootComponent->addChildrenComponent(newComponent))
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

	//Called each frame if _actorCanTick is true
	void tickActor(float deltaTime);
	//Sets if the actor can tick per frame or not.
	void setActorCanTick(bool canTick);
	bool canTick()
	{
		return _actorCanTick;
	}

protected:
	//Root component. It will be created automatically when the first component is added. (Of that type)
	FSceneComponent* _rootComponent;
	//Input component. Its dynamically allocated when method enableInput is called;
	//By default its NULL at the beginning (input deactivated)
	FInputComponent* _inputComponent;

	//Vector with all the owned components by the actor
	std::vector<FComponent*> _ownedComponents;

	//True if the actor can tick, false by default
	bool _actorCanTick;
};

