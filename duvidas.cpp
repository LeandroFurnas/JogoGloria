#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TAMANHO_TABULEIRO = 30;

// Primeiro declare o enum, depois o array
enum class CasaTipo
{
    Normal = 0,
    PerdeVez = 1,
    Retorna3 = 2,
    Avanca3 = 3,
    JogarDenovo = 4,
    Esperar = 5
};

// Agora declare o array
CasaTipo casas[TAMANHO_TABULEIRO];

struct jogador
{
    string nome;
    int posicao;
};

string NomeCasa(CasaTipo c){
    switch (c)
    {
    case CasaTipo::Normal: return "N ";
    case CasaTipo::PerdeVez: return "PV";
    case CasaTipo::Retorna3: return "R3";
    case CasaTipo::Avanca3: return "A3";
    case CasaTipo::JogarDenovo: return "JN";
    case CasaTipo::Esperar: return "E ";
    default: return "?";
    }
}

void ColocarCasaAleatoriamente() {
    srand(time(NULL));

    // Inicializa todas as casas como normais
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        casas[i] = CasaTipo::Normal;
    }

    // Define casas especiais aleatoriamente
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if ((i + 1) % 6 == 0) { //a cada 6
            int tipo = (rand() % 5) + 1; // rand de 0-5
            casas[i] = static_cast<CasaTipo>(tipo);
        }
    }
}

void MostrarTabuleiroComJogador(const jogador& jogador) {
    cout << "\n=== TABULEIRO ===\n";
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (i == jogador.posicao) {
            cout << "[J]"; // Mostra o jogador
        } else {
            cout << "[" << NomeCasa(casas[i]) << "]";
        }
        
        if ((i + 1) % 10 == 0) 
            cout << "\n";
    }
    cout << "=================\n";
}

void menu() {
    cout << "Pressione Enter para lancar o dado.\n";
    cout << "=========================================\n";
}

void mostrarDado(int numero) {
    cout << "=========================================\n";
    cout << "          Gira o dado para andares!    \n";
    cout << "=========================================\n";
    cout << "Resultado do dado: " << numero << endl;
    cout << "=================\n";
    switch (numero) {
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

int LancarDado() {
    return (rand() % 6) + 1;
}

void MoverJogador(jogador& jogador, int resultadoDado) {
    int novaPosicao = jogador.posicao + resultadoDado;
    
    // Verifica se chegou ao final
    if (novaPosicao >= TAMANHO_TABULEIRO) {
        jogador.posicao = TAMANHO_TABULEIRO - 1;
        cout << jogador.nome << " chegou ao final!\n";
        return;
    }
    
    jogador.posicao = novaPosicao;
    
    // Verifica o tipo da casa
    CasaTipo casaAtual = casas[jogador.posicao];
    cout << jogador.nome << " caiu na casa: " << NomeCasa(casaAtual) << "\n";
    
    // Aplica efeitos da casa
    switch (casaAtual) {
        case CasaTipo::Avanca3:
            jogador.posicao += 3;
            if (jogador.posicao >= TAMANHO_TABULEIRO) {
                jogador.posicao = TAMANHO_TABULEIRO - 1;
            }
            cout << "Avancou 3 casas!\n";
            break;
            
        case CasaTipo::Retorna3:
            jogador.posicao -= 3;
            if (jogador.posicao < 0) {
                jogador.posicao = 0;
            }
            cout << "Retornou 3 casas!\n";
            break;
            
        case CasaTipo::PerdeVez:
            cout << "Perde a vez!\n";
            break;
            
        case CasaTipo::JogarDenovo:
            cout << "Joga novamente!\n";
            break;
            
        case CasaTipo::Esperar:
            cout << "Espera 1 rodada!\n";
            break;
            
        default:
            break;
    }
}

void JogarTurno(jogador& jogador) {
    menu();
    
    int resultadoDado = LancarDado();
    mostrarDado(resultadoDado);
    
    MoverJogador(jogador, resultadoDado);
    
    cout << "Nova posicao: " << jogador.posicao << "\n";
}

int main() {
    srand(time(0));
    
    // Criar jogador
    jogador jogador;
    cout << "Digite o nome do jogador: ";
    cin >> jogador.nome;
    jogador.posicao = 0;
    
    // Inicializar tabuleiro
    ColocarCasaAleatoriamente();
    
    int rodada = 1;
    
    while (jogador.posicao < TAMANHO_TABULEIRO - 1) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        
        cout << "=== RODADA " << rodada << " ===\n";
        cout << "Jogador: " << jogador.nome << "\n";
        cout << "Posicao atual: " << jogador.posicao << "\n";
        
        MostrarTabuleiroComJogador(jogador);
        
        cout << "\nPressione Enter para lancar o dado...";
        cin.ignore();
        cin.get();
        
        JogarTurno(jogador);
        
        if (jogador.posicao >= TAMANHO_TABULEIRO - 1) {
            cout << "\n🎉 PARABENS! " << jogador.nome << " VENCEU O JOGO! 🎉\n";
            break;
        }
        
        cout << "\nPressione Enter para continuar...";
        cin.get();
        
        rodada++;
    }
    
    return 0;
}
