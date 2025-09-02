#pragma once
#include <string>
#include <iostream>

class Produto {
private:
	std::string nome;
	int codigo{};
	int quantidade{};
	float preco{};

	void gerarCodigo();

public:
	Produto();
	Produto(const std::string& n, int q, float p);

	void setNome(const std::string& n);
	void setQuantidade(int q);
	void setPreco(float p);

	std::string getNome() const;
	int getCodigo() const;
	int getQuantidade() const;
	float getPreco() const;

	void salvarNoArquivo(std::ofstream& arquivo) const;
	void mostrarDados() const;
};