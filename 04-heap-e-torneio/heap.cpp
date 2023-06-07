/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
    alterado em 2023 by Renato
*/

#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

bool operator>(dado d1, dado d2) {
    return d1.energiaGasta > d2.energiaGasta;
}

bool operator<(dado d1, dado d2) {
    return d1.energiaGasta < d2.energiaGasta;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade <<"] "; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
};

MaxHeap::MaxHeap(int cap) {
    capacidade = cap;
    tamanho = 0;
    heap = new dado[cap];
}

MaxHeap::~MaxHeap() {
    delete[] heap;
}

int MaxHeap::pai(int i) {
    return (i - 1) / 2;
}

int MaxHeap::esquerdo(int i) {
    return 2 * i + 1;
}

int MaxHeap::direito(int i) {
    return 2 * i + 2;
}

void MaxHeap::corrigeDescendo(int i) {
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;

    if ((esq < tamanho) && (heap[esq].energiaGasta > heap[maior].energiaGasta)) {
        maior = esq;
    }

    if ((dir < tamanho) && (heap[dir].energiaGasta > heap[maior].energiaGasta)) {
        maior = dir;
    }

    if(maior != i) {
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i) {
    int p = pai(i);
    if(heap[i].energiaGasta > heap[p].energiaGasta) {
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}
        
void MaxHeap::imprime() {
    if(tamanho == 0) {
        throw runtime_error("Heap vazia!");
    }
    for (int i=0; i<tamanho; i++) {
        operator<<(cout, heap[i]);
    }
    cout << endl;
}

dado MaxHeap::retiraRaiz() {
    if(tamanho == 0) {
        throw runtime_error("Erro ao retirar raiz");
    }
    dado aux = heap[0];
    swap(heap[0], heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}


void MaxHeap::insere(dado d){
    if(tamanho == capacidade) {
        throw runtime_error("Erro ao inserir");
    }
    heap[tamanho] = d; 
    corrigeSubindo(tamanho);
    tamanho++;
}


int main() {
    int capacidade;
    dado info;
    char comando;

    cin >> capacidade;
    MaxHeap meuHeap(capacidade);

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                    meuHeap.insere(info);
                    break;
                case 'r': // remover
                    cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                    break;
                case 'p': // limpar tudo
                    meuHeap.imprime();
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
    cout << endl;
    return 0;
}

/* TESTES (ENTRADA E SAÍDA ESPERADOS)
10
r
Erro ao retirar raiz
p
Heap vazia!
i livingroom r 35 58 5
i tvroom t 18 28 8
i kitchen c 180 200 1
i bedroom1 x 99 90 2
i bedroom2 x 33 50 5
i bedroom3 v 56 80 8
p
[kitchen/c/180/200/1] [bedroom1/x/99/90/2] [bedroom3/v/56/80/8] [tvroom/t/18/28/8] [bedroom2/x/33/50/5] [livingroom/r/35/58/5] 
r
kitchen
p
[bedroom1/x/99/90/2] [livingroom/r/35/58/5] [bedroom3/v/56/80/8] [tvroom/t/18/28/8] [bedroom2/x/33/50/5] 
f
*/