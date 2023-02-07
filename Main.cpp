	#include <iostream>

	#define SDL_MAIN_HANDLED

	#include <SDL.h>
	#include <SDL_image.h>
	#include "Player_Plane.h"
	#include "LinkedList.h"
	#include "PBullet.h"
	#include <Windows.h>
	#include <thread>
	#include <stdlib.h> 
	#include "Dodger.h"
	#include "Shooter.h"
	#include "Missile.h"
	#include "SDL_ttf.h"
	#include <string>
	#include "Smoke.h"
	#include <SDL_mixer.h>
	#include"Boss.h"
	#include "Turret.h"

	const int WIDTH = 1000, HEIGHT = 1000;

	int main(int argc, char* argv) {

		TTF_Init();

		Mix_Music* Game_Music = NULL;
		Mix_Music* Menu_Music = NULL;
		Mix_Chunk* Shot_Aircraft = NULL;
		Mix_Chunk* Rocket = NULL;
		Mix_Chunk* Hitmarker = NULL;
		Mix_Chunk* Explosion = NULL;

		SDL_Surface* WindowSurface;
		SDL_Renderer* R;

		LinkedList P_Bullet;
		LinkedList Rockets;

		LinkedList Dodge;
		LinkedList Shoot;
		LinkedList XBoss;
		LinkedList Turrets;

		LinkedList Particles;

		int seconds = 30;
		int UAVx = 0;
		int F35x = 0;

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

			std::cout << "SDL Failed to initialize. Error Code : " << SDL_GetError() << std::endl;

		}

		SDL_Window* window = SDL_CreateWindow("Plane Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
		WindowSurface = SDL_GetWindowSurface(window);

		if (window == NULL) {
			std::cout << "Could not initialize SDL Window. Error Code : " << SDL_GetError() << std::endl;
			return EXIT_FAILURE;
		}

		if (!(IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG) {
			std::cout << "Could not initialize PNG. Error Code : " << SDL_GetError() << std::endl;
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		SDL_Event window_event;

		R = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		//Load Player Plane
		SDL_Texture* BG = IMG_LoadTexture(R, "Art/BG.jpg");

		Player_Plane* player = new Player_Plane(500 - 64, 800, R);

		std::cout << "Player Created" << std::endl;

		int frames = 1700;

		SDL_Texture* PB = IMG_LoadTexture(R, "Art/Play_Button.png");
		SDL_Texture* EB = IMG_LoadTexture(R, "Art/Exit_Button.png");
		SDL_Texture* Radar = IMG_LoadTexture(R, "Art/Radar.jpg");

		SDL_Rect* P = new SDL_Rect();
		P->x = 500 - 256;
		P->y = 500;
		P->w = 512;
		P->h = 256;

		SDL_Rect* T1 = new SDL_Rect();
		T1->x = 10;
		T1->y = 24;
		T1->w = 150;
		T1->h = 18;

		SDL_Rect* T2 = new SDL_Rect();
		T2->x = 10;
		T2->y = 48;
		T2->w = 150;
		T2->h = 18;

		SDL_Rect* T3 = new SDL_Rect();
		T3->x = 10;
		T3->y = 72;
		T3->w = 150;
		T3->h = 18;

		SDL_Rect* T4 = new SDL_Rect();
		T4->x = 0;
		T4->y = 0;
		T4->w = 1000;
		T4->h = 100;

		SDL_Rect* T5 = new SDL_Rect();
		T5->x = 850;
		T5->y = 48;
		T5->w = 150;
		T5->h = 18;


		SDL_Rect* T6 = new SDL_Rect();
		T6->x = 850;
		T6->y = 24;
		T6->w = 150;
		T6->h = 18;

		TTF_Font* RELOAD = TTF_OpenFont("Art/Reload-Light.ttf", 18);


		Game_Music = Mix_LoadMUS("Music/Game Music.mp3");
		Menu_Music = Mix_LoadMUS("Music/Menu Music.mp3");
		Rocket = Mix_LoadWAV("Music/Missile.wav");	
		Shot_Aircraft = Mix_LoadWAV("Music/Shot.wav");
		Explosion = Mix_LoadWAV("Music/Explosion.wav");
		Hitmarker = Mix_LoadWAV("Music/Hitmarker.wav");


			if (Game_Music == NULL)
			{
				printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
			}
			if (Menu_Music == NULL)
			{
				printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
			}

		Mix_PlayMusic(Menu_Music, -1);

		//Game Menu
		while (true) {

			if (SDL_PollEvent(&window_event)) {

				if (SDL_QUIT == window_event.type) {
					break;
				}

				if (SDL_KEYDOWN == window_event.type) {

					if (SDLK_SPACE == window_event.key.keysym.sym) {
						Mix_HaltMusic();
						break;
					}

					if (SDLK_ESCAPE == window_event.key.keysym.sym) {
						return EXIT_SUCCESS;
					}
				}


			}

			SDL_RenderCopy(R, BG, NULL, NULL);
			SDL_RenderCopy(R, PB, NULL, P);
			//Clearing of Renderer
			SDL_RenderPresent(R);
			SDL_RenderClear(R);

		}

		Mix_PlayMusic(Game_Music, -1);

		while (true) {



			srand(time(0));
			frames++;

			if (player->alive == false) {
				break;
			}

			//srand(time(0));

			if (frames % 60 == 0) {

				//std::cout << "Current Player Bullets : " << P_Bullet.length << std::endl;
				seconds--;
			}

			if (frames % 120 == 0) {

				player->AddMissile();

			}

			if (frames % 120 == 0 && frames < 1700) {

				int random = (rand() % 650) + 20;
				Dodger* X = new Dodger(random, 0, R);
				Dodge.insertHead(X);

			}


			if (frames % 180 == 0 && frames < 1700) {

				int random = (rand() % 650) + 20;
				Shooter* X = new Shooter(random, 0, R);
				Shoot.insertHead(X);

			}

			if (frames == 1800) {
				Boss* X = new Boss((WIDTH-800)/2, -0,R);
				XBoss.insertHead(X);

				std::cout << "Boss Man!" << std::endl;
			}

			if (frames == 2000) {
	
				//Galting = 0,1 , ScatterShot =2 , AccuracyInternational = 3
				Turret* Z = new Turret(400 + (rand() % 160), 200 + rand() % 170, player, R);
				Turrets.insertHead(Z);

				Turret* Y = new Turret(350 + (rand() % 200), 200 + rand() % 60, player, R);
				Turrets.insertHead(Y);

				Turret* X = new Turret(100 + (rand()%40), 250+rand()%70, player, R);
				Turrets.insertHead(X);

				Turret* X1 = new Turret(700 - (rand() % 100), 200 + rand() % 70, player, R);
				Turrets.insertHead(X1);

			}

			if (SDL_PollEvent(&window_event)) {

				if (SDL_QUIT == window_event.type) {
					break;
				}

				if (SDL_KEYDOWN == window_event.type) {
					if (SDLK_DOWN == window_event.key.keysym.sym) {
						player->Direction(0, +5.0f);
					}
					if (SDLK_UP == window_event.key.keysym.sym) {
						player->Direction(0, -5.0f);
					}
					if (SDLK_LEFT == window_event.key.keysym.sym) {
						player->Direction(-10.0f, 0);
						player->Texture = IMG_LoadTexture(R, "Art/SU47-L.png");
					}
					if (SDLK_RIGHT == window_event.key.keysym.sym) {
						player->Direction(+10.0f, 0);
						player->Texture = IMG_LoadTexture(R, "Art/SU47-R.png");
					}
					if (SDLK_SPACE == window_event.key.keysym.sym) {

						PBullet* X = new PBullet(player->Bounding_Box->x + 50, player->Bounding_Box->y, R, false);
						PBullet* Y = new PBullet(player->Bounding_Box->x + 78, player->Bounding_Box->y, R, false);
						Mix_PlayChannel(-1, Shot_Aircraft, 0);
						P_Bullet.insertHead(X);
						P_Bullet.insertHead(Y);

					}


					if (SDLK_b == window_event.key.keysym.sym) {


						GameObject* TTK = NULL;

						for (int i = 0; i < Shoot.length; i++)
						{
							TTK = Shoot.at(i);
							if (TTK->alive == true && TTK->hasTarget == false) {
								break;
							}
						}

						if (player->missiles > 0 && TTK != NULL) {
							std::cout << "Missile Launched!" << std::endl;
							player->missiles = player->missiles - 1;
							std::cout << "Missile Left : " << player->missiles << std::endl;
							Missile* X = new Missile(player->Bounding_Box->x - 2 + (player->Bounding_Box->w) / 2, player->Bounding_Box->y, TTK ,R);
							Rockets.insertHead(X);
							Mix_PlayChannel(-1, Rocket, 0);
						}
						else {
							std::cout << "Out of Missiles Comrade!" << std::endl;
						}
					}
				}
				if (SDL_KEYUP == window_event.type) {
					player->Texture = IMG_LoadTexture(R, "Art/SU47.png");
				}

			}
			//BG Render
			SDL_RenderCopy(R, BG, NULL, NULL);

			//Player Movement
			player->Move();

			//Boss Movement
			for (int i = 0; i < XBoss.length; i++)
			{
				GameObject* bullet = XBoss.at(i);
				bullet->Move();
				SDL_RenderCopy(R, bullet->getTexture(), NULL, bullet->getRect());

				if (bullet->Bounding_Box->y == 199) {
					std::cout << "Frame # : " << frames << std::endl;
				}
			}

			//Turrets Rendering
			for (int i = 0; i < Turrets.length; i++)
			{
				GameObject* bullet = Turrets.at(i);
				bullet->Move();
				SDL_RenderCopy(R, bullet->getTexture(), NULL, bullet->getRect());

			}


			//Bullet Movement
			for (int i = 0; i < P_Bullet.length; i++)
			{
				GameObject* bullet = P_Bullet.at(i);
				bullet->Move();
				SDL_RenderCopy(R, bullet->getTexture(), NULL, bullet->getRect());
				//free(bullet);
			}

			//Missile Movement
			for (int i = 0; i < Rockets.length; i++)
			{
				GameObject* bullet = Rockets.at(i);
				bullet->Move();
				SDL_RenderCopy(R, bullet->getTexture(), NULL, bullet->getRect());
				if (frames%30 == 0) {
					Smoke* S = new Smoke(bullet->Bounding_Box->x-3, bullet->Bounding_Box->y, R);
					Particles.insertHead(S);

					std::cout << "Smoke Generated | List size :" << Particles.length << std::endl;
				}
				//free(bullet);
			}

			//Enemy Movement
			//Dodger
			for (int i = 0; i < Dodge.length; i++)
			{
				GameObject* dodger = Dodge.at(i);
				dodger->Move();
				SDL_RenderCopy(R, dodger->getTexture(), NULL, dodger->getRect());
				//free(bullet);
			}

			//Shooter
			for (int i = 0; i < Shoot.length; i++)
			{
				GameObject* shooter = Shoot.at(i);
				shooter->Move();
				SDL_RenderCopy(R, shooter->getTexture(), NULL, shooter->getRect());
				//free(bullet);
			}

			//Smoke Render
			for (int i = 0; i < Particles.length; i++)
			{
				GameObject* P = Particles.at(i);
				P->Move();
				SDL_RenderCopy(R, P->getTexture(), NULL, P->getRect());
				//free(bullet);
			}

			//Player Render
			SDL_RenderCopy(R, player->getTexture(), NULL, player->getRect());

			//Colliders
			//Bullet
			for (int i = 0; i < P_Bullet.length; i++)
			{
				GameObject* B = P_Bullet.at(i);


				//Player Bullet to Dodger
				for (int j = 0; j < Dodge.length; j++) {

					GameObject* E = Dodge.at(j);

					if (B->Bounding_Box->x >= E->Bounding_Box->x && B->Bounding_Box->x + 8 <= E->Bounding_Box->x + 72 && E->alive == true) {

						if (B->Bounding_Box->y <= E->Bounding_Box->y + 41 && B->Bounding_Box->y >= E->Bounding_Box->y && B->enemyB == false) {

							E->health = E->health - 1;
							E->Texture = IMG_LoadTexture(R, "Art/Explosion.png");
							Mix_PlayChannel(-1, Hitmarker, 0);
							B->alive = false;
							Mix_PlayChannel(-1, Explosion, 0);

						}

					}

				}

				//Player Bullet to Boss Turrets
				for (int j = 0; j < Turrets.length; j++) {

					GameObject* E =Turrets.at(j);

					if (B->Bounding_Box->x >= E->Bounding_Box->x && B->Bounding_Box->x + 8 <= E->Bounding_Box->x + 72 && E->alive == true) {

						if (B->Bounding_Box->y <= E->Bounding_Box->y + 41 && B->Bounding_Box->y >= E->Bounding_Box->y && B->enemyB == false) {

							E->health = E->health - 1;
							Mix_PlayChannel(-1, Hitmarker, 0);
							B->alive = false;
							if (E->health == 0) {
								Mix_PlayChannel(-1, Explosion, 0);
								E->alive = false;
							}
						}

					}

				}

				//Enemy Bullet to Player
				if (B->Bounding_Box->x >= player->Bounding_Box->x && B->Bounding_Box->x + 8 <= player->Bounding_Box->x + 130) {
					if (B->Bounding_Box->y <= player->Bounding_Box->y + 120 && B->Bounding_Box->y >= player->Bounding_Box->y + 30 && B->enemyB == true) {

						player->alive = false;
						player->Texture = IMG_LoadTexture(R, "Art/SU47-E.png");

					}
				}

				//Player Bullet to Shooter
				for (int j = 0; j < Shoot.length; j++) {

					GameObject* E = Shoot.at(j);

					if (B->Bounding_Box->x >= E->Bounding_Box->x && B->Bounding_Box->x + 8 <= E->Bounding_Box->x + 89 && E->alive == true) {

						if (B->Bounding_Box->y <= E->Bounding_Box->y + 85 && B->Bounding_Box->y >= E->Bounding_Box->y && B->enemyB == false) {

							E->health = E->health - 1;
							if (E->health < 1) {
								E->Texture = IMG_LoadTexture(R, "Art/Explosion.png");
								Mix_PlayChannel(-1, Explosion, 0);
							}
							else if (E->health < 4) {
								E->Texture = IMG_LoadTexture(R, "Art/F-35-E.png");
							}
							else if (E->health < 2) {
								E->Texture = IMG_LoadTexture(R, "Art/F-35-EE.png");
							}
							Mix_PlayChannel(-1, Hitmarker, 0);
							B->alive = false;
						}

					}

				}
			}

			//Missiles
			for (int i = 0; i < Rockets.length; i++)
			{
				GameObject* B = Rockets.at(i);
				//Player Missile to Dodger
				for (int j = 0; j < Dodge.length; j++) {

					GameObject* E = Dodge.at(j);

					if (B->Bounding_Box->x >= E->Bounding_Box->x && B->Bounding_Box->x + 8 <= E->Bounding_Box->x + 72 && E->alive == true) {

						if (B->Bounding_Box->y <= E->Bounding_Box->y + 41 && B->Bounding_Box->y >= E->Bounding_Box->y) {

							E->health = E->health - 3;
							E->Texture = IMG_LoadTexture(R, "Art/Explosion.png");
							B->alive = false;
							Mix_PlayChannel(-1, Hitmarker, 0);
						}

					}

				}

				//Player Missile to Shooter
				for (int j = 0; j < Shoot.length; j++) {

					GameObject* E = Shoot.at(j);

					if (B->Bounding_Box->x >= E->Bounding_Box->x && B->Bounding_Box->x + 8 <= E->Bounding_Box->x + 89 && E->alive == true) {

						if (B->Bounding_Box->y <= E->Bounding_Box->y + 130 && B->Bounding_Box->y >= E->Bounding_Box->y) {

							E->health = E->health - 3;
							if (E->health < 1) {
								E->Texture = IMG_LoadTexture(R, "Art/Explosion.png");
							}
							else if (E->health < 4) {
								E->Texture = IMG_LoadTexture(R, "Art/F-35-E.png");
							}
							else if (E->health < 2) {
								E->Texture = IMG_LoadTexture(R, "Art/F-35-EE.png");
							}
							Mix_PlayChannel(-1, Hitmarker, 0);
							B->alive = false;

						}

					}

				}

			}

			//Player and Enemy Collisions
			for (int i = 0; i < Dodge.length; i++) {

				GameObject* E = Dodge.at(i);
				if (E->Bounding_Box->x >= player->Bounding_Box->x && E->Bounding_Box->x <= player->Bounding_Box->x + 128 && E->alive == true) {
					if (E->Bounding_Box->y + 41 >= player->Bounding_Box->y && E->Bounding_Box->y <= player->Bounding_Box->y + 130) {
						player->alive = false;
						player->Texture = IMG_LoadTexture(R, "Art/SU47-E.png");
					}
				}

			}

			for (int i = 0; i < Shoot.length; i++) {
				GameObject* E = Shoot.at(i);
				if (E->Bounding_Box->x >= player->Bounding_Box->x && E->Bounding_Box->x <= player->Bounding_Box->x + 128 && E->alive == true) {
					if (E->Bounding_Box->y + 130 >= player->Bounding_Box->y && E->Bounding_Box->y <= player->Bounding_Box->y + 130) {
						player->alive = false;
						player->Texture = IMG_LoadTexture(R, "Art/SU47-E.png");
					}
				}
			}

			//AI
			//Dodger
			for (int i = 0; i < P_Bullet.length; i++)
			{
				GameObject* B = P_Bullet.at(i);


				//Player Bullet to Dodger
				for (int j = 0; j < Dodge.length; j++) {

					GameObject* E = Dodge.at(j);

					if (B->Bounding_Box->x >= E->Bounding_Box->x && B->Bounding_Box->x + 8 <= E->Bounding_Box->x + 60 && E->alive == true) {

						if (B->Bounding_Box->y <= E->Bounding_Box->y + 120 && E->dodge == true) {

							E->dodge = false;
							if (rand() % 20 > 10) {
								E->Bounding_Box->x = E->Bounding_Box->x + 36;
							}
							else {
								E->Bounding_Box->x = E->Bounding_Box->x - 36;
							}
						}

					}

				}
			}

			//Shooter
			for (int i = 0; i < Shoot.length; i++) {

				GameObject* D = Shoot.at(i);
				if (D->shoot == true && D->alive == true) {
					PBullet* X = new PBullet(D->Bounding_Box->x + 30, D->Bounding_Box->y, R, true);
					P_Bullet.insertHead(X);
					PBullet* Y = new PBullet(D->Bounding_Box->x + 60, D->Bounding_Box->y, R, true);
					P_Bullet.insertHead(Y);
					D->shoot = false();
				}

			}

			//Turrets
			for (int i = 0; i < Turrets.length; i++) {

				GameObject* D = Turrets.at(i);

				if(D->alive) {

					if ((i == 0 || i == 1) && D->shoot == true) { //Galting
						PBullet* X = new PBullet(D->Bounding_Box->x + 15, D->Bounding_Box->y, R, true);
						P_Bullet.insertHead(X);
						PBullet* Y = new PBullet(D->Bounding_Box->x + 30, D->Bounding_Box->y, R, true);
						P_Bullet.insertHead(Y);
					}

					if ((i==2 || i == 3) && D->shoot == true) { //Scattershot

						PBullet* X = new PBullet(D->Bounding_Box->x + 15, D->Bounding_Box->y, R, true);
						X->ScatterL = true;
						PBullet* Y = new PBullet(D->Bounding_Box->x + 30, D->Bounding_Box->y, R, true);
						Y->ScatterR = true;
						P_Bullet.insertHead(X);
						P_Bullet.insertHead(Y);

					}

				}

			}

			//Deleting of Unalive GameObjects
			//Bullets
			for (int i = 0; i < P_Bullet.length; i++)
			{
				GameObject* D = P_Bullet.at(i);
				if (D->alive == false) {
					SDL_DestroyTexture(D->getTexture());
					P_Bullet.deleteIndex(i);
				}
			}

			//Missiles
			for (int i = 0; i < Rockets.length; i++)
			{
				GameObject* D = Rockets.at(i);
				if (D->alive == false) {
					SDL_DestroyTexture(D->getTexture());
					Rockets.deleteIndex(i);
				}
			}


			if (frames % 30 == 0) {

				//Dodger
				for (int i = 0; i < Dodge.length; i++)
				{
					GameObject* D = Dodge.at(i);
					if (D->alive == false) {
						SDL_DestroyTexture(D->getTexture());
						if (D->health < 1) {
							UAVx++;
						}
						Dodge.deleteIndex(i);
					}
				}

				//Shooter
				for (int i = 0; i < Shoot.length; i++)
				{
					GameObject* D = Shoot.at(i);
					if (D->alive == false) {
						SDL_DestroyTexture(D->getTexture());
						if (D->health < 1) {
							F35x++;
						}
						//SDL_free(D->getRect());
						Shoot.deleteIndex(i);
					}
				}

				//Turrets
				for (int i = 0; i < Turrets.length; i++)
				{
					GameObject* D = Turrets.at(i);
					if (D->health < 1) {
						SDL_DestroyTexture(D->getTexture());
						D->alive = false;
					}
				}

				//Smoke
				for (int i = 0; i < Particles.length; i++)
				{
					GameObject* D = Particles.at(i);
					if (D->alive == false) {
						SDL_DestroyTexture(D->getTexture());
						Particles.deleteIndex(i);
					}
				}
			}

			//Scoring & GUI
			std::string one = "F35 Kills : ";
			one = one.append(std::to_string(F35x));
			const char* str = one.c_str();
			SDL_Surface* F35D = TTF_RenderText_Solid(RELOAD, str, { 247, 255, 0 });

			one = "UAV Kills : ";
			one = one.append(std::to_string(UAVx));
			str = one.c_str();
			SDL_Surface* UAVD = TTF_RenderText_Solid(RELOAD, str, { 247, 255, 0 });

			one = "Score : ";
			one = one.append(std::to_string((UAVx + F35x)));
			str = one.c_str();
			SDL_Surface* SCORE = TTF_RenderText_Solid(RELOAD, str, { 255,255,255 });

			if (seconds < 0) {

				seconds = 0;

			}

			one = "ETA : ";
			one = one.append(std::to_string(seconds));
			one = one.append(" Seconds");
			str = one.c_str();
			SDL_Surface* ACTIVITY = TTF_RenderText_Solid(RELOAD, str, { 255,255,255 });

			one = "Missiles : ";
			one = one.append(std::to_string((player->missiles)));
			str = one.c_str();
			SDL_Surface* MISSILE = TTF_RenderText_Solid(RELOAD, str, { 255,255,255 });

			SDL_Texture* FF = SDL_CreateTextureFromSurface(R, F35D);
			SDL_Texture* UU = SDL_CreateTextureFromSurface(R, UAVD);
			SDL_Texture* SS = SDL_CreateTextureFromSurface(R, SCORE);
			SDL_Texture* AA = SDL_CreateTextureFromSurface(R, ACTIVITY);
			SDL_Texture* MM = SDL_CreateTextureFromSurface(R, MISSILE);

			SDL_QueryTexture(FF, NULL, NULL, &T1->w, &T1->h);
			SDL_QueryTexture(UU, NULL, NULL, &T2->w, &T2->h);
			SDL_QueryTexture(SS, NULL, NULL, &T3->w, &T3->h);
			SDL_QueryTexture(AA, NULL, NULL, &T5->w, &T5->h);
			SDL_QueryTexture(MM, NULL, NULL, &T6->w, &T6->h);

			T5->x = 980 - T5->w;
			T6->x = 980 - T6->w;

			SDL_RenderCopy(R, Radar, NULL, T4);
			SDL_RenderCopy(R, FF, NULL, T1);
			SDL_RenderCopy(R, UU, NULL, T2);
			SDL_RenderCopy(R, SS, NULL, T3);
			SDL_RenderCopy(R, AA, NULL, T5);
			SDL_RenderCopy(R, MM, NULL, T6);


			//Clearing of Renderer
			SDL_RenderPresent(R);
			SDL_RenderClear(R);
			SDL_FreeSurface(F35D);
			SDL_FreeSurface(UAVD);
			SDL_FreeSurface(SCORE);
			SDL_DestroyTexture(FF);
			SDL_DestroyTexture(UU);
			SDL_DestroyTexture(SS);

			//SDL_UpdateWindowSurface(window);
			std::this_thread::sleep_for(std::chrono::milliseconds(17));
		}

		SDL_FreeSurface(WindowSurface);

		std::cout << " " << std::endl;
		std::cout << " " << std::endl;
		std::cout << "////////////////////SCORE/////////////////" << std::endl;
		std::cout << "F35s Destroyed : " << F35x << std::endl;
		std::cout << "UAVs Destroyed : " << UAVx << std::endl;
		std::cout << " " << std::endl;
		std::cout << " " << std::endl;

		WindowSurface = NULL;

		Mix_HaltMusic();

		Mix_FreeMusic(Menu_Music);
		Mix_FreeMusic(Game_Music);
		Mix_FreeChunk(Explosion);
		Mix_FreeChunk(Rocket);
		Mix_FreeChunk(Hitmarker);
		Mix_FreeChunk(Shot_Aircraft);
						
		TTF_CloseFont(RELOAD);
		TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_Quit();

		//Wait for 5 seconds
		while (true) {
			break;
		}
		return EXIT_SUCCESS;
	}