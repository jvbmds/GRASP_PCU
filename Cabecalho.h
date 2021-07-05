#pragma once

#include <vector>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct registro {           // Estrutura de entrada.
    int demanda;		    // Demanda total.
    int tamanho;            // Largura do item.
    int indice;				//Indice original da peca.
};

int central(vector<registro> item, int barra_padrao, int num_itens_const, clock_t t0_GRASP,
    string N_instancia, string repeticao_instancia, string& M, string& R,
    clock_t& tempo_best_sol, int& best_sol, double& alfa_sol, vector <vector<int> >& MS);

string Const_GRASP
(int num_itens_const
	, registro peca_const[]
	, int barra_padrao
	, string N_instancia,
	clock_t t0_GRASP, vector<vector<int> >& MS_aux, double alfa, int& const_sol, int& qtd_padroes_const,
	int iteracao, int& perda_total_const, clock_t& tempo_const)
	;

string melhoria_bl(int num_itens_bl, registro peca_bl[], int barra_padrao, int num_barra_bl, int const_sol,
	vector<vector<int> >& MS, int& qtd_padroes_const, int& local_sol, int num_itens_const,
	int& qtd_padroes_bl, int& perda_total_bl, clock_t t0_GRASP, clock_t& tempo_melh);

int maxpeca(registro peca[], int num_itens, double barra_aux, vector<int> demanda_aux);

int minpeca(registro peca[], int num_itens, vector<int> demanda_aux);

int lir(registro peca[], double ALFA, int n, int iBETA, vector<int> demanda_aux);
