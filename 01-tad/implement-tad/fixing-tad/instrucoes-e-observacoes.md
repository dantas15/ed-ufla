# Notas

## Instrucoes

- Enunciado 11

- [x] Redimensionar o vetor adicionando duas novas posições a cada redimensionamento

## Construtor de cópia

- Quando os atributos são alocados dinamicamente, implementamos um **construtor de cópia** para sobrecarregar o operador de atribuição `=`.
- Para criar um construtor de cópia, vamos criar mais um construtor, que recebe como parâmetro uma referência para um objeto `const` do mesmo tipo da classe.:

```cpp
radio(const radio& nRadio);
```

- A implementação do construtor de cópia ficará da seguinte forma:
  
```cpp
radio::radio(const radio& nRadio) {
 this->capacidadeMaxima = nRadio.capacidadeMaxima;
 this->quantidadeDeItens = nRadio.quantidadeDeItens;
 this->listaDeMusicas = new musica[this->capacidadeMaxima];
 copy (nRadio.listaDeMusicas, nRadio.listaDeMusicas+nRadio.capacidadeMaxima, this->listaDeMusicas);
}
```

- Com o novo construtor de cópia, podemos implementar o redimensionamento corretamente:

```cpp
void radio::redimensionarCapacidade() {
 int novaCapacidade = this->capacidadeMaxima+2;

 musica *arrAux = new musica[novaCapacidade];
 
 copy (this->listaDeMusicas, this->listaDeMusicas+this->capacidadeMaxima, arrAux);
 this->capacidadeMaxima = novaCapacidade;

 delete [] this->listaDeMusicas;
 
 listaDeMusicas = arrAux;
 // cout << this->capacidadeMaxima; // testando
}
```
