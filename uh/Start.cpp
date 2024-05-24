#include "Game.h"
#include "Sorter.h"
#include "FallingSand.h"
#include "Menu.h"
#include "DeltaTime.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((unsigned int)time(0));
	DeltaTime dt;
	Mode* game = new Menu();
	SCENECALLBACK SceneCallBack = SCENECALLBACK::NOTHING;
	while (SceneCallBack != SCENECALLBACK::QUIT) {
		SceneCallBack = game->Update((float)dt.dt());
		game->Render();
		game->HandleEvents();
		dt.restartClock();

		if (SceneCallBack != SCENECALLBACK::NOTHING && SceneCallBack != SCENECALLBACK::QUIT)
		{
			delete game;
			switch (SceneCallBack)
			{
			case MENU:
				game = new Menu();
				break;
			case BOUNCING_BALLS:
				game = new Game();
				break;
			case SORTER:
				game = new Sorter();
				break;
			case FALLING_SAND:
				game = new FallingSand();
				break;
			default:
				break;
			}
		}
	}
	delete game;
	return 0;
}
