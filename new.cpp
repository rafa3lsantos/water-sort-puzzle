#include "raylib.h"

int main() {
    // 1. Inicialização
    const int larguraTela = 900;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Meu Primeiro Teste Raylib");
    SetTargetFPS(60); // Crava o jogo em 60 quadros por segundo

    // Variáveis que guardam a posição da bola
    float posicaoX = larguraTela / 2.0f; // Começa no meio da tela
    float posicaoY = alturaTela / 2.0f;

    // 2. O Loop Principal do Jogo (roda 60 vezes por segundo)
    while (!WindowShouldClose()) { 
        
        // --- PARTE 1: LÓGICA (UPDATE) ---
        // Altera a posição baseada na tecla pressionada
        if (IsKeyDown(KEY_RIGHT)) posicaoX += 50.0f;
        if (IsKeyDown(KEY_LEFT))  posicaoX -= 50.0f;
        if (IsKeyDown(KEY_UP))    posicaoY -= 50.0f;
        if (IsKeyDown(KEY_DOWN))  posicaoY += 50.0f;

        // --- PARTE 2: DESENHO (DRAW) ---
        BeginDrawing();
        
            ClearBackground(RAYWHITE); // Limpa o rastro da bola anterior
            // Desenha um bloco de "água" azul
            DrawRectangle(100, 200, 40, 30, BLUE);

            Rectangle tubo = { 100, 100, 50, 150 };
            DrawRectangleLinesEx(tubo, 3, BLACK); // Borda do tubo com 3 pixels de largura
            
            // Desenha instruções na tela (Texto, x, y, tamanho, cor)
            DrawText("Mova a bolinha com as setas do teclado!", posicaoX, posicaoY, 20, RED);
            
            // Desenha a bola na posição X e Y atuais
            DrawCircle(posicaoX, posicaoY, 40.0f, MAROON); 
            
        EndDrawing();
    }

    // 3. Finalização
    CloseWindow(); // Fecha a janela e libera a memória
    return 0;
}