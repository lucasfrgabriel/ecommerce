#include "../../include/ui/Menu.hpp"
#include <iostream>

using namespace std;

void exibirMenuPrincipal() {
    cout << "\n===== E-commerce: Menu Principal =====\n";
    cout << "Selecione uma opcao:\n";
    cout << "--------------------------------------\n";
    cout << "1. Gerenciar Produtos\n";
    cout << "2. Gerenciar Vendedores\n";
    cout << "3. Gerenciar Compradores\n";
    cout << "4. Gerenciar Vendas\n";
    cout << "0. Sair\n";
    cout << "--------------------------------------\n";
    cout << "Opcao: ";
}

void exibirSubMenu(const string& tipo) {
    cout << "\n--- Menu de " << tipo << " ---\n";
    cout << "1. Criar " << tipo << "\n";
    cout << "2. Alterar " << tipo << "\n";
    cout << "3. Excluir " << tipo << "\n";
    cout << "4. Consultar " << tipo << "\n";
    cout << "0. Voltar ao menu principal\n";
    cout << "--------------------------------------\n";
    cout << "Opcao: ";
}