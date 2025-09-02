#include "../../include/services/Servicos.hpp"
#include "../../include/ui/Menu.hpp"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int encontrarIndiceProduto(const vector<Produto>& produtos, int codigo) {
    for (size_t i = 0; i < produtos.size(); ++i) {
        if (produtos[i].getCodigo() == codigo) return i;
    }
    return -1;
}

int encontrarIndiceVendedor(const vector<Vendedor>& vendedores, int numero) {
    for (size_t i = 0; i < vendedores.size(); ++i) {
        if (vendedores[i].getNumero() == numero) return i;
    }
    return -1;
}

int encontrarIndiceComprador(const vector<Comprador>& compradores, const string& cpf) {
    for (size_t i = 0; i < compradores.size(); ++i) {
        if (compradores[i].getCpf() == cpf) return i;
    }
    return -1;
}

int encontrarIndiceVenda(const vector<Venda>& vendas, int codigo) {
    for (size_t i = 0; i < vendas.size(); ++i) {
        if (vendas[i].getCodigoVenda() == codigo) return i;
    }
    return -1;
}

void gerarNotaFiscal(const Venda& venda, ofstream& arquivo) {
    const Comprador& comprador = venda.getComprador();
    const Vendedor& vendedor = venda.getVendedor();
    const auto& produtos = venda.getProdutosVendidos();

    arquivo << "--------------------------------------------\n";
    arquivo << "                 NOTA FISCAL\n";
    arquivo << "                Venda #" << venda.getCodigoVenda() << "\n";
    arquivo << "--------------------------------------------\n\n";

    arquivo << "DADOS DO COMPRADOR:\n";
    arquivo << "Nome: " << comprador.getNome() << "\n";
    arquivo << "CPF: " << comprador.getCpf() << "\n";
    arquivo << "Endereco de Entrega: " << comprador.getEndereco().getEnderecoCompleto() << "\n\n";

    arquivo << "DADOS DO VENDEDOR:\n";
    arquivo << "Nome: " << vendedor.getNome() << " (Codigo: " << vendedor.getNumero() << ")\n\n";

    arquivo << "--------------------------------------------\n";
    arquivo << "PRODUTOS VENDIDOS:\n";
    for (const auto& produto : produtos) {
        arquivo << "- " << produto.getNome() << "\n";
        arquivo << "  Quantidade: " << produto.getQuantidade() << "\n";
        arquivo << "  Preco Unitario: R$ " << produto.getPreco() << "\n";
        arquivo << "  Subtotal: R$ " << produto.getPreco() * produto.getQuantidade() << "\n\n";
    }

    arquivo << "--------------------------------------------\n";
    arquivo << "VALOR TOTAL: R$ " << venda.getValorTotal() << "\n";
    arquivo << "--------------------------------------------\n";
}

// Produto

void cadastrarProduto(vector<Produto>& produtos) {
    string nome;
    int qtd;
    float preco;

    cout << "Nome do produto: ";
    limparBuffer();
    getline(cin, nome);

    cout << "Quantidade em estoque: ";
    cin >> qtd;

    cout << "Preco (R$): ";
    cin >> preco;

    produtos.emplace_back(nome, qtd, preco);

    ofstream arquivo("produto.txt", ios::app);

    if (arquivo.is_open()) {
        produtos.back().salvarNoArquivo(arquivo);
        arquivo.close();
    } else {
        cerr << "ERRO: Nao foi possivel abrir o arquivo produto.txt para salvamento." << endl;
    }
    cout << "\nProduto cadastrado com sucesso! Codigo gerado: " << produtos.back().getCodigo() << endl;
}

void alterarProduto(vector<Produto>& produtos) {
    int codigo;
    cout << "Digite o codigo do produto a ser alterado: ";
    cin >> codigo;
    int indice = encontrarIndiceProduto(produtos, codigo);

    if (indice == -1) {
        cout << "Erro: Produto nao encontrado.\n";
        return;
    }

    cout << "Produto encontrado:\n";
    produtos[indice].mostrarDados();

    int opcao;
    cout << "O que deseja alterar?\n1. Nome\n2. Quantidade\n3. Preco\nOpcao: ";
    cin >> opcao;

    switch (opcao) {
        case 1: {
            string novoNome;
            cout << "Digite o novo nome: ";
            limparBuffer();
            getline(cin, novoNome);
            produtos[indice].setNome(novoNome);
            break;
        }
        case 2: {
            int novaQtd;
            cout << "Digite a nova quantidade: ";
            cin >> novaQtd;
            produtos[indice].setQuantidade(novaQtd);
            break;
        }
        case 3: {
            float novoPreco;
            cout << "Digite o novo preco: ";
            cin >> novoPreco;
            produtos[indice].setPreco(novoPreco);
            break;
        }
        default:
            cout << "Opcao invalida.\n";
            return;
    }
    cout << "Produto alterado com sucesso!\n";
}

void excluirProduto(vector<Produto>& produtos) {
    int codigo;
    cout << "Digite o codigo do produto a ser excluido: ";
    cin >> codigo;
    int indice = encontrarIndiceProduto(produtos, codigo);

    if (indice == -1) {
        cout << "Erro: Produto nao encontrado.\n";
        return;
    }
    produtos.erase(produtos.begin() + indice);
    cout << "Produto excluido com sucesso!\n";
}

void consultarProduto(const vector<Produto>& produtos) {
    int codigo;
    cout << "Digite o codigo do produto a ser consultado: ";
    cin >> codigo;
    int indice = encontrarIndiceProduto(produtos, codigo);

    if (indice == -1) {
        cout << "Erro: Produto nao encontrado.\n";
        return;
    }
    produtos[indice].mostrarDados();
}

// Vendedor

void cadastrarVendedor(vector<Vendedor>& vendedores) {
    string nome;
    float salario;

    cout << "Nome do vendedor: ";
    limparBuffer();
    getline(cin, nome);
    cout << "Salario fixo do vendedor: ";
    cin >> salario;

    vendedores.emplace_back(nome, salario);

    ofstream arquivo("vendedor.txt", ios::app);
    if (arquivo.is_open()) {
        vendedores.back().salvarNoArquivo(arquivo);
        arquivo.close();
    } else {
        cerr << "ERRO: Nao foi possivel abrir o arquivo vendedor.txt para salvamento." << endl;
    }
    // ------------------------------------------------

    cout << "\nVendedor cadastrado com sucesso! Numero gerado: " << vendedores.back().getNumero() << endl;
}

void alterarVendedor(vector<Vendedor>& vendedores) {
    int numero;
    cout << "Digite o numero do vendedor a ser alterado: ";
    cin >> numero;
    int indice = encontrarIndiceVendedor(vendedores, numero);

    if (indice == -1) {
        cout << "Erro: Vendedor nao encontrado.\n";
        return;
    }

    cout << "Vendedor encontrado:\n";
    vendedores[indice].mostrarDados();

    int opcao;
    cout << "O que deseja alterar?\n1. Nome\n2. Salario\nOpcao: ";
    cin >> opcao;

    switch (opcao) {
        case 1: {
            string novoNome;
            cout << "Digite o novo nome: ";
            limparBuffer();
            getline(cin, novoNome);
            vendedores[indice].setNome(novoNome);
            break;
        }
        case 2: {
            float novoSalario;
            cout << "Digite o novo salario: ";
            cin >> novoSalario;
            vendedores[indice].setSalario(novoSalario);
            break;
        }
        default:
            cout << "Opcao invalida.\n";
            return;
    }
    cout << "Vendedor alterado com sucesso!\n";
}

void excluirVendedor(vector<Vendedor>& vendedores) {
    int numero;
    cout << "Digite o numero do vendedor a ser excluido: ";
    cin >> numero;
    int indice = encontrarIndiceVendedor(vendedores, numero);

    if (indice == -1) {
        cout << "Erro: Vendedor nao encontrado.\n";
        return;
    }
    vendedores.erase(vendedores.begin() + indice);
    cout << "Vendedor excluido com sucesso!\n";
}

void consultarVendedor(const vector<Vendedor>& vendedores) {
    int numero;
    cout << "Digite o numero do vendedor a ser consultado: ";
    cin >> numero;
    int indice = encontrarIndiceVendedor(vendedores, numero);

    if (indice == -1) {
        cout << "Erro: Vendedor nao encontrado.\n";
        return;
    }
    vendedores[indice].mostrarDados();
}

// Comprador

void cadastrarComprador(vector<Comprador>& compradores) {
    string nome, cpf, email, rua, bairro, cidade, estado, cep;
    cout << "Nome do comprador: ";
    limparBuffer();
    getline(cin, nome);
    cout << "CPF: ";
    getline(cin, cpf);
    cout << "Email: ";
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

    Endereco novoEndereco(rua, bairro, cidade, estado, cep);
    compradores.emplace_back(nome, cpf, email, novoEndereco);

    cout << "\nComprador cadastrado com sucesso!\n";
}

void alterarComprador(vector<Comprador>& compradores) {
    string cpf;
    cout << "Digite o CPF do comprador a ser alterado: ";
    limparBuffer();
    getline(cin, cpf);
    int indice = encontrarIndiceComprador(compradores, cpf);

    if (indice == -1) {
        cout << "Erro: Comprador nao encontrado.\n";
        return;
    }

    cout << "Comprador encontrado:\n";
    compradores[indice].exibirDados();

    int opcao;
    cout << "O que deseja alterar?\n1. Nome\n2. Email\n3. Endereco\nOpcao: ";
    cin >> opcao;

    switch (opcao) {
        case 1: {
            string novoNome;
            cout << "Digite o novo nome: ";
            limparBuffer();
            getline(cin, novoNome);
            compradores[indice].setNome(novoNome);
            break;
        }
        case 2: {
            string novoEmail;
            cout << "Digite o novo email: ";
            limparBuffer();
            getline(cin, novoEmail);
            compradores[indice].setEmail(novoEmail);
            break;
        }
        case 3: {
            string rua, bairro, cidade, estado, cep;
            cout << "--- Novo Endereco ---\n";
            limparBuffer();
            cout << "Rua: "; getline(cin, rua);
            cout << "Bairro: "; getline(cin, bairro);
            cout << "Cidade: "; getline(cin, cidade);
            cout << "Estado: "; getline(cin, estado);
            cout << "CEP: "; getline(cin, cep);
            compradores[indice].setEndereco(Endereco(rua, bairro, cidade, estado, cep));
            break;
        }
        default:
            cout << "Opcao invalida.\n";
            return;
    }
    cout << "Comprador alterado com sucesso!\n";
}

void excluirComprador(vector<Comprador>& compradores) {
    string cpf;
    cout << "Digite o CPF do comprador a ser excluido: ";
    limparBuffer();
    getline(cin, cpf);
    int indice = encontrarIndiceComprador(compradores, cpf);

    if (indice == -1) {
        cout << "Erro: Comprador nao encontrado.\n";
        return;
    }
    compradores.erase(compradores.begin() + indice);
    cout << "Comprador excluido com sucesso!\n";
}

void consultarComprador(const vector<Comprador>& compradores) {
    string cpf;
    cout << "Digite o CPF do comprador a ser consultado: ";
    limparBuffer();
    getline(cin, cpf);
    int indice = encontrarIndiceComprador(compradores, cpf);

    if (indice == -1) {
        cout << "Erro: Comprador nao encontrado.\n";
        return;
    }
    compradores[indice].exibirDados();
}

// Venda

void realizarVenda(vector<Venda>& vendas, vector<Vendedor>& vendedores, vector<Comprador>& compradores, vector<Produto>& produtos) {
    if (vendedores.empty() || compradores.empty() || produtos.empty()) {
        cout << "Nao e possivel realizar uma venda. Cadastre vendedores, compradores e produtos primeiro.\n";
        return;
    }

    string cpfComprador;
    int numVendedor;

    cout << "Digite o CPF do comprador: ";
    limparBuffer();
    getline(cin, cpfComprador);
    int indiceComprador = encontrarIndiceComprador(compradores, cpfComprador);
    if (indiceComprador == -1) {
        cout << "Comprador nao encontrado. Venda cancelada.\n";
        return;
    }

    cout << "Digite o numero do vendedor: ";
    cin >> numVendedor;
    int indiceVendedor = encontrarIndiceVendedor(vendedores, numVendedor);
    if (indiceVendedor == -1) {
        cout << "Vendedor nao encontrado. Venda cancelada.\n";
        return;
    }

    Venda novaVenda(vendedores[indiceVendedor], compradores[indiceComprador]);
    char continuar = 'S';

    while (toupper(continuar) == 'S') {
        int codProduto, qtdDesejada;
        cout << "\nDigite o codigo do produto a adicionar ao carrinho: ";
        cin >> codProduto;
        int indiceProduto = encontrarIndiceProduto(produtos, codProduto);

        if (indiceProduto != -1) {
            produtos[indiceProduto].mostrarDados();
            cout << "Digite a quantidade desejada: ";
            cin >> qtdDesejada;
            if (qtdDesejada > 0 && produtos[indiceProduto].getQuantidade() >= qtdDesejada) {
                novaVenda.adicionarProduto(produtos[indiceProduto], qtdDesejada);
                int estoqueAtual = produtos[indiceProduto].getQuantidade();
                produtos[indiceProduto].setQuantidade(estoqueAtual - qtdDesejada);
                cout << "Produto adicionado ao carrinho!\n";
            } else {
                cout << "Quantidade invalida ou estoque insuficiente. (Estoque: " << produtos[indiceProduto].getQuantidade() << ")\n";
            }
        } else {
            cout << "Produto nao encontrado.\n";
        }

        cout << "Deseja adicionar outro produto? (S/N): ";
        cin >> continuar;
    }

    if (novaVenda.getValorTotal() > 0) {
        vendas.push_back(novaVenda);
        vendedores[indiceVendedor].calculaComissao(novaVenda.getValorTotal());
        cout << "\n--- Venda Realizada com Sucesso! ---\n";
        novaVenda.mostrarDados();

        string nomeArquivo;
        cout << "Digite o nome para o arquivo da nota fiscal (ex: nota01.txt): ";
        limparBuffer();
        getline(cin, nomeArquivo);

        ofstream arquivoNota(nomeArquivo);

        if (!arquivoNota.is_open()) {
            cerr << "ERRO: Nao foi possivel criar o arquivo da nota fiscal: " << nomeArquivo << endl;
        } else {
            gerarNotaFiscal(novaVenda, arquivoNota);
            arquivoNota.close();
            cout << "Nota fiscal gerada com sucesso no arquivo '" << nomeArquivo << "'\n";
        }
    } else {
        cout << "Carrinho vazio. Venda cancelada.\n";
    }
}

void consultarVenda(const vector<Venda>& vendas) {
    int codigo;
    cout << "Digite o codigo da venda a ser consultada: ";
    cin >> codigo;
    int indice = encontrarIndiceVenda(vendas, codigo);

    if (indice == -1) {
        cout << "Erro: Venda nao encontrada.\n";
        return;
    }
    vendas[indice].mostrarDados();
}

// Menu

void menuProdutos(vector<Produto>& produtos) {
    int opcao;
    do {
        exibirSubMenu("Produto");
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarProduto(produtos); break;
            case 2: alterarProduto(produtos); break;
            case 3: excluirProduto(produtos); break;
            case 4: consultarProduto(produtos); break;
            case 0: break;
            default: cout << "Opcao invalida.\n"; break;
        }
    } while (opcao != 0);
}

void menuVendedores(vector<Vendedor>& vendedores) {
    int opcao;
    do {
        exibirSubMenu("Vendedor");
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarVendedor(vendedores); break;
            case 2: alterarVendedor(vendedores); break;
            case 3: excluirVendedor(vendedores); break;
            case 4: consultarVendedor(vendedores); break;
            case 0: break;
            default: cout << "Opcao invalida.\n"; break;
        }
    } while (opcao != 0);
}

void menuCompradores(vector<Comprador>& compradores) {
    int opcao;
    do {
        exibirSubMenu("Comprador");
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarComprador(compradores); break;
            case 2: alterarComprador(compradores); break;
            case 3: excluirComprador(compradores); break;
            case 4: consultarComprador(compradores); break;
            case 0: break;
            default: cout << "Opcao invalida.\n"; break;
        }
    } while (opcao != 0);
}

void menuVendas(vector<Venda>& vendas, vector<Vendedor>& vendedores, vector<Comprador>& compradores, vector<Produto>& produtos) {
    int opcao;
    cout << "\n--- Menu de Vendas ---\n";
    cout << "1. Realizar Nova Venda\n";
    cout << "2. Consultar Venda\n";
    cout << "0. Voltar\n";
    cout << "Opcao: ";
    cin >> opcao;

    switch(opcao) {
        case 1:
            realizarVenda(vendas, vendedores, compradores, produtos);
            break;
        case 2:
            consultarVenda(vendas);
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida.\n";
            break;
    }
}