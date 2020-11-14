#include "Renderer.h"

//TODO quiero una referencia o ahora quiero un nombre ...
//ERROR ....
//const SDL_Rect* Renderer::Rect2SDL(const RECT* r) { return { r->x, r->y, r->w, r->h }; }

Renderer::Renderer()
{
	// SDL --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	m_window = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (m_window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//IMG --- INIT ---
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_imageinit";

	//TTF --- INIT ---
	if (TTF_Init() != 0) throw"No es pot inicialitzar SDL_ttf";



	LoadScenes();
	
};

Renderer::~Renderer()
{
	for (auto &t : m_textureData) SDL_DestroyTexture(t.second), t.second = nullptr;
	for (auto &f : m_fontData) TTF_CloseFont(f.second), f.second = nullptr;
	for (auto& f : m_rects) { delete f.second; f.second = nullptr; };

	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

};

void Renderer::Clear() { SDL_RenderClear(m_renderer); };

void Renderer::Render() { SDL_RenderPresent(m_renderer); };

void Renderer::LoadFont(const Font &font) {
	TTF_Font *ttfFont{ TTF_OpenFont(font.path.c_str(), font.size) };
	if (ttfFont == nullptr) throw"No espot inicialitzar TTF_Font";
	m_fontData[font.id] = ttfFont;
};

void Renderer::LoadTexture(const std::string &id, const std::string &path) {
	SDL_Texture *texture{ IMG_LoadTexture(m_renderer, path.c_str()) };
	if (texture == nullptr) throw "No s'han pogut crear les textures";
	m_textureData[id] = texture;
};

VEC2 Renderer::LoadTextureText(const std::string &fontId, Text text) {
	SDL_Surface	*tmpSurf = TTF_RenderText_Blended(m_fontData[fontId], text.text.c_str(), SDL_Color{ text.color.r, text.color.g, text.color.b,text.color.a });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	m_textureData[text.id] = SDL_CreateTextureFromSurface(m_renderer, tmpSurf); //hace un new
	return { tmpSurf->w,tmpSurf->h };
};

void Renderer::LoadRect(const std::string& idRect, const RECT &rect) {
	m_rects[idRect] = new SDL_Rect{ rect.x,rect.y,rect.w,rect.h };
};

VEC2 Renderer::GetTextureSize(const std::string &id) {
	int w; int h;
	SDL_QueryTexture(m_textureData[id], NULL, NULL,&w, &h);
	return {w, h};
};

//Enseñarle a Aniol
void Renderer::PushImage(const std::string &id, const std::string &idRect) {
	SDL_RenderCopy(m_renderer, m_textureData[id], nullptr, m_rects[idRect]);
};

void Renderer::PushSprite(const std::string &id, const  std::string &idRectSprite,const  std::string &idRectPos) {

	SDL_RenderCopy(m_renderer, m_textureData[id],m_rects[idRectSprite], m_rects[idRectPos]);
}

void Renderer::PushRotatedSprite(const std::string & id, const std::string& idRectSprite, const std::string& idRectPos ,float angle){
	SDL_Point center = { m_rects[idRectPos]->w / 2, m_rects[idRectPos]->h / 2 };
	SDL_RenderCopyEx(m_renderer, m_textureData[id], m_rects[idRectSprite], m_rects[idRectPos], angle, &center, SDL_FLIP_NONE);
}

void Renderer::SetRenderDrawColor(int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
}

void Renderer::SetRenderDrawColor(const Color &c)
{
	SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, 255);
}

void Renderer::LoadScenes()
{
	switch (currentState)
	{
	case Renderer::GameState::SPLASHSCREEN:
		break;
	case Renderer::GameState::MENU:
		break;
	case Renderer::GameState::GAME:
		//TEXTURE --- INIT ---
#pragma region BACKGROUND
		LoadTexture(G_TF, pathBGcastle);
		LoadRect(SCR_R, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
		PushImage(G_IF, SCR_R);
#pragma endregion

#pragma region Animated Sprite TIMER
		LoadTexture(G_TIMER, pathNUM);
		
		int textWidth, textHeight, frameWidth, frameHeight;
		VEC2 aux = GetTextureSize(G_TIMER);
		textWidth = aux.x;
		textHeight = aux.y;
		frameWidth = textWidth / widthNUM;
		frameHeight = textHeight / heightNUM;
		LoadRect(G_TIMER_mR, { 0, 0, frameWidth * 5, frameHeight });	//decenas de segundo
		LoadRect(G_TIMER_mP, { 0, 0, frameWidth, frameHeight });
		LoadRect(G_TIMER_sR, { 0, 0, frameWidth * 9, frameHeight });		//segundos menor que 10
		LoadRect(G_TIMER_sP, { frameWidth, 0 ,frameWidth, frameHeight });
		int frameTime = 0;
#pragma endregion

#pragma region FONTS
		LoadFont({SAYAN_F, pathFONTsaiyan, 72});
		VEC2 aux = LoadTextureText(SAYAN_F, { "id", { "An SDL project is ready" }, {255,128,0},100,20 }); //falta id, texto color definidos 
		LoadRect(G_TEXT, { 100, 50, aux.x, aux.y });
#pragma endregion

#pragma region AUDIO
		Mix_Music* soundtrack{ Mix_LoadMUS(pathSOUNDTRACK) };
		if (!soundtrack)
			throw "Unable to load soundtrack";
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		Mix_PlayMusic(soundtrack, -1);
#pragma endregion

//#pragma region //  --- TIME ---  DELTATIME
//		clock_t lastTime = clock();
//		float timeDown = gameTIME; //Timer
//		float deltaTime = 0;
//#pragma endregion

			// --- GAME LOOP ---
		SDL_Event event;
#pragma region Booleans
		bool isRunning = true;
		bool escBtn = true;
#pragma endregion
		while (isRunning) {
			// HANDLE EVENTS
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN:
					escBtn = !(event.key.keysym.sym == SDLK_ESCAPE);
					break;
				default:;
				}
			}

			// UPDATE
				//FPS mode
//			frameTime++;
//			if (FPS == frameTime) // if (FPS / frameTime <= 9)//9
//			{
//				frameTime = 0;
//				secRect.x -= frameWidth;
//				if (secRect.x <= 0) { secRect.x = frameWidth * 10; minRect.x -= frameWidth; }
//			}
//#pragma region //  --- TIME --- DELTATIME
//			deltaTime = (clock() - lastTime);
//			lastTime = clock();
//			deltaTime /= CLOCKS_PER_SEC;
//			timeDown -= deltaTime;
//			if (timeDown == 0) isRunning = false;
//			std::cout << timeDown << std::endl;
//#pragma endregion

			isRunning = escBtn;

		}
		break;
	case Renderer::GameState::RANKING:
		break;
	case Renderer::GameState::EXIT:
		break;
	case Renderer::GameState::MAX:
	default:
		break;
	}

	Render();
}
