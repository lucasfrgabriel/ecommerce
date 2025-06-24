#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;
    class Endereco{
        private:
            string rua;
            string bairro;
            string cidade;
            string estado;
            string cep;
        public:
            Endereco(){
                rua = "";
                bairro = "";
                cidade = "";
                estado = "";
                cep = "";
            }
    void setRua(string r){
            rua = r;
            }
    void setBairro(string b){
            bairro = b;
            }
    void setCidade(string c){
            cidade = c;
            }
    void setEstado(string e){
            estado = e;
            }
    void setCep(string c){
            cep = c;
            }
    string getRua(){
        return rua;
        }
    string getBairro(){
        return bairro;
        }
    string getCidade(){
        return cidade;
        }
    string getEstado(){
        return estado;
        }
    string getCep() {
        return cep;
        }
    string getEnderecoCompleto(){
        return rua + "," + bairro + "," + cidade + " - " + estado + ", CEP:" + cep;
        }
    };
int main(){}