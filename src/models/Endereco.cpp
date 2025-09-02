#include "../../include/models/Endereco.hpp"

using namespace std;

Endereco::Endereco() : rua(""), bairro(""), cidade(""), estado(""), cep("") {}

Endereco::Endereco(const string& r, const string& b, const string& c, const string& e, const string& cp)
    : rua(r), bairro(b), cidade(c), estado(e), cep(cp) {}

void Endereco::setRua(const string& r) { rua = r; }
void Endereco::setBairro(const string& b) { bairro = b; }
void Endereco::setCidade(const string& c) { cidade = c; }
void Endereco::setEstado(const string& e) { estado = e; }
void Endereco::setCep(const string& cp) { cep = cp; }

string Endereco::getRua() const { return rua; }
string Endereco::getBairro() const { return bairro; }
string Endereco::getCidade() const { return cidade; }
string Endereco::getEstado() const { return estado; }
string Endereco::getCep() const { return cep; }

string Endereco::getEnderecoCompleto() const {
    if (rua.empty()) return "Endereco nao cadastrado.";
    return rua + ", " + bairro + ", " + cidade + " - " + estado + ", CEP: " + cep;
}