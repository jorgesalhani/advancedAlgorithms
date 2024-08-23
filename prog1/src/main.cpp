/**
 * Projeto 1: STL 1
 * Reconhecimento de tarefas para dado tempo necessário
 * 
 * @author Jorge Salhani, 8927418
 */

#include <iostream>
#include <map>

using namespace std;

/**
 * Reconhecer, dada lista de tarefas, se o tempo disponível é adequado
 * @param N {int} Número de tarefas listadas para cada decisão
 * @returns {int} -1: se inviável; 0: se atrasado; 1: se possivel
 */
int tratarCasos(int N) {
  map<string, int> mapStrToInt;

  for (int j = 0; j < N; j++) {
    string assunto;
    cin >> assunto;

    int diasD;
    cin >> diasD;
    mapStrToInt[assunto] = diasD;
  }

  int diasDisponiveis;
  cin >> diasDisponiveis;
  
  string assuntoPedido;
  cin >> assuntoPedido;

  int diasNecessarios = mapStrToInt[assuntoPedido];

  return 
    (diasNecessarios == 0 || diasNecessarios > diasDisponiveis + 5) ? -1 :
    (diasNecessarios <= diasDisponiveis + 5 && diasNecessarios > diasDisponiveis) ? 0 : 1;
}

/**
 * Reconhecer se tempo é suficiente para dada lista de tarefas a receber
 * @param N {int} número de tarefas a fazer
 */
void executarPara(int N) {
  for (int i = 0; i < N; i++) {
    int totalAssuntos;
    cin >> totalAssuntos;

    cout << "Case " << i+1 << ": ";
    switch (tratarCasos(totalAssuntos)) {
      case 1:
        cout << "Ufa!" << endl;
        break;
      
      case 0:
        cout << "Atrasado" << endl;
        break;

      default:
        cout << "Deu ruim! Va trabalhar" << endl;
        break;
    }

  }
}

/**
 * Reconhecer o número de ocorrências
 * e executar reconhecimento de tarefa
 */
int main() {
  int N;
  cin >> N;
  executarPara(N);
}