#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "../include/models/Produto.hpp"
#include "../include/models/Vendedor.hpp"
#include "../include/models/Comprador.hpp"
#include "../include/models/Venda.hpp"
#include "../include/ui/Menu.hpp"
#include "../include/services/Servicos.hpp"

using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(0)));

    vector<Produto> listaDeProdutos;
    vector<Vendedor> listaDeVendedores;
    vector<Comprador> listaDeCompradores;
    vector<Venda> listaDeVendas;

    int opcao;

    do {
        exibirMenuPrincipal();
        cin >> opcao;

        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, digite um numero.\n";
            cin.clear();
            limparBuffer();
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                menuProdutos(listaDeProdutos);
                break;
            case 2:
                menuVendedores(listaDeVendedores);
                break;
            case 3:
                menuCompradores(listaDeCompradores);
                break;
            case 4:
                menuVendas(listaDeVendas, listaDeVendedores, listaDeCompradores, listaDeProdutos);
                break;
            case 0:
                cout << "Encerrando o sistema... Ate logo!\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }
    } while (opcao != 0);

    return 0;
}