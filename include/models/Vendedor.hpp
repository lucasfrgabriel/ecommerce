#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Vendedor {
private:
    std::string nome;
    int numero{};
    float salario{};
    float taxaComissao = 0.03f;

    void gerarNumero();

public:
    Vendedor();
    Vendedor(const std::string& name, float salarioFixo);

    void setNome(const std::string& n);
    void setSalario(float s);

    std::string getNome() const;
    int getNumero() const;
    float getSalario() const;
    float getTaxaComissao() const;

    void calculaComissao(float valorVenda);
    void salvarNoArquivo(std::ofstream& arquivo) const;
    void mostrarDados() const;
};