#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TAMANHO_TABULEIRO = 30;
const int CasaNormal = 0;
const int CasaPerdeVida = 1;
const int CasaRetorna3 = 2;
const int CasaAvanca3 = 3;
const int CasaJogar = 4;
const int CasaEsperar = 5;

void ColocarCasaAleatoriamente(){
    srand(time(0));
    for (int i = 1; i <= TAMANHO_TABULEIRO; i++) {
        cout << "[ ]";
        if (i % 10 == 0){ cout << "\n";

     
       
} 
    cout << "\n";
}
}

void exibirCabecalho() {
    cout << "=========================================\n";
    cout << "          Jogo de Lançamento de Dados    \n";
    cout << "=========================================\n";
}

void menu() {
    cout << "Pressione Enter para lançar o dado.\n";
    cout << "=========================================\n";
}

void mostrarDado(int numero) {
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

        exibirCabecalho();
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
        ColocarCasaAleatoriamente();
    exibirCabecalho();
    dado();

    return 0;
}
