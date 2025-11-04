#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TAMANHO_TABULEIRO = 30;

const int CasaNormal    = 0;
const int CasaPerdeVida = 1;
const int CasaRetorna3  = 2;
const int CasaAvanca3   = 3;
const int CasaJogar     = 4;
const int CasaEsperar   = 5;

void ColocarCasaAleatoriamente() {
    srand(time(0));

    int tabuleiro[TAMANHO_TABULEIRO + 1];

    // 1️⃣ Inicializa todas as casas como normais
    for (int i = 1; i <= TAMANHO_TABULEIRO; i++) {
        tabuleiro[i] = CasaNormal;
    }

    // 2️⃣ Sorteia posições únicas para as casas especiais
    int posPerdeVida = rand() % TAMANHO_TABULEIRO + 1;
    int posRetorna3  = rand() % TAMANHO_TABULEIRO + 1;
    int posAvanca3   = rand() % TAMANHO_TABULEIRO + 1;
    int posJogar     = rand() % TAMANHO_TABULEIRO + 1;
    int posEsperar   = rand() % TAMANHO_TABULEIRO + 1;

    // Garante que não repita posições
    while (posRetorna3 == posPerdeVida)
        posRetorna3 = rand() % TAMANHO_TABULEIRO + 1;
    while (posAvanca3 == posPerdeVida || posAvanca3 == posRetorna3)
        posAvanca3 = rand() % TAMANHO_TABULEIRO + 1;
    while (posJogar == posPerdeVida || posJogar == posRetorna3 || posJogar == posAvanca3)
        posJogar = rand() % TAMANHO_TABULEIRO + 1;
    while (posEsperar == posPerdeVida || posEsperar == posRetorna3 ||
           posEsperar == posAvanca3 || posEsperar == posJogar)
        posEsperar = rand() % TAMANHO_TABULEIRO + 1;

    // 3️⃣ Define as casas especiais
    tabuleiro[posPerdeVida] = CasaPerdeVida;
    tabuleiro[posRetorna3]  = CasaRetorna3;
    tabuleiro[posAvanca3]   = CasaAvanca3;
    tabuleiro[posJogar]     = CasaJogar;
    tabuleiro[posEsperar]   = CasaEsperar;

    // 4️⃣ Mostra o tabuleiro
    for (int i = 1; i <= TAMANHO_TABULEIRO; i++) {
        switch (tabuleiro[i]) {
            case CasaNormal:    cout << "[ ]";  break;
            case CasaPerdeVida: cout << "[☠]";  break;
            case CasaRetorna3:  cout << "[↩]";  break;
            case CasaAvanca3:   cout << "[→]";  break;
            case CasaJogar:     cout << "[🎲]";  break;
            case CasaEsperar:   cout << "[⏳]";  break;
        }

        if (i % 10 == 0) cout << "\n"; // quebra de linha a cada 10 casas
    }
}

int main() {
    ColocarCasaAleatoriamente();
    return 0;
}
