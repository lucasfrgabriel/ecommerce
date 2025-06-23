#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Produtos{
    private:
        string nome;
        int codigo;
        int quantidade;
        float preco;
    public:
        void setNome(string n){
            nome = n;
        }
        void setQuantidade(int q){
            quantidade = q;
        }
        void setPreco(float p){
            preco = p;
        }
        void gerarCodigo(){
            unsigned seed = time(0);
            srand(seed);
            codigo = rand()%1000;
        }
        Produtos(string nome, float preco){
            setNome(nome);
            setPreco(preco);
            setQuantidade(quantidade);
            gerarCodigo();
        }
        string getNome(){
            return nome;
        }

        int getCodigo(){
            return codigo;
        }
        int getQuantidade(){
            return quantidade;
        }
        float getPreco(){
            return preco;
        }




int main(){}