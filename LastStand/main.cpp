#include "FEngine.h"

#include <memory>

int main()
{
	std::unique_ptr<FEngine> engine(new FEngine);

	engine->initializeEngine("LastStand", 1280, 720);

	engine->runEngine();

	return 0;
}