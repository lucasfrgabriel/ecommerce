#pragma once
#include <iostream>
using namespace std;

class Endereco {
private:
    string rua;
    string bairro;
    string cidade;
    string estado;
    string cep;

public:
    Endereco() {
        rua = "";
        bairro = "";
        cidade = "";
        estado = "";
        cep = "";
    }

    void setRua(const string& r) { rua = r; }
    void setBairro(const string& b) { bairro = b; }
    void setCidade(const string& c) { cidade = c; }
    void setEstado(const string& e) { estado = e; }
    void setCep(const string& c) { cep = c; }

    string getRua() const { return rua; }
    string getBairro() const { return bairro; }
    string getCidade() const { return cidade; }
    string getEstado() const { return estado; }
    string getCep() const { return cep; }

    string getEnderecoCompleto() const {
        if (rua.empty()) return "Endereco nao cadastrado.";
        return rua + ", " + bairro + ", " + cidade + " - " + estado + ", CEP: " + cep;
    }
};

class Comprador {
private:
    string nome;
    string cpf;
    string email;
    Endereco enderecoEntrega;

public:
    Comprador() {
        nome = "";
        cpf = "";
        email = "";
    }

    Comprador(const string& nomeComprador, const string& cpfComprador, const string& emailComprador,
              const string& rua, const string& bairro, const string& cidade, const string& estado, const string& cep) :
        nome(nomeComprador),
        cpf(cpfComprador),
        email(emailComprador)
    {
        setDadosEndereco(rua, bairro, cidade, estado, cep);
    }
    ~Comprador(){}


    void setNome(const string& n) { nome = n; }
    string getNome() const { return nome; }

    void setCpf(const string& c) { cpf = c; }
    string getCpf() const { return cpf; }

    void setEmail(const string& e) { email = e; }
    string getEmail() const { return email; }

    void setDadosEndereco(const string& r, const string& b, const string& cid, const string& est, const string& cp) {
        enderecoEntrega.setRua(r);
        enderecoEntrega.setBairro(b);
        enderecoEntrega.setCidade(cid);
        enderecoEntrega.setEstado(est);
        enderecoEntrega.setCep(cp);
    }

    const Endereco& getEndereco() const {
        return enderecoEntrega;
    }

    void exibirDados() const {
        cout << "\n Dados do Comprador \n";
        cout << "Nome: " << getNome() << endl;
        cout << "CPF: " << getCpf() << endl;
        cout << "E-mail: " << getEmail() << endl;
        cout << "Endereco: " << getEndereco().getEnderecoCompleto() << endl;
    }
};