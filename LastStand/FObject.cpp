#include "FObject.h"

FObject::FObject(std::string name, FTransformationObject* parentTransformation /*= NULL*/)
	:_name(name),
	_rootTransformationObject(name, parentTransformation)
{
}


FObject::~FObject()
{
}
