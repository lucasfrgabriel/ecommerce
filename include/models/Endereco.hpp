#pragma once
#include <string>

class Endereco {
private:
    std::string rua;
    std::string bairro;
    std::string cidade;
    std::string estado;
    std::string cep;

public:
    Endereco();
    Endereco(const std::string& r, const std::string& b, const std::string& c, const std::string& e, const std::string& cp);

    void setRua(const std::string& r);
    void setBairro(const std::string& b);
    void setCidade(const std::string& c);
    void setEstado(const std::string& e);
    void setCep(const std::string& cp);

    std::string getRua() const;
    std::string getBairro() const;
    std::string getCidade() const;
    std::string getEstado() const;
    std::string getCep() const;
    std::string getEnderecoCompleto() const;
};