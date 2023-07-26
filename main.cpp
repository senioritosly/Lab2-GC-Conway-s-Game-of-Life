#include <iostream>
#include <fstream>
#include <SDL.h>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 5; // Smaller cell size
const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

// Function to count the number of live neighbors for a given cell.
int countLiveNeighbors(int y, int x, int grid[GRID_HEIGHT][GRID_WIDTH]) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue; // Skip the center cell.
            }
            int newY = y + i;
            int newX = x + j;
            if (newY >= 0 && newY < GRID_HEIGHT && newX >= 0 && newX < GRID_WIDTH) {
                if (grid[newY][newX] == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Update the grid based on the rules of Conway's Game of Life.
void updateGrid(int grid[GRID_HEIGHT][GRID_WIDTH]) {
    int nextGeneration[GRID_HEIGHT][GRID_WIDTH] = {0};

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            int liveNeighbors = countLiveNeighbors(y, x, grid);
            if (grid[y][x] == 1) {
                // Any live cell with fewer than two live neighbors dies (underpopulation).
                // Any live cell with more than three live neighbors dies (overpopulation).
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    nextGeneration[y][x] = 0;
                } else {
                    nextGeneration[y][x] = 1;
                }
            } else {
                // Any dead cell with exactly three live neighbors becomes a live cell (reproduction).
                if (liveNeighbors == 3) {
                    nextGeneration[y][x] = 1;
                }
            }
        }
    }

    // Update the original grid with the next generation.
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            grid[y][x] = nextGeneration[y][x];
        }
    }
}

// Function to generate a random color in RGB format.
SDL_Color generateRandomColor() {
    SDL_Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int grid[GRID_HEIGHT][GRID_WIDTH] = {0};

    // Initialize some live cells randomly.
    std::srand(std::time(0));
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (rand() % 5 == 0) {
                grid[y][x] = 1;
            }
        }
    }

    // Initialize some live cells with the penta-decathlon pattern.
    grid[10][15] = 1;
    grid[11][15] = 1;
    grid[12][14] = 1;
    grid[12][16] = 1;
    grid[13][15] = 1;
    grid[14][15] = 1;
    grid[15][15] = 1;
    grid[16][14] = 1;
    grid[16][16] = 1;
    grid[17][15] = 1;
    grid[18][15] = 1;
    grid[19][15] = 1;

    // Initialize some live cells with the pulsar pattern.
    grid[5][3] = 1;
    grid[5][4] = 1;
    grid[5][5] = 1;
    grid[5][9] = 1;
    grid[5][10] = 1;
    grid[5][11] = 1;

    grid[7][1] = 1;
    grid[7][6] = 1;
    grid[7][8] = 1;
    grid[7][13] = 1;

    grid[8][1] = 1;
    grid[8][6] = 1;
    grid[8][8] = 1;
    grid[8][13] = 1;

    grid[9][1] = 1;
    grid[9][6] = 1;
    grid[9][8] = 1;
    grid[9][13] = 1;

    grid[10][3] = 1;
    grid[10][4] = 1;
    grid[10][5] = 1;
    grid[10][9] = 1;
    grid[10][10] = 1;
    grid[10][11] = 1;

    grid[12][3] = 1;
    grid[12][4] = 1;
    grid[12][5] = 1;
    grid[12][9] = 1;
    grid[12][10] = 1;
    grid[12][11] = 1;

    grid[13][1] = 1;
    grid[13][6] = 1;
    grid[13][8] = 1;
    grid[13][13] = 1;

    grid[14][1] = 1;
    grid[14][6] = 1;
    grid[14][8] = 1;
    grid[14][13] = 1;

    grid[15][1] = 1;
    grid[15][6] = 1;
    grid[15][8] = 1;
    grid[15][13] = 1;

    grid[17][3] = 1;
    grid[17][4] = 1;
    grid[17][5] = 1;
    grid[17][9] = 1;
    grid[17][10] = 1;
    grid[17][11] = 1;

    // Initialize some live cells with the middle-weight spaceship pattern.
    grid[30][10] = 1;
    grid[30][11] = 1;
    grid[30][12] = 1;
    grid[30][13] = 1;
    grid[31][9] = 1;
    grid[31][13] = 1;
    grid[32][13] = 1;
    grid[33][9] = 1;
    grid[33][12] = 1;

    bool isRunning = true;

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear the screen.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the grid.
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                if (grid[y][x] == 1) {
                    // Set a random color for live cells.
                    SDL_Color cellColor = generateRandomColor();
                    SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, 255);
                } else {
                    // Set the color for dead cells (black).
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                }

                // Calculate the cell's position on the screen.
                SDL_Rect cellRect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};

                // Draw the cell.
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }

        // Update the screen.
        SDL_RenderPresent(renderer);

        // Update the grid based on the rules of Conway's Game of Life.
        updateGrid(grid);

        // Add a small delay to control the frame rate.
        SDL_Delay(100); // Adjust the delay time as needed.
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
