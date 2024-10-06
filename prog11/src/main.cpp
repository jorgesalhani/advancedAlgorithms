/**
 * @author Jorge Salhani
 * 8927418
 * 
 * Livros
 */

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> v2i;

vi obterPrecos(int N) {
	vi precos;
	for (int i = 0; i < N; i++) {
		int preco;
		cin >> preco;
		precos.push_back(preco);
	}
	return precos;
}

vi obterPaginas(int N) {
	vi paginas;
	for (int i = 0; i < N; i++) {
		int pagina;
		cin >> pagina;
		paginas.push_back(pagina);
	}
	return paginas;
}

int maximoPaginasPossivel(int i, int valDisponivel, vi &precos, vi &paginas, v2i &memo) {
	if (i == 0 || valDisponivel == 0) return 0;

	if (memo[i][valDisponivel] != -1) return memo[i][valDisponivel];

	if (precos[i-1] > valDisponivel)
		return memo[i][valDisponivel] = maximoPaginasPossivel(i-1, valDisponivel, precos, paginas, memo);

	return memo[i][valDisponivel] = max(
		paginas[i-1] + maximoPaginasPossivel(i-1, valDisponivel - precos[i-1], precos, paginas, memo),
		maximoPaginasPossivel(i-1, valDisponivel, precos, paginas, memo)
	);
}

int main(void) {

	int N, T;
	cin >> N;
	cin >> T;

	vi precos = obterPrecos(N);
	vi paginas = obterPaginas(N);

	v2i memo(N+1, vi(T+1, -1));

	cout << maximoPaginasPossivel(N, T, precos, paginas, memo) << endl;

	return 0;
}