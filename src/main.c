#include "raylib.h"
#include "raymath.h"

#include "config.h"
#include "utils/utils.h"
#include "state/state.h"
#include "controller/controller.h"
#include "player/player.h"
#include "guys/guys.h"
#include "scenes/win.h"
#include "obstacles/obstacles.h"

#include <stdio.h>

void update(State *state, Controller controller)
{
    state->time = GetTime();

    switch (state->scene)
    {
    case Win:
        winScene(state, controller);
        break;

    case Pause:
        if (IsKeyPressed(controller.pause))
            state->scene = Play;

        break;

    default:
        if (IsKeyPressed(controller.pause))
            state->scene = Pause;
        if (state->guys.guysAlive == 0)
            state->scene = Win;

        movePlayer(&state->player, controller, *state);
        if (!TURN_OFF_GUY_MOVEMENT)
            forEachAliveGuy(state, moveGuy);
        forEachAliveGuy(state, handleGuyPlayerVisionCollision);
        forEachAliveGuy(state, handlePlayerGuyCollision);
        break;
    }
}

void draw(State state)
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (DRAW_GUY_VISION)
        forEachAliveGuy(&state, drawGuyVision);

    forEachObstacle(&state, drawObstacle, 0);

    if (state.scene == Win)
    {
        const char *winner = TextFormat("WINNER");
        int winnerSize = MeasureText(winner, 100);
        DrawText(winner, (GetScreenWidth() / 2) - (winnerSize / 2), (GetScreenHeight() / 2) - (winnerSize / 2), 100, WHITE);
    }

    if (TURN_ON_STAMINA)
        DrawText(TextFormat("boosts: %d", state.player.stamina.amount), 10, 10, 20, WHITE);

    const char *score = TextFormat("Guys: %d", state.guys.guysAlive);
    int scoreSize = MeasureText(score, 50);
    DrawText(score, (GetScreenWidth() / 2) - (scoreSize / 2), 20, 50, WHITE);

    forEachAliveGuy(&state, drawGuy);
    drawPlayer(state.player);

    if (state.scene == Pause)
    {
        DrawText("QUITATE", 50, 50, 30, WHITE);
    }

    // DrawText(TextFormat("x: %.2f y: %.2f h: %.2f w: %.2f", state.obstacles.rec[0].x, state.obstacles.rec[0].y, state.obstacles.rec[0].height, state.obstacles.rec[0].width), 5, 40, 20, WHITE);

    // DrawText(TextFormat("Position x: %.1f y: %.1f", state.player.body.position.x, state.player.body.position.y), 5, 20, 20, WHITE);
    // DrawText(TextFormat("Direction x: %.0f y: %.0f", state.player.body.direction.x, state.player.body.direction.y), 5, 40, 20, WHITE);

    // DrawText(TextFormat("colliding: %d", state.player.body.colliding), 5, 60, 20, WHITE);
    // DrawCircleV(nearestPoint, 5, RED);
    // DrawCircleV(rayToNearest, 5, ORANGE);
    // if (overlap != 4.0f)
    // {
    //     DrawText(TextFormat("overlap: %f", overlap), 5, 60, 20, WHITE);
    //     printf("overlap: %f\n", overlap);
    // }

    // DrawText(TextFormat("nearest X: %f, nearest Y: %f", nearestX, nearestY), 5, 80, 20, WHITE);

    EndDrawing();
}

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Guy Catch");
    Controller controller = initController();
    State state = initState();
    SetTargetFPS(60);

    while (!WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
    {
        update(&state, controller);
        draw(state);
    }
    CloseWindow();
    return 0;
}