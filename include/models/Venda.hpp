#pragma once
#include <vector>
#include "Produto.hpp"
#include "Vendedor.hpp"
#include "Comprador.hpp"

class Venda {
private:
    int codigoVenda;
    const Vendedor& vendedor;
    const Comprador& comprador;
    std::vector<Produto> produtosVendidos;
    float valorTotal;

    void gerarCodigoVenda();
    void calcularValorTotal();

public:
    Venda(const Vendedor& vend, const Comprador& comp);

    void adicionarProduto(const Produto& produto, int quantidade);

    int getCodigoVenda() const;
    float getValorTotal() const;
    const Vendedor& getVendedor() const;
    const Comprador& getComprador() const;
    const std::vector<Produto>& getProdutosVendidos() const;

    void mostrarDados() const;
};