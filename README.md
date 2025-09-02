# Sistema de E-commerce em C++

Este projeto é um sistema de gerenciamento de e-commerce via linha de comando, desenvolvido como trabalho interdisciplinar das disciplinas Fundamentos da Engenharia de Software e Algoritmos e Estruturas de Dados I na PUC Minas. O software foi escrito em C++ com foco em Programação Orientada a Objetos, separação de responsabilidades e boas práticas de organização de código.

---

## 🚀 Funcionalidades

O sistema permite o gerenciamento completo das quatro entidades principais de um e-commerce:

* **📦 Gestão de Produtos:**
    * Cadastro de novos produtos com nome, quantidade em estoque e preço.
    * Alteração dos dados de um produto existente.
    * Exclusão de produtos do sistema.
    * Consulta de produtos por código.

* **👤 Gestão de Vendedores:**
    * Cadastro de vendedores com nome e salário base.
    * Alteração de nome e salário.
    * Exclusão e consulta de vendedores por número de registro.

* **🛒 Gestão de Compradores:**
    * Cadastro de compradores com nome, CPF, e-mail e endereço.
    * Alteração dos dados cadastrais.
    * Exclusão e consulta de compradores por CPF.

* **💰 Gestão de Vendas:**
    * Realização de vendas associando um comprador, um vendedor e múltiplos produtos.
    * Cálculo automático da comissão do vendedor.
    * Atualização do estoque de produtos após a venda.
    * Geração de uma **Nota Fiscal** em um arquivo de texto (`.txt`).

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++.
* **IDE:** Desenvolvido no CLion.
* **Controle de Versão:** Git e GitHub.

---

## 📁 Estrutura do Projeto

O projeto foi organizado em uma estrutura de pastas que separa a interface (`include`) e a implementação (`src`), seguindo as melhores práticas de desenvolvimento em C++.

```
ecommerce/
├── include/
│   ├── models/       # Classes que representam os dados (Produto, Vendedor, etc.)
│   ├── services/     # Funções de serviço que orquestram as operações
│   └── ui/           # Funções da interface do usuário (menus)
├── src/
│   ├── models/       # Implementação das classes de modelo
│   ├── services/     # Implementação dos serviços
│   └── ui/           # Implementação dos menus
│   └── main.cpp      # Ponto de entrada da aplicação
├── .gitignore        # Arquivo para ignorar arquivos de build e da IDE
└── README.md         # Este arquivo
