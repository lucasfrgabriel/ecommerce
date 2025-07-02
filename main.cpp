#include <iostream>
#include <ctime>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;
#include "LuisGustavo/produtos.hpp"
#include "Henrique/compradores.hpp"
#include "Lucas/vendedores.hpp"
#include "Lucas/vendas.hpp"

void exibirMenu() {
    cout << "E-commerce: Menu principal" << endl;
    cout <<"Selecione uma opção:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "1. Cadastrar Produto" << endl;
    cout << "2. Cadastrar Vendedor" << endl;
    cout << "3. Cadastrar Comprador" << endl;
    cout << "4. Realizar Venda" << endl;
    cout << "0. Sair" << endl;
    cout << "--------------------------------------------" << endl;
}

void limpaBuffer() {
    cin.clear;
    cin.ignore;
}

void cadastrarProduto(Produtos listaDeProdutos[], int i) {
    string nome;
    int qtd;
    float preco;

    cout << "Nome do produto: ";
    limpaBuffer();
    getline(cin, nome);
    cout << "Quantidade de produtos em estoque: ";
    limpaBuffer();
    cin >> qtd;
    cout << "Preco de venda do produto em R$: ";
    limpaBuffer();
    cin >> preco;

    listaDeProdutos[i].Produtos(nome, qtd, preco);
    cout << "Produto cadastrado com sucesso!" << endl;
}

void cadastrarVendedor(Vendedores listaDeVendedores[], int i) {
    string nome;
    float salario;

    cout << "Nome do vendedor: ";
    limpaBuffer();
    getline(cin, nome);
    cout << "Salario fixo do vendedor: ";
    limpaBuffer();
    cin >> salario;

    listaDeVendedores[i].Vendedores(nome, salario);
    cout << "Vendedor cadastrado com sucesso!" << endl;
}

void cadastrarComprador(Comprador listaDeCompradores[], int i) {
    string nome, cpf, email, rua, bairro, cidade, estado, cep;
    cout << "Nome do comprador: ";
    getline(cin, nome);
    cout << "CPF: ";
    getline(cin, cpf);
    cout << "Email do comprador: ";
    getline(cin, email);
    cout << "Endereço de entrega:" << endl;
    cout << "Rua: ";
    getline(cin, rua);
    cout << "Bairro: ";
    getline(cin, bairro);
    cout << "Cidade: ";
    getline(cin, cidade);
    cout << "Estado: ";
    getline(cin, estado);
    cout << "CEP: ";
    getline(cin, cep);

    listaDeCompradores[i].Comprador(nome, cpf, email, rua, bairro, cidade, estado, cep);
    cout << "Comprador cadastrado com sucesso!" << endl;
}

int main() {
    Produtos *listaDeProdutos = new Produtos[20];
    Vendedores *listaDeVendedores = new Vendedores[20];
    Comprador *listaDeCompradores = new Compradores[20];
    Vendas *listaDeVendas = new Vendas[20];

    int qtdProdutos = 0, qtdVendedores = 0, qtdCompradores = 0;

    int opcao;

    do {
        exibirMenu();
        cin >> opcao;

        while (cin.fail()) {
            cout << "Opcao invalida!" << endl;
            limpaBuffer();
            exibirMenu();
            cin >> opcao;
        }

        switch (opcao) {
            case 1:
                cout << "Cadastro de produto" << endl;
                cadastrarProduto(listaDeProdutos, qtdProdutos);
                qtdProdutos++;
                break;
            case 2:
                cout << "Cadastro de vendedor" << endl;
                cadastrarVendedor(listaDeVendedores, qtdVendedores);
                qtdVendedores++;
                break;
            case 3:
                cout << "Cadastro de comprador" << endl;
                cadastrarComprador(listaDeCompradores, qtdCompradores);
                qtdCompradores++;
                break;
            case 4:
                cout << "Realizar Venda" << endl;
                realizarVenda();
                break;
            case 0:
                cout << "Encerrando sistema de e-commerce..." << endl;
                cout << "Agradecemos pelo acesso, volte sempre!" << endl;
                break;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }

        delete[] listaDeProdutos;
        delete[] listaDeVendedores;
        delete[] listaDeCompradores;
        delete[] listaDeVendas;

    }while (opcao!=0);

    return 0;
}