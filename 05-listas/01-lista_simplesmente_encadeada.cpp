/* 
 * Classe lista, uma lista dinamicamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe {
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d) {
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
lista::lista() {
    this->tamanho = 0;
    this->primeiro = NULL;
    this->ultimo = NULL;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
    this->tamanho = 0;
    this->primeiro = NULL;
    this->ultimo = NULL;

    noh* aux = umaLista.primeiro;

    while(aux != NULL) {
        this->insereNoFim(aux->elenco);
        aux = aux->proximo;
    }
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista() {
    this->removeTodos();
}    

// remove todos os elementos da lista
void lista::removeTodos( ) {
    noh* aux = this->primeiro;
    noh* temp;

    while(aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }  

    this->tamanho = 0;
    this->primeiro = NULL;
    this->ultimo = NULL;
}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista) {
    // limpa a lista atual
    this->removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        this->insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

void lista::insere(equipe elenco) {
    this->insereNoFim(elenco);
}

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
    noh* novo = new noh(elenco);

    if(this->vazia()) {
        this->primeiro = novo;
        this->ultimo = novo;
    } else {
        this->ultimo->proximo = novo;
        this->ultimo = novo;
    }
    this->tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
    noh* novo = new noh(elenco);

    if(this->vazia()) {
        this->primeiro = novo;
        this->ultimo = novo;
    } else {
        novo->proximo = this->primeiro;
        this->primeiro = novo;
    }
    this->tamanho++;
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){
    noh* novo = new noh(elenco);
    if((posicao <= this->tamanho) and (posicao >= 0)) {
        if(this->vazia()) {
            this->primeiro = novo;
            this->ultimo = novo;
        } else if (posicao == 0) {
            novo->proximo = primeiro;
            this->primeiro = novo;
        } else if (posicao == tamanho) {
            this->ultimo->proximo = novo;
            this->ultimo = novo;
        } else {
            noh* aux = this->primeiro;
            int posAux = 0;

            while( posAux < (posicao-1)) {
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        this->tamanho++;
    } else {
        cerr << "Posição Inexistente!" << endl;
        exit(EXIT_FAILURE);
    }
}

// procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (this->vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;
    int posAux = 0;

    while((aux != NULL) and (aux->elenco.nomeEquipe != valor)) {
        posAux++;
        aux = aux->proximo;
    }

    if(aux == NULL) {
        posAux = -1;
    }

    if (posAux == -1) {
        throw runtime_error("Nao encontrado");
    }

    return posAux;
}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (this->vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;

    while(aux != NULL) {
        cout << "(" << aux->elenco.nomeEquipe << ", ";
        cout << aux->elenco.lider << ", ";
        cout << aux->elenco.linguagem << ", ";
        cout << aux->elenco.qtdMembros << ")";
        aux = aux->proximo;
        cout << endl;
    }
}

void lista::imprimeReverso() {
    this->imprimeReversoAux(primeiro);
    cout << endl;
}


void lista::imprimeReversoAux(noh* umNoh) {
    if(umNoh != NULL) {
        imprimeReversoAux(umNoh->proximo);
        cout << "(" << umNoh->elenco.nomeEquipe << ", ";
        cout << umNoh->elenco.lider << ", ";
        cout << umNoh->elenco.linguagem << ", ";
        cout << umNoh->elenco.qtdMembros << ")" << endl;
    }
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}
   
void lista::removeNoFim() {
     if (primeiro == NULL) {
        // A lista está vazia, não há nada para remover
        throw runtime_error("Remoção em lista vazia!");
    } else if (primeiro->proximo == NULL) {
        // A lista tem apenas um elemento, então remove o primeiro nó
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
        return;
    }

    // Encontra o penúltimo nó
    noh* penultimo = this->primeiro;
    while (penultimo->proximo->proximo != NULL) {
        penultimo = penultimo->proximo;
    }

    // Remove o último nó
    delete this->ultimo;
    this->ultimo = penultimo;
    this->ultimo->proximo = NULL;
}
    
void lista::removeNoInicio() {
    if(this->vazia()){
        throw runtime_error("Remoção em lista vazia!");
    }

    noh* aux = primeiro;
    this->primeiro = this->primeiro->proximo;
    delete aux;

    if (this->primeiro == NULL) {
        // Se o primeiro era o único também atualiza o ponteiro de último
        ultimo = NULL;
    }
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // remover
                    cin >> nomeEquipe;
                    cout << minhaLista.procura(nomeEquipe) <<endl;
                    break;                    
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaLista.imprime();
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