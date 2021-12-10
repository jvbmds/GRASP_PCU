#include "Cabecalho.hpp"

// Funcao que troca o conteudo de 2 variaveis.
void troca_GRASP2D(registro& a, registro& b){
	registro aux = a;
	a = b;
	b = aux;
}

// Procedimento auxiliar que recebe um segmento em peca[], a extremidade
// esquerda do segmento em l e a extremidade direita em r.
// Retorna peca[] reordenado decrescente.
int particao_GRASP2D(
	registro peca[], 
	int l, 
	int r)
{
	int j, k;
	j = l;
	k = r;
	while (j < k)
	{
		while (j < k && peca[j].tamanho >= peca[k].tamanho) k--;
		if (j < k) troca_GRASP2D(peca[j++], peca[k]);
		while (peca[j].tamanho > peca[k].tamanho) j++;
		if (j < k) troca_GRASP2D(peca[j], peca[k--]);
	}
	return j;
}

// Procedimento principal do algoritmo de ordenacao QuickSort
void quicksort_GRASP2D(registro peca[], int l, int r){
	int j;
	if (l < r) {
		j = particao_GRASP2D(peca, l, r);
		quicksort_GRASP2D(peca, l, j - 1);
		quicksort_GRASP2D(peca, j + 1, r);
	}
}

//construcao do probelma da melhoria
string const_prob_bl  (int qtd_padroes_const,vector<vector<int> >&MS_aux,int num_itens_const,
	vector<int> &ind_padroes_escolhidos,int &qtd_padroes_escolhidos,registro peca_const[],registro peca_bl[],
	int &num_itens_bl, int &perda_prob_bl,int &num_barra_bl) {

	

	if ((int)ind_padroes_escolhidos.size() < qtd_padroes_const) {
		ind_padroes_escolhidos.resize(qtd_padroes_const, -1);
	}

	for (int i = 0; i < qtd_padroes_const; i++) {
		ind_padroes_escolhidos[i] = -1;
	}
	qtd_padroes_escolhidos = 0;
	num_itens_bl = 0;
	perda_prob_bl = 0;
	num_barra_bl = 0;


	string saida_str;
	int mpi = 0;//guarda a maior perda individual
	int impi;//guarda o indice da linha do padrao com maior perda individual
	int mpt = 0;//guarda a maior perda total
	int impt;//guarda o indice da linha do padrao com maior perda total
	int mqp = 0;//guarda a maior quantidade de pecas n?o-nulas entre os padroes
	int mqp_aux = 0;
	int impp = 0;
	int imqp;//guarda o indice da linha do padrao com a maior quantidade de pecas n?o-nulas
	int mpp = 0;
	int arit;// variavel utilizada para evitar estouro aritmetico
	int aa1 = 0, aa2 = 0, aa3 = 0, aa4 = 0, sorteio = -1;


	vector<int> AA1(qtd_padroes_const);
	vector<int> AA2(qtd_padroes_const);
	vector<int> AA3(qtd_padroes_const);
	vector<int> AA4(qtd_padroes_const);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! escolhe os padroes !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	arit = num_itens_const + 1;

	for (int i = 0; i < qtd_padroes_const; i++) {
		mqp_aux = 0;
		if (MS_aux[i][num_itens_const] > mpi) {
			aa1 = 0;
			mpi = MS_aux[i][num_itens_const];
			AA1[aa1] = i;
			aa1++;
		}
		else {
			if (MS_aux[i][num_itens_const] == mpi) {
				AA1[aa1] = i;
				aa1++;
			}
		}
		if (MS_aux[i][num_itens_const] * MS_aux[i][arit] > mpt) {
			aa2 = 0;
			mpt = MS_aux[i][num_itens_const] * MS_aux[i][arit];
			AA2[aa2] = i;
			aa2++;
		}
		else {
			if (MS_aux[i][num_itens_const] * MS_aux[i][arit] == mpt) {
				AA2[aa2] = i;
				aa2++;
			}
		}
		for (int j = 0; j < num_itens_const; j++) {
			if (MS_aux[i][j] > 0) {
				mqp_aux++;
			}
		}
		if (mqp_aux > mqp) {
			aa3 = 0;
			mqp = mqp_aux;
			AA3[aa3] = i;
			aa3++;
		}
		else {
			if (mqp_aux == mqp) {
				AA3[aa3] = i;
				aa3++;
			}
		}
		if (mqp_aux * MS_aux[i][arit] > mpp) {
			aa4 = 0;
			mpp = mqp_aux * MS_aux[i][arit];
			AA4[aa4] = i;
			aa4++;
		}
		else {
			if (mqp_aux * MS_aux[i][arit] == mpp) {
				mpp = mqp_aux;
				AA4[aa4] = i;
				aa4++;
			}
		}
	}
	sorteio = rand() % aa1;
	impi = AA1[sorteio];
	sorteio = rand() % aa2;
	impt = AA2[sorteio];
	sorteio = rand() % aa3;
	imqp = AA3[sorteio];
	sorteio = rand() % aa4;
	impp = AA4[sorteio];
	ind_padroes_escolhidos[impi] = impi;
	ind_padroes_escolhidos[impt] = impt;
	ind_padroes_escolhidos[imqp] = imqp;
	ind_padroes_escolhidos[impp] = impp;
	qtd_padroes_escolhidos = 0;
	for (int i = 0; i < qtd_padroes_const; i++) {
		if (ind_padroes_escolhidos[i] >= 0) {
			ind_padroes_escolhidos[qtd_padroes_escolhidos] = ind_padroes_escolhidos[i];
			qtd_padroes_escolhidos++;
		}
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! escolhe os padroes !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//!!!!!!!!!!!!!!!!!!!!!!!!!! preenche a struct auxiliar dos itens !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	arit = num_itens_const + 1;

	for (int i = 0; i < num_itens_const; i++) {
		if (MS_aux[impi][i] > 0 || MS_aux[impt][i] > 0 || MS_aux[imqp][i] > 0 || MS_aux[impp][i] > 0) {
			peca_bl[num_itens_bl] = peca_const[i];
			peca_bl[num_itens_bl].demanda = 0;
			for (int j = 0; j < qtd_padroes_escolhidos; j++) {

				peca_bl[num_itens_bl].demanda += MS_aux[ind_padroes_escolhidos[j]][i] *
					MS_aux[ind_padroes_escolhidos[j]][arit];
			}
			num_itens_bl++;
		}
	}
	num_barra_bl = 0;
	perda_prob_bl = 0;
	for (int j = 0; j < qtd_padroes_escolhidos; j++) {
		num_barra_bl += MS_aux[ind_padroes_escolhidos[j]][arit];
		perda_prob_bl += MS_aux[ind_padroes_escolhidos[j]][num_itens_const] *
			MS_aux[ind_padroes_escolhidos[j]][arit];
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!! preenche a struct auxiliar dos itens !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//!!!!!!!!!!!!!!!!!!!!!!!!!! escreve quais padroes foram escolhidos !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	stringstream a0, a1, a2, a7, a11;// , a9;
	string A0, A1, A2, A7, A11;// , A9;
	saida_str += "\nProblema da busca local:\n\n";
	saida_str += "Maior perda individual: PC";
	a0 << impi + 1;
	a0 >> A0;
	saida_str += A0;
	saida_str += ".\n";
	saida_str += "Maior perda total: PC";
	//saida_str += to_string(impt + 1);
	a1 << impt + 1;
	a1 >> A1;
	saida_str += A1;
	saida_str += ".\n";
	saida_str += "Maior numero de pecas: PC";
	//saida_str += to_string(imqp + 1);
	a2 << imqp + 1;
	a2 >> A2;
	saida_str += A2;
	saida_str += ".\n";
	saida_str += "Maior numero de pecas construidas: PC";
	//saida_str += to_string(imqp + 1);
	a11 << impp + 1;
	a11 >> A11;
	saida_str += A11;
	saida_str += ".\n";
	saida_str += "total de barras para a melhoria: ";
	//saida_str += to_string(local_sol);
	a7 << num_barra_bl;
	a7 >> A7;
	//cout << "total de barras para a mehoria: " << local_sol << endl;
	saida_str += A7;
	saida_str += ".\n";
	saida_str += "Conteudo da struct peca_aux:\n";
	for (int i = 0; i < num_itens_bl; i++) {
		stringstream a3, a4, a5, a6;
		string  A3, A4, A5, A6;
		saida_str += "peca_aux[";
		//saida_str += to_string(i + 1);
		a3 << i + 1;
		a3 >> A3;
		saida_str += A3;
		saida_str += "].demanda = ";
		//saida_str += to_string(peca_aux[i].demanda);
		a4 << peca_bl[i].demanda;
		a4 >> A4;
		saida_str += A4;
		saida_str += ".\n";
		saida_str += "peca_aux[";
		//saida_str += to_string(i + 1);
		saida_str += A3;
		saida_str += "].tamanho = ";
		//saida_str += to_string(peca_aux[i].tamanho);
		a5 << peca_bl[i].tamanho;
		a5 >> A5;
		saida_str += A5;
		saida_str += ".\n";
		saida_str += "peca_aux[";
		//saida_str += to_string(i + 1);
		saida_str += A3;
		saida_str += "].indice = ";
		//saida_str += to_string(peca_aux[i].indice);
		a6 << peca_bl[i].indice;
		a6 >> A6;
		saida_str += A6;
		saida_str += ".\n";
		A3.erase();
		A4.erase();
		A5.erase();
		A6.erase();
	}
	A0.erase();
	A1.erase();
	A2.erase();
	A7.erase();
	A11.erase();

	//cout << "fim problema" << endl;

	//!!!!!!!!!!!!!!!!!!!!!!!!!! escreve quais padroes foram escolhidos !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return (saida_str);
}


int central(vector<registro> item, int barra_padrao, int num_itens_const, clock_t t0_GRASP,
	string N_instancia, string repeticao_instancia, string& M, string& R,
	clock_t& tempo_best_sol, int& best_sol, double& alfa_sol, vector <vector<int> >& MS){

	string N_saida = N_instancia + "_Teste" + repeticao_instancia +".txt";
	int repeticao_GRASP = 50;
	clock_t tempo_const;
	clock_t tempo_melh;
	clock_t tempo_sol;
	int perda_total = 0;
	int perda_total_bl = 0;
	int perda_total_const = 0;
	int iteracao = 0;
	int perda_prob_bl = 0;
	int num_itens_bl = 0;
	int num_barra_bl = 0;//numero de barras que vao para a busca local
	int total_sol = 0;
	int qtd_padroes_const = 0;//Guarda a quantidade de padroes.
	int qtd_padroes_bl = 0;
	int qtd_padroes_total = 0;
	int best_qtd_padroes_total = 0;
	int local_sol = 0;
	int const_sol = 0;
	double best_alfa = 0;
	int best_freq = 0;

	srand((unsigned)time(NULL));

	string saida_const;
	string melhoria_bl_str;
	string saida_const_prob;
	string saida_aux;
	string saida;
	string best_saida;
    string str_aux;

	clock_t tempo; //Variavel que guarda o instante em que a solucao foi escrita.

	vector<int> ind_padroes_escolhidos(100, -1);
	int qtd_padroes_escolhidos = 0;


	//t0_GRASP = clock();//Salva o tempo inicial na vari?vel

	//cout << N_saida << endl;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  leitura da instancia !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    str_aux = N_instancia + ".txt" ;
    //ifstream dados;
	//dados.open( str_aux.c_str() );   // entrada da instancia

	//dados >> barra_padrao >> num_itens_const; // le a o tamanho da barra padrao e o numero de itens.

	//vector <vector<int> > MS(100, vector<int>(num_itens_const + 2));// cria vetor que guarda a melhor solucao
	MS.resize(100,vector<int> (num_itens_const+2));
	vector <int> Best_A(100);

	registro* peca_const = new registro[num_itens_const]; // declarou um ponteiro para matriz peca do tipo registro
	registro* peca_bl = new registro[num_itens_const];

	for (int i = 0; i < num_itens_const; i++)
	{// le os Valores de demanda e tamanho
		peca_const[i].demanda = item[i].demanda;
		peca_const[i].tamanho = item[i].tamanho;
		peca_const[i].indice = i;
	}
	//dados.close();//Fecha a inst?ncia.

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	//@@@@@@@@@@@@@@@@@@@@@@@@@ Ordenamento da struct em ordem decrescente @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	int l = 0; // l parametro da funcao particao
	int r = num_itens_const - 1; // r parametro da funcao particao
	quicksort_GRASP2D(peca_const, l, r); // Chama o procedimento de ordena??o.

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	//######################################## CALIBRAGEM ########################################################

	for (double alfa = 0.1; alfa < 1; alfa = alfa + 0.1) {
		for (int c = 1; c <= repeticao_GRASP; c++) {
			saida_const.clear();
			saida_const_prob.clear();
			melhoria_bl_str.clear();
			qtd_padroes_const = 0;
			const_sol = 0;
			qtd_padroes_escolhidos = 0;
			local_sol = 0;
			num_barra_bl = 0;
			vector <vector<int> > MS_aux(100, vector<int>(num_itens_const + 2));// cria vetor que guarda a solucao

			iteracao++;

			saida_const = Const_GRASP(num_itens_const, peca_const, barra_padrao, N_instancia, t0_GRASP,
				MS_aux, alfa, const_sol, qtd_padroes_const, iteracao, perda_total_const,tempo_const);//Chamada da construcao

			saida_const_prob += const_prob_bl(qtd_padroes_const, MS_aux, num_itens_const,
				ind_padroes_escolhidos, qtd_padroes_escolhidos, peca_const, peca_bl, num_itens_bl,
				perda_prob_bl,num_barra_bl);//construcao do problema da melhoria

			melhoria_bl_str = melhoria_bl(num_itens_bl, peca_bl, barra_padrao, num_barra_bl, const_sol,
				MS_aux, qtd_padroes_const, local_sol, num_itens_const, qtd_padroes_bl, perda_total_bl,
				t0_GRASP, tempo_melh);//chamada da melhoria

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATUALIZA AS INFORMACOES DA STRING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			if (local_sol < num_barra_bl) {
				
				total_sol = const_sol - (num_barra_bl - local_sol);
				perda_total = perda_total_const - (perda_prob_bl - perda_total_bl);
				qtd_padroes_total = qtd_padroes_const + qtd_padroes_bl;
				for (int i = qtd_padroes_escolhidos - 1; i >= 0; i--) {
					MS_aux.erase(MS_aux.begin() + ind_padroes_escolhidos[i]);
					qtd_padroes_total--;
				}
				tempo_sol = tempo_melh;

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ESCREVE A SAIDA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//saida_aux = "\nCALIBRAGEM:\n" + saida_const + saida_const_prob + melhoria_bl_str;
				stringstream a0, a1, a2, a3, a4, a5;// a6, a7, a8, a9;
				string A0, A1, A2, A3, A4, A5; //A6, A7, A8, A9;
				saida_aux += "\nFinal GRASP:\nbarras usadas:";
				//saida_aux += to_string(aux_sol);
				a0 << total_sol;
				a0 >> A0;
				saida_aux += A0;
				saida_aux += ".\n";
				saida_aux += "melhoria:";
				a5 << (num_barra_bl - local_sol);
				a5 >> A5;
				saida_aux += A5;
				saida_aux += ".\n";
				saida_aux += "alfa = ";
				//saida_aux += to_string(alfa);
				a1 << alfa;
				a1 >> A1;
				saida_aux += A1;
				saida_aux += ".\n";
				saida_aux += "Perda Total = ";
				//saida_aux += to_string(perda_total);
				a2 << perda_total;
				a2 >> A2;
				saida_aux += A2;
				saida_aux += ".\n";
				saida_aux += "Iteracao: ";
				//saida_aux += to_string(iteracao);
				a3 << iteracao;
				a3 >> A3;
				saida_aux += A3;
				saida_aux += ".\n";
				saida_aux += "Tempo = ";
				//saida_aux += to_string(((double)(tempo - t0_GRASP)) / CLOCKS_PER_SEC);
				a4 << ((double)tempo_sol) / CLOCKS_PER_SEC;
				a4 >> A4;
				saida_aux += A4;
				saida_aux += " s";
				saida_aux += ".\n";
				saida.clear();
				saida += saida_aux;
				saida_aux.clear();
				A0.erase();
				A1.erase();
				A2.erase();
				A3.erase();
				A4.erase();
				A5.erase();

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ESCREVE A SAIDA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			}
			else {
				
				total_sol = const_sol;
				perda_total = perda_total_const;
				qtd_padroes_total = qtd_padroes_const;

				tempo_sol = tempo_const;
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ESCREVE A SAIDA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				saida_aux = /*"\nCALIBRAGEM:\n" +*/ saida_const + saida_const_prob + "\n Nao Ocorreu Melhoria!! \n";
				stringstream a0, a1, a2, a3, a4, a5;// a6, a7, a8, a9;
				string A0, A1, A2, A3, A4, A5; //A6, A7, A8, A9;
				saida_aux += "\nFinal GRASP:\nbarras usadas:";
				//saida_aux += to_string(aux_sol);
				a0 << const_sol;
				a0 >> A0;
				saida_aux += A0;
				saida_aux += ".\n";
				saida_aux += "melhoria:";
				a5 << 0;
				a5 >> A5;
				saida_aux += A5;
				saida_aux += ".\n";
				saida_aux += "alfa = ";
				//saida_aux += to_string(alfa);
				a1 << alfa;
				a1 >> A1;
				saida_aux += A1;
				saida_aux += ".\n";
				saida_aux += "Perda Total = ";
				//saida_aux += to_string(perda_total);
				a2 << perda_total_const;
				a2 >> A2;
				saida_aux += A2;
				saida_aux += ".\n";
				saida_aux += "Iteracao: ";
				//saida_aux += to_string(iteracao);
				a3 << iteracao;
				a3 >> A3;
				saida_aux += A3;
				saida_aux += ".\n";
				saida_aux += "Tempo = ";
				//saida_aux += to_string(((double)(tempo - t0_GRASP)) / CLOCKS_PER_SEC);
				a4 << ((double)tempo_const) / CLOCKS_PER_SEC;
				a4 >> A4;
				saida_aux += A4;
				saida_aux += " s";
				saida_aux += ".\n";
				saida.clear();
				saida += saida_aux;
				saida_aux.clear();
				A0.erase();
				A1.erase();
				A2.erase();
				A3.erase();
				A4.erase();

				A5.erase();

			}


			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATUALIZA AS INFORMACOES DA STRING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATUALIZA A MELHOR SOLUCAO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (best_sol == total_sol) {
				Best_A[int(100 * alfa)]++;
			}
			else {
				if (best_sol > total_sol) {
					//cout << total_sol << endl;
					if (local_sol < num_barra_bl) {
						M = "M";
					}
					else {
						M = " ";
					}
					tempo_best_sol = tempo_sol;
					alfa_sol = alfa;

					for (int i = 0; i < 100; i++) {
						Best_A[i] = 0;
					}
					Best_A[int(100 * alfa)]++;
					best_qtd_padroes_total = qtd_padroes_total;
					best_sol = total_sol;

					if (MS.size() < MS_aux.size()) {
						MS.resize(MS_aux.size(), vector<int>(MS[0].size()));
					}

					for (int i = 0; i < best_qtd_padroes_total; i++) {
						for (int j = 0; j < num_itens_const + 2; j++) {
							MS[i][j] = MS_aux[i][j];
						}
					}
					best_saida.clear();
					best_saida += saida;

				}
				else {
					if (best_sol == 0) {
						tempo_best_sol = tempo_sol;
						alfa_sol = alfa;
						Best_A[int(100 * alfa)]++;
						best_qtd_padroes_total = qtd_padroes_total;
						best_sol = total_sol;

						if (MS.size() < MS_aux.size()) {
							MS.resize(MS_aux.size(), vector<int>(MS[0].size()));
						}

						for (int i = 0; i < best_qtd_padroes_total; i++) {
							for (int j = 0; j < num_itens_const + 2; j++) {
								MS[i][j] = MS_aux[i][j];
							}
						}
						best_saida += saida;
						saida.clear();
					}
				}

			}

			MS_aux.clear();
			saida.clear();
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATUALIZA A MELHOR SOLUCAO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
	}

	
	stringstream a0, a1, a2, a3;// , a4, a5, a6, a7, a8, a9;
	string A0, A1, A2, A3;// , A4, A5A6, A7, A8, A9;


	a1 << ((double)tempo_best_sol - t0_GRASP) / CLOCKS_PER_SEC;
	a1 >> A1;

	best_saida += "Tempo Total = ";
	//saida_aux += to_string(((double)(tempo - t0_GRASP)) / CLOCKS_PER_SEC);
	tempo = clock();
	a2 << ((double)tempo - t0_GRASP) / CLOCKS_PER_SEC;
	a2 >> A2;
	best_saida += A2;
	best_saida += " s";
	best_saida += ".\n";

	//estatistica_str += N_saida + " ";
	//estatistica_str += A2 + " ";
	//estatistica_str += A1 + " ";

	//a3 << alfa_sol;
	//a3 >> A3;
	//estatistica_str += A3 + " ";

	a0 << best_sol;
	a0 >> A0;
	//estatistica_str += A0 + " " + M + " " + R;

	//N_saida += "_" + A0 +".txt";


	A0.erase();
	
	ofstream teste;
	teste.open(N_saida.c_str(), ios::trunc);
	if (!teste.good()) {
		cout << "o arquivo de saida n?o pode ser aberto." << endl;
		return 0;
	}
	teste << best_saida << endl;
	teste.close();
	best_saida.clear();


	saida += "Conteudo da matriz MS:\n";
	for (int i = 0; i < best_qtd_padroes_total; i++) {


		stringstream a0, a3, a4;//, a5, a6, a7, a8, a9;
		string A0, A3, A4;//, A5, A6, A7, A8, A9;
		saida += "PC";
		//saida += to_string(i+1);
		a0 << i + 1;
		a0 >> A0;
		saida += A0;
		saida += ": (";
		for (int j = 0; j < num_itens_const; j++) {
			stringstream a1, a2;
			string A1, A2;
			if (j != num_itens_const - 1) {
				//saida += to_string(MS[i][j]);
				a1 << MS[i][j];
				a1 >> A1;
				saida += A1;
				saida += ",";
			}
			else {
				//saida += to_string(MS[i][j]);
				a2 << MS[i][j];
				a2 >> A2;
				saida += A2;
				saida += "), perda = ";
			}
			A1.erase();
			A2.erase();
		}
		//saida += to_string(MS[i][num_itens_const]);
		a3 << MS[i][num_itens_const];
		a3 >> A3;
		saida += A3;
		saida += ", repeticoes = ";
		//saida += to_string(MS[i][num_itens_const+1]);
		a4 << MS[i][num_itens_const + 1];
		a4 >> A4;
		saida += A4;
		saida += ".\n";

		A0.erase();
		A3.erase();
		A4.erase();
	}


    str_aux = "Matriz_MS_" + N_instancia + "_Teste" + repeticao_instancia + ".txt";
	teste.open( str_aux.c_str() , ios::trunc);
	if (!teste.good()) {
		cout << "o arquivo de saida n?o pode ser aberto." << endl;
		return 0;
	}
	teste << saida << endl;
	teste.close();


	return 0;
	}
	
