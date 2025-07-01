#include <iostream>
#include <ctime>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;
#include "../LuisGustavo/produtos.hpp"
#include "../Henrique/compradores.hpp"
#include "../Lucas/vendedores.hpp"
#include "../Lucas/vendas.hpp"
using namespace std;

void exibirMenuPrincipal();
void gerenciarProdutos(Produtos*& lista, int& total, int& capacidade);
void gerenciarVendedores(Vendedores*& lista, int& total, int& capacidade);
void gerenciarCompradores(Comprador*& lista, int& total, int& capacidade);
void realizarVenda(Vendas*& lista_vendas, int& total_vendas, int& capacidade_vendas,
                   Produtos* lista_produtos, int total_produtos,
                   Vendedores* lista_vendedores, int total_vendedores,
                   Comprador* lista_compradores, int total_compradores);
void emitirNotaFiscal(const Vendas* lista_vendas, int total_vendas);

int main() {
    int capacidade_produtos = 5;
    int capacidade_vendedores = 5;
    int capacidade_compradores = 5;
    int capacidade_vendas = 5;

    int total_produtos = 0;
    int total_vendedores = 0;
    int total_compradores = 0;
    int total_vendas = 0;

    Produtos* lista_produtos = new Produtos[capacidade_produtos];
    Vendedores* lista_vendedores = new Vendedores[capacidade_vendedores];
    Comprador* lista_compradores = new Comprador[capacidade_compradores];
    Vendas* lista_vendas = new Vendas[capacidade_vendas];

    int opcao;
    do {
        exibirMenuPrincipal();
        cin >> opcao;

        if (cin.fail()) {
            cout << "\nErro: Entrada invalida. Por favor, insira um numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 1:
                gerenciarProdutos(lista_produtos, total_produtos, capacidade_produtos);
                break;
            case 2:
                gerenciarVendedores(lista_vendedores, total_vendedores, capacidade_vendedores);
                break;
            case 3:
                gerenciarCompradores(lista_compradores, total_compradores, capacidade_compradores);
                break;
            case 4:
                realizarVenda(lista_vendas, total_vendas, capacidade_vendas,
                               lista_produtos, total_produtos,
                               lista_vendedores, total_vendedores,
                               lista_compradores, total_compradores);
                break;
            case 5:
                emitirNotaFiscal(lista_vendas, total_vendas);
                break;
            case 0:
                cout << "\nSaindo do sistema. Ate logo!" << endl;
                break;
            default:
                cout << "\nOpcao invalida! Tente novamente." << endl;
                break;
        }

        if (opcao != 0) {
            cout << "\nPressione ENTER para continuar...";
            cin.get();
        }

    } while (opcao != 0);

    delete[] lista_produtos;
    delete[] lista_vendedores;
    delete[] lista_compradores;
    delete[] lista_vendas;

    return 0;
}

void exibirMenuPrincipal() {
    cout << "\n\n--- SISTEMA DE E-COMMERCE ---\n";
    cout << "1. Cadastrar Produto\n";
    cout << "2. Cadastrar Vendedor\n";
    cout << "3. Cadastrar Comprador\n";
    cout << "4. Realizar Venda\n";
    cout << "5. Emitir Nota Fiscal\n";
    cout << "0. Sair\n";
    cout << "-----------------------------\n";
    cout << "Escolha uma opcao: ";
}

void gerenciarProdutos(Produtos*& lista, int& total, int& capacidade) {
    cout << "\n--- Cadastro de Produtos ---\n";

    if (total == capacidade) {
        int nova_capacidade = capacidade * 2;
        Produtos* nova_lista = new Produtos[nova_capacidade];
        for (int i = 0; i < total; ++i) {
            nova_lista[i] = lista[i];
        }
        delete[] lista;
        lista = nova_lista;
        capacidade = nova_capacidade;
        cout << "(Espaco de armazenamento de produtos expandido.)\n";
    }

    string nome;
    int quantidade;
    float preco;

    cout << "Digite o nome do produto: ";
    getline(cin, nome);
    cout << "Digite a quantidade em estoque: ";
    cin >> quantidade;
    cout << "Digite o preco de venda (R$): ";
    cin >> preco;

    Produtos novo_produto;
    novo_produto.setNome(nome);
    novo_produto.setQuantidade(quantidade);
    novo_produto.setPreco(preco);

    lista[total] = novo_produto;
    total++;

    cout << "\nProduto '" << novo_produto.getNome() << "' (Codigo: " << novo_produto.getCodigo() << ") cadastrado com sucesso!" << endl;
}

void gerenciarVendedores(Vendedores*& lista, int& total, int& capacidade) {
    cout << "\n--- Cadastro de Vendedores ---\n";
    if (total == capacidade) {
        int nova_capacidade = capacidade * 2;
        Vendedores* nova_lista = new Vendedores[nova_capacidade];
        for (int i = 0; i < total; ++i) {
            nova_lista[i] = lista[i];
        }
        delete[] lista;
        lista = nova_lista;
        capacidade = nova_capacidade;
        cout << "(Espaco de armazenamento de vendedores expandido.)\n";
    }

    string nome;
    float salario;

    cout << "Digite o nome do vendedor: ";
    getline(cin, nome);
    cout << "Digite o salario fixo (R$): ";
    cin >> salario;

    Vendedores novo_vendedor;
    novo_vendedor.setNome(nome);
    novo_vendedor.setSalario(salario);

    lista[total] = novo_vendedor;
    total++;

    cout << "\nVendedor '" << novo_vendedor.getNome() << "' (Numero: " << novo_vendedor.getNumero() << ") cadastrado com sucesso!" << endl;
}

void gerenciarCompradores(Comprador*& lista, int& total, int& capacidade) {
    cout << "\n--- Cadastro de Compradores ---\n";
    if (total == capacidade) {
        int nova_capacidade = capacidade * 2;
        Comprador* nova_lista = new Comprador[nova_capacidade];
        for (int i = 0; i < total; ++i) {
            nova_lista[i] = lista[i];
        }
        delete[] lista;
        lista = nova_lista;
        capacidade = nova_capacidade;
        cout << "(Espaco de armazenamento de compradores expandido.)\n";
    }

    string nome, cpf, email, rua, bairro, cidade, estado, cep;

    cout << "Digite o nome do comprador: ";
    getline(cin, nome);
    cout << "Digite o CPF: ";
    getline(cin, cpf);
    cout << "Digite o e-mail: ";
    getline(cin, email);
    cout << "--- Endereco de Entrega ---\n";
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

    Comprador novo_comprador;
    novo_comprador.setNome(nome);
    novo_comprador.setCpf(cpf);
    novo_comprador.setEmail(email);
    novo_comprador.setDadosEndereco(rua, bairro, cidade, estado, cep);

    lista[total] = novo_comprador;
    total++;

    cout << "\nComprador '" << novo_comprador.getNome() << "' cadastrado com sucesso!" << endl;
}

void realizarVenda(Vendas*& lista_vendas, int& total_vendas, int& capacidade_vendas,
                   Produtos* lista_produtos, int total_produtos,
                   Vendedores* lista_vendedores, int total_vendedores,
                   Comprador* lista_compradores, int total_compradores) {
    cout << "\n--- Realizar Venda ---\n";

    if (total_produtos == 0 || total_vendedores == 0 || total_compradores == 0) {
        cout << "Erro: E necessario ter ao menos um produto, um vendedor e um comprador cadastrado para realizar uma venda." << endl;
        return;
    }

    cout << "\nSelecione o Comprador (pelo indice):\n";
    for (int i = 0; i < total_compradores; ++i) {
        cout << i << ". " << lista_compradores[i].getNome() << " (CPF: " << lista_compradores[i].getCpf() << ")\n";
    }
    int idx_comprador;
    cout << "Indice: ";
    cin >> idx_comprador;

    cout << "\nSelecione o Vendedor (pelo indice):\n";
    for (int i = 0; i < total_vendedores; ++i) {
        cout << i << ". " << lista_vendedores[i].getNome() << " (Numero: " << lista_vendedores[i].getNumero() << ")\n";
    }
    int idx_vendedor;
    cout << "Indice: ";
    cin >> idx_vendedor;

    if (idx_comprador < 0 || idx_comprador >= total_compradores || idx_vendedor < 0 || idx_vendedor >= total_vendedores) {
        cout << "Erro: Indice invalido." << endl;
        return;
    }

    Vendas nova_venda(lista_compradores[idx_comprador], lista_vendedores[idx_vendedor], total_produtos);

    int idx_produto, quantidade;
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        cout << "\nSelecione o Produto a ser adicionado (pelo indice):\n";
        for (int i = 0; i < total_produtos; ++i) {
            cout << i << ". " << lista_produtos[i].getNome() << " (Estoque: " << lista_produtos[i].getQuantidade() << ") - R$ " << fixed << setprecision(2) << lista_produtos[i].getPreco() << "\n";
        }
        cout << "Indice do produto: ";
        cin >> idx_produto;

        if(idx_produto >= 0 && idx_produto < total_produtos){
            cout << "Quantidade: ";
            cin >> quantidade;
            nova_venda.adicionarProduto(lista_produtos[idx_produto], quantidade);
        } else {
            cout << "Erro: Indice de produto invalido." << endl;
        }

        cout << "\nDeseja adicionar outro produto? (s/n): ";
        cin >> continuar;
    }

    nova_venda.finalizarVenda();

    if (total_vendas == capacidade_vendas) {
        int nova_capacidade = capacidade_vendas * 2;
        Vendas* nova_lista = new Vendas[nova_capacidade];
        for(int i = 0; i < total_vendas; ++i) {
            nova_lista[i] = lista_vendas[i];
        }
        delete[] lista_vendas;
        lista_vendas = nova_lista;
        capacidade_vendas = nova_capacidade;
        cout << "(Espaco de armazenamento de vendas expandido.)\n";
    }
    lista_vendas[total_vendas] = nova_venda;
    total_vendas++;
}

void emitirNotaFiscal(const Vendas* lista_vendas, int total_vendas) {
    cout << "\n--- Emissao de Nota Fiscal ---\n";
    if (total_vendas == 0) {
        cout << "Nenhuma venda foi realizada ainda." << endl;
        return;
    }

    cout << "Selecione a Venda para emitir a NF (pelo codigo):\n";
    for(int i = 0; i < total_vendas; ++i) {
        cout << "Codigo da Venda: " << lista_vendas[i].getCodigoVenda() << "\n";
    }
    int cod_venda;
    cout << "Codigo: ";
    cin >> cod_venda;

    int idx_venda = -1;
    for(int i = 0; i < total_vendas; ++i){
        if(lista_vendas[i].getCodigoVenda() == cod_venda){
            idx_venda = i;
            break;
        }
    }

    if (idx_venda == -1) {
        cout << "Erro: Venda com o codigo informado nao encontrada." << endl;
        return;
    }

    const Vendas& venda_selecionada = lista_vendas[idx_venda];
    float total_venda = venda_selecionada.getValorTotal();
    float frete = 0.0;

    if (total_venda <= 100.00) {
        frete = 30.00;
    } else if (total_venda > 100.00 && total_venda <= 300.00) {
        frete = 20.00;
    } else {
        frete = 0.00;
    }

    float total_com_frete = total_venda + frete;

    cout << "\n\n================ NOTA FISCAL ================\n";
    cout << "Venda Codigo: " << venda_selecionada.getCodigoVenda() << "\n";
    cout << "-------------------------------------------\n";
    cout << "DADOS DO COMPRADOR:\n";
    cout << " (Dados detalhados do comprador nao sao acessiveis via classe Venda)\n";
    cout << "-------------------------------------------\n";
    cout << "PRODUTOS VENDIDOS:\n";
    cout << " (Lista de produtos nao e acessivel via classe Venda)\n";
    cout << "-------------------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Subtotal dos Produtos: R$ " << setw(10) << total_venda << "\n";
    cout << "Custo do Frete:        R$ " << setw(10) << frete << "\n";
    cout << "-------------------------------------------\n";
    cout << "VALOR TOTAL DA NOTA:   R$ " << setw(10) << total_com_frete << "\n";
    cout << "===========================================\n";
}