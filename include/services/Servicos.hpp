#pragma once
#include <vector>
#include "../models/Produto.hpp"
#include "../models/Vendedor.hpp"
#include "../models/Comprador.hpp"
#include "../models/Venda.hpp"

void limparBuffer();

void menuProdutos(std::vector<Produto>& produtos);
void menuVendedores(std::vector<Vendedor>& vendedores);
void menuCompradores(std::vector<Comprador>& compradores);
void menuVendas(std::vector<Venda>& vendas, std::vector<Vendedor>& vendedores, std::vector<Comprador>& compradores, std::vector<Produto>& produtos);

void realizarVenda(std::vector<Venda>& vendas, std::vector<Vendedor>& vendedores, std::vector<Comprador>& compradores, std::vector<Produto>& produtos);