/*
    Preparatoria Dredd : Questão 1: Hash com encadeamento
*/


#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

class noh {
    friend class lista;
    friend class tabelaHash;
private:
    string chave;
    char tipo;
    int valor;
    noh* proximo;
    noh(const string& c = "", const char& t = 'a', const int& v = 0, noh* prox = NULL) :
        chave(c), tipo(t), valor(v), proximo(prox) {}
};

class lista {
    friend class tabelaHash;
private:
    noh* primeiro;
    unsigned short numElementos;
public:
    lista();
    ~lista();
    unsigned short tamanho();
    void insere(const string& c, const char& t, const int& v);
    bool remove(const string& c);
    bool busca(const string& c, char& tipoBuscado, int& valorBuscado);
    bool verificaOcorrencia(const string& c);
    void imprime();
};


//Construtor da lista deixando NULL ao "primeiro termo" e num de elementos = 0
lista::lista() : primeiro(NULL), numElementos(0) {}

//Destrutor: enquanto o primeiro não for igual a nulo, ele continua assumindo valor do proximo e aux se iguala a ele e vai apagando até que chegue ao fim
lista::~lista() {
    while (primeiro != NULL) {
        noh* aux = primeiro;
        primeiro = primeiro->proximo;
        delete aux;
    }
}

//Retorna o tamanho
unsigned short lista::tamanho() {
    return numElementos;
}

//Para a inserção em lista é tranquila, pois o tratamento de colisão será feito apenas no insere da outra classe
//Portanto é só atribuir os valores
void lista::insere(const string& c, const char& t, const int& v) {
    noh* novo = new noh(c, t, v);
    
    if(primeiro == NULL || novo->chave < primeiro->chave) {
		novo->proximo = primeiro;
		primeiro = novo;
	} else {
		noh* aux = primeiro;
		noh* auxAnterior = NULL;
		while (aux->proximo != NULL && aux->proximo->chave < novo->chave) {
			aux = aux->proximo;
		}
		
		if (auxAnterior != NULL) {
			auxAnterior->proximo = novo;
		}
		novo->proximo = aux->proximo;
		aux->proximo = novo;
	}   

	numElementos++;
}

//Implementação padrão para a remoção em lista, enquanto a "chave" de busca não é encontrada, a busca continua
bool lista::remove(const string& c) {
    if (primeiro == NULL)
        return false;

    if (primeiro->chave == c) {
        noh* aux = primeiro;
        primeiro = primeiro->proximo;
        delete aux;
        numElementos--;
        return true;
    }

    noh* atual = primeiro;
    while (atual->proximo != NULL && atual->proximo->chave != c)
        atual = atual->proximo;

    if (atual->proximo != NULL) {
        noh* aux = atual->proximo;
        atual->proximo = atual->proximo->proximo;
        delete aux;
        numElementos--;
        return true;
    }

    return false;
}

bool lista::busca(const string& c, char& tipoBuscado, int& valorBuscado) {
    noh* atual = primeiro;
    while (atual != NULL) {
        if (atual->chave == c) {
            tipoBuscado = atual->tipo;
            valorBuscado = atual->valor;
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

bool lista::verificaOcorrencia(const string& c) {
    noh* atual = primeiro;
    while (atual != NULL) {
        if (atual->chave == c)
            return true;
        atual = atual->proximo;
    }
    return false;
}

void lista::imprime() {
    noh* atual = primeiro;
    while (atual != NULL) {
        cout << "[" << atual->chave << "/" << atual->valor << "]";
        atual = atual->proximo;
    }
}

class tabelaHash {
private:
    lista* tabela;
    unsigned numPosicoes;

    unsigned funcaoHash(const string& s);
    unsigned funcaoHash(const string& s, int cap);

public:
    tabelaHash(unsigned cap = 100);
    ~tabelaHash();
    bool insere(const string& c, char& t, const int& v);
    bool valor(const string& c, char& tipoBuscado, int& valorRetorno);
    bool remove(const string& c);
    void imprime();
};

//Lista declarada explicitamente para a construção da tabela Hash
tabelaHash::tabelaHash(unsigned cap) : numPosicoes(cap) {
    tabela = new lista[numPosicoes];
}

//Simplesmente deleta o vetor de listas
tabelaHash::~tabelaHash() {
    delete[] tabela;
}

//Funções para retornar o índice com base na função hash
unsigned tabelaHash::funcaoHash(const string& s) {
    return funcaoHash(s, numPosicoes);
}


unsigned tabelaHash::funcaoHash(const string& s, int cap) {
    unsigned pos = 0;
    for (unsigned int i = 0; i < s.size(); ++i)
        pos = (UMPRIMO * pos + s[i]) % cap;
    return pos;
}

bool tabelaHash::insere(const string& c, char& t, const int& v) {
    unsigned posicao = funcaoHash(c);
    if (tabela[posicao].verificaOcorrencia(c)) {
        return false;
	}
    tabela[posicao].insere(c, t, v);
    cout << "chave '" << c << "' inserida na posicao " << posicao << endl;
    return true;
}

bool tabelaHash::valor(const string& c, char& tipoBuscado, int& valorRetorno) {
    unsigned posicao = funcaoHash(c);
    return tabela[posicao].busca(c, tipoBuscado, valorRetorno);
}

bool tabelaHash::remove(const string& c) {
    unsigned posicao = funcaoHash(c);
    return tabela[posicao].remove(c);
}

void tabelaHash::imprime() {
    for (unsigned i = 0; i < numPosicoes; i++) {
        cout << i << ": ";
        tabela[i].imprime();
        cout << endl;
    }
}

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;

    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> chave >> tipo >> valor;
                if (!tabela.insere(chave, tipo, valor))
                    cout << "Erro na inserção: chave já existente!" << endl;
                break;
            case 'r': // remover
                cin >> chave;
                if (!tabela.remove(chave))
                    cout << "Erro na remoção: chave não encontrada!" << endl;
                break;
            case 'l': // remover
                cin >> chave;
                if (!tabela.valor(chave, tipo, valor))
                    cout << "Erro na busca: chave não encontrada!" << endl;
                else
                    cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                break;
            case 'p': // mostrar estrutura
                tabela.imprime();
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

    tabela.imprime();
    cout << endl;

    return 0;
}
/*
6
r dez
i um a 1
i dois b 2
i quatro d 4
i sete g 7
i oito h 8
i dez j 10
i tres c 3
*/

