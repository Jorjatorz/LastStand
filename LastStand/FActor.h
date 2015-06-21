#pragma once

#include <vector>

#include "FObject.h"
#include "FSceneComponent.h"

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
	void translate(const Vector3& delta);
	void setOrientation(const Quaternion& delta);
	void rotate(const Quaternion& delta);
	void rotate(const Vector3& degreeDelta);
	void setScale(const Vector3& scale);
	void scale(const Vector3& delta);
	
	//Add an already created scenecomponent to the rootComponent.
	void addComponentToRootComponent(FSceneComponent* component);
	//Creates and add a new component to the rootComponent
	template <typename T>
	T* addComponentToRootComponent(std::string name)
	{
		T* newComponent = new T(name, this);
		if (!_rootComponent.addChildrenComponent(newComponent))
		{
			delete newComponent;
			return NULL; ///Change this to return the component with that name
		}

		return newComponent;
	}
	//Remove a component from the actor root component. Sames as removing directly from the root component itself
	void removeComponentFromRootComponent(std::string name);

	//Return a vector with the owned components.
	std::vector<FComponent*> getComponents()
	{
		return _ownedComponents;
	}
	//Adds a component to the _ownedComponents array. This should only be called by the component
	void addOwnedComponent(FComponent* ownedComp);
	//Remove a owned componend from the owned vector
	void removeOwnedComponent(FComponent* ownedComp);

protected:
	//Root component. Always a tranformationComponent
	FSceneComponent _rootComponent;
	//Vector with all the owned components by the actor
	std::vector<FComponent*> _ownedComponents;
};

