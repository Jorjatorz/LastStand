#include "FEngine.h"
#include "Quaternion.h"
#include "Vector3.h"

#include "Test.h"

#include <memory>

int main()
{
	std::unique_ptr<FEngine> engine(new FEngine);

	engine->initializeEngine("LastStand", 1280, 720);

	Test t;

	engine->runEngine();

	return 0;
}