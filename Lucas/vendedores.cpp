#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Vendedores{
    private:
    string nome;
    int numero;
    float salario;
    float comissoes;

    public:
    Vendedores(){
        nome = "";
        numero = 0;
        salario = 0;
        comissoes = 0;
    }

    void setNome(string n){
        if(!n.empty()){
            nome = n;
        }
    }

    void setNumero() {
        if (numero == 0) {
            numero = 1000 + rand() % 9000;
        }
    }

    void setSalario(float s){
        if(s > 0){
            salario = s;
        }
    }

    void setComissoes(float c){
        if(c > 0){
            comissoes += c;
        }
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
};

int main(){
    srand(time(0));
}