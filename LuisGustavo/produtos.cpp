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
             if(!n.empty()){
            	nome = n;
        	}
        }
		void setCodigo(int c){
			codigo = c;
		}
        void setQuantidade(int q){
            if (q>=0){
				quantidade = q;
			}

        }
        void setPreco(float p){
           	if (p>0){
				preco = p;
			}
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
    private:
        void gerarCodigo(){
            unsigned seed = time(0);
            srand(seed);
            codigo = rand()%1000;
        }
	public:
        Produtos(){
           nome = "";
			codigo = 0;
			quantidade = 0;
			preco = 0;

        }

};



int main(){

}