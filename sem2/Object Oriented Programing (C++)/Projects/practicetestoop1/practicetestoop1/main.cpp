#include "UI.h"

int main()
{
	Repository repo;
	Service service{ repo };
	UI ui{ service };
	ui.run();
	return 0;
}