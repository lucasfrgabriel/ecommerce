#pragma once
#include <string>
#include <iostream>
#include "Endereco.hpp"

class Comprador {
private:
    std::string nome;
    std::string cpf;
    std::string email;
    Endereco enderecoEntrega;

public:
    Comprador();
    Comprador(const std::string& nome, const std::string& cpf, const std::string& email, const Endereco& endereco);

    void setNome(const std::string& n);
    void setCpf(const std::string& c);
    void setEmail(const std::string& e);
    void setEndereco(const Endereco& endereco);
    void exibirDados() const;
    const Endereco& getEndereco() const;

    std::string getNome() const;
    std::string getCpf() const;
    std::string getEmail() const;

};