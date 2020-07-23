#include <Bart2d.h>
#include <Engine.h>
#include <RandomService.h>
#include <time.h>

using namespace std;

bool bart::RandomService::Initialize()
{
	InitRanSeed();
	return true;
}

void bart::RandomService::Destroy()
{
}

void bart::RandomService::InitRanSeed()
{
	srand(static_cast<unsigned int>(time(nullptr)));
}

unsigned int bart::RandomService::GetRandom(int a, int b)
{
	return a + static_cast<int>(rand()) / (static_cast<int> (RAND_MAX / (b - a)));
}
