#pragma once
#include <iostream>
#include "vendedores.hpp"
#include "../LuisGustavo/produtos.hpp"
using namespace std;

class Vendas {
private:
    int codVendedor;
    int quantidadeProdutos;
    float valorTotal;
    int codigo_venda;
    Produtos *produtos = new Produtos[20];

    bool vendaFinalizada;

    void gerarCodigoVenda() {
        codigo_venda = rand() % 1000;
    }


    void calcularValorTotal(int itens[], int n, int quantidade[]) {
        valorTotal = 0;
        for (int i = 0; i < n; i++) {
            int j = itens[i];
            valorTotal += produtos[j].getPreco() * quantidade[i];
        }
    }

public:
    Vendas() {
        quantidadeProdutos = 0;
        valorTotal = 0;
        codVendedor = -1;
    }

    Vendas(int indiceVendedor, int indiceComprador, int carrinho[], int nItens, int quantidade[]) {
        gerarCodigoVenda();
        calcularValorTotal(carrinho, nItens, quantidade);
        quantidadeProdutos = nItens;
    }

    ~Vendas() {
        delete[] produtos;
    }
    void setCodigoVenda(int c) {
        codigo_venda = c;
    }

    int getCodigoVenda() const { return codigo_venda; }
    float getValorTotal() { return valorTotal; }

    void mostrarDados() {
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Codigo do vendedor: " << codVendedor << " - quantidade de produtos: " << quantidadeProdutos << " - valor total: " << valorTotal << " - codigo de venda: " << codigo_venda << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};