#include "GameManager.h"


GameManager::GameManager() {
	gWindow = nullptr;
	gRenderer = nullptr;
	texturaBomber1 = nullptr;
	texturaBomber2 = nullptr;

	enemigoBomber1 = nullptr;
	enemigoBomber2 = nullptr;
	enemigoBomber3 = nullptr;
	enemigoBomber4 = nullptr;
	enemigoBomber5 = nullptr;

	explosionBomber1 = nullptr;
	explosionBomber2 = nullptr;
	explosionBomber3 = nullptr;
	explosionBomber4 = nullptr;
	explosionBomber5 = nullptr;

}

bool GameManager::onInit() {

	//Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Bomber Man USFX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{

			////Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
};

bool GameManager::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture("texture.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}


void GameManager::close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int GameManager::onExecute() {
	if (!onInit()) {
		cout << "Failed to initialize!" << endl;
		return -1;
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event event;

		texturaBomber1 = new Texture(gRenderer);
		texturaBomber1->loadFromImage("resources/bomber.bmp");
		texturaBomber2 = new Texture(gRenderer);
		texturaBomber2->loadFromImage("resources/textures.bmp");

		//////////////////////////////////////////////Enemigos////////
		enemigoBomber1 = new Texture(gRenderer);
		enemigoBomber1->loadFromImage("resources/textures.bmp");
		enemigoBomber2 = new Texture(gRenderer);
		enemigoBomber2->loadFromImage("resources/textures.bmp");
		enemigoBomber3 = new Texture(gRenderer);
		enemigoBomber3->loadFromImage("resources/textures.bmp");
		enemigoBomber4 = new Texture(gRenderer);
		enemigoBomber4->loadFromImage("resources/textures.bmp");
		enemigoBomber5 = new Texture(gRenderer);
		enemigoBomber5->loadFromImage("resources/textures.bmp");
		////////////////////////////Explosion////////////////+
		explosionBomber1 = new Texture(gRenderer);
		explosionBomber1->loadFromImage("resources/textures.bmp");
		explosionBomber2 = new Texture(gRenderer);
		explosionBomber2->loadFromImage("resources/textures.bmp");
		explosionBomber3 = new Texture(gRenderer);
		explosionBomber3->loadFromImage("resources/textures.bmp");
		explosionBomber4 = new Texture(gRenderer);
		explosionBomber4->loadFromImage("resources/textures.bmp");
		explosionBomber5 = new Texture(gRenderer);
		explosionBomber5->loadFromImage("resources/textures.bmp");


		Bomber* b1 = new Bomber(texturaBomber1);
		Bomber* b2 = new Bomber(texturaBomber2);
		/////////////////////////////////////////////////enemigo///
		Enemigo* e1 = new Enemigo(enemigoBomber1);
		Enemigo* e2 = new Enemigo(enemigoBomber2);
		Enemigo* e3 = new Enemigo(enemigoBomber3);
		Enemigo* e4 = new Enemigo(enemigoBomber3);
		Enemigo* e5 = new Enemigo(enemigoBomber3);
		////////////////explosion////////////
		Explosion* ex1 = new Explosion(explosionBomber1);
		Explosion* ex2 = new Explosion(explosionBomber1);
		Explosion* ex3 = new Explosion(explosionBomber1);
		Explosion* ex4 = new Explosion(explosionBomber1);
		Explosion* ex5 = new Explosion(explosionBomber1);



		b1->setImagenX(3);
		b1->setImagenY(3);
		b1->setAncho(20);
		b1->setAlto(30);

		b2->setImagenX(560);
		b2->setImagenY(3);
		b2->setAncho(30);
		b2->setAlto(35);

		e1->setImagenX(4);
		e1->setImagenY(162);
		e1->setAncho(24);
		e1->setAlto(20);

		e2->setImagenX(6);
		e2->setImagenY(190);
		e2->setAncho(24);
		e2->setAlto(20);

		e3->setImagenX(9);
		e3->setImagenY(215);
		e3->setAncho(24);
		e3->setAlto(20);

		e4->setImagenX(8);
		e4->setImagenY(243);
		e4->setAncho(24);
		e4->setAlto(20);

		e5->setImagenX(6);
		e5->setImagenY(264);
		e5->setAncho(24);
		e5->setAlto(20);

		////////////Explowion//
		ex1->setImagenX(420);
		ex1->setImagenY(400);
		ex1->setAncho(75);
		ex1->setAlto(75);

		ex2->setImagenX(813);
		ex2->setImagenY(417);
		ex2->setAncho(75);
		ex2->setAlto(75);

		ex3->setImagenX(727);
		ex3->setImagenY(617);
		ex3->setAncho(75);
		ex3->setAlto(75);

		ex4->setImagenX(329);
		ex4->setImagenY(727);
		ex4->setAncho(75);
		ex4->setAlto(75);

		ex5->setImagenX(633);
		ex5->setImagenY(623);
		ex5->setAncho(75);
		ex5->setAlto(75);

		actoresJuego.push_back(b1);
		actoresJuego.push_back(b2);
		actoresJuego.push_back(e1);
		actoresJuego.push_back(e2);
		actoresJuego.push_back(e3);
		actoresJuego.push_back(e4);
		actoresJuego.push_back(e5);
		actoresJuego.push_back(ex1);
		actoresJuego.push_back(ex2);
		actoresJuego.push_back(ex3);
		actoresJuego.push_back(ex4);
		actoresJuego.push_back(ex5);


		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&event) != 0)
			{
				//User requests quit
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			//Clear screen
			//SDL_RenderClear(gRenderer);

			//Render texture to screen
			//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
			
				
			////Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Update screen

			/*onLoop();
			onRender();*/
			////Inge estaba dificil ubicar las imagenes ;(  ///////////
			for (int i = 0; i < actoresJuego.size(); i++) {
				((GameActor*)actoresJuego[i])->setPosicionX(rand() % SCREEN_WIDTH);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				((GameActor*)actoresJuego[i])->setPosicionY(rand() % SCREEN_HEIGHT);
				actoresJuego[i]->render();
			}

			SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;

}

SDL_Texture* GameManager::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}