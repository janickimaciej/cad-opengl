#include "guis/gui.hpp"
#include "scene.hpp"
#include "window.hpp"

int main()
{
	static constexpr int initialWindowWidth = 1900;
	static constexpr int initialWindowHeight = 1000;

	Window window{initialWindowWidth, initialWindowHeight};
	Scene scene{initialWindowWidth, initialWindowHeight};
	GUI gui{window.getPtr(), scene, initialWindowWidth, initialWindowHeight};
	window.setWindowData(scene, gui);

	while (!window.shouldClose())
	{
		gui.update();
		window.clear();
		scene.render();
		gui.render();
		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}
