#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

class Produtos{
    private:
        string nome;
        int codigo;
        int quantidade;
        float preco;

		void gerarCodigo(){
			codigo = rand()%1000;
		}
    public:
		Produtos(){
			nome = "";
			quantidade = 0;
			preco = 0;
		}
		Produtos(string n, int q, float p){
			setNome(n);
			setQuantidade(q);
			setPreco(p);
			gerarCodigo();
		}
		~Produtos(){}

		void setCodigo(int c) {
			codigo = c;
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