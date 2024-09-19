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

typedef vector<vector<int>> array2d;

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
  array2d labirinto(M, vector<int>(N));

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      labirinto[i][j] = 0;
    }
  }

  labirinto[0][0] = 2;
  labirinto[M-1][N-1] = 3;

  string buff;
  getline(cin, buff);
  getline(cin, buff);
  while (buff.size() > 1) {
    int x, y;

    x = (int) buff[0] - 48;
    y = (int) buff[2] - 48;
    labirinto[x][y] = 1;

    getline(cin, buff);
  }

  return labirinto;
}

int main(void) {
  int M, N;
  cin >> M;
  cin >> N;

  array2d labirinto = construirLabirinto(M, N);
  imprimirLabirinto(labirinto);
  
  return 0;
}