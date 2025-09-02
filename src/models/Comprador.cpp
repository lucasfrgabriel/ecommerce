#include "../../include/models/Comprador.hpp"

using namespace std;

Comprador::Comprador() : nome(""), cpf(""), email("") {}

Comprador::Comprador(const string& nome, const string& cpf, const string& email, const Endereco& endereco)
    : nome(nome), cpf(cpf), email(email), enderecoEntrega(endereco) {}

void Comprador::setNome(const string& n) { nome = n; }
string Comprador::getNome() const { return nome; }

void Comprador::setCpf(const string& c) { cpf = c; }
string Comprador::getCpf() const { return cpf; }

void Comprador::setEmail(const string& e) { email = e; }
string Comprador::getEmail() const { return email; }

void Comprador::setEndereco(const Endereco& endereco) { enderecoEntrega = endereco; }
const Endereco& Comprador::getEndereco() const { return enderecoEntrega; }

void Comprador::exibirDados() const {
    cout << "\n>> Dados do Comprador <<\n";
    cout << "Nome: " << getNome() << endl;
    cout << "CPF: " << getCpf() << endl;
    cout << "E-mail: " << getEmail() << endl;
    cout << "Endereco: " << getEndereco().getEnderecoCompleto() << endl;
}