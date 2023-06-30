#include <iostream>
#include <fstream>

using namespace std;

class noh {
    friend class ABB;
private:
    int num;
    noh* esquerdo;
    noh* direito;
    noh* pai;
    int nivel;

public:
    noh(int valor) {
        num = valor;
        esquerdo = NULL;
        direito = NULL;
        pai = NULL;
        nivel = 0;
    }

    noh() {
        num = -1;
        esquerdo = NULL;
        direito = NULL;
        pai = NULL;
        nivel = 0;
    }
};

class ABB {
private:
    noh* raiz;
    noh* buscAux(int umValor);
    void atualizaNiveis(noh* n, int nivel);

public:
    ABB();
    ~ABB();
    void inserir(int valor);
    int minimo();
    noh* minimoAux(noh* raizSub);
    int maximo();
    noh* maximoAux(noh* raizSubArvore);
    void busca(int umValor, noh* &aux);
    void imprime(noh* n);
    void percorreEmOrdem();
    void percorreEmOrdemAux(noh* n);
    void percorrePreOrdem();
    void percorrePreOrdemAux(noh *aux);
    void percorrePosOrdem();
    void percorrePosOrdemAux(noh *aux);
    void transplanta(noh *antigo, noh *novo);
    bool remove(int umValor);

};

ABB::ABB() {
    raiz = NULL;
}

ABB::~ABB() {
    // Implementação da destruição da árvore
}

void ABB::inserir(int valor) {
    noh* novo = new noh(valor);

    if (raiz == NULL) {
        raiz = novo;
    } else {
        noh* aux = raiz;
        noh* anterior;
        int nivel = 0;
        while (aux != NULL) {
            anterior = aux;
            if (aux->num >= valor) {
                aux = aux->esquerdo;
            } else {
                aux = aux->direito;
            }
            nivel++;
        }
        novo->pai = anterior;
        if (anterior->num >= novo->num) {
            anterior->esquerdo = novo;
        } else {
            anterior->direito = novo;
        }
        novo->nivel = nivel;
    }
    atualizaNiveis(raiz, 0);
}

void ABB::atualizaNiveis(noh* n, int nivel) {
    if (n != NULL) {
        n->nivel = nivel;
        atualizaNiveis(n->esquerdo, nivel + 1);
        atualizaNiveis(n->direito, nivel + 1);
    }
}

int ABB::minimo() {
    if (raiz == NULL) {
    	// cerr << "Árvore vazia\n";
        return -1;
    } else {
        noh *min = minimoAux(raiz);
        return min->num;
    }
}

noh* ABB::minimoAux(noh* raizSub) {
    while (raizSub->esquerdo != NULL) {
        raizSub = raizSub->esquerdo;
    }
    return raizSub;
}

int ABB::maximo() {
    if (raiz == NULL) {
        // cerr << "Árvore vazia\n";
        return -1;
    } else {
        noh *max = maximoAux(raiz);
        return max->num;
    }
}

noh* ABB::maximoAux(noh* raizSubArvore) {
    while (raizSubArvore->direito != NULL) {
        raizSubArvore = raizSubArvore->direito;
    }
    return raizSubArvore;
}

noh* ABB::buscAux(int umValor) {
    noh* atual = raiz;
    while (atual != NULL) {
        if (atual->num == umValor) {
            return atual;
        } else if (atual->num > umValor) {
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }
    return atual;
}

void ABB::busca(int umValor, noh* &aux) {
    noh* novo = buscAux(umValor);
    if (novo == NULL) {
    	// cerr << "Não encontrado\n";
    } else {
        aux = novo;
    }
}

void ABB::imprime(noh* n) {
    cout << n->num << "/" << n->nivel << " ";
}

void ABB::percorreEmOrdem() {
    percorreEmOrdemAux(raiz);
    cout << endl;
}

void ABB::percorreEmOrdemAux(noh* n) {
    if (n != NULL) {
        percorreEmOrdemAux(n->esquerdo);
        imprime(n);
        percorreEmOrdemAux(n->direito);
    }
}

void ABB::percorrePreOrdem(){
    percorrePreOrdemAux(raiz);
    cout << endl;
}

void ABB::percorrePreOrdemAux(noh* aux){
    if(aux != NULL) {
        imprime(aux);
        percorrePreOrdemAux(aux->esquerdo);
        percorrePreOrdemAux(aux->direito);
    }
}

void ABB::percorrePosOrdem(){
    percorrePosOrdemAux(raiz);
    cout << endl;
}

void ABB::percorrePosOrdemAux(noh* aux){
    if(aux != NULL) {
        percorrePosOrdemAux(aux->esquerdo);
        percorrePosOrdemAux(aux->direito);
        imprime(aux);
    }
}

void ABB::transplanta(noh *antigo, noh *novo) {
    if(raiz == antigo) {
        raiz = novo;
    } else if(antigo == antigo->pai->esquerdo) {
        antigo->pai->esquerdo = novo;
    } else {
        antigo->pai->direito = novo;
    }

    if(novo != NULL) {
        novo->pai = antigo->pai;
    }
}

bool ABB::remove(int umValor) {
    noh *nohRemover = buscAux(umValor);
    if (nohRemover == NULL) {
        return false;
    } else {
        if(nohRemover->esquerdo == NULL) {
            transplanta(nohRemover, nohRemover->direito);
        } else if(nohRemover->direito == NULL) {
            transplanta(nohRemover, nohRemover->esquerdo);
        } else {
            noh *sucessor = minimoAux(nohRemover->direito);
            if(sucessor->pai != nohRemover) {
                transplanta(sucessor, sucessor->direito);
                sucessor->direito = nohRemover->direito;
                sucessor->direito->pai = sucessor;
            }
            transplanta(nohRemover, sucessor);
            sucessor->esquerdo = nohRemover->esquerdo;
            sucessor->esquerdo->pai = sucessor;
        }
        delete nohRemover;
    }
    atualizaNiveis(raiz, 0);
    return true;
}

int main() {
    ABB arvore;
    char key;
    bool verif;
    int numero;

    do {
    	try {
    	  cin >> key;
    	  switch (key) {
    	  
	    case'i':
	      cin >> numero;
	      arvore.inserir(numero);
	      break;
	    case'r':
	      cin >> numero;
	      verif = arvore.remove(numero);
	      if (verif) {
	        cerr << "ERRO\n";
	      }
	      break;
	    case 'o':
	      arvore.percorreEmOrdem();
	      break;
	    case 'p':
	      arvore.percorrePreOrdem();
	      break;
	    case 'f': // finaliza (checado no do-while)
	    	break;
	    default:
            cerr << "comando inválido\n";
	  }
	} catch (runtime_error& e) {
	  cout << e.what() << endl;
	}
    } while(key != 'f');
    return 0;
}
