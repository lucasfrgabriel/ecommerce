#include "../../include/models/Vendedor.hpp"
#include <cstdlib>

using namespace std;

Vendedor::Vendedor() : nome(""), numero(0), salario(0.0f) {}

Vendedor::Vendedor(const string& name, float salarioFixo) {
    setNome(name);
    setSalario(salarioFixo);
    gerarNumero();
}

void Vendedor::gerarNumero() {
    numero = rand() % 1000 + 1;
}

void Vendedor::setNome(const string& n) {
    if (!n.empty()) {
        nome = n;
    }
}

void Vendedor::setSalario(float s) {
    if (s > 0) {
        salario = s;
    }
}

void Vendedor::calculaComissao(float valorVenda) {
    salario += (taxaComissao * valorVenda);
}

string Vendedor::getNome() const { return nome; }
int Vendedor::getNumero() const { return numero; }
float Vendedor::getSalario() const { return salario; }
float Vendedor::getTaxaComissao() const { return taxaComissao; }

void Vendedor::salvarNoArquivo(ofstream& arquivo) const {
    arquivo << "-----------------------------------\n";
    arquivo << "Nome: " << nome << "\n";
    arquivo << "Numero: " << numero << "\n";
    arquivo << "Salario Base: " << salario << "\n";
    arquivo << "-----------------------------------\n";
}

void Vendedor::mostrarDados() const {
    cout << "-----------------------------------\n";
    cout << "Nome: " << nome << "\n";
    cout << "Numero: " << numero << "\n";
    cout << "Salario: " << salario << "\n";
    cout << "-----------------------------------\n";
}