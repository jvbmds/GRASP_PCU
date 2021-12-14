#include "quicksort.hpp"

// Funcao que troca o conteudo de 2 variaveis.
void troca(registro& a, registro& b){
	registro aux = a;
	a = b;
	b = aux;
}

// Procedimento auxiliar que recebe um segmento em peca[], a extremidade
// esquerda do segmento em l e a extremidade direita em r.
// Retorna peca[] reordenado decrescente.
int particao(std::vector<registro> &item, int l, int r){
	int j, k;
	j = l;
	k = r;
	while (j < k)
	{
		while (j < k && item[j].tamanho >= item[k].tamanho) k--;
		if (j < k) troca(item[j++], item[k]);
		while (item[j].tamanho > item[k].tamanho) j++;
		if (j < k) troca(item[j], item[k--]);
	}
	return j;
}

// Sorteia o vetor da instancia de maneira decrescente
void quicksort(std::vector<registro> &item, int l,int r){
	int j;
	if (l < r) {
		j = particao(item, l, r);
		quicksort(item, l, j - 1);
		quicksort(item, j + 1, r);
	}
}