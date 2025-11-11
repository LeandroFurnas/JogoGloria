#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // para usleep
#include <vector>
#include <string>
using namespace std;

const int TAM = 30;

enum CasaTipo {
    Normal = 0,
    PerdeVez,
    Retorna3,
    Avanca3,
    JogarDenovo,
    Esperar
};

CasaTipo casas[TAM];

struct Jogador {
    string nome;
    string cor;
    int pos;
    bool perdeVez;
    int pontos;
};

string NomeCasa(CasaTipo c) {
    switch (c) {
    case Normal: return "N ";
    case PerdeVez: return "PV";
    case Retorna3: return "R3";
    case Avanca3: return "A3";
    case JogarDenovo: return "JN";
    case Esperar: return "E ";
    default: return "??";
    }
}

void waitEnter() {
    string tmp;
    getline(cin, tmp);
}

void CriarCasas() {
    for (int i = 0; i < TAM; i++) casas[i] = Normal;

    vector<int> posicoes;
    for (int i = 0; i < TAM; i++) {
        if ((i + 1) % 6 == 0) posicoes.push_back(i);
    }

    vector<int> tipos = {1,2,3,4,5};

    int nDisponiveis = (int)posicoes.size();
    int nParaGarantir = (nDisponiveis >= 5) ? 5 : nDisponiveis;

    for (int i = 0; i < nDisponiveis; ++i) {
        int j = rand() % nDisponiveis;
        int tmp = posicoes[i];
        posicoes[i] = posicoes[j];
        posicoes[j] = tmp;
    }

    for (int i = 0; i < 5; ++i) {
        int j = rand() % 5;
        int tmp = tipos[i];
        tipos[i] = tipos[j];
        tipos[j] = tmp;
    }

    for (int k = 0; k < nParaGarantir; ++k) {
        int idxPos = posicoes[k];
        int tipo = tipos[k];
        casas[idxPos] = (CasaTipo)tipo;
    }

    for (int k = nParaGarantir; k < nDisponiveis; ++k) {
        int idxPos = posicoes[k];
        int tipoAleatorio = (rand() % 5) + 1;
        casas[idxPos] = (CasaTipo)tipoAleatorio;
    }
}

void MostrarTabuleiro(const Jogador &j1, const Jogador &j2) {
    cout << "\n    TABULEIRO \n";
    for (int i = 0; i < TAM; i++) {
        if (i == j1.pos)
            cout << "[" << j1.cor << "J" << "\033[0m]";
        else if (i == j2.pos)
            cout << "[" << j2.cor << "J" << "\033[0m]";
        else
            cout << "[" << NomeCasa(casas[i]) << "]";
        if ((i + 1) % 10 == 0)
            cout << "\n";
    }
    cout << "\n";

    cout << "\nPONTUAÇÃO:\n";
    cout << j1.cor << j1.nome << "\033[0m: " << j1.pontos << " Casas\n";
    cout << j2.cor << j2.nome << "\033[0m: " << j2.pontos << " Casas\n\n";
}

void MostrarDado(int valor) {
    cout << "=================\n";
    cout << "   RESULTADO: " << valor << "\n";
    cout << "=================\n";

    switch (valor) {
    case 1:
        cout << "|             |\n";
        cout << "|      O      |\n";
        cout << "|             |\n";
        break;
    case 2:
        cout << "|   O         |\n";
        cout << "|             |\n";
        cout << "|         O   |\n";
        break;
    case 3:
        cout << "|   O         |\n";
        cout << "|      O      |\n";
        cout << "|         O   |\n";
        break;
    case 4:
        cout << "|   O     O   |\n";
        cout << "|             |\n";
        cout << "|   O     O   |\n";
        break;
    case 5:
        cout << "|   O     O   |\n";
        cout << "|      O      |\n";
        cout << "|   O     O   |\n";
        break;
    case 6:
        cout << "|   O     O   |\n";
        cout << "|   O     O   |\n";
        cout << "|   O     O   |\n";
        break;
    }
    cout << "=================\n";
}

int AnimarDado() {
    int valor = 1;
    for (int i = 0; i < 8; i++) {
        valor = (rand() % 6) + 1;
        system("clear");
        MostrarDado(valor);
        usleep(100000); // substituindo Sleep(100)
    }

    system("clear");
    MostrarDado(valor);

    cout << "\nPressione Enter para continuar...";
    waitEnter();
    return valor;
}

void Mover(Jogador &j, int valor) {
    int posInicial = j.pos;

    j.pos += valor;
    if (j.pos >= TAM) {
        j.pos = TAM - 1;
    }

    CasaTipo c = casas[j.pos];
    cout << j.cor << j.nome << "\033[0m" << " caiu na casa " << NomeCasa(c) << "\n";

    switch (c) {
        case Avanca3:
            j.pos += 3;
            if (j.pos >= TAM) j.pos = TAM - 1;
            cout << "Avancou 3 casas!\n";
            break;

        case Retorna3:
            j.pos -= 3;
            if (j.pos < 0) j.pos = 0;
            cout << "Retornou 3 casas!\n";
            break;

        case PerdeVez:
            j.perdeVez = true;
            cout << "Vai perder a proxima vez!\n";
            break;

        case JogarDenovo:
            j.perdeVez = false;
            cout << "Vai jogar de novo!\n";
            break;

        case Esperar:
            j.perdeVez = true;
            cout << "Vai esperar uma rodada!\n";
            break;

        default:
            break;
    }

    int avancou = j.pos - posInicial;
    if (avancou < 0) avancou = -avancou;

    j.pontos += avancou;

    cout << "Posicao final: " << j.pontos << "\n";
    cout << "Pontuacao adicionada: " << avancou << "\n";
}

int main() {
    srand((unsigned int)time(NULL));

    Jogador azul = {"Azul", "\033[34m", 0, false, 1};
    Jogador vermelho = {"Vermelho", "\033[31m", 0, false, 1};

    CriarCasas();

    int rodada = 1;

    while (true) {
        system("clear");
        cout << "    RODADA " << rodada << " \n";
        MostrarTabuleiro(azul, vermelho);

        if (!azul.perdeVez) {
            cout << azul.cor << azul.nome << "\033[0m, pressione Enter para jogar...";
            waitEnter();
            int r = AnimarDado();
            MostrarDado(r);
            Mover(azul, r);
        } else {
            cout << azul.nome << " esta a perder a vez...\n";
            azul.perdeVez = false;
            usleep(1000000); // substituindo Sleep(1000)
        }

        if (azul.pos >= TAM - 1) {
            cout << azul.nome << " ganhou!\n";
            break;
        }

        usleep(500000); // substituindo Sleep(500)
        system("clear");
        MostrarTabuleiro(azul, vermelho);

        if (!vermelho.perdeVez) {
            cout << vermelho.cor << vermelho.nome << "\033[0m, pressione Enter para jogar...";
            waitEnter();
            int r = AnimarDado();
            MostrarDado(r);
            Mover(vermelho, r);
        } else {
            cout << vermelho.nome << " esta a perder a vez...\n";
            vermelho.perdeVez = false;
            usleep(1000000); // substituindo Sleep(1000)
        }

        if (vermelho.pos >= TAM - 1) {
            cout << vermelho.nome << " ganhou!\n";
            break;
        }

        usleep(1500000); // substituindo Sleep(1500)
        rodada++;
    }

    cout << "\nFim de jogo. Prima Enter para fechar...";
    waitEnter();
    return 0;
}
 
