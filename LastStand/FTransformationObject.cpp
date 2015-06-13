#include "FTransformationObject.h"

FTransformationObject::FTransformationObject(std::string name, FTransformationObject* parent /*= NULL*/)
	:_name(name),
	_parentTransformationObject(parent),
	_localPosition(0.0),
	_worldPosition(0.0),
	_rotationValue(),
	_scaleValue(1.0)
{
}


FTransformationObject::~FTransformationObject()
{
}
