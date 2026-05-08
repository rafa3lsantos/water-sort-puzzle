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

struct Movimento {
    int origem;
    int destino;
};

enum Tela {
    MENU,
    JOGO, 
    FIM
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
    InitWindow(900, 600, "Water Sort Puzzle");
    SetTargetFPS(60);  

    Tela tela_atual = MENU;

    // =========================================================
    // 1. INICIALIZAÇÃO (Roda apenas uma vez antes do jogo abrir)
    // =========================================================
    Tubo meus_tubos[6];
    vector<int> cores = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};
    vector<Movimento> historico;

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
                meus_tubos[i].liquidos.push(cores[cont_cor++]);
            }    
        }
    }

    int id_origem = - 1;
    int id_destino = -1;   
    int cont_jogadas = 0;

    // =========================================================
    // 2. LOOP PRINCIPAL DO JOGO (Roda 60 vezes por segundo)
    // =========================================================
    while(!WindowShouldClose()) {

        // --- ATUALIZAÇÃO DE LÓGICA E INPUTS ---
        if(tela_atual == MENU) {
            if(IsKeyPressed(KEY_ENTER)) {
                tela_atual = JOGO;
            } 

            if(IsKeyPressed(KEY_ESCAPE)) {
                CloseWindow();
            }
        } 
        else if(tela_atual == JOGO) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ) {
                for(int i = 0; i < qtd_tubos; i++) {
                    if(CheckCollisionPointRec(GetMousePosition(), meus_tubos[i].corpo)) {
                        if(id_origem == -1) {
                            if(!meus_tubos[i].liquidos.empty()) {
                                id_origem = i;
                                meus_tubos[i].selecionado = true;                    
                            }
                        } else {
                            id_destino = i;
                            if(id_destino != id_origem and meus_tubos[id_destino].liquidos.size() < 4 and (meus_tubos[id_destino].liquidos.empty() or (meus_tubos[id_destino].liquidos.top() == meus_tubos[id_origem].liquidos.top()))) {
                                int cor = meus_tubos[id_origem].liquidos.top();
                                meus_tubos[id_origem].liquidos.pop();
                                meus_tubos[id_destino].liquidos.push(cor);
                                historico.push_back({id_origem, id_destino});
                                cont_jogadas++;
                            } else {
                                Rectangle r = meus_tubos[i].corpo;
                                DrawLineEx({r.x, r.y}, {r.x, r.y + r.height}, 5, RED);
                                DrawLineEx({r.x + r.width, r.y}, {r.x + r.width, r.y + r.height}, 5, RED);
                                DrawLineEx({r.x - 3, r.y + r.height}, {r.x + r.width + 2, r.y + r.height}, 8, RED);
                            }

                            meus_tubos[id_origem].selecionado = false;
                            id_origem = -1;
                            id_destino = -1;
                        }
                        break;
                    } 
                }
            }  

            if(IsKeyPressed(KEY_U) and !historico.empty()) {
                Movimento ultimo = historico.back();
                if(!meus_tubos[ultimo.destino].liquidos.empty()) {
                    int cor = meus_tubos[ultimo.destino].liquidos.top();
                    meus_tubos[ultimo.destino].liquidos.pop();
                    meus_tubos[ultimo.origem].liquidos.push(cor);
                    cont_jogadas--;
                }
                historico.pop_back();
            }
        } else if(tela_atual == FIM) {
            if(IsKeyPressed(KEY_ESCAPE)) {
                CloseWindow();
            }        
        }

        // --- DESENHO NA TELA ---
        BeginDrawing();
        ClearBackground(BLACK);

        if(tela_atual == MENU) {
            DrawText("WATER SORT", 230, 100, 60, BLUE);

            const char* txtMenu = "Pressione [ENTER] para Iniciar | [ESC] para Fechar";
            int larguraMenu = MeasureText(txtMenu, 20); // Calcula a largura do texto para centralizar
            DrawText(txtMenu, (900 / 2) - (larguraMenu / 2), 180, 20, GRAY); // Desenha no Y: 180
        } else if(tela_atual == JOGO) {
            const char* txtMovimentos = TextFormat("MOVIMENTOS: %d", cont_jogadas);
            int larguraTxt = MeasureText(txtMovimentos, 40);
            DrawText(txtMovimentos, (900/2) - (larguraTxt/2), 60, 40, GOLD);
                
            for(int i = 0; i < qtd_tubos; i++) {
                Rectangle r = meus_tubos[i].corpo;

                DrawLineEx({r.x, r.y}, {r.x, r.y + r.height}, 5, WHITE);
                DrawLineEx({r.x + r.width, r.y}, {r.x + r.width, r.y + r.height}, 5, WHITE);
                DrawLineEx({r.x - 3, r.y + r.height}, {r.x + r.width + 2, r.y + r.height}, 8, WHITE);

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
            
            const char* txtInstrucoes = "Pressione [R] para Restart | [U] para Undo";
            int larguraInst = MeasureText(txtInstrucoes, 20);
            DrawText(txtInstrucoes, (900/2) - (larguraInst/2), 540, 20, GRAY);
        } else if(tela_atual == FIM) {
            // CODIGO PARA O FIM DA TELA
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}