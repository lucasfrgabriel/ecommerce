#pragma once
#include <iostream>
#include "vendedores.hpp"
#include "../LuisGustavo/produtos.hpp"
using namespace std;

class Vendas {
private:
    int codigo_venda;
    string nomeComprador;
    Vendedores &vendedor;

    Produtos* listaProdutos;
    int capacidade;
    int quantidadeProdutos;

    float valorTotal;
    bool vendaFinalizada;

    void gerarCodigoVenda() {
        srand(time(0));
        codigo_venda = rand() % 1000;
    }

    void calcularValorTotal() {
        valorTotal = 0;
        for (int i = 0; i < quantidadeProdutos; i++) {
            valorTotal += listaProdutos[i].getPreco() * listaProdutos[i].getQuantidade();
        }
    }

public:
    Vendas() : codigo_venda(0), nomeComprador(""), vendedor(*(new Vendedores)),
               listaProdutos(nullptr), capacidade(0), quantidadeProdutos(0),
               valorTotal(0), vendaFinalizada(false) {}

    Vendas(string nomeComprador, Vendedores &vendedor, int totalItensDistintos)
        : nomeComprador(nomeComprador), vendedor(vendedor) {
        valorTotal = 0;
        quantidadeProdutos = 0;
        vendaFinalizada = false;

        capacidade = (totalItensDistintos > 0) ? totalItensDistintos : 1;
        listaProdutos = new Produtos[capacidade];

        gerarCodigoVenda();
    }

    ~Vendas() {
        delete[] listaProdutos;
    }

    void finalizarVenda() {
        if (vendaFinalizada) {
            cout << "Aviso: Venda já finalizada." << endl;
            return;
        }

        calcularValorTotal();
        vendedor.setComissoes(valorTotal);
        vendaFinalizada = true;
    }

    int getCodigoVenda() const { return codigo_venda; }
    string getNomeComprador() const { return nomeComprador; }
    string getNomeVendedor() const { return vendedor.getNome(); }
    float getValorTotal() { calcularValorTotal(); return valorTotal; }
    bool isFinalizada() const { return vendaFinalizada; }

    void setNomeComprador(const string &novoNome) {
        if (!vendaFinalizada) {
            nomeComprador = novoNome;
        } else {
            cout << "Erro: Venda finalizada. Não é possível alterar o comprador." << endl;
        }
    }

    void setProduto(Produtos &p, int quantidadeVendida) {
        if (vendaFinalizada) {
            cout << "Erro: Venda finalizada. Não é possível adicionar produtos." << endl;
            return;
        }

        if (quantidadeProdutos >= capacidade) {
            cout << "Erro: Capacidade máxima de produtos atingida." << endl;
            return;
        }

        if (p.getQuantidade() < quantidadeVendida) {
            cout << "Erro: Estoque insuficiente para " << p.getNome() << endl;
            return;
        }

        Produtos produtoVendido = p;
        produtoVendido.setQuantidade(quantidadeVendida);
        listaProdutos[quantidadeProdutos] = produtoVendido;
        quantidadeProdutos++;

        p.setQuantidade(p.getQuantidade() - quantidadeVendida);
    }
};