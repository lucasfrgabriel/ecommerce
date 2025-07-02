#include <iostream>
#include <string>

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
    cin.clear();
    cin.ignore();
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

    listaDeProdutos[i] = Produtos(nome, qtd, preco);
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

    listaDeVendedores[i] = Vendedores(nome, salario);
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

    listaDeCompradores[i] = Comprador(nome, cpf, email, rua, bairro, cidade, estado, cep);
    cout << "Comprador cadastrado com sucesso!" << endl;
}

bool realizarVenda(Vendas vendas[], Produtos produtos[], Vendedores vendedores[], Comprador compradores[],
                   int qtd_vendas, int qtd_produtos, int qtd_vendedores, int qtd_compradores) {
    string cpfComprador;
    int codVendedor, codProduto;
    int qtd;
    bool selecionaProdutos = true;
    int carrinho[20];
    int quantidade[20];
    int itensNoCarrinho = 0;
    int indiceVendedor = -1, indiceComprador = -1, indiceProduto = -1;

    cout << "Digite o CPF do comprador: ";
    limpaBuffer();
    getline(cin, cpfComprador);

    for (int i = 0; i < qtd_compradores; i++) {
        if (compradores[i].getCpf() == cpfComprador) {
            indiceComprador = i;
        }
    }
    if (indiceComprador < 0) {
        cout << "Comprador inexistente, venda cancelada." << endl;
        return false;
    }

    cout << "Digite o codigo do vendedor: ";
    limpaBuffer();
    cin >> codVendedor;

    for (int i = 0; i < qtd_vendedores; i++) {
        if (vendedores[i].getNumero() == codVendedor) {
            indiceVendedor = i;
        }
    }
    if (indiceVendedor < 0) {
        cout << "Vendedor inexistente, venda cancelada." << endl;
        return false;
    }

    while (selecionaProdutos){
        bool encontrou = false;

        cout << "Adicione um produto novo para a compra" << endl;
        cout << "Codigo do produto: ";
        limpaBuffer();
        cin >> codProduto;

        for (int i = 0; i < qtd_produtos; i++) {
            if (produtos[i].getCodigo() == codProduto) {
                encontrou = true;
                indiceProduto = i;
            }
        }
        if (encontrou) {
            cout << "Produto selecionado: " << produtos[indiceProduto].getNome() << endl;
            cout << "Valor do produto: " << produtos[indiceProduto].getPreco() << endl;
            cout << "Digite a quantidade desejada: ";
            cin >> qtd;

            if (produtos[indiceProduto].getQuantidade() >= qtd) {
                cout << qtd << " itens selecionados." << endl;
                cout << "Valor total dos itens: " << (produtos[indiceProduto].getPreco() * qtd) << endl;
                carrinho[itensNoCarrinho] = indiceProduto;
                quantidade[itensNoCarrinho] = qtd;
                itensNoCarrinho++;
                cout << "Produto adicionado ao carrinho" << endl;

                char verifica;
                cout << "Deseja adicionar um produto novo? S ou N" << endl;
                limpaBuffer();
                cin >> verifica;
                if (verifica == 'N') {
                    selecionaProdutos = false;
                }
                else if (verifica == 'S') {
                    selecionaProdutos = true;
                }
            }
            else {
                cout << "Itens em falta. Estoque do produto: " << produtos[indiceProduto].getQuantidade() << endl;
                selecionaProdutos = false;
            }
        }
        else {
            cout << "Produto nao encontrado, tente novamente." << endl;
            selecionaProdutos = false;
        }
    }

    vendas[qtd_vendas] = Vendas(indiceVendedor, indiceComprador, carrinho, itensNoCarrinho, quantidade);
    cout << "A venda ficou no valor de R$" << vendas[qtd_vendas].getValorTotal() << endl;
    cout << "Venda realizada com sucesso!" << endl;
    vendedores[indiceVendedor].setComissoes(vendas[qtd_vendas].getValorTotal());
    cout << "Comissao de R$" << (vendas[qtd_vendas].getValorTotal() * 0.03) << " para o vendedor" << endl;

    return true;
}

int main() {
    srand(time(0));

    Produtos *listaDeProdutos = new Produtos[20];
    Vendedores *listaDeVendedores = new Vendedores[20];
    Comprador *listaDeCompradores = new Comprador[20];
    Vendas *listaDeVendas = new Vendas[20];

    int qtdProdutos = 0, qtdVendedores = 0, qtdCompradores = 0, qtdVendas = 0;

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
            case 4: {
                cout << "Realizar Venda" << endl;
                bool resposta = realizarVenda(listaDeVendas, listaDeProdutos, listaDeVendedores, listaDeCompradores,
                                qtdVendas, qtdProdutos, qtdVendedores, qtdCompradores);
                if (resposta) {
                    qtdVendas++;
                }
                break;
            }
            case 0:
                cout << "Encerrando sistema de e-commerce..." << endl;
                cout << "Agradecemos pelo acesso, volte sempre!" << endl;
                break;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    }while (opcao!=0);

    delete[] listaDeProdutos;
    delete[] listaDeVendedores;
    delete[] listaDeCompradores;
    delete[] listaDeVendas;

    return 0;
}
