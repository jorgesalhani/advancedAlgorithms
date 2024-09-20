/**
 * Projeto 7: Labirinto
 * 
 * 
 * @author Jorge Salhani, 8927418
 */

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>

using namespace std;

typedef vector<int> vecInt;
typedef vector<vecInt> array2d;

void imprimirLabirinto(array2d labirinto) {
  int M = labirinto.size();
  int N = labirinto[0].size();
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cout << labirinto[i][j] << " ";
    }
    cout << endl;
  }
}

array2d construirLabirinto(int M, int N) {
  array2d labirinto(M+2, vector<int>(N+2));

  for (int i = 0; i < M+2; i++) {
    for (int j = 0; j < N+2; j++) {
      labirinto[i][j] = 0;

      if (i == 0 || i == M+1) labirinto[i][j] = 1;
      if (j == 0 || j == N+1) labirinto[i][j] = 1;
    }
  }

  labirinto[1][1] = 2;
  labirinto[M][N] = 3;

  string buff;
  getline(cin, buff);
  getline(cin, buff);
  while (buff.size() > 1) {
    int x, y;

    x = (int) buff[0] - 47;
    y = (int) buff[2] - 47;
    labirinto[x][y] = 1;

    getline(cin, buff);
  }

  return labirinto;
}

bool encontrarSaida(array2d &labirinto, vecInt coordAtual, int &contadorPassos, int ordem);

void caminharParaCoordenada(array2d &labirinto, vecInt proxCoord, bool proxLivre, int &contadorPassos, int ordem) {
  labirinto[proxCoord[0]][proxCoord[1]] = 1;
  if (proxLivre) encontrarSaida(labirinto, {proxCoord[0], proxCoord[1]}, ++contadorPassos, ordem);
}

void caminharPorOrdem(array2d &labirinto, vecInt proxCoord, int &contadorPassos, int ordem) {
  vecInt baiCoordProx = {proxCoord[0] + 1, proxCoord[1]};
  vecInt dirCoordProx = {proxCoord[0], proxCoord[1] + 1};
  vecInt cimCoordProx = {proxCoord[0] - 1, proxCoord[1]};
  vecInt esqCoordProx = {proxCoord[0], proxCoord[1] - 1};

  bool baiLivre = labirinto[baiCoordProx[0]][baiCoordProx[1]] != 1;
  bool dirLivre = labirinto[dirCoordProx[0]][dirCoordProx[1]] != 1;
  bool cimLivre = labirinto[cimCoordProx[0]][cimCoordProx[1]] != 1;
  bool esqLivre = labirinto[esqCoordProx[0]][esqCoordProx[1]] != 1;
  
  switch (ordem) {
    case 0:
        caminharParaCoordenada(labirinto, baiCoordProx, baiLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, dirCoordProx, dirLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, cimCoordProx, cimLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, esqCoordProx, esqLivre, contadorPassos, ordem);
      break;

    case 1:
        caminharParaCoordenada(labirinto, baiCoordProx, baiLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, esqCoordProx, esqLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, cimCoordProx, cimLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, dirCoordProx, dirLivre, contadorPassos, ordem);
      break;

    case 2:
        caminharParaCoordenada(labirinto, cimCoordProx, cimLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, dirCoordProx, dirLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, baiCoordProx, baiLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, esqCoordProx, esqLivre, contadorPassos, ordem);
      break;

    case 3:
        caminharParaCoordenada(labirinto, cimCoordProx, cimLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, esqCoordProx, esqLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, baiCoordProx, baiLivre, contadorPassos, ordem);
        caminharParaCoordenada(labirinto, dirCoordProx, dirLivre, contadorPassos, ordem);
      break;
    
    default:
      break;
  }
}

int totalCaminhos = 0;
vecInt distancias;

bool encontrarSaida(array2d &labirinto, vecInt coordAtual, int &contadorPassos, int ordem) {
  int M = labirinto.size();
  int N = labirinto[0].size();

  vecInt saida = {M-2, N-2};

  if (coordAtual[0] == saida[0] && coordAtual[1] == saida[1]) {
    totalCaminhos++;
    distancias.push_back(contadorPassos);
    return true;
  }

  // imprimirLabirinto(labirinto);
  // cout << contadorPassos << endl;

  caminharPorOrdem(labirinto, coordAtual, contadorPassos, ordem);
  
  return false;
}

int main(void) {
  int M, N;
  cin >> M;
  cin >> N;


  for (int i = 0; i < 4; i++) {
    int contPassos = 0;
    array2d labirinto = construirLabirinto(M, N);
    encontrarSaida(labirinto, {1,1}, contPassos, i);  
    for (auto &x : distancias) cout << x << ", ";
    cout << endl;
  }

  // imprimirLabirinto(labirinto);
  
  return 0;
}