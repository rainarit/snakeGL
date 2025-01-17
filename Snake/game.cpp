//
//  game.cpp
//  SnakeGL
//
//  Created by Ritik Raina on 12/24/19.
//  Copyright © 2019 rraina. All rights reserved.
//

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#include <ctime>
#include <stdlib.h>
#include "game.hpp"

int gridX;
int gridY;

int snakeLength = 5;

short snakeDirection = RIGHT;

extern bool gameOver;

extern int FPS;

extern int score;

bool food = true;
int foodX;
int foodY;

int positionX[60] = {25, 24, 23, 22, 21};
int positionY[60] = {25, 24, 23, 22, 21};

// Creating a grid
void initGrid(int x, int y) {
    gridX = x;
    gridY = y;
}

// Draw a simple square based on drawGrid()
void unit(int x, int y) {
    if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) {
        // Setting the color /thickness of the line
        glLineWidth(2.0);
        glColor3f(1.0, 0.0, 0.0);
    }
    else {
        glLineWidth(1.0);
        glColor3f(1.0, 1.0, 1.0);
    }
    
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y); // Vertex 1
        glVertex2f(x+1, y); // Vertex 2
        glVertex2f(x+1, y+1); // Vertex 3
        glVertex2f(x, y+1); // Vertex 4
    glEnd();
}

void drawGrid() {
    for (int i = 0; i < gridX; i++) {
        for (int j = 0; j < gridY; j++) {
            unit(i, j);
        }
    }
}

void drawSnake() {
    for (int i = snakeLength - 1; i > 0; i--) {
        positionX[i] = positionX[i-1];
        positionY[i] = positionY[i-1];
    }
    if (snakeDirection == UP) {
        positionY[0]++;
    }
    else  if (snakeDirection == DOWN) {
        positionY[0]--;
    }
    else if (snakeDirection == LEFT) {
        positionX[0]--;
    }
    else if (snakeDirection == RIGHT) {
        positionX[0]++;
    }
    for (int i = 0; i < snakeLength; i++) {
        if (i == 0) {
            glColor3f(0.0, 0.0, 1.0);
        }
        else {
            glColor3f(i*0.05, i*0.5, i*0.05);
        }
        glRectd(positionX[i], positionY[i], positionX[i]+1, positionY[i]+1);
    }
    if (positionX[0] <= 0 || positionX[0] >= gridX || positionY[0] <= 0 || positionY[0] >= gridY) {
        if (positionX[0] < 0) {
            positionX[0] = gridX;
        }
        else if (positionX[0] >= gridX) {
            positionX[0] = 0;
        }
        else if (positionY[0] < 0) {
            positionY[0] = gridY;
        }
        else if (positionY[0] >= gridY) {
            positionY[0] = 0;
        }
    }
    for (int i = snakeLength - 1; i > 0; i--) {
        
        if (positionX[0] == positionX[i] && positionY[0] == positionY[i]) {
            gameOver = true;
        }
    }
    if (positionX[0] == foodX && positionY[0] == foodY) {
        score++;
        snakeLength++;
        if(snakeLength > MAX) {
            snakeLength = MAX;
        }
        food = true;
    }
}

void randomize(int &x, int &y) {
    int _maxX = gridX - 2;
    int _maxY = gridY - 2;
    int _min = 1;
    srand(time(NULL));
    x = _min + rand() % (_maxX - _min);
    y = _min + rand() % (_maxY - _min);
}

void drawFood() {
    if (food == true) {
        randomize(foodX, foodY);
    }
    food = false;
    glColor3f(1.0, 1.0, 0.0);
    glRectf(foodX, foodY, foodX+1, foodY+1);
}
