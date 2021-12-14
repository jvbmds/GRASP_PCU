#include "Cabecalho.hpp"

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

	
	//preenche buffer que guarda a informacao dos itens que vao
	//para a busca local
	saida_str += "\nProblema da busca local:\n\n";
	saida_str += "Maior perda individual: PC" + to_string(impi + 1) + ".\n";
	saida_str += "Maior perda total: PC" + to_string(impt + 1) + ".\n";
	saida_str += "Maior numero de pecas: PC" + to_string(imqp + 1) + ".\n";
	saida_str += "Maior numero de pecas construidas: PC" + to_string(imqp + 1) + ".\n";
	saida_str += "total de barras para a melhoria: " + to_string(num_barra_bl) + ".\n";
	saida_str += "Conteudo da struct peca_aux:\n";
	for (int i = 0; i < num_itens_bl; i++) {
		saida_str += "peca_aux[" + to_string(i + 1) + "].demanda = " + to_string(peca_bl[i].demanda) + ".\n";
		saida_str += "peca_aux[" + to_string(i + 1) + "].tamanho = " + to_string(peca_bl[i].tamanho) + ".\n";
		saida_str += "peca_aux[" + to_string(i + 1) + "].indice = " + to_string(peca_bl[i].indice) + ".\n";
	}
	
	// retorna o buffer
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

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  leitura da instancia !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    str_aux = N_instancia + ".txt" ;
    
	MS.resize(100,vector<int> (num_itens_const+2));
	vector <int> Best_A(100);

	registro* peca_const = new registro[num_itens_const]; // declarou um ponteiro para matriz peca do tipo registro
	registro* peca_bl = new registro[num_itens_const];

	for (int i = 0; i < num_itens_const; i++)
	{
		peca_const[i].demanda = item[i].demanda;
		peca_const[i].tamanho = item[i].tamanho;
		peca_const[i].indice = item[i].indice;
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

				//Escreve o buffer do arquivo de saida
				saida_aux += "\nFinal GRASP:\n";
				saida_aux += "barras usadas:" + to_string(total_sol) + ".\n";
				saida_aux += "melhoria:" + to_string(num_barra_bl - local_sol) + ".\n";
				saida_aux += "alfa = " + to_string(alfa) + ".\n";
				saida_aux += "Perda Total = " + to_string(perda_total) + ".\n";
				saida_aux += "Iteracao: " + to_string(iteracao) + ".\n";
				saida_aux += "Tempo = " + to_string(((double)tempo_sol) / CLOCKS_PER_SEC) + "s.\n";
				saida.clear();
				saida += saida_aux;
				saida_aux.clear();

			}
			else {
				total_sol = const_sol;
				perda_total = perda_total_const;
				qtd_padroes_total = qtd_padroes_const;
				tempo_sol = tempo_const;

				//Escreve o buffer do arquivo de saida
				saida_aux = saida_const + saida_const_prob + "\n Nao Ocorreu Melhoria!! \n";
				saida_aux += "\nFinal GRASP:";
				saida_aux += "\nbarras usadas:" + to_string(const_sol) + ".\n";
				saida_aux += "melhoria:0.\n";
				saida_aux += "alfa = " + to_string(alfa) + ".\n";
				saida_aux += "Perda Total = " + to_string(perda_total) + ".\n";
				saida_aux += "Iteracao: " + to_string(iteracao) + ".\n";
				saida_aux += "Tempo = " + to_string(((double)tempo_const) / CLOCKS_PER_SEC) + " s.\n";
				saida.clear();
				saida += saida_aux;
				saida_aux.clear();
			}

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATUALIZA A MELHOR SOLUCAO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (best_sol == total_sol) {
				Best_A[int(100 * alfa)]++;
			}
			else {
				if (best_sol > total_sol) {
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

	//Escreve o buffer do arquivo de saida
	tempo = clock();
	best_saida += "Tempo Total = " + to_string(((double)tempo - t0_GRASP) / CLOCKS_PER_SEC) + " s.\n";

	//Abre escreve o arquivo de saida
	ofstream teste;
	teste.open(N_saida.c_str(), ios::trunc);
	if (!teste.good()) {
		cout << "o arquivo de saida n?o pode ser aberto." << endl;
		return 1;
	}
	teste << best_saida << endl;
	teste.close();
	best_saida.clear();

	//Escreve o buffer do arquivo que contem
	//o conteudo da matriz solucao
	saida += "Conteudo da matriz MS:\n";
	for (int i = 0; i < best_qtd_padroes_total; i++) {
		saida += "PC" + to_string( i + 1 ) + ": (";
		for (int j = 0; j < num_itens_const; j++) {
			if (j != num_itens_const - 1) saida += to_string(MS[i][j]) + ','; 
			else saida += to_string(MS[i][j]) + "), perda = ";
		}
		saida += to_string(MS[i][num_itens_const]) + ", repeticoes = " + to_string(MS[i][num_itens_const+1]) + ".\n";
	}
    str_aux = "Matriz_MS_" + N_instancia + "_Teste" + repeticao_instancia + ".txt";

	//Abre e escreve o arquivo da matriz solucao
	teste.open( str_aux.c_str() , ios::trunc);
	if (!teste.good()) {
		cout << "o arquivo de saida n?o pode ser aberto." << endl;
		return 0;
	}
	teste << saida << endl;
	teste.close();
	return 0;
	}
	
