#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()

#define WIDTH 20
#define HEIGHT 10

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point body[WIDTH * HEIGHT];
    int length;
    Point direction;
} Snake;

void drawBoard(Snake snake, Point fruit) {
    system("cls"); // Clear the screen on Windows
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                printf("#");
            } else if (x == fruit.x && y == fruit.y) {
                printf("*");
            } else {
                int printed = 0;
                for (int i = 0; i < snake.length; i++) {
                    if (snake.body[i].x == x && snake.body[i].y == y) {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }
                if (!printed) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void moveSnake(Snake* snake) {
    Point prev = snake->body[0];
    Point prev2;
    snake->body[0].x += snake->direction.x;
    snake->body[0].y += snake->direction.y;
    for (int i = 1; i < snake->length; i++) {
        prev2 = snake->body[i];
        snake->body[i] = prev;
        prev = prev2;
    }
}

int checkCollision(Snake snake) {
    // Check collision with walls
    if (snake.body[0].x == 0 || snake.body[0].x == WIDTH - 1 ||
        snake.body[0].y == 0 || snake.body[0].y == HEIGHT - 1) {
        return 1;
    }

    // Check collision with self
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x &&
            snake.body[0].y == snake.body[i].y) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Snake snake;
    Point fruit;
    int gameOver = 0;
    int key;

    // Initialize snake
    snake.length = 1;
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
    snake.direction.x = 1;
    snake.direction.y = 0;

    // Initialize fruit
    fruit.x = rand() % (WIDTH - 2) + 1;
    fruit.y = rand() % (HEIGHT - 2) + 1;

    while (!gameOver) {
        drawBoard(snake, fruit);

        if (_kbhit()) {
            key = _getch();
            switch (key) {
                case 'a': // Left
                    if (snake.direction.x == 0) {
                        snake.direction.x = -1;
                        snake.direction.y = 0;
                    }
                    break;
                case 'd': // Right
                    if (snake.direction.x == 0) {
                        snake.direction.x = 1;
                        snake.direction.y = 0;
                    }
                    break;
                case 'w': // Up
                    if (snake.direction.y == 0) {
                        snake.direction.x = 0;
                        snake.direction.y = -1;
                    }
                    break;
                case 's': // Down
                    if (snake.direction.y == 0) {
                        snake.direction.x = 0;
                        snake.direction.y = 1;
                    }
                    break;
            }
        }

        moveSnake(&snake);

        if (snake.body[0].x == fruit.x && snake.body[0].y == fruit.y) {
            snake.length++;
            fruit.x = rand() % (WIDTH - 2) + 1;
            fruit.y = rand() % (HEIGHT - 2) + 1;
        }

        gameOver = checkCollision(snake);

        Sleep(100); // Adjust speed here
    }

    printf("Game Over!\n");
    return 0;
}
