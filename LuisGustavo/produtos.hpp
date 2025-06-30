#pragma once
#include <iostream>
using namespace std;

class Produtos{
    private:
        string nome;
        int codigo;
        int quantidade;
        float preco;

		void gerarCodigo(){
			srand(seed);
			codigo = rand()%1000;
		}
    public:
		Produtos(){
			nome = "";
			gerarCodigo();
			quantidade = 0;
			preco = 0;
		}
		Produtos(string n, int q, float p){
			setNome(n);
			setQuantidade(q);
			setPreco(p);

		}
        void setNome(string n){
             if(!n.empty()){
            	nome = n;
        	}
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
	void salvarNoArquivo(ofstream &arquivo) {
			arquivo << "--------------------------------------------------------------------------------------------------------------------------\n";
			arquivo << "Nome: " << nome << " - codigo: " << codigo << " - quantidade: " << quantidade << " - preço: " << preco << "\n";
			arquivo << "---------------------------------------------------------------------------------------------------------------------------\n";
	}
};