/* Classe pilha encadeada
 *
 * by Gustavo Dantas Galote de Lima Padilha, 2023, Estruturas de Dados
 *
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
   cout << "Nome: " << umDado.nome << " ";
   cout << " Tipo: " << umDado.tipo << " ";
   cout << " Valor: " << umDado.valor << endl;
}

class Noh {
    friend class Pilha;
    private:
        Dado mDado;
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Pilha {
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se não for possível desempilhar.
        Dado Desempilhar(); // retorna o mPtTopo da Pilha.
        // Insere um valor na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no mPtTopo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
    private:
        Noh* mPtTopo;
};

Pilha::Pilha() {
  this->mPtTopo = nullptr;
}

bool Pilha::Vazia() {
    return (this->mPtTopo == nullptr);
}

Pilha::~Pilha() {
  while (this->mPtTopo != nullptr)
  {
    Noh *temp = this->mPtTopo;
    this->mPtTopo = this->mPtTopo->mProx;
    delete temp;
  }
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    Dado dado = this->mPtTopo->mDado; // guarda o dado do topo
    Noh *aux = this->mPtTopo; // guarda o endereço do topo
    this->mPtTopo = this->mPtTopo->mProx;  // atualiza o topo
    delete aux; // desaloca o topo previo
    return dado;
}

void Pilha::Empilhar(const Dado& d) {
   Noh *novoNoh = new Noh(d);
   novoNoh->mProx = this->mPtTopo;
   this->mPtTopo = novoNoh;
}

void Pilha::LimparTudo() {
  while(this->mPtTopo != nullptr) {
    Noh *aux = this->mPtTopo->mProx;
    delete this->mPtTopo;
    this->mPtTopo = aux;
  }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    imprimir_dado(this->mPtTopo->mDado);
}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar                
                    pilha.Topo();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}