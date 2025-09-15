#include "UI.h"

int main() {
	DynamicVector<WeatherStation> stations;
	Repository repo{ stations };
	Service service{ repo };
	UI ui{ service };
	ui.run();
}