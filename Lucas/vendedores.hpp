#pragma once
#include <iostream>
using namespace std;

class Vendedores{
    private:
    string nome;
    int numero;
    float salario;
    float comissoes;

    void setNumero() {
        if (numero == 0) {
            srand(seed);
            numero = rand()%1000;
        }
    }

    public:
    Vendedores(){
        nome = "";
        numero = 0;
        salario = 0;
        comissoes = 0,03;
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

    void setComissoes(float c){
        salario += (comissoes * c);
    }

    void setVendedor(string name, float salarioFixo, float comissao){
        setNome(name);
        setNumero();
        setSalario(salarioFixo);
        setComissoes(comissao);
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