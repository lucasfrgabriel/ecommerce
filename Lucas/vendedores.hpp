#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

class Vendedores{
    private:
    string nome;
    int numero;
    float salario;
    float comissoes = 0.03;

    void gerarNumero() {
        if (numero == 0) {
            numero = rand()%1000;
        }
    }

    public:
    Vendedores(){
        nome = "";
        numero = 0;
        salario = 0;
    }
    Vendedores(string name, float salarioFixo){
        setNome(name);
        gerarNumero();
        setSalario(salarioFixo);
    }
    ~Vendedores(){}
    void setNome(string n){
        if(!n.empty()){
            nome = n;
        }
    }
    void setNumero(int n) {
        numero = n;
    }
    void setSalario(float s){
        if(s > 0){
            salario = s;
        }
    }

    void caculaComissao(float c) {
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
    void mostrarDados() {
        cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Nome: " << nome << " - numero: " << numero << " - salário: " << salario << " - comissões: " << comissoes << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    }
};