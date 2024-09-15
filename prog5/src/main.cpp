/**
 * Projeto 5: Pontos
 * 
 * 
 * @author Jorge Salhani, 8927418
 */

#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <limits>

using namespace std;
typedef vector<long int> vecLonInt;
typedef vector<vecLonInt> vecVecLonInt;

struct {
  bool operator()(vecLonInt itemA, vecLonInt itemB) { 
    return itemA[0] != itemB[0] 
      ? itemA[0] > itemB[0]
      : itemA[1] != itemB[1]
      ? itemA[1] < itemB[1]
      : itemA[1] > itemB[1]; 
  }
} ordemTuplaXY;

struct {
  bool operator()(vecLonInt itemA, vecLonInt itemB) { 
    return itemA[1] != itemB[1] 
      ? itemA[1] > itemB[1]
      : itemA[0] != itemB[0]
      ? itemA[0] < itemB[0]
      : itemA[0] > itemB[0]; 
  }
} ordemTuplaYX;

vecVecLonInt obterPontos(int N) {
  vecVecLonInt vetorPontos;
  for (int i = 0; i < N; i++) {
    long int x, y;

    cin >> x;
    cin >> y;

    vetorPontos.push_back({x,y});
  }

  sort(vetorPontos.begin(), vetorPontos.end(), ordemTuplaXY);

  return vetorPontos;
}


float obterMenorDistanciaFaixaCentral(vecVecLonInt vetorPontosEsq, vecVecLonInt vetorPontosDir, float menorDist) {

  struct {
    bool operator()(vecLonInt itemA, vecLonInt itemB) { 
      return itemA[1] != itemB[1]
        ? itemA[1] > itemB[1]
        : itemA[1] < itemB[1]; 
    }
  } ordemTuplaCrescY;

  vecVecLonInt pontosFaixaDoMeio;

  long int tamVetEsq = (long int) vetorPontosEsq.size();
  long int tamVetDir = (long int) vetorPontosDir.size();

  for (long int i = 0; i < tamVetDir; i++) {
    vecLonInt v1 = {vetorPontosDir[i][0], vetorPontosDir[i][1]};
    // vecLonInt v2 = {vetorPontosDir[i+1][0], vetorPontosDir[i+1][1]};

    // if (abs(v1[0] - v2[0]) > menorDist) break;
    pontosFaixaDoMeio.push_back(v1);
    // pontosFaixaDoMeio.push_back(v2);
  }

  for (long int i = tamVetEsq - 2; i >= 0; i--) {
    vecLonInt v1 = {vetorPontosEsq[i][0], vetorPontosEsq[i][1]};
    // vecLonInt v2 = {vetorPontosEsq[i+1][0], vetorPontosEsq[i+1][1]};

    // if (abs(v1[0] - v2[0]) > menorDist) break;
    pontosFaixaDoMeio.push_back(v1);
    // pontosFaixaDoMeio.push_back(v2);
  }


  sort(pontosFaixaDoMeio.begin(), pontosFaixaDoMeio.end(), ordemTuplaCrescY);

  float novaMenorDist = menorDist;
  for (long int i = 0; i < (long int) (pontosFaixaDoMeio.size() - 1); i++) {
    long int dx = pontosFaixaDoMeio[i][0] - pontosFaixaDoMeio[i+1][0];
    long int dy = pontosFaixaDoMeio[i][1] - pontosFaixaDoMeio[i+1][1];

    float novaDist = sqrtf(dx*dx + dy*dy);
    novaMenorDist = novaDist < novaMenorDist ? novaDist : novaMenorDist;
  }

  return novaMenorDist;
}


float menorDist = 1000000.0;

float obterMenorDistancia(vecVecLonInt vetorPontos) {
  long int meio = (long int) (vetorPontos.size() / 2);
  
  if (meio == 1 || meio == 2) {
    vecLonInt v0 = {vetorPontos[0][0], vetorPontos[0][1]};
    vecLonInt v1 = {vetorPontos[1][0], vetorPontos[1][1]};
    vecLonInt v2 = {vetorPontos[2][0], vetorPontos[2][1]};

    float d01 = sqrtf((v0[0]-v1[0])*(v0[0]-v1[0]) + (v0[1]-v1[1])*(v0[1]-v1[1]));
    float d02 = sqrtf((v0[0]-v2[0])*(v0[0]-v2[0]) + (v0[1]-v2[1])*(v0[1]-v2[1]));
    float d12 = sqrtf((v1[0]-v2[0])*(v1[0]-v2[0]) + (v1[1]-v2[1])*(v1[1]-v2[1]));

    vector<float> dists = {d01, d02, d12};
    sort(dists.begin(), dists.end());

    return dists[0];
  }

  vecVecLonInt vetPontosEsquerda = vecVecLonInt(vetorPontos.begin(), vetorPontos.end() - meio);
  float menorEsquerda = obterMenorDistancia(vetPontosEsquerda);

  vecVecLonInt vetPontosDireita = vecVecLonInt(vetorPontos.begin() + meio, vetorPontos.end());
  float menorDireita = obterMenorDistancia(vetPontosDireita);

  menorDist = menorDireita < menorEsquerda ? menorDireita : menorEsquerda;

  float menorFaixaCentral = obterMenorDistanciaFaixaCentral(vetPontosEsquerda, vetPontosDireita, menorDist);

  menorDist = menorFaixaCentral < menorDist ? menorFaixaCentral : menorDist;

  return menorDist;
}

int main() {

  int N;
  cin >> N;

  vecVecLonInt vetorPontos = obterPontos(N);

  float menorDistancia = obterMenorDistancia(vetorPontos);

  cout << menorDistancia;

  return 0;
}