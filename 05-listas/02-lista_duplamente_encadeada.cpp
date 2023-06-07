/* 
 * Classe listadup, uma lista dinamicamente duplamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma {
    int identificador;
    string nomeAcao;
    int tempoExecucao; 
    int tempoConsumido;
};


class noh {
friend class listadup;
private: 
    acaoPrograma acao; // poderia ser outro tipo de variável
    noh* proximo;
    noh* anterior;
public:
    //noh();
    noh(acaoPrograma d);
};

// construindo dado chamando seu construtor
noh::noh(acaoPrograma d){
    this->acao = d;
    this->proximo = NULL;
    this->anterior = NULL;
}


// lista dinamicamente encadeada
class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista    
public:
    listadup();
    listadup(const listadup& umaLista);
    ~listadup();
    // sobrecarga do operador de atribuição
    listadup& operator=(const listadup& umaLista);  
    // inserção, remoção e procura
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
listadup::listadup() {
    this->primeiro = NULL;
    this->ultimo = NULL;
    this->tamanho = 0;
}

// construtor de cópia
listadup::listadup(const listadup& umaLista) {
    this->primeiro = NULL;
    this->ultimo = NULL;
    this->tamanho = 0;
    noh* aux = umaLista.primeiro;
    while (aux != NULL) {
        this->insereNoFim(aux->acao);
        aux = aux->proximo;
    }
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup() {
    removeTodos();
}    

// remove todos os elementos da lista
void listadup::removeTodos() {
    noh* aux = this->primeiro;
    noh* temp;
    while (aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }  
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// sobrecarga do operador de atribuição
listadup& listadup::operator=(const listadup& umaLista){
    // limpa a lista atual
    this->removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        this->insereNoFim(aux->acao);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere por no final da lista
void listadup::insereNoFim(acaoPrograma acao) {
    noh* novo = new noh(acao);
    if (this->vazia()) {
        this->primeiro = novo;
        this->ultimo = novo;
    } else {
        novo->anterior = ultimo;
        this->ultimo->proximo = novo;
        this->ultimo = novo;
    }
    this->tamanho++;
}

// insere no início da lista
void listadup::insereNoInicio(acaoPrograma acao) {
    noh* novo = new noh(acao);
    if (this->vazia()) {
        this->primeiro = novo;
        this->ultimo = novo;
    } else {
        novo->proximo = primeiro;
        this->primeiro->anterior = novo;
        this->primeiro = novo;
    }
    this->tamanho++;
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, acaoPrograma acao){
    noh* novo = new noh(acao);
    if ((posicao <= this->tamanho) and (posicao >= 0)) {
        if (this->vazia()) {
            this->primeiro = novo;
            this->ultimo = novo;
        } else if (posicao == 0) {
            novo->proximo = this->primeiro;
            this->primeiro->anterior = novo;
            this->primeiro = novo;
        } else if (posicao == this->tamanho) {
            novo->anterior = this->ultimo;
            this->ultimo->proximo = novo;
            this->ultimo = novo;
        } else {
            noh* aux = this->primeiro;
            int posAux = 0;
            while (posAux < posicao - 1) {
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            novo->anterior = aux;
            aux->proximo->anterior = novo;
            aux->proximo = novo;
        }
        this->tamanho++;
    } else {
        cerr << "Posição Inexistente!" << endl;
        exit(EXIT_FAILURE);
    }
}
                   

int listadup::procura(string valor) {
    noh* aux = this->primeiro;
    int posAux = 0;
    while ((aux != NULL) and (aux->acao.nomeAcao != valor)) {
        posAux++;
        aux = aux->proximo;
    }
    if (aux == NULL) {
        posAux = -1;
    }
    return posAux;
}

// método básico que *percorre* uma lista, imprimindo seus elementos
void listadup::imprime() {
    if(this->vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = this->primeiro;
    while (aux != NULL) {
        cout << "(" << aux->acao.identificador << ", ";
        cout << aux->acao.nomeAcao << ", ";
        cout << aux->acao.tempoExecucao << ", ";
        cout << aux->acao.tempoConsumido << ")";
        aux = aux->proximo;
        cout << endl;
    }

    cout << "IMPRIMINDO REVERSO \n";
    
    aux = this->ultimo;
    while(aux != NULL) {
        cout << "(" << aux->acao.identificador << ", ";
        cout << aux->acao.nomeAcao << ", ";
        cout << aux->acao.tempoExecucao << ", ";
        cout << aux->acao.tempoConsumido << ")";
        aux = aux->anterior;
        cout << endl;
    }
}

// verifica se a lista está vazia
inline bool listadup::vazia() {
    return (primeiro == NULL);
}

void listadup::removeNoInicio() {
    if (this->vazia()) {
        cerr << "Remoção em lista vazia!" << endl;
        return;
    }

    noh* aux = this->primeiro;

    if (this->primeiro == this->ultimo) {
        // Se a lista tiver apenas um elemento
        this->primeiro = NULL;
        this->ultimo = NULL;
    } else {
        this->primeiro = this->primeiro->proximo;
        this->primeiro->anterior = NULL;
    }

    delete aux;
    this->tamanho--;
}


void listadup::removeNoFim() {
    if (this->vazia()) {
        cerr << "Remoção em lista vazia!" << endl;
        return;
    }

    noh* aux = this->ultimo;

    if (this->primeiro == this->ultimo) {
        // Se a lista tiver apenas um elemento
        this->primeiro = NULL;
        this->ultimo = NULL;
    } else {
        this->ultimo = this->ultimo->anterior;
        this->ultimo->proximo = NULL;
    }

    delete aux;
    this->tamanho--;
}


int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // procurar
                    cin >> nomeEquipe;
                    posicao = minhaLista.procura(nomeEquipe);
                    if (minhaLista.vazia()) {
                        cout << "Lista vazia!" << endl;
                    } else if(posicao < 0) {
                        cout << "Nao encontrado"<< endl;
                    } else {
                        cout << posicao << endl;
                    }
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
                    break;
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}