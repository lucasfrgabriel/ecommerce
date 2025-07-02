#pragma once
#include <iostream>
using namespace std;

class Vendedores{
    private:
    string nome;
    int numero;
    float salario;
    float comissoes;

    void gerarNumero() {
        if (numero == 0) {
            seed = time(0);
            srand(seed);
            numero = rand()%1000;
        }
    }

    public:
    Vendedores(){
        nome = "";
        numero = 0;
        salario = 0;
        comissoes = 0.03;
    }
    Vendedores(string name, float salarioFixo);{
        setNome(name);
        gerarNumero();
        setSalario(salarioFixo);
        comissoes = 0.03;
    }

    void setNome(string n){
        if(!n.empty()){
            nome = n;
        }
    }

    void setSalario(float s){
        if(s > 0){
            salario = s;
        }
    }

    void setComissoes(float c) {
        salario += (comissoes * c);
    }

    string getNome(){return nome;}
    int getNumero(){return numero;}
    float getSalario(){return salario;}
    float getComissoes(){return comissoes;}

    void salvarNoArquivo(ofstream &arquivo) {
        arquivo << "-------------------------------------------------------------------------------------------------------------------------\n";
        arquivo << "Nome: " << nome << " - numero: " << numero << " - salário: " << salario << " - comissões: " << comissoes<< "\n";
        arquivo << "-------------------------------------------------------------------------------------------------------------------------\n";
    }
};