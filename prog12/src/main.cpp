#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

#define ITENS 3
const int W=6;
int p[ITENS+1] = {0,2,2,3}; // ignorar o item zero...

int MEMO[ITENS+1][W+1];

void printMat(){
	for (int i = 0; i <=ITENS; ++i){
		for (int p = 0; p <= W; ++p){
			printf("%d ", MEMO[i][p]);
		}
		printf("\n");
	}
}

int wsspPD(){
	for (int w = 0; w <=W; w++){
		MEMO[0][w] = 0;
	}

	// para todos os itens
	for (int i = 1; i <=ITENS; ++i){
		// para todos os pesos
		for (int w = 0; w <=W; w++){
			if (w < p[i])
				MEMO[i][w] = MEMO[i-1][w];
			else MEMO[i][w] = max(MEMO[i-1][w], p[i]+MEMO[i-1][w-p[i]]);
		}
	}
	return MEMO[ITENS][W];
}




int wsspRECPD(int i, int peso){
	if (i ==0)
		return 0;

	if (MEMO[i][peso]!= -1)
		return MEMO[i][peso];


	if (peso < p[i])
		return MEMO[i][peso] = wsspRECPD(i-1, peso);

	return MEMO[i][peso] = 
	max(wsspRECPD(i-1, peso),p[i]+wsspRECPD(i-1,peso-p[i]));
}


int wsspREC(int i, int peso){
	if (i ==0)
		return 0;
	if (peso < p[i])
		return wsspREC(i-1, peso);

	return max(wsspREC(i-1, peso),p[i]+wsspREC(i-1,peso-p[i]));
}



int main(int argc, char const *argv[])
{
	/* code */
	printf("O peso maximo (REC) = %d\n", wsspREC(ITENS, W));
	
	memset(MEMO,-1, sizeof MEMO);
	printf("O peso maximo (RECPD) = %d\n", wsspRECPD(ITENS, W));
	printMat();

	printf("O peso maximo (PD) = %d\n", wsspPD());
	printMat();

	return 0;
}