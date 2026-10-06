#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <vector>

struct Zombia{
   short Time;
   Color color;
    Rectangle ZombiaRect;


};
Zombia NewZombia() {
    Zombia z = {
        0,
        GREEN,
        {(float)(rand() % 720), (float)(rand() % 720), 80, 80} // Ограничили 720, чтобы зомби не спавнились за краем экрана (800 - 80)
    };
    return z;

}
int main() {    srand(time(NULL));


    InitWindow(800,800,"Move Circle");
    SetTargetFPS(60);
    Vector2 player=GetMousePosition();
    std::vector<Zombia> zombias;
    int o=0;
    int HP=5;
    short time=0;
    for (int i = 0; i < 5; i++) {
        zombias.push_back(NewZombia());
    }
    while (!WindowShouldClose()) {
        player=GetMousePosition();

        BeginDrawing();
        DrawText(TextFormat("Score: %d  HP: %d ", o,HP), 20, 20, 20, RED);

        ClearBackground({155, 220, 235,94});
        for (int i = 0; i < zombias.size(); i++) {
            DrawRectangleRec(zombias[i].ZombiaRect,zombias[i].color);
            zombias[i].Time+=1;
            if (zombias[i].Time>=240) {
                zombias.erase(zombias.begin()+i);
                HP-=1;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&CheckCollisionPointRec(player,zombias[i].ZombiaRect)) {
                zombias.erase(zombias.begin()+i);
                o+=1;
            }
        }
        DrawCircleV(player,7,YELLOW);
        EndDrawing();
        time+=1;

        if (time>=80) {
            time=0;
            zombias.push_back(NewZombia());

        }

    }
    CloseWindow();
    return 0;
}