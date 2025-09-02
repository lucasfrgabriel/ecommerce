#include "../../include/models/Venda.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

Venda::Venda(const Vendedor& vend, const Comprador& comp)
    : vendedor(vend), comprador(comp), valorTotal(0.0f) {
    gerarCodigoVenda();
}

void Venda::gerarCodigoVenda() {
    codigoVenda = rand() % 10000 + 1;
}

void Venda::calcularValorTotal() {
    valorTotal = 0.0f;
    for (const auto& produto : produtosVendidos) {
        valorTotal += produto.getPreco() * produto.getQuantidade();
    }
}

void Venda::adicionarProduto(const Produto& produto, int quantidade) {
    if (quantidade > 0) {
        Produto itemVendido = produto;
        itemVendido.setQuantidade(quantidade);
        produtosVendidos.push_back(itemVendido);
        calcularValorTotal();
    }
}

int Venda::getCodigoVenda() const { return codigoVenda; }
float Venda::getValorTotal() const { return valorTotal; }
const Vendedor& Venda::getVendedor() const { return vendedor; }
const Comprador& Venda::getComprador() const { return comprador; }
const vector<Produto>& Venda::getProdutosVendidos() const { return produtosVendidos; }


void Venda::mostrarDados() const {
    cout << "-----------------------------------\n";
    cout << ">> Detalhes da Venda #" << getCodigoVenda() << " <<\n";
    cout << "Vendedor: " << vendedor.getNome() << "\n";
    cout << "Comprador: " << comprador.getNome() << " (CPF: " << comprador.getCpf() << ")\n";
    cout << "Produtos Comprados:\n";
    for (const auto& produto : produtosVendidos) {
        cout << "  - " << produto.getNome()
                  << " | Qtd: " << produto.getQuantidade()
                  << " | Subtotal: R$" << produto.getPreco() * produto.getQuantidade()
                  << endl;
    }
    cout << "Valor Total da Venda: R$" << getValorTotal() << endl;
    cout << "-----------------------------------\n";
}