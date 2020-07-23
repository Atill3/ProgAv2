#include <MathService.h>
#include <ctime>

bool bart::MathService::Initialize()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	return true;
}

void bart::MathService::Destroy()
{
}

int bart::MathService::Random()
{
	return rand();
}
