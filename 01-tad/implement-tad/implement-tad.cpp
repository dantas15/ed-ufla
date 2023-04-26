#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Pokemon {
  private: 
    string nome;
    char tipo;
    int posicao;
    float velocidade;
    float ataque;
    float defesa;
    float ataqueEspecial;
    float defesaEspecial;
  public:
    Pokemon() {}
    Pokemon(string nome, char tipo, int posicao, float velocidade, float ataque, float defesa, float ataqueEspecial, float defesaEspecial) {
      this->nome = nome;
      this->tipo = tipo;
      this->posicao = posicao;
      this->velocidade = velocidade;
      this->ataque = ataque;
      this->defesa = defesa;
      this->ataqueEspecial = ataqueEspecial;
      this->defesaEspecial = defesaEspecial;
    }
    string getNome() {
      return this->nome;
    }
};

class Treinador {
  private:
    string nome;
    string nomeGinasio;
    char tipoPokemonPreferencial;
    char tipoPokemonContra;
  public:
    string getNome() {
      return nome;
    }
};

int main() {
  
}