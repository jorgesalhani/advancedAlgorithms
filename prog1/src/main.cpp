#include <iostream>
#include <map>

using namespace std;

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


int main() {
  int N;
  cin >> N;
  executarPara(N);
}