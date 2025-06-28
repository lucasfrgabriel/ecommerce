class Vendas {
private:
    int codigo_venda;
    Comprador comprador;
    Vendedores &vendedor;

    Produtos* listaProdutos;
    int capacidade;
    int quantidadeProdutos;

    float valorTotal;
    bool vendaFinalizada;

    void gerarCodigoVenda() {
        codigo_venda = rand()%1000;
    }

    void calcularValorTotal() {
        valorTotal = 0;
        for (int i = 0; i < quantidadeProdutos; i++) {
            valorTotal += listaProdutos[i].getPreco() * listaProdutos[i].getQuantidade();
        }
    }

public:
    Vendas(Comprador c, Vendedores &v, int totalItensDistintos) : vendedor(v) {
        comprador = c;
        valorTotal = 0;
        quantidadeProdutos = 0;
        vendaFinalizada = false;

        capacidade = totalItensDistintos > 0 ? totalItensDistintos : 1;
        listaProdutos = new Produtos[capacidade];

        gerarCodigoVenda();
    }

    ~Vendas() {
        delete[] listaProdutos;
    }

    void adicionarProduto(Produtos &p, int quantidadeVendida) {
        if (vendaFinalizada) {
            std::cout << "Erro: Esta venda ja foi finalizada e nao pode ser alterada." << std::endl;
            return;
        }

        if (quantidadeProdutos >= capacidade) {
            std::cout << "Erro: Limite de produtos para esta venda foi atingido!" << std::endl;
            return;
        }

        if (p.getQuantidade() < quantidadeVendida) {
            std::cout << "Erro: Estoque insuficiente para o produto " << p.getNome() << std::endl;
            return;
        }

        Produtos produtoVendido = p;
        produtoVendido.setQuantidade(quantidadeVendida);

        listaProdutos[quantidadeProdutos] = produtoVendido;
        quantidadeProdutos++;

        p.setQuantidade(p.getQuantidade() - quantidadeVendida);
    }

    void finalizarVenda() {
        if (vendaFinalizada) {
            std::cout << "Aviso: Esta venda ja foi finalizada anteriormente." << std::endl;
            return;
        }
        calcularValorTotal();

        vendedor.setComissoes(valorTotal);

        vendaFinalizada = true;

        std::cout << "Venda " << getCodigoVenda() << " finalizada com sucesso!" << std::endl;
        std::cout << "Valor total: R$ " << getValorTotal() << std::endl;
        std::cout << "Comissao de R$ " << comissaoDaVenda << " adicionada ao vendedor " << vendedor.getNome() << "." << std::endl;
    }

    int getCodigoVenda() { return codigo_venda; }
    float getValorTotal() {
        calcularValorTotal();
        return valorTotal;
    }
};