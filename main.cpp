#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;
#include "LuisGustavo/produtos.hpp"
#include "Henrique/compradores.hpp"
#include "Lucas/vendedores.hpp"
#include "Lucas/vendas.hpp"

void exibirMenu() {
    cout << "E-commerce: Menu principal" << endl;
    cout <<"Selecione uma opcao:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "1. Menu de produtos" << endl;
    cout << "2. Menu de vendedores" << endl;
    cout << "3. Menu de compradores" << endl;
    cout << "4. Menu de vendas" << endl;
    cout << "5. Realizar Venda" << endl;
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
        case 4:
            tipo = "venda";
            break;
    }
    cout << "E-commerce: Menu de " << tipo << endl;
    cout <<"Selecione uma opcao:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "1. Criar " << tipo << endl;
    if (opcao == 4) {
        cout << "2. Excluir " << tipo << endl;
    }
    else {
        cout << "2. Alterar " << tipo <<endl;
        cout << "3. Excluir " << tipo <<endl;
    }
     if (opcao != 4) {
        cout << "4. Consultar " << tipo << endl;
    } else {
        cout << "3. Consultar " << tipo << endl;
    }
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
    cin >> qtd;
    cout << "Preco de venda do produto em R$: ";
    cin >> preco;

    listaDeProdutos[i] = Produtos(nome, qtd, preco);

    ofstream arquivo("produto.txt", ios::app);
    listaDeProdutos[i].salvarNoArquivo(arquivo);
    cout << "Produto cadastrado com sucesso!" << endl;
}

bool cadastrarVendedor(Vendedores listaDeVendedores[], int i) {
    string nome;
    float salario;

    cout << "Nome do vendedor: ";
    limpaBuffer();
    getline(cin, nome);
    cout << "Salario fixo do vendedor: ";
    cin >> salario;
    if (salario >= 0) {
        listaDeVendedores[i] = Vendedores(nome, salario);
        ofstream arquivo("vendedor.txt", ios::app);
        listaDeVendedores[i].salvarNoArquivo(arquivo);
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
    limpaBuffer();
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

void notaFiscal(Comprador c, Produtos p[], int qtdProduto, Vendas v , ofstream &notaFiscal) {

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

bool realizarVenda(Vendas vendas[], Produtos produtos[], Vendedores vendedores[], Comprador compradores[],
                   int qtd_vendas, int qtd_produtos, int qtd_vendedores, int qtd_compradores) {
    string cpfComprador;
    int codVendedor, codProduto;
    int qtd;
    bool selecionaProdutos = true;
    int carrinho[20];
    int quantidade[20];
    int itensNoCarrinho = 0;
    int indiceVendedor = -1, indiceComprador = -1;

    cout << "Digite o CPF do comprador: ";
    limpaBuffer();
    getline(cin, cpfComprador);

    for (int i = 0; i < qtd_compradores; i++) {
        if (compradores[i].getCpf() == cpfComprador) {
            indiceComprador = i;
            break;
        }
    }
    if (indiceComprador < 0) {
        cout << "Comprador inexistente, venda cancelada." << endl;
        return false;
    }

    cout << "Digite o codigo do vendedor: ";
    cin >> codVendedor;

    for (int i = 0; i < qtd_vendedores; i++) {
        if (vendedores[i].getNumero() == codVendedor) {
            indiceVendedor = i;
            break;
        }
    }
    if (indiceVendedor < 0) {
        cout << "Vendedor inexistente, venda cancelada." << endl;
        return false;
    }

    while (selecionaProdutos){
        bool encontrou = false;
        int indiceProduto = -1;

        cout << "Adicione um produto novo para a compra" << endl;
        cout << "Codigo do produto: ";
        cin >> codProduto;

        for (int i = 0; i < qtd_produtos; i++) {
            if (produtos[i].getCodigo() == codProduto) {
                encontrou = true;
                indiceProduto = i;
                break;
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
                if (toupper(verifica) == 'N') {
                    selecionaProdutos = false;
                }
            }
            else {
                cout << "Itens em falta. Estoque do produto: " << produtos[indiceProduto].getQuantidade() << endl;
            }
        }
        else {
            cout << "Produto nao encontrado, tente novamente." << endl;
        }

        if (selecionaProdutos) {
             char verifica;
             cout << "Deseja continuar adicionando produtos? S ou N" << endl;
             limpaBuffer();
             cin >> verifica;
             if (toupper(verifica) == 'N') {
                selecionaProdutos = false;
            }
        }
    }

    if (itensNoCarrinho == 0) {
        cout << "Carrinho vazio. Venda cancelada." << endl;
        return false;
    }

    vendas[qtd_vendas] = Vendas(indiceVendedor, indiceComprador, carrinho, itensNoCarrinho, quantidade);

    float valorTotalCalculado = 0;
    for(int i = 0; i < itensNoCarrinho; i++){
        int produtoIdx = carrinho[i];
        valorTotalCalculado += produtos[produtoIdx].getPreco() * quantidade[i];
    }

    cout << "A venda ficou no valor de R$" << valorTotalCalculado << endl;
    cout << "Venda realizada com sucesso!" << endl;
    vendedores[indiceVendedor].caculaComissao(vendas[qtd_vendas].getValorTotal());
    cout << "Comissao de R$" << (vendas[qtd_vendas].getValorTotal() * 0.03) << " para o vendedor" << endl;
    cout << "Digite o nome da nota fiscal (formato - nome.txt): " << endl;
    string nf;
    getline(cin, nf);
    ofstream arquivo(nf);
    notaFiscal(compradores[indiceComprador],produtos,qtd_produtos,vendas[qtd_vendas],arquivo);

    vendedores[indiceVendedor].caculaComissao(valorTotalCalculado);
    cout << "Comissao de R$" << (valorTotalCalculado * vendedores[indiceVendedor].getComissoes()) << " para o vendedor" << endl;

    return true;
}

void alterarVendedor(Vendedores listaDeVendedores[], int qtdVendedores) {
    int numero = -1, indiceVendedor = -1, opcao;
    bool verifica = true;

    cout << "Digite o numero do vendedor a ser alterado: ";
    cin >> numero;
    for (int i=0; i<qtdVendedores; i++) {
        if (listaDeVendedores[i].getNumero() == numero) {
            indiceVendedor = i;
            break;
        }
    }
    if (indiceVendedor == -1) {
        cout << "Vendedor nao encontrado." << endl;
    }
    else {
        cout << "Vendedor encontrado! Informacoes do Vendedor:" << endl;
        cout << "Nome: " << listaDeVendedores[indiceVendedor].getNome() << endl;
        cout << "Salario: " << listaDeVendedores[indiceVendedor].getSalario() << endl;
        while (verifica) {
            cout << "--------" << listaDeVendedores[indiceVendedor].getNome() << "--------" << endl;
            cout << "1. Alterar nome" << endl;
            cout << "2. Alterar salario" << endl;
            cout << "0. Voltar ao menu anterior" << endl;
            cout << "-----------------" << endl;
            cin >> opcao;
            switch (opcao) {
                case 1:
                    {
                        string nome;
                        cout << "Digite o nome novo: ";
                        limpaBuffer();
                        getline(cin, nome);
                        listaDeVendedores[indiceVendedor].setNome(nome);
                        cout << "Nome alterado com sucesso!" << endl;
                    }
                    break;
                case 2:
                    {
                        int salario;
                        cout << "Digite o novo salario: ";
                        cin >> salario;
                        if (salario>=0) {
                            listaDeVendedores[indiceVendedor].setSalario(salario);
                            cout << "Salario alterado com sucesso!" << endl;
                        }
                        else {
                            cout << "Salario invalido." << endl;
                        }
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
}

void alterarComprador(Comprador listaDeCompradores[], int qtdCompradores) {
    int indiceComprador = -1, opcao;
    bool verifica = true;
    string cpf = "";

    cout << "Digite o cpf do comprador a ser alterado: ";
    limpaBuffer();
    getline(cin, cpf);
    for (int i=0; i<qtdCompradores; i++) {
        if (listaDeCompradores[i].getCpf() == cpf) {
            indiceComprador = i;
            break;
        }
    }
    if (indiceComprador == -1) {
        cout << "Comprador nao encontrado." << endl;
    }
    else {
        cout << "Comprador encontrado! Informacoes do Comprador:" << endl;
        cout << "Nome: " << listaDeCompradores[indiceComprador].getNome() << endl;
        cout << "Email: " << listaDeCompradores[indiceComprador].getEmail() << endl;
        cout << "Endereco: " << listaDeCompradores[indiceComprador].getEndereco().getEnderecoCompleto() << endl;
        while (verifica) {
            cout << "--------" << listaDeCompradores[indiceComprador].getNome() << "--------" << endl;
            cout << "1. Alterar nome" << endl;
            cout << "2. Alterar email" << endl;
            cout << "3. Alterar endereco" << endl;
            cout << "0. Voltar ao menu anterior" << endl;
            cout << "-----------------" << endl;
            cin >> opcao;
            switch (opcao) {
                case 1:
                    {
                        string nome;
                        cout << "Digite o nome novo: ";
                        limpaBuffer();
                        getline(cin, nome);
                        listaDeCompradores[indiceComprador].setNome(nome);
                        cout << "Nome alterado com sucesso!" << endl;
                    }
                    break;
                case 2:
                    {
                        string email;
                        cout << "Digite o novo email: ";
                        limpaBuffer();
                        getline(cin, email);
                        listaDeCompradores[indiceComprador].setEmail(email);
                        cout << "Email alterado com sucesso!" << endl;
                    }
                    break;
                case 3:
                    {
                        string rua, bairro, cidade, estado, cep;
                        cout << "Digite a rua: ";
                        limpaBuffer();
                        getline(cin, rua);
                        cout << "Digite o bairro: ";
                        getline(cin, bairro);
                        cout << "Digite a cidade: ";
                        getline(cin, cidade);
                        cout << "Digite o estado: ";
                        getline(cin, estado);
                        cout << "Digite o CEP: ";
                        getline(cin, cep);
                        listaDeCompradores[indiceComprador].setDadosEndereco(rua, bairro, cidade, estado, cep);
                        cout << "Endereco alterado com sucesso" << endl;
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
}

void alterarProduto(Produtos listaDeProdutos[], int qtdProdutos) {
    int codigo = -1, indiceProduto = -1, opcao;
    bool verifica = true;

    cout << "Digite o codigo do produto a ser alterado: ";
    cin >> codigo;
    for (int i=0; i<qtdProdutos; i++) {
        if (listaDeProdutos[i].getCodigo() == codigo) {
            indiceProduto = i;
            break;
        }
    }
    if (indiceProduto == -1) {
        cout << "Produto nao encontrado." << endl;
    }
    else {
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
                    {
                        string nome;
                        cout << "Digite o nome novo: ";
                        limpaBuffer();
                        getline(cin, nome);
                        listaDeProdutos[indiceProduto].setNome(nome);
                        cout << "Nome alterado com sucesso!" << endl;
                    }
                    break;
                case 2:
                    {
                        int quantidade;
                        cout << "Digite a nova quantidade em estoque: ";
                        cin >> quantidade;
                        if (quantidade>=0) {
                            listaDeProdutos[indiceProduto].setQuantidade(quantidade);
                            cout << "Quantidade alterada com sucesso!" << endl;
                        }
                        else {
                            cout << "Quantidade invalida." << endl;
                        }
                    }
                    break;
                case 3:
                    {
                        float preco;
                        cout << "Digite o novo preco por unidade: ";
                        cin >> preco;
                        if (preco>=0) {
                            listaDeProdutos[indiceProduto].setPreco(preco);
                            cout << "Preco alterado com sucesso!" << endl;
                        }
                        else {
                            cout << "Preco invalido." << endl;
                        }
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
}
void consultarProdutos(Produtos  *listaDeProdutos ,int qtdProdutos) {
    int codigo, indiceProduto = -1;

    cout << "Digite o codigo do produto a ser consultado: ";
    limpaBuffer();
    cin >> codigo;
    for (int i=0; i<qtdProdutos; i++) {
        if (listaDeProdutos[i].getCodigo() == codigo) {
            indiceProduto = i;
            break;
        }
    }
    if (indiceProduto == -1) {
        cout << "Produto nao encontrado!\n";
    } else {
        listaDeProdutos[indiceProduto].mostrarDados();
    }
}
void consultarVendedor(Vendedores *listaDeVendedores, int qtdVendedores) {
    int codigo, indiceVendedor = -1;

    cout << "Digite o codigo do vendedor a ser consultado: ";
    limpaBuffer();
    cin >> codigo;

    for (int i = 0; i < qtdVendedores; i++) {
        if (listaDeVendedores[i].getNumero() == codigo) {
            indiceVendedor = i;
            break;
        }
    }

    if (indiceVendedor == -1) {
        cout << "Vendedor nao encontrado!\n";
    } else {
        listaDeVendedores[indiceVendedor].mostrarDados();
    }
}
void consultarComprador(Comprador *listaDeCompradores, int qtdCompradores) {
    int indiceComprador = -1;
    string cpf;
    cout << "Digite o cpf do comprador a ser consultado: ";
    limpaBuffer();
    getline(cin, cpf);

    for (int i = 0; i < qtdCompradores; i++) {
        if (listaDeCompradores[i].getCpf() == cpf) {
            indiceComprador = i;
            break;
        }
    }

    if (indiceComprador == -1) {
        cout << "Comprador nao encontrado!\n";
    } else {
        listaDeCompradores[indiceComprador].exibirDados();
    }
}
void consultarVendas(Vendas *listaDeVendas, int qtdVendas) {
    int codigo, indiceVenda = -1;

    cout << "Digite o codigo da venda a ser consultada: ";
    limpaBuffer();
    cin >> codigo;

    for (int i = 0; i < qtdVendas; i++) {
        if (listaDeVendas[i].getCodigoVenda() == codigo) {
            indiceVenda = i;
            break;
        }
    }

    if (indiceVenda == -1) {
        cout << "Venda nao encontrada!\n";
    } else {
        listaDeVendas[indiceVenda].mostrarDados();
    }
}
void excluirDoArquivo(int codigo) {
    ifstream arquivoLeitura("produtos.txt");
    ofstream arquivoTemp("temp.txt");
    string linha;
    bool encontrado = false;

    if (!arquivoLeitura || !arquivoTemp) {
        cout << "Erro ao abrir arquivos!\n";
        return;
    }

    while (getline(arquivoLeitura, linha)) {
        size_t pos = linha.find("codigo: " + to_string(codigo));
        if (pos == string::npos) {
            arquivoTemp << linha << endl;
        } else {
            encontrado = true;
        }
    }

    arquivoLeitura.close();
    arquivoTemp.close();

    remove("produtos.txt");
    rename("temp.txt", "produtos.txt");

    if (!encontrado) {
        cout << "Produto com codigo " << codigo << " nao encontrado no arquivo.\n";
    }
}
void excluirProduto(Produtos *listaDeProdutos, int& qtdProdutos) {
    int codigo, indiceProduto = -1;

    cout << "Digite o codigo do produto a ser excluido: ";
    cin >> codigo;
    for (int i=0; i<qtdProdutos; i++) {
        if (listaDeProdutos[i].getCodigo() == codigo) {
            indiceProduto = i;
            break;
        }
    }

    if (indiceProduto != -1) {
        excluirDoArquivo(codigo);
        cout << "Produto - " << listaDeProdutos[indiceProduto].getNome() << " - excluido com sucesso.\n";
        for (int i = indiceProduto; i < qtdProdutos - 1; i++) {
            listaDeProdutos[i] = listaDeProdutos[i+1];
        }
        qtdProdutos--;
    } else {
        cout << "Produto nao encontrado.\n";
    }
}
void excluirVendedor(Vendedores *listaDeVendedores, int& qtdVendedores) {
    int codigo, indiceVendedor = -1;

    cout << "Digite o codigo do vendedor a ser excluido: ";
    cin >> codigo;
    for (int i=0; i<qtdVendedores; i++) {
        if (listaDeVendedores[i].getNumero() == codigo) {
            indiceVendedor = i;
            break;
        }
    }

    if(indiceVendedor != -1) {
        cout << "Vendedor - " << listaDeVendedores[indiceVendedor].getNome() << " - excluido com sucesso.\n";
        for(int i = indiceVendedor; i < qtdVendedores - 1; i++) {
            listaDeVendedores[i] = listaDeVendedores[i+1];
        }
        qtdVendedores--;
    } else {
        cout << "Vendedor nao encontrado.\n";
    }
}
void excluirComprador(Comprador *listaDeCompradores, int& qtdCompradores) {
    string cpf;
    int indiceComprador = -1;

    cout << "Digite o cpf do comprador a ser excluido: ";
    limpaBuffer();
    getline(cin, cpf);
    for (int i=0; i<qtdCompradores; i++) {
        if (listaDeCompradores[i].getCpf() == cpf) {
            indiceComprador = i;
            break;
        }
    }

    if(indiceComprador != -1) {
        cout << "Comprador - " << listaDeCompradores[indiceComprador].getNome() << " - excluido com sucesso.\n";
        for(int i = indiceComprador; i < qtdCompradores - 1; i++) {
            listaDeCompradores[i] = listaDeCompradores[i+1];
        }
        qtdCompradores--;
    } else {
        cout << "Comprador nao encontrado.\n";
    }
}
void excluirVendas(Vendas *listaDeVendas, int& qtdVendas ) {
    int codigo, indiceVendas = -1;

    cout << "Digite o codigo da venda a ser excluida: ";
    cin >> codigo;
    for (int i=0; i<qtdVendas; i++) {
        if (listaDeVendas[i].getCodigoVenda() == codigo) {
            indiceVendas = i;
            break;
        }
    }

    if (indiceVendas != -1) {
        cout << "Venda com o codigo - " << listaDeVendas[indiceVendas].getCodigoVenda() << " - excluida com sucesso.\n";
        for(int i = indiceVendas; i < qtdVendas - 1; i++){
            listaDeVendas[i] = listaDeVendas[i+1];
        }
        qtdVendas--;
    } else {
        cout << "Venda nao encontrada.\n";
    }
}

void menuProdutos(int opcao, Produtos listaDeProdutos[], int& qtdProdutos) {
    switch (opcao) {
        case 1:
            cout << "Cadastro de produto" << endl;
            cadastrarProduto(listaDeProdutos, qtdProdutos);
            qtdProdutos++;
            break;
        case 2:
            cout << "Alteracao de produto" << endl;
            alterarProduto(listaDeProdutos, qtdProdutos);
            break;
        case 3:
            cout << "Excluir produto" << endl;
            excluirProduto(listaDeProdutos, qtdProdutos);
            break;
        case 4:
            cout << "Consultar produto" << endl;
            consultarProdutos(listaDeProdutos, qtdProdutos);
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida." << endl;
            break;
    }
}

void menuVendas(int opcao, Vendas listaDeVendas[], int& qtdVendas,
                Produtos listaDeProdutos[], Vendedores listaDeVendedores[], Comprador listaDeCompradores[],
               int qtdProdutos, int qtdVendedores, int qtdCompradores) {
    switch (opcao) {
        case 1:
            cout << "Realizar Venda" << endl;
            if (realizarVenda(listaDeVendas, listaDeProdutos, listaDeVendedores, listaDeCompradores,
                                qtdVendas, qtdProdutos, qtdVendedores, qtdCompradores)) {
                qtdVendas++;
            }
            break;
        case 2:
            cout << "Excluir venda" << endl;
            excluirVendas(listaDeVendas, qtdVendas);
            break;
        case 3:
            cout << "Consultar venda" << endl;
            consultarVendas(listaDeVendas, qtdVendas);
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida." << endl;
            break;
    }
}

void menuVendedores(int opcao, Vendedores listaDeVendedores[], int& qtdVendedores) {
    switch (opcao) {
        case 1:
            cout << "Cadastro de vendedor" << endl;
            if (cadastrarVendedor(listaDeVendedores, qtdVendedores)){
                qtdVendedores++;
            }
            break;
        case 2:
            cout << "Alteracao de vendedor" << endl;
            alterarVendedor(listaDeVendedores, qtdVendedores);
            break;
        case 3:
            cout << "Excluir vendedor" << endl;
            excluirVendedor(listaDeVendedores, qtdVendedores);
            break;
        case 4:
            cout << "Consultar vendedor" << endl;
            consultarVendedor(listaDeVendedores, qtdVendedores);
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida." << endl;
            break;
    }
}

void menuCompradores(int opcao, Comprador listaDeCompradores[], int& qtdCompradores) {
    switch (opcao) {
        case 1:
            cout << "Cadastro de comprador" << endl;
            cadastrarComprador(listaDeCompradores, qtdCompradores);
            qtdCompradores++;
            break;
        case 2:
            cout << "Alteracao de comprador" << endl;
            alterarComprador(listaDeCompradores, qtdCompradores);
            break;
        case 3:
            cout << "Excluir comprador" << endl;
            excluirComprador(listaDeCompradores, qtdCompradores);
            break;
        case 4:
            cout << "Consultar comprador" << endl;
            consultarComprador(listaDeCompradores, qtdCompradores);
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida." << endl;
            break;
    }
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
            cin.clear();
            cin.ignore(10000, '\n');
            exibirMenu();
            cin >> opcao;
        }

        switch (opcao) {
            case 1:
                {
                    int produtoMenu;
                    do {
                        exibirSubMenu(opcao);
                        cin >> produtoMenu;
                        menuProdutos(produtoMenu, listaDeProdutos, qtdProdutos);
                    } while (produtoMenu!=0);
                }
                break;
            case 2:
                {
                    int vendedorMenu;
                    do {
                        exibirSubMenu(opcao);
                        cin >> vendedorMenu;
                        menuVendedores(vendedorMenu,listaDeVendedores, qtdVendedores);
                    } while (vendedorMenu !=0);
                }
                break;
            case 3:
                {
                    int compradorMenu;
                    do {
                        exibirSubMenu(opcao);
                        cin >> compradorMenu;
                        menuCompradores(compradorMenu, listaDeCompradores, qtdCompradores);
                    } while (compradorMenu!=0);
                }
                break;
            case 4:
                {
                    int vendaMenu;
                    do {
                        exibirSubMenu(opcao);
                        cin >> vendaMenu;
                        menuVendas(vendaMenu, listaDeVendas, qtdVendas,
                                    listaDeProdutos, listaDeVendedores, listaDeCompradores,
                                    qtdProdutos, qtdVendedores, qtdCompradores);
                    } while (vendaMenu!=0);
                }
                break;
            case 5: {
                cout << "Realizar Venda" << endl;
                if (realizarVenda(listaDeVendas, listaDeProdutos, listaDeVendedores, listaDeCompradores,
                                qtdVendas, qtdProdutos, qtdVendedores, qtdCompradores)) {
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
    } while (opcao!=0);

    delete[] listaDeProdutos;
    delete[] listaDeVendedores;
    delete[] listaDeCompradores;
    delete[] listaDeVendas;

    return 0;
}