#include "raylib.h"

int main() {
    InitWindow(900, 600, "Laboratorio de Funcoes Raylib");
    SetTargetFPS(60);

    // Definindo um "tubo" como um retângulo
    Rectangle tubo01 = { 100, 150, 60, 200 };
    Color corTubo = BLACK;

    while (!WindowShouldClose()) {
        // --- Lógica ---
        // Se clicar com o botão esquerdo e o mouse estiver sobre o tubo
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), tubo01)) {
                corTubo = MAROON; // Muda a cor se clicar no tubo
            } else {
                corTubo = BLACK;  // Reseta se clicar fora
            }
        }

        // --- Desenho ---
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
        
            DrawText("Clique no tubo para mudar a cor da borda!", 20, 20, 20, DARKGRAY);

            // Desenha o "líquido" (Pilha estática para teste)
            DrawRectangle(tubo01.x + 5, tubo01.y + 160, 50, 35, BLUE);
            DrawRectangle(tubo01.x + 5, tubo01.y + 125, 50, 35, RED);

            DrawLine(100, 500, 200, 800, RED);

            // Desenha a borda do tubo
            DrawRectangleLinesEx(tubo01, 4, corTubo);

            // Desenha a posição do mouse para você entender as coordenadas
            Vector2 m = GetMousePosition();
            DrawCircleV(m, 5, GOLD); // Uma pequena bolinha no cursor
            DrawText(TextFormat("X: %0.0f, Y: %0.0f", m.x, m.y), m.x + 10, m.y + 10, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}