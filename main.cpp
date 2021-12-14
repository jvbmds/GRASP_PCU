#include "Cabecalho.hpp"

int main(int argc, char *argv[])
{	
	//Declaracao de variaveis
	vector<registro> item_residual; 		// Variavel que guarda os itens usados no problema residual (Obsoleto)
	vector<registro> item;					// Variavel que guarda os itens usados no problema principal
	vector<vector<int> > MS;				// Salva a matriz solucao
	double alfa_sol;						// Guarda o alfa da solucao
	int numero_barras = 0;					// Guarda o numero de barras usadas pela GC (Obsoleto)
	int numero_barras_total = 0;			// Guarda o total de barras da GC+Residual (Obsoleto)
	int best_sol = 0;						// Guarda a melhor solucao da GRASP 
	int tamanho_barra_padrao;				// Tamanho da barra de estoque
	int numero_itens_instancia;				// Quantidade de itens na instancia 
	int status = 0;                 		// Status das funcoes
	string repeticao_instancia = argv[2];	// Guarda o numero do teste em caso de multiplas repeticoes
	string nome_instancia;					// Guarda o nome da instancia
	string nome_arquivo_instancia;			// Guarda o nome do arquivo onde a instancia esta
	string saida;							// String de buffer da saida
	string M;								// String que escreve se a solucao foi obtida na melhoria
	string R = " ";							// String que esqueve se a solucao foi obtida na parte reativa
	string estatistica_str;					// String de buffer do arquivo de estatistica
	string str_desenho;						// String de buffer do arquivo que alimenta
	string N_saida;							// Guarda o nome do arquivo de saida
	clock_t tempo;							// Variavel que recebe o clock
	clock_t t0 = clock();					// Clock inicial
	clock_t tempo_best_sol;					// Clock da melhor solucao - clock inicial
	ifstream dados;							// Variavel para lidar com o arquivo de entrada
	ofstream teste;							// Variavel para lidar com os arquivos de saida

	
	// Abre o arquivo de instancia
	nome_instancia = argv[1];
	nome_arquivo_instancia = nome_instancia + ".txt";
	N_saida = nome_instancia + "_Teste" + repeticao_instancia + ".txt";
	dados.open(nome_arquivo_instancia);   
	if (dados.fail() == 1) {
		cout << "Nao foi possivel abrir o arquivo de instancia!!!" << endl;
		system("pause");
		return 1;
	}

	// Le os dados da instancia
	dados >> tamanho_barra_padrao >> numero_itens_instancia;
	item.resize(numero_itens_instancia);
	for (int i = 0; i < numero_itens_instancia; i++)
	{
		dados >> item[i].demanda >> item[i].tamanho;
		item[i].indice = i;
	}

	// Fecha o arquivo de instancia
	dados.close(); 

	//ordena os itens de maneira decrescente
	quicksort(item, 0 , numero_itens_instancia - 1);

	// Chama a funcao de solucao
	status = central(item, tamanho_barra_padrao, numero_itens_instancia, t0, nome_instancia, 
	repeticao_instancia, M, R, tempo_best_sol, best_sol, alfa_sol, MS);
	if (status) {
		cout << "falha na chamada do grasp";
		return 1;
	}

	// Obsoleto
	numero_barras_total = numero_barras + best_sol;
	
	// Pega o clock final do codigo
	tempo = clock();									
	
	// Preenche o arquivo de de buffer da estatistica
	estatistica_str = N_saida + "\t";												// Nome da instancia e numero do teste
	estatistica_str += to_string(((double)tempo_best_sol) / CLOCKS_PER_SEC) + '\t';	// Tempo da melhor solucao
	estatistica_str += to_string(((double)tempo - t0) / CLOCKS_PER_SEC) + '\t';		// Tempo total
	estatistica_str += to_string(alfa_sol) + '\t';									// Alfa da solucao 
	estatistica_str += to_string(numero_barras_total) + '\t';						// Numero total de barras								
	estatistica_str += '\t' + M;													// Melhoria 

	// Escreve o arquivo de saida estatistica.txt
	teste.open("estatistica.txt", ios::app);
	if (!teste.good()) {
		cout << "o arquivo de saida nao pode ser aberto." << endl;
		return 1;
	}
	teste << estatistica_str << endl;
	teste.close();

	// chama funcao para preencher o buffer da saida do desenho
	str_desenho = S_saida_desenho(MS, item, item_residual, tamanho_barra_padrao, best_sol);

	// escreve o arquivo de saida "desenho.txt"
	teste.open("desenho.txt", ios::trunc);
	if (!teste.good()) {
		cout << "o arquivo de saida nao pode ser aberto." << endl;
		return 1;
	}
	teste << str_desenho << endl;
	teste.close();

	return 0;
}	// final do main

// Escreve o buffer do arquivo de texto que alimenta as informacoes do grafico
string S_saida_desenho( 
	vector<vector<int>> MS,
	vector<registro> item,
	vector<registro> item_residual,
	int barra_padrao,
	int best_sol) {	

	// Declaracao de variaveis
	int a = 0;					// Auxiliar que ajuda a contar a quantidade de padroes
	int i, j;					// Contadores
	int I_padrao_GRASP = 0;		// Guarda a quantidade de padroes da GRASP
	int qtd_item_padrao = 0;

	string S_desenho = "";

	// Conta a quantidade de padroes da GRASP
	for (i = 0; i < MS.size(); i++) {
		if (a < best_sol) {
			I_padrao_GRASP++;
			a += MS[i][MS[i].size() - 1];
		}
	}


	// Preenche o Buffer
	S_desenho = to_string(I_padrao_GRASP) + '|'; 					// Quantidade de padroes de corte
	S_desenho += to_string(barra_padrao) + '\n';					// Tamanho da barra padrao
	for (i = 0; i < I_padrao_GRASP; i++) {

		// Conta e escreve quantos itens um padrao tem
		qtd_item_padrao = 0;
		for (j = 0; j < MS[i].size() - 2; j++) {
			if (MS[i][j] != 0) 	qtd_item_padrao++;
		}
		S_desenho += to_string(qtd_item_padrao) + '|';				// Quantidade de itens no padrao

		for (j = 0; j < MS[i].size() - 2; j++) {
			if (MS[i][j] != 0) {
				S_desenho += to_string(MS[i][j]) + '|';				// Quantidade do item i no padrao
				S_desenho += to_string(item[j].tamanho) + '|';		// Tamanho do item i
			}
		}
		S_desenho += to_string(MS[i][MS[i].size() - 2]) + '|';		// Perda do padrao
		S_desenho += to_string(MS[i][MS[i].size() - 1]) + '\n';		// Repeticoes do padrao
	}
	return (S_desenho);
}
