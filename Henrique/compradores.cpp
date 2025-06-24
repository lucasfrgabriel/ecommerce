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
    class Comprador {
        private:
            string nome;
            string cpf;
            string email;
            Endereco enderecoEntrega;
        public:
        Comprador() {
            nome = "";
            cpf = "";
            email = "";
        }
        void setNome(string n){
            nome = n;
        }
        string getNome(){
            return nome;
        }
        void setCpf(string c){
            cpf = c;
        }
        string getCpf(){
        return cpf;
        }
        void setEmail(string e){
            email = e;
        }
        string getEmail(){
            return email;
        }
        void setDadosEndereco(string r, string b, string cid, string est, string cp) {
           enderecoEntrega.setRua(r);
           enderecoEntrega.setBairro(b);
           enderecoEntrega.setCidade(cid);
           enderecoEntrega.setEstado(est);
           enderecoEntrega.setCep(cp);
        }
        const Endereco& getEndereco() const {
            return enderecoEntrega;
        }
        void exibirDados(){
            cout << "\n Dados do Comprador \n"
            cout << "Nome: " << getNome() << endl;
            cout << "CPF: " << getCpf << endl;
            cout << "E-mail: " << getEmail << endl;
            cout << "Endereco: " << getEndereco().getEnderecoCompleto() << endl;
        }
    };
int main(){
}