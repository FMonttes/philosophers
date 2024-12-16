# philosophers

O **philosophers** é um projeto em C que simula o problema clássico de sincronização conhecido como "Problema dos Filósofos Comedores". O objetivo do projeto é desenvolver uma solução eficiente para o problema, onde múltiplos filósofos se sentam à mesa, pensam e comem alternadamente, compartilhando garfos para comer. O desafio consiste em gerenciar o acesso aos garfos de forma a evitar condições de corrida (deadlock) e garantir que todos os filósofos possam comer sem bloquear uns aos outros.

## Descrição

O **philosophers** é uma simulação de filósofos que se comportam da seguinte maneira:

- Cada filósofo tem duas ações: **pensar** e **comer**.
- Para comer, o filósofo precisa de dois garfos (um à sua esquerda e outro à sua direita).
- Os garfos são compartilhados entre os filósofos, e o desafio é garantir que o acesso aos garfos seja feito de forma segura, evitando deadlock e garantindo que todos os filósofos comam sem paralisar o sistema.

O projeto é uma implementação do problema de sincronização utilizando threads e mutexes para garantir a segurança e eficiência no compartilhamento dos recursos (os garfos).

## Requisitos

- O programa deve simular uma mesa com `n` filósofos.
- Cada filósofo pode:
  - Pensar (não utiliza garfo).
  - Comer (precisa de dois garfos).
- O tempo para cada filósofo comer e pensar deve ser especificado como argumentos do programa.
- O programa deve gerenciar as condições de concorrência e evitar deadlocks.

## Como Funciona?

- **Número de filósofos**: O programa aceita como argumento o número de filósofos na mesa.
- **Tempo de vida de cada filósofo**: Cada filósofo tem um tempo específico para comer e pensar.
- **Acesso aos garfos**: Os filósofos devem pegar os garfos à sua esquerda e direita de forma sincronizada usando mutexes, para evitar que mais de um filósofo pegue o mesmo garfo ao mesmo tempo.

## Exemplo de Execução

Para compilar e executar o programa, você pode usar os seguintes comandos:

### Compilação

Clone o repositório e compile o projeto com os seguintes comandos:

```bash
git clone https://github.com/usuario/philosophers.git
cd philosophers
make
