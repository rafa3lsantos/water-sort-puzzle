#include <iostream>
#include "raylib.h"
#include <vector>
#include <algorithm>
#include <stack>
#include <random>
using namespace std;

struct Tubo {
    Rectangle corpo;
    stack<int> liquidos;
    int capacidade = 4;
    bool selecionado;
};

Color ObterCor(int cor) {
    switch(cor) {
        case 1: return BLUE;
        case 2: return RED;
        case 3: return GREEN;
        case 4: return YELLOW;
        default: return BLANK;
    }
}

int main() {
    InitWindow(900, 600, "Rafaela, menina do Bobs");
    SetTargetFPS(60);
    
    Tubo meus_tubos[6];
    vector<int> cores = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};

    float largura_tubo = 60.0;
    float altura_tubo = 200.0;
    float espessura_tubo = 3.0;


    random_device rd; // gera uma semente baseada no hw
    mt19937 motor(rd()); // motor matemático
    shuffle(cores.begin(), cores.end(), motor); // embaralha o vetor
       
    int cont_cor = 0;   
    int qtd_tubos = sizeof(meus_tubos) / sizeof(meus_tubos[0]);        

    for(int i = 0; i < qtd_tubos; i++) {
        meus_tubos[i].corpo = {(50.0f + (i * 150.0f)), 200.0f, 60.0f, 200.0f};
        if(i < 4) {
            for(int j = 0; j < 4; j++) {
                // CORREÇÃO 1: Pilha usa push() em vez de push_back()
                meus_tubos[i].liquidos.push(cores[cont_cor++]);
            }    
        }
    }

    while(!WindowShouldClose()) {
        BeginDrawing();
            
        ClearBackground(BLACK);
           
        for(int i = 0; i < qtd_tubos; i++) {
            Rectangle r = meus_tubos[i].corpo;

            DrawLineEx({r.x, r.y}, {r.x, r.y + r.height}, 3, WHITE);
            DrawLineEx({r.x + r.width, r.y}, {r.x + r.width, r.y + r.height}, 3, WHITE);
            DrawLineEx({r.x, r.y + r.height}, {r.x + r.width, r.y + r.height}, 3, WHITE);

            stack<int> copia_pilha = meus_tubos[i].liquidos;
            int tamanho = copia_pilha.size();
            float altura_camada = r.height / 4;

                        
            for(int j = tamanho; j > 0; j--) {
                int cor_topo = copia_pilha.top();
                copia_pilha.pop();

                DrawRectangle(r.x + 1, (r.y + r.height) - (altura_camada * j), r.width - 3, altura_camada, ObterCor(cor_topo));
            }
        }

        Vector2 m = GetMousePosition();
        DrawCircleV(m, 5, GOLD); // Uma pequena bolinha no cursor
        DrawText(TextFormat("X: %0.0f, Y: %0.0f", m.x, m.y), m.x + 10, m.y + 10, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}