#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int CELL_SIZE = SCREEN_WIDTH / 3;

enum GameState { PLAYING, WIN_X, WIN_O, DRAW };
enum CellValue { EMPTY = 0, X = 1, O = -1 };

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color textColor = {255, 0, 0, 255};  // Red color
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY) {
    const int radius = 75;
    const int segments = 100;
    SDL_Point points[101];
    
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * M_PI * i / segments;
        points[i].x = centerX + radius * cos(theta);
        points[i].y = centerY + radius * sin(theta);
    }
    
    SDL_RenderDrawLines(renderer, points, segments + 1);
}

void drawX(SDL_Renderer* renderer, int centerX, int centerY) {
    const int offset = 100;
    SDL_RenderDrawLine(renderer, centerX - offset, centerY - offset, 
                      centerX + offset, centerY + offset);
    SDL_RenderDrawLine(renderer, centerX - offset, centerY + offset, 
                      centerX + offset, centerY - offset);
}

GameState checkGameState(const int grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] != EMPTY && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return (grid[i][0] == X) ? WIN_X : WIN_O;
        if (grid[0][i] != EMPTY && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
            return (grid[0][i] == X) ? WIN_X : WIN_O;
    }
    
    if (grid[1][1] != EMPTY) {
        if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
            return (grid[1][1] == X) ? WIN_X : WIN_O;
        if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
            return (grid[1][1] == X) ? WIN_X : WIN_O;
    }
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == EMPTY)
                return PLAYING;
                
    return DRAW;
}

void drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i < 3; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0) {
        cerr << "Initialization failed: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tic-tac-toe", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("font.ttf", 48);
    if (!font) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
        return 1;
    }

    int grid[3][3] = {0};
    bool isXTurn = true;
    GameState gameState = PLAYING;
    bool running = true;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    drawGrid(renderer);
    SDL_RenderPresent(renderer);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && gameState == PLAYING) {
                int x = event.button.x / CELL_SIZE;
                int y = event.button.y / CELL_SIZE;
                
                if (grid[x][y] == EMPTY) {
                    grid[x][y] = isXTurn ? X : O;
                    int centerX = (x * CELL_SIZE) + (CELL_SIZE / 2);
                    int centerY = (y * CELL_SIZE) + (CELL_SIZE / 2);
                    
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    if (isXTurn)
                        drawX(renderer, centerX, centerY);
                    else
                        drawCircle(renderer, centerX, centerY);
                        
                    gameState = checkGameState(grid);
                    if (gameState != PLAYING) {
                        const char* result = gameState == WIN_X ? "X wins!" :
                                          gameState == WIN_O ? "O wins!" : "Draw!";
                        renderText(renderer, font, result, SCREEN_WIDTH/2 - 100, 10);
                    }
                    
                    SDL_RenderPresent(renderer);
                    isXTurn = !isXTurn;
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                fill(&grid[0][0], &grid[0][0] + 9, EMPTY);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                drawGrid(renderer);
                SDL_RenderPresent(renderer);
                gameState = PLAYING;
                isXTurn = true;
            }
        }
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}