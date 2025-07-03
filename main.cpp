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
    cout << "1. Menu de produtos" << endl;
    cout << "2. Menu de vendedores" << endl;
    cout << "3. Menu de compradores" << endl;
    cout << "4. Menu de vendas" << endl;
    cout << "4. Realizar Venda" << endl;
    cout << "0. Sair" << endl;
    cout << "--------------------------------------------" << endl;
}

void exibirSubMenu(int opcao) {
    string tipo;
    switch (opcao) {
        case 1:
            tipo = "produto";
            break;
        case 2:
            tipo = "vendedor";
            break;
        case 3:
            tipo = "comprador";
            break;
    }
    cout << "E-commerce: Menu de " << tipo << endl;
    cout <<"Selecione uma opção:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "1. Criar novo " << tipo << endl;
    cout << "2. Alterar " << tipo <<endl;
    cout << "3. Excluir " << tipo <<endl;
    cout << "0. Voltar ao menu principal" << endl;
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

bool cadastrarVendedor(Vendedores listaDeVendedores[], int i) {
    string nome;
    float salario;

    cout << "Nome do vendedor: ";
    limpaBuffer();
    getline(cin, nome);
    cout << "Salario fixo do vendedor: ";
    limpaBuffer();
    cin >> salario;
    if (salario >= 0) {
        listaDeVendedores[i] = Vendedores(nome, salario);
        cout << "Vendedor cadastrado com sucesso!" << endl;
        return true;
    }
    else {
        cout << "Erro ao cadastrar vendedor, salario invalido." << endl;
        return false;
    }
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
    vendedores[indiceVendedor].caculaComissao(vendas[qtd_vendas].getValorTotal());
    cout << "Comissao de R$" << (vendas[qtd_vendas].getValorTotal() * 0.03) << " para o vendedor" << endl;

    return true;
}

void alterarProduto(Produtos listaDeProdutos[], int qtdProdutos) {
    int codigo, indiceProduto, opcao;
    bool verifica = true;

    cout << "Digite o codigo do produto a ser alterado: ";
    limpaBuffer();
    cin >> codigo;
    for (int i=0; i<qtdProdutos; i++) {
        if (listaDeProdutos[i].getCodigo() == codigo) {
            indiceProduto = i;
        }
    }
    cout << "Produto encontrado! Informacoes do Produto:" << endl;
    cout << "Nome: " << listaDeProdutos[indiceProduto].getNome() << endl;
    cout << "Quantidade em estoque: " << listaDeProdutos[indiceProduto].getQuantidade() << endl;
    cout << "Preco por unidade: " << listaDeProdutos[indiceProduto].getPreco() << endl;
    while (verifica) {
        cout << "--------" << listaDeProdutos[indiceProduto].getNome() << "--------" << endl;
        cout << "1. Alterar nome" << endl;
        cout << "2. Alterar quantidade em estoque" << endl;
        cout << "3. Alterar preco por unidade" << endl;
        cout << "0. Voltar ao menu anterior" << endl;
        cout << "-----------------" << endl;
        cin >> opcao;
        switch (opcao) {
            case 1:
                string nome;
                cout << "Digite o nome novo: ";
                limpaBuffer();
                getline(cin, nome);
                listaDeProdutos[indiceProduto].setNome(nome);
                cout << "Nome alterado com sucesso!" << endl;
                break;
            case 2:
                int quantidade;
                cout << "Digite a nova quantidade em estoque: ";
                limpaBuffer();
                cin >> quantidade;
                if (quantidade>=0) {
                    listaDeProdutos[indiceProduto].setQuantidade(quantidade);
                    cout << "Quantidade alterada com sucesso!" << endl;
                }
                else {
                    cout << "Quantidade invalida." << endl;
                }
                break;
            case 3:
                float preco;
                cout << "Digite o novo preco por unidade: ";
                limpaBuffer();
                cin >> preco;
                if (preco>=0) {
                    listaDeProdutos[indiceProduto].setPreco(preco);
                    cout << "Preco alterado com sucesso!" << endl;
                }
                else {
                    cout << "Preco invalido." << endl;
                }
                break;
            case 0:
                verifica = false;
                break;
            default:
                cout << "Opcao invalida, tente novamente." << endl;
                break;
        }
    }

}

void excluirProduto() {

}
void excluirVendedor(Vendedores *listaDeVendedores, int qtdVendedores) {
    int codigo, indiceVendedor;

    cout << "Digite o codigo do vendedor a ser excluido: ";
    limpaBuffer();
    cin >> codigo;
    for (int i=0; i<qtdVendedores; i++) {
        if (listaDeVendedores[i].getNumero() == codigo) {
            indiceVendedor = i;
            break;
        }
    }
    listaDeVendedores[indiceVendedor].setNumero(-1);
    cout << "Vendedor - " << listaDeVendedores[indiceVendedor].getNome() << " - excluido com sucesso.\n";

}
void excluirComprador(Comprador *listaDeCompradores, int qtdCompradores) {
    string cpf;
    int indiceComprador = 0;

    cout << "Digite o cpf do comprador a ser excluido: ";
    limpaBuffer();
    cin >> cpf;
    for (int i=0; i<qtdCompradores; i++) {
        if (listaDeCompradores->getCpf() == cpf) {
            indiceComprador = i;
            break;
        }
    }
    listaDeCompradores[indiceComprador].setCpf("");
    cout << "Vendedor - " << listaDeCompradores[indiceComprador].getNome() << " - excluido com sucesso.\n";

}
}
void menuProdutos(int opcao, Produtos listaDeProdutos[], int qtdProdutos) {
    switch (opcao) {
        case 1:
            cout << "Cadastro de produto" << endl;
            cadastrarProduto(listaDeProdutos, qtdProdutos);
            qtdProdutos++;
            break;
        case 2:
            cout << "Alteracao de produto" << endl;
            alterarProduto(listaDeProdutos, qtdProdutos);
        case 3:
        case 0:
        default:
    }
}

float calculoFrete( Vendas v) {
        float frete;
        float precoTotal = v.getValorTotal();
        if (precoTotal >= 100) {
            frete = 30;
        }
        else if (precoTotal > 100 && precoTotal <= 300) {
            frete = 20;
        }
        else {
            frete = 0;
        }

    return frete;
}

void notaFiscal(Comprador c, Produtos *p, int qtdProduto, Vendas v) {
    fstream notaFiscal("notaFiscal.txt", ios::in | ios::out | ios::trunc);
    if (!notaFiscal.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    notaFiscal << "--------------------------------------------" << endl;
    notaFiscal << "                 NOTA FISCAL"                 << endl;
    notaFiscal << "--------------------------------------------" << endl;

    notaFiscal << "-Comprador: " << endl;
    notaFiscal << "Nome: "<< c.getNome() << endl;
    notaFiscal << "CPF: "<< c.getCpf() << endl;
    notaFiscal << "Endereço: "<< c.getEndereco().getEnderecoCompleto() << endl;
    notaFiscal << endl;

    notaFiscal << "--------------------------------------------" << endl;
    notaFiscal << "-Produtos Vendidos: " << endl;

    for (int i = 0; i < qtdProduto; i++) {
        notaFiscal << i << ") "<< "Produto: "<< p[i].getNome() << endl;
        notaFiscal << "   Quantidade: "<< p[i].getQuantidade() << endl;
        notaFiscal << "   Produto: "<< p[i].getNome() << endl;
        notaFiscal << "   Preço Unitário: "<< p[i].getPreco() << endl;
        notaFiscal << "   Subtotal: "<< p[i].getPreco() * p[i].getQuantidade() << endl;
        notaFiscal << endl;
    }
    float frete = calculoFrete(v);
    float valorTotal = v.getValorTotal();
    notaFiscal << "--------------------------------------------" << endl;
    notaFiscal << "-Total dos Produtos: " << "R$" << valorTotal << endl;
    notaFiscal << endl;
    notaFiscal << "-Frete: " << "R$" <<frete << endl;
    notaFiscal << endl;
    notaFiscal << "-Valor Total: " << "R$" << valorTotal + frete << endl;
    notaFiscal << "--------------------------------------------" << endl;
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
                int resposta;
                do {
                    exibirSubMenu(opcao);
                    cin >> resposta;
                    menuProdutos(resposta, listaDeProdutos, qtdProdutos);
                }while (resposta!=0);
                break;
            case 2:
                exibirSubMenu(opcao);
                cout << "Cadastro de vendedor" << endl;
                bool cadastroOk = cadastrarVendedor(listaDeVendedores, qtdVendedores);
                if (cadastroOk){
                    qtdVendedores++;
                }
                break;
            case 3:
                exibirSubMenu(opcao);
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
