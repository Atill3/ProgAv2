#include <Bart2d.h>
#include <RandomService.h>


bool bart::RandomService::Initialize()
{
	InitSeed();
	return true;
}

void bart::RandomService::Destroy()
{
}

unsigned int bart::RandomService::GetRandom(int a, int b)
{
	return a + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (b - a)));
}

void bart::RandomService::InitSeed()
{
	srand(static_cast<unsigned int>(time(nullptr)));
}
