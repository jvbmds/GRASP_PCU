#include "Cabecalho.hpp"


int maxpeca(registro peca[] , int num_itens_const, double barra_aux, vector<int> demanda_aux)
{ // Retorna o indice da maior pe�a que cabe na barra restante e tem demanda maior que 0.
	int ibeta = -1; //Guarda o ?ndice  da pe?a desejada.
	int i;
	for (i = 0; i < num_itens_const; i++)
	{
		if (peca[i].tamanho <= barra_aux && demanda_aux[i] > 0)
		{
			ibeta = i;
			break;
		}
	}
	return (ibeta);
}

int minpeca(registro peca[], int num_itens_const, vector<int> demanda_aux)
{ // Retorna o ?ndice da menor pe?a com demanda maior que 0.
	int imnp = -1;//Guarda o ?ndice  da pe?a desejada.
	int i;
	for (i = num_itens_const - 1; i >= 0; i--)
	{
		if (demanda_aux[i] > 0 && peca[i].indice >= 0)
		{
			imnp = i;
			break;
		}
	}
	return (imnp);
}

int lir(registro peca[], double ALFA, int n, int iBETA, vector<int> demanda_aux)
{// Retorna o ?ndice da pe?a escolhida aleatoriamente na LCR.
	int ind = 0; // N?mero de elementos da LCR.
	int i; // Contador
	int ik; // ?ndice da pe?a escolhida.
	int indLRC = 0; // ?ndices da LCR.
	int iRand; // Guarda o n?mero obtido aleat?riamente.
	if (iBETA < 0) {
		return(-1);
	}

	double q = ((ALFA) * (peca[iBETA].tamanho));// Guarda o tamanho m?nimo das pe?as da LCR.

	for (i = 0; i < n; i++)
	{// Verifica quantos ?ndices a LCR tem.
		if (peca[i].tamanho >= q && demanda_aux[i] > 0 && peca[i].tamanho <= peca[iBETA].tamanho)
		{
			ind = ind + 1;
		}
	}

	vector<int> LCR(ind);

	if (ind != 0) {
		for (i = 0; i < n; i++)
		{
			if (peca[i].tamanho >= q && demanda_aux[i] > 0 && peca[i].tamanho <= peca[iBETA].tamanho)
			{
				LCR[indLRC++] = i;//Preenche a LCR.
			}
		}
		iRand = rand() % ind;  // <cstdlib>
		ik = LCR[iRand];
		LCR.clear();
		return (ik);
	}
	else {
		ik = -1;
		return (ik);
	}
}


string Const_GRASP(int num_itens_const, registro peca_const[], int barra_padrao, string N_instancia,
	clock_t t0_GRASP, vector<vector<int>> &MS_aux, double alfa, int& const_sol, int& qtd_padroes_const,
	int iteracao, int& perda_total_const,clock_t &tempo_const){
	const_sol = 0;

	//cout << "inicio construcao" << endl;


	clock_t tempo;
	int i = 0, j = 0;//Contador.
	//int qtd_padroes_const = 0;
	//int iteracao = 0;//Contador que guarda a itera??o para ser escrita na saida
//	int inst;//Vari?vel utilizada para escolha da inst?ncia.
	int imp;//Guarda o ?ndice da maior pe?a.
	int cb;//Guarda a quantidade de vezes que o item escolhido cabe na peca.
	int repeticao;//variavel que guarda quantas vezes o padrao de corte vai se repetir
	//int num_itens_const;//Guarda o n?mero de itens do pedido.
	//int barra = 0;//Guarda o n?mero de barras usadas.
	int ik; // ?ndice da pe?a escolhida.
	int imnp;
	//int barra_padrao;// Tamanho da barra padr?o.
	int perda;//Guarda a perda de cada padr?o criado.
	//int perda_total = 0;//Guarda o somat?rio da perda dos padr?es.
	int barra_aux;// auxiliar que guarda o tamanho restante da barra que pode ser utilizado.

	//int local_sol = 0;
	string saida_aux;//String auxiliar que guarda a sa?da enquanto ela est? sendo construida
	string melhor_solucao;//string que guarda a melhor solu??o
	ofstream teste;//Declara??o da ofstream que abrir? os arquivos de sa?da.
//ifstream dados;//Declara??o da ifstream que abrir? os arquivos da inst?ncia escolhida.
	ifstream instancia;//Declara??o da ifstream que abrir? o txt com o nome das inst?ncias.

	//clock_t tempo; //Var?avel que guarda o instante em que a solu??o foi escrita.






	vector <int> demanda_aux(num_itens_const); // vetor auxiliar que guarda a demanda e vai sendo alterado no meio do processo.

	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ PROCESSO $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


	//!!!!!!!!!!!!!!!!!!!!!!! atualiza a demanda e o indice da menor peca !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	for (i = 0; i < num_itens_const; i++) {//Preenche peca.demanda com a demanda ordenada.
		demanda_aux[i] = peca_const[i].demanda;


	}
	//!!!!!!!!!!!!!!!!!!!!!!! atualiza a demanda e o indice da menor peca !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	imnp = minpeca(peca_const, num_itens_const, demanda_aux);
	//################################ construcao do padrao de corte completo #############################################
	imnp = minpeca(peca_const, num_itens_const, demanda_aux);
	do {
		perda = 0;
		barra_aux = barra_padrao;
		repeticao = 0;
		qtd_padroes_const++;
		vector <int> PC(num_itens_const + 2);// Guarda a quantidade de vezes que determinada pe?a ser? repetida no padr?o criado.
		vector <int> Aux(num_itens_const);// Auxiliar usado para ver quantas vezes se pode repetir o padr?o de corte adquirido


		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  constru��o de um padrao @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		do {// while (barra_aux >= peca[imnp].tamanho && imnp >= 0);
			imp = maxpeca(peca_const, num_itens_const, barra_aux, demanda_aux);//devolve o indice da maior peca com demanda disponivel
			cb = 0;
			ik = -1;

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!! escolha do item !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			ik = lir(peca_const, alfa, num_itens_const, imp, demanda_aux);

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!! escolha do item !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


			//!!!!!!!!!!!!!!!!!!!!!!!! ve quantas vezes o padr�o pode rodar sem estourar a demanda
			// do item escolhido !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			cb = barra_aux / peca_const[ik].tamanho;


			if (demanda_aux[ik] >= cb) {
				PC[ik] = cb;
			}
			else {
				cb = demanda_aux[ik];
				PC[ik] = cb;
				demanda_aux[ik] = 0;
				Aux[ik] = 1;
				if (imnp == ik) {
					imnp = minpeca(peca_const, num_itens_const, demanda_aux);
				}
			}

			//!!!!!!!!!!!!!!!!!!!!!!!! ve quantas vezes o padr�o pode rodar sem estourar a demanda
			// do item escolhido !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


			//////////Atualiza o valor da barra auxiliar

			barra_aux = barra_aux - cb * peca_const[ik].tamanho;
		} while (barra_aux >= peca_const[imnp].tamanho && imnp >= 0);

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  constru��o de um padrao @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


		//!!!!!!!!!!!!!!!!!!!!!!!!! verifica a quantidade de vezes que o padrao pode ser executado !!!!!!!!!!!!!!!
		for (i = 0; i < num_itens_const; i++)
		{
			if (PC[i] != 0 && Aux[i] == 0) {//Preenche o vetor A.
				Aux[i] = demanda_aux[i] / PC[i];
			}
		}
		for (i = 0; i < num_itens_const; i++) {
			if (Aux[i] > repeticao) {
				repeticao = Aux[i];
			}
		}
		for (i = 0; i < num_itens_const; i++) {
			if (PC[i] != 0 && repeticao > Aux[i]) {
				repeticao = Aux[i];
			}
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!! verifica a quantidade de vezes que o padrao pode ser executado !!!!!!!!!!!!!!!




		perda = perda + barra_aux;//Conta a perda de cada padr?o.
		const_sol = const_sol + repeticao;//conta as barras usadas.
		perda_total_const = perda_total_const + perda * repeticao;//conta a perda de todos os padr?es.
		PC[num_itens_const] = perda;//Salva perda em uma matriz temporaria
		PC[num_itens_const + 1] = repeticao;//Salva as repeti??es em uma matriz tempor?ria.


		if (qtd_padroes_const - 1 == (int)MS_aux.size()) {
			MS_aux.resize(MS_aux.size() + 100, vector<int>(MS_aux[0].size()));
		}

		for (j = 0; j < num_itens_const + 2; j++) {
			MS_aux[qtd_padroes_const - 1][j] = PC[j];
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!! salva as alteracoes na matriz principal !!!!!!!!!!!!!!!


		//!!!!!!!!!!!!!!!!!!!!!!! atualiza a demanda e o indice da menor peca !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		for (i = 0; i < num_itens_const; i++) {
			if (demanda_aux[i] != 0) {
				demanda_aux[i] = demanda_aux[i] - PC[i] * repeticao;
			}
		}
		imnp = minpeca(peca_const, num_itens_const, demanda_aux);

		//!!!!!!!!!!!!!!!!!!!!!!! atualiza a demanda e o indice da menor peca !!!!!!!!!!!!!!!!!!!!!!!!!!!!!


		// escreve o no buffer da saida o padrao de corte criado
		saida_aux += "PC" + to_string(qtd_padroes_const) + ':';
		for (i = 0; i < num_itens_const; i++) {
			if (i != num_itens_const - 1 ){ if( PC[i] > 0) saida_aux += '(' + to_string(PC[i]) + ", " + to_string(peca_const[i].tamanho) + ')'; 
			}else {
				if (repeticao == 1) {
					if (PC[i] > 0) saida_aux += '(' + to_string(PC[i]) + ", " + to_string(peca_const[i].tamanho) + ')';
					saida_aux += " perda = " + to_string(perda) + ", 1 repeticao.\n";
				}
				else {
					if (PC[i] > 0) saida_aux += '(' + to_string(PC[i]) + ", " + to_string(peca_const[i].tamanho) + ')';
					saida_aux += " perda = " + to_string(perda) + ", " + to_string(repeticao) + " repeticoes.\n";
				}
			}
		}

		Aux.clear();
		PC.clear();
	} while (imnp >= 0);

	//Escreve as informacoes do padrao criado no buffer da saida
	tempo = clock();
	tempo_const = tempo - t0_GRASP;
	saida_aux += "barras usadas:" + to_string(const_sol) + ".\n";
	saida_aux += "Melhor alfa = " + to_string(alfa) + ".\n";
	saida_aux += "Perda Total = " + to_string(perda_total_const) + ".\n";
	saida_aux += "Iteracao: " + to_string(iteracao) + ".\n";
	saida_aux += "Tempo = " + to_string(((double)tempo_const) / CLOCKS_PER_SEC) + " s.\n";
	return (saida_aux);
}
