#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TAMANHO_TABULEIRO = 30;

void MainPlayer(){
    const string nome = "L";
    int casa;
    
}

enum class CasaTipo
{
    Normal = 0,
    PerdeVez = 1,
    Retorna3 = 2,
    Avanca3 = 3,
    JogarDenovo = 4,
    Esperar = 5
    
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
        break;
      default: return "?";
        break;
    }

}

void ColocarCasaAleatoriamente() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    CasaTipo casas[TAMANHO_TABULEIRO];

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

        cout << "[" << NomeCasa(casas[i]) << "]";
            if ((i + 1) % 10 == 0) 
            cout << "\n";
    }
}

void CasaJogada(CasaTipo casas){
    
}

void menu() {
    cout << "Pressione Enter para lançar o dado.\n";
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

void dado() {
    int tentativa = 0;
    srand(time(0)); // semente baseada no horário atual

    while (true) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        menu();

        int numero = (rand() % 6) + 1;
        mostrarDado(numero);

        tentativa++;
        cout << "Tentativas: " << tentativa << endl;
        cout << "Pressione Enter para jogar novamente ou Ctrl + C para sair.\n";

        cin.get(); // aguarda Enter
    }
}

int main() {

    while (true)
    {
        ColocarCasaAleatoriamente();
        cin.get();
        dado(); 
    }

    return 0;
}
