#include "cabecalho.h"






string melhoria_bl(int num_itens_bl, registro peca_bl[], int barra_padrao, int num_barra_bl, int const_sol,
	vector<vector<int>>& MS, int& qtd_padroes_const, int& local_sol, int num_itens_const,
	int& qtd_padroes_bl, int& perda_total_bl, clock_t t0_GRASP, clock_t& tempo_melh) {

	//cout << "inicio melhoria" << endl;
	int repeticao_melhoria = 50;
	clock_t tempo;
	int i = 0, j = 0, k = 0, c = 0;//Contador.
	int iteracao = 0;//Contador que guarda a itera??o para ser escrita na saida
//	int inst;//Vari?vel utilizada para escolha da inst?ncia.
	int imp;//Guarda o ?ndice da maior pe?a.
	int cb;//Guarda a quantidade de vezes que o item escolhido cabe na peca.
	int repeticao;//variavel que guarda quantas vezes o padrao de corte vai se repetir
//	int num_itens_bl;Guarda o n?mero de itens do pedido.
	int aux_sol = 0;
	local_sol = num_barra_bl;//Guarda o numero de barras utilizada na construcao
//	int barra = 0;Guarda o n?mero de barras usadas.
	int ik; // indice da peca escolhida
	double alfa;//Coeficiente de aleatoriedade.
	int imnp;//Guarda o indice da menor pe?a com demanda restante.
//	int barra_padrao;// Tamanho da barra padr?o.
	int perda;//Guarda a perda de cada padr?o criado.
	int perda_total = 0;//Guarda o somat?rio da perda dos padr?es.
	int barra_aux;// auxiliar que guarda o tamanho restante da barra que pode ser utilizado.

//	int mpi = 0;//guarda a maior perda individual
//	int impi;//guarda o indice da linha do padrao com maior perda individual
//	int mpt = 0;//guarda a maior perda total
//	int impt;//guarda o indice da linha do padrao com maior perda total
//	int mqp = 0;//guarda a maior quantidade de pecas n?o-nulas entre os padroes
//	int mqp_aux = 0;
//	int imqp;//guarda o indice da linha do padrao com a maior quantidade de pecas n?o-nulas
	string N_instancia;// Nome do arquivo de entrada.
	string N_saida_busca_local;//Nome do arquivo de sa?da.
	string saida_aux;//String auxiliar que guarda a sa?da enquanto ela est? sendo construida.
	string melhor_solucao;//string que guarda a melhor solu??o
	ofstream teste;//Declara??o da ofstream que abrir? os arquivos de sa?da.
	ifstream dados;//Declara??o da ifstream que abrir? os arquivos da inst?ncia escolhida.
	ifstream instancia;//Declara??o da ifstream que abrir? o txt com o nome das inst?ncias.
	//clock_t t0_GRASP;// Vari?vel que guarda o tempo inicial do programa.
	//srand((unsigned)time(NULL)); // Retorna uma sequencia de numeros pseudo-aleatorio.
	N_saida_busca_local = "Melhor_solucao_busca_local.txt";
	//t0_GRASP = clock();//Salva o tempo inicial na vari?vel


	vector <int> indice_aux(num_itens_bl);
	vector < vector <int> > PC_aux(100, vector<int>(num_itens_bl + 2));//vetor auxiliar que guarda os padroes de corte
	vector <int> demanda_aux(num_itens_bl); // vetor auxiliar que guarda a demanda e vai sendo alterado no meio do processo.

	for (i = 0; i < num_itens_bl; i++) {
		indice_aux[i] = peca_bl[i].indice;
		peca_bl[i].indice = i;
	}

	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ PROCESSO $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	for  (alfa = 0.1; alfa <= 1; alfa = alfa + 0.1)
	{//Loop que altera os testes.

		for (c = 1; c <= repeticao_melhoria; c++)
		{//Loop que altera os alfas.
			//cout << "alfa " << alfa;
			//cout << "oi2";
			iteracao++;
			//cout << "inicio solucao" << endl;
			for (i = 0; i < num_itens_bl; i++) {//Preenche peca_bl.demanda com a demanda ordenada.
				demanda_aux[i] = peca_bl[i].demanda;
			}

			imnp = minpeca(peca_bl, num_itens_bl, demanda_aux);//Atualiza o valor do indice da menor pe?a com demanda.

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CRIA A SOLUCAO @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			saida_aux += "\nMelhoria:\n\n";
			do {
				perda = 0;
				barra_aux = barra_padrao;
				repeticao = 0;
				k++;
				vector <int> PC(num_itens_bl + 2);// Guarda a quantidade de vezes que determinada pe?a ser? repetida no padr?o criado.
				vector <int> Aux(num_itens_bl);// Auxiliar usado para ver quantas vezes se pode repetir o padr?o de corte adquirido

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CRIA O PADRAO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//cout << "inicio padrao" << endl;
				do {
					imp = maxpeca(peca_bl, num_itens_bl, barra_aux, demanda_aux);//devolve o indice da maior peca com demanda disponivel
					cb = 0;
					ik = -1;



					ik = lir(peca_bl, alfa, num_itens_bl, imp, demanda_aux);// seleciona o item

					cb = barra_aux / peca_bl[ik].tamanho;

					if (demanda_aux[ik] >= cb) {
						PC[peca_bl[ik].indice] = cb;
					}
					else {
						cb = demanda_aux[ik];
						PC[peca_bl[ik].indice] = cb;
						demanda_aux[ik] = 0;
						Aux[peca_bl[ik].indice] = 1;
						if (imnp == ik) {
							imnp = minpeca(peca_bl, num_itens_bl, demanda_aux);//Atualiza o valor do indice da menor pe?a com demanda.
						}
					}

					barra_aux = barra_aux - cb * peca_bl[ik].tamanho;//Atualiza o valor da barra aux.
				} while (barra_aux >= peca_bl[imnp].tamanho && imnp >= 0);
				//cout << "fim padrao" << endl;
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CRIA O PADRAO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! VE QUANTAS VEZES O PADRAO PODE SER REPETIDO !!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//cout << "inicio repeticao" << endl;
				for (i = 0; i < num_itens_bl; i++)
				{
					if (PC[i] != 0 && Aux[i] == 0) {//Preenche o vetor A.
						Aux[i] = demanda_aux[peca_bl[i].indice] / PC[i];
					}
				}
				for (i = 0; i < num_itens_bl; i++) {
					if (Aux[i] > repeticao) {
						repeticao = Aux[i];
					}
				}
				for (i = 0; i < num_itens_bl; i++) {
					if (PC[i] != 0 && repeticao > Aux[i]) {
						repeticao = Aux[i];
					}
				}

				//cout << "fim repeticao" << endl;
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! VE QUANTAS VEZES O PADRAO PODE SER REPETIDO !!!!!!!!!!!!!!!!!!!!!!!!!!!!

				//cout << "inicio alocacao" << endl;

				perda = perda + barra_aux;//Conta a perda de cada padrao.
				aux_sol = aux_sol + repeticao;//conta as barras usadas.
				perda_total = perda_total + perda * repeticao;//conta a perda de todos os padr?es.
				PC[num_itens_bl] = perda;//Salva perda em uma matriz temporaria
				PC[num_itens_bl + 1] = repeticao;//Salva as repeti??es em uma matriz temporaria.
				if (k - 1 == PC_aux.size()) {
					PC_aux.resize(PC_aux.size() + 100, vector<int>(PC_aux[0].size()));
				}
				for (j = 0; j < num_itens_bl + 2; j++) {
					PC_aux[k - 1][j] = PC[j];
				}


				//!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATUALIZA A DEMANDA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				for (i = 0; i < num_itens_bl; i++) {
					if (demanda_aux[i] != 0) {
						demanda_aux[i] = demanda_aux[i] - PC[peca_bl[i].indice] * repeticao;
					}
				}
				imnp = minpeca(peca_bl, num_itens_bl, demanda_aux);
				//cout << "fim alocacao" << endl;
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATUALIZA A DEMANDA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!! ESCREVE O PADRAO EM STRING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				stringstream a0;//, a1, a2, a3, a4, a5, a6, a7, a8, a9;
				string A0;//, A1, A2, A3, A4, A5, A6, A7, A8, A9;

				saida_aux += "PC";
				//saida_aux += to_string(k);
				a0 << k;
				a0 >> A0;
				saida_aux += A0;
				saida_aux += ":";

				A0.erase();


				for (i = 0; i < num_itens_bl; i++) {
					if (i != num_itens_bl - 1) {
						if (PC[i] > 0) {



							stringstream a0, a1;//, a2, a3, a4, a5, a6, a7, a8, a9;
							string A0, A1;//, A2, A3, A4, A5, A6, A7, A8, A9;
							saida_aux += "(";
							//saida_aux += to_string(PC[i]);
							a0 << PC[i];
							a0 >> A0;
							saida_aux += A0;
							saida_aux += ", ";
							//saida_aux += to_string(peca_bl[peca_bl[i].indice].tamanho);
							a1 << peca_bl[peca_bl[i].indice].tamanho;
							a1 >> A1;
							saida_aux += A1;
							saida_aux += ")";

							A0.erase();
							A1.erase();

						}
					}
					else {
						if (repeticao == 1) {
							if (PC[i] > 0) {


								stringstream a0, a1;//, a2, a3, a4, a5, a6, a7, a8, a9;
								string A0, A1;//, A2, A3, A4, A5, A6, A7, A8, A9;
								saida_aux += "(";
								//saida_aux += to_string(PC[i]);
								a0 << PC[i];
								a0 >> A0;
								saida_aux += A0;
								saida_aux += ", ";
								//saida_aux += to_string(peca_bl[peca_bl[i].indice].tamanho);
								a1 << peca_bl[peca_bl[i].indice].tamanho;
								a1 >> A1;
								saida_aux += A1;
								saida_aux += ")";

								A0.erase();
								A1.erase();


							}



							stringstream a0, a1;//, a2, a3, a4, a5, a6, a7, a8, a9;
							string A0, A1;//, A2, A3, A4, A5, A6, A7, A8, A9;
							saida_aux += " perda = ";
							//saida_aux += to_string(perda);
							a0 << perda;
							a0 >> A0;
							saida_aux += A0;
							saida_aux += ", ";
							//saida_aux += to_string(repeticao);
							a1 << repeticao;
							a1 >> A1;
							saida_aux += A1;
							saida_aux += " repeticao.\n";

							A0.erase();
							A1.erase();

						}
						else {
							if (PC[i] > 0) {

								stringstream a0, a1;//, a2, a3, a4, a5, a6, a7, a8, a9;
								string A0, A1;//, A2, A3, A4, A5, A6, A7, A8, A9;
								saida_aux += "(";
								//saida_aux += to_string(PC[i]);
								a0 << PC[i];
								a0 >> A0;
								saida_aux += A0;
								saida_aux += ", ";
								//saida_aux += to_string(peca_bl[peca_bl[i].indice].tamanho);
								a1 << peca_bl[peca_bl[i].indice].tamanho;
								a1 >> A1;
								saida_aux += A1;
								saida_aux += ")";

								A0.erase();
								A1.erase();


							}

							stringstream a0, a1;//, a2, a3, a4, a5, a6, a7, a8, a9;
							string A0, A1;//, A2, A3, A4, A5, A6, A7, A8, A9;
							saida_aux += " perda = ";
							//saida_aux += to_string(perda);
							a0 << perda;
							a0 >> A0;
							saida_aux += A0;
							saida_aux += ", ";
							//saida_aux += to_string(repeticao);
							a1 << repeticao;
							a1 >> A1;
							saida_aux += A1;
							saida_aux += " repeticao.\n";

							A0.erase();
							A1.erase();


						}
					}
				}

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!! ESCREVE O PADRAO EM STRING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				Aux.clear();
				PC.clear();
			} while (imnp >= 0);
			tempo = clock();

			//cout << "fim solucao" << endl;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CRIA A SOLUCAO @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ATUALIZA A SOLUCAO @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//cout << "inicio atualizacao" << endl;
			if (local_sol > aux_sol) {
				perda_total_bl = perda_total;
				qtd_padroes_bl = k;
				local_sol = aux_sol;
				for (i = 0; i < qtd_padroes_bl; i++) {
					if (qtd_padroes_const + qtd_padroes_bl > MS.size()) {
						MS.resize(MS.size() + 100, vector<int>(MS[0].size()));
					}
					for (j = 0; j < num_itens_bl; j++) {
						MS[qtd_padroes_const + i][j] = PC_aux[i][peca_bl[j].indice];
					}
					MS[qtd_padroes_const + i][num_itens_const] = PC_aux[i][num_itens_bl];
					MS[qtd_padroes_const + i][num_itens_const + 1] = PC_aux[i][num_itens_bl + 1];
				}

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ESCREVE A SAIDA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				stringstream a0, a1, a2, a3, a4, a5;// a6, a7, a8, a9;
				string A0, A1, A2, A3, A4, A5; //A6, A7, A8, A9;
				saida_aux += "barras usadas:";
				//saida_aux += to_string(aux_sol);
				a0 << aux_sol;
				a0 >> A0;
				saida_aux += A0;
				saida_aux += ".\n";
				saida_aux += "melhoria:";
				a5 << num_barra_bl - local_sol;
				a5 >> A5;
				saida_aux += A5 ;
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
				tempo_melh = tempo - t0_GRASP;
				a4 << ((double)tempo_melh) / CLOCKS_PER_SEC;
				a4 >> A4;
				saida_aux += A4;
				saida_aux += " s";
				saida_aux += ".\n";
				melhor_solucao.clear();
				melhor_solucao += saida_aux;

				A0.erase();
				A1.erase();
				A2.erase();
				A3.erase();
				A4.erase();
				A5.erase();

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ESCREVE A SAIDA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ATUALIZA A SOLUCAO @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			}
			//cout << "fim atualizacao" << endl;
			k = 0;
			perda_total = 0;
			aux_sol = 0;
			saida_aux.clear();
		}
	}

	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ PROCESSO $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//cout << "fim melhoria" << endl;
	PC_aux.clear();
	demanda_aux.clear();
	return (melhor_solucao);
}
