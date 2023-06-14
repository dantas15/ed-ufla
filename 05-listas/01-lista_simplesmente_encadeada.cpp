/* 
 * Classe lista, uma lista dinamicamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe{
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
noh::noh(equipe d){
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
lista::~lista( ) {

}    

// remove todos os elementos da lista
void lista::removeTodos( ) {

}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {


    if(this->vazia()) {
        this->primeiro = novo;
        this->ultimo = novo;
    } else {
        novo->proximo = this->primeiro;
        this->primeiro = novo;
    }
    this->tamanho++;
 
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

}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 

}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }
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
}
    
void lista::removeNoInicio() {
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
