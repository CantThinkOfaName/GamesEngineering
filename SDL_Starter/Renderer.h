#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer();
	~Renderer();
	void ClearScreen();
	void renderPresent();
	void Draw(SDL_Rect *rect);
	void Draw(SDL_Texture *sprite, SDL_Rect *rect);
	void LoadAssets();
	void DrawSprite(SDL_Texture *texture, SDL_Rect rcSrc, SDL_Rect rcSprite);
	SDL_Window* GetWindow();
	SDL_Surface* GetScreenSurface();
	SDL_Renderer* GetRenderer();
	int GetScreenWidth();
private:
	SDL_Window* window;



	SDL_Surface* screenSurface;

	SDL_Renderer *ren;

	const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
};

#endif