# Algumas observações importantes sobre a atividade

## Outra forma de construtor

- suponha que tenha os atributos teste e teste2

```cpp
Pokedex(int teste, int teste2 = 0): teste(teste), teste2(teste2) {}
```

## some random code of pokedex

```cpp
Pokedex(Pokemon *pks = nullptr, int qnt = 0): pokemons(pks), quantidade(qnt) {}
    
    void adicionarPokemon(string nome, char tipo, float velocidade, float ataque, float defesa, float ataqueEspecial, float defesaEspecial) {
      Pokemon * novaPokedex = new Pokemon(nome, tipo, this->quantidade++, velocidade, ataque, defesa, ataqueEspecial, defesaEspecial) [this->quantidade++];
      Pokemon novoPokemon(nome, tipo, this->quantidade, velocidade, ataque, defesa, ataqueEspecial, defesaEspecial);
      this->pokemons[this->quantidade] = novoPokemon;
      this->quantidade++;
    }
    void removerPokemonPorNome(char *nome) {
      bool encontrou = false;
      int i = 0;
      while (i < this->quantidade && !encontrou) {
        if (strcmp(this->pokemons[i].getNome(), nome) == 0) {
          for (int j = i; j < this->quantidade; j++) {
            this->pokemons[j] = this->pokemons[j + 1];
          }
          this->quantidade--;
          encontrou == true;
        }
        i++;
      }
    }
```

## obs

- é preciso deletar o char* do nome do pokemon?

```cpp
~Pokemon() {
  delete[] nome;
}
```
