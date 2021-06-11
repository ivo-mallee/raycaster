/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/



#include "raylib.h"
#include <math.h>
float rayangle[4000];
float PlayerAngle =0;
float rayX[4000];
float rayY[4000];
int rayCoordXnumber[4000];
int raylength[4000];
float rayamount =800;
bool RayAlive[4000];
float FOV = 40;
float FOVDSF =0;
float FOVSTEP;
int MaxWallSize = 100;
int xoffset =0;
int screenmiddle = 225;

int worldMap[24][24]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};
float playerX = 10;
float playerY = 10;

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {


            BeginDrawing();

            ClearBackground(BLACK);
            resetRays();
            for (int i=0; i<rayamount;i++){handleRays(i);}
            checkInput();
            EndDrawing();
        
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

      return 0;
}



void drawMap() 
{
    for (int x =0; x<24;x++) 
    {
        for (int y =0; y<24;y++) 
        {
            if (worldMap[x][y] == 1) {DrawRectangle(x*10,y*10,10,10,PINK);}
            if (worldMap[x][y] == 2) {DrawRectangle(x*10,y*10,10,10,YELLOW);}
            if (worldMap[x][y] == 3) {DrawRectangle(x*10,y*10,10,10,GREEN);}
            if (worldMap[x][y] == 4) {DrawRectangle(x*10,y*10,10,10,SKYBLUE);}
            if (worldMap[x][y] == 5) {DrawRectangle(x*10,y*10,10,10,PURPLE);}
            if (worldMap[x][y] == 6) {DrawRectangle(x*10,y*10,10,10,BEIGE);}
            if (worldMap[x][y] == 7) {DrawRectangle(x*10,y*10,10,10,DARKBLUE);}
            if (worldMap[x][y] == 8) {DrawRectangle(x*10,y*10,10,10,DARKPURPLE);}
            if (worldMap[x][y] == 9) {DrawRectangle(x*10,y*10,10,10,DARKBROWN);}
            if (worldMap[x][y] == 10) {DrawRectangle(x*10,y*10,10,10,VIOLET);}

        }
    }

}

void drawPlayer() 
{
int integerX = (int) (playerX *10);
int integerY = (int) (playerY *10);
int lineX = integerX +cos(PlayerAngle)*20;
int lineY = integerY +sin(PlayerAngle)*20;

DrawCircle(integerX,integerY,5,RED);
DrawLine(integerX,integerY,lineX,lineY,RED);
}

void checkInput() 
{
        if (IsKeyDown(KEY_RIGHT)) {
            PlayerAngle+=0.1;
                                }
        if (IsKeyDown(KEY_LEFT)) {
            PlayerAngle-=0.1;
                                 }
        if (IsKeyDown(KEY_UP)) {
            moveplayerup();
                                 }
        if (IsKeyDown(KEY_M)) {
            drawMap();
            drawPlayer();
            }
        if (IsKeyDown(KEY_TAB)) 
        {
            FOV++;
        }

        if (IsKeyDown(KEY_BACKSPACE)) 
        {
            FOV--;
        }


}

void moveplayerup() 
{
    playerY += sin(PlayerAngle)*0.5;
    playerX += cos(PlayerAngle)*0.5;

}

void resetRays() 
{
    FOVDSF =0;
    FOVSTEP = FOV/rayamount;     
    for (int i=0; i<rayamount;i++) 
    {
        rayCoordXnumber[i] = i;
        rayX[i] = playerX;
        rayY[i] = playerY;
        raylength[i] = 0;
        RayAlive[i] = true;
        rayangle[i] = PlayerAngle +(FOVDSF+FOVSTEP-FOV/2) * PI/180;
        FOVDSF += FOVSTEP;
    }
}
void handleRays(int selection) 
{
    rayX[selection] = playerX;
    rayY[selection] = playerY;
    int lifetime =0;
    bool valid = true;
    while (true) 
    {
        lifetime++;
        rayX[selection] += cos(rayangle[selection]) *0.1;
        rayY[selection] += sin(rayangle[selection]) *0.1;
        if (lifetime > 300) {valid =false; break;}
        if (worldMap[(int)rayX[selection]][(int)rayY[selection]] != 0) {break;}        
    }
    if (valid) {
    //DrawCircle(rayX[selection]*10,rayY[selection]*10,2,RED);
    //DrawLine(playerX*10,playerY*10,rayX[selection]*10,rayY[selection]*10,BLUE);
    float distance = sqrt(pow((rayX[selection]-playerX),2) + pow((rayY[selection]-playerY),2));
    //float distance = raylength[selection];
 
     
            distance *= cos(rayangle[selection]-PlayerAngle)*4;

    distance *=2;
    
    
    Color linecol = BLUE;
    switch (worldMap[(int)rayX[selection]][(int)rayY[selection]]) {  
    case 1:
      linecol = PINK;
      break;

    case 2:
      linecol = YELLOW;
      break;
    case 3:
      linecol = GREEN;
      break;
    case 4:
      linecol = SKYBLUE;
      break;
    case 5:
      linecol = PURPLE;
      break;
    case 6:
      linecol = BEIGE;
      break;
    case 7:
      linecol = DARKBLUE;
      break;
    case 8:
      linecol = DARKPURPLE;
      break;
    case 9:
      linecol = DARKBROWN;
      break;
    case 10:
      linecol = VIOLET;
      break;
    }

    int wallsize = (MaxWallSize-(int)distance);
    wallsize /= 2;
    if (wallsize <= 0) {wallsize=1;}
    DrawLine(xoffset+rayCoordXnumber[selection],screenmiddle+wallsize,xoffset+rayCoordXnumber[selection],screenmiddle-wallsize,linecol);
    }
}