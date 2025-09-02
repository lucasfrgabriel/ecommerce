#include "../../include/models/Produto.hpp"
#include <cstdlib>
#include <fstream>

using namespace std;

Produto::Produto() : nome(""), codigo(0), quantidade(0), preco(0.0f) {}

Produto::Produto(const string& n, int q, float p) {
    setNome(n);
    setQuantidade(q);
    setPreco(p);
    gerarCodigo();
}

void Produto::gerarCodigo() {
    codigo = rand() % 1000 + 1;
}

void Produto::setNome(const string& n) {
    if (!n.empty()) {
        nome = n;
    }
}

void Produto::setQuantidade(int q) {
    if (q >= 0) {
        quantidade = q;
    }
}

void Produto::setPreco(float p) {
    if (p > 0) {
        preco = p;
    }
}

string Produto::getNome() const { return nome; }
int Produto::getCodigo() const { return codigo; }
int Produto::getQuantidade() const { return quantidade; }
float Produto::getPreco() const { return preco; }

void Produto::salvarNoArquivo(ofstream& arquivo) const {
    arquivo << "-----------------------------------\n";
    arquivo << "Nome: " << nome << "\n";
    arquivo << "Codigo: " << codigo << "\n";
    arquivo << "Quantidade: " << quantidade << "\n";
    arquivo << "Preco: R$" << preco << "\n";
    arquivo << "-----------------------------------\n";
}

void Produto::mostrarDados() const {
    cout << "-----------------------------------\n";
    cout << "Nome: " << nome << "\n";
    cout << "Codigo: " << codigo << "\n";
    cout << "Quantidade: " << quantidade << "\n";
    cout << "Preco: R$" << preco << "\n";
    cout << "-----------------------------------\n";
}