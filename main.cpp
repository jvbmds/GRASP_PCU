    #include "cabecalho.h"
    
    

    int main(int argc,char** argv)
    {
        // Declaracao das variaveis

                                          
        vector<registro> item_residual; 
        vector<registro> item;              
        vector<vector<int> > MS;
        //vector<int> col;

        double alfa_sol;

        int numero_barras = 0;
        int numero_barras_total = 0;
        //int deslocamento = 0;
        int best_sol = 0;
        int tamanho_barra_padrao;
        int numero_itens_instancia;
        int status = 0;                 // status das operacoes
        //int i, j, k;                    // contadores
       
        string repeticao_instancia = argv[2];
        string nome_instancia;
        string nome_arquivo_instancia;
        string saida;
        string M;
        string R = " ";
        string estatistica_str;
        string str_excel;
        string N_saida;
        
        clock_t tempo;
        clock_t t0 = clock();
        clock_t tempo_best_sol;
        
        ifstream dados;
        ofstream teste;

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  leitura da instancia !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        nome_instancia = argv[1];
        nome_arquivo_instancia = nome_instancia + ".txt";
        N_saida = nome_instancia + "_Teste" + repeticao_instancia + ".txt";
       
        dados.open(nome_arquivo_instancia);   //abre a instancia
        if (dados.fail() == 1) {

            cout << "Nao foi possivel abrir o arquivo de instancia!!!" << endl;

            system("pause");

            return 0;
        }

        
        
        dados >> tamanho_barra_padrao >> numero_itens_instancia;

        item.resize(numero_itens_instancia);
        
        for (int i = 0; i < numero_itens_instancia; i++)
        {
            dados >> item[i].demanda >> item[i].tamanho;
            item[i].indice = i;
        }
        dados.close();//Fecha a instancia.

        
        //chamada da grasp
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

       
        status = central(item, tamanho_barra_padrao,
            numero_itens_instancia,
            t0, nome_instancia, repeticao_instancia,M,R,tempo_best_sol,best_sol,
            alfa_sol,MS);
        if (status) {
            cout << "falha na chamada do grasp";
            return 0;
        }
            numero_barras_total = numero_barras + best_sol;
            estatistica_str = N_saida + "\t";
            tempo = clock();

            estatistica_str += to_string(((double)tempo_best_sol) / CLOCKS_PER_SEC);// tempo da melhor solucao
            estatistica_str += "\t";
            estatistica_str += to_string(((double)tempo - t0) / CLOCKS_PER_SEC);//tempo total
            estatistica_str += "\t";
            estatistica_str += to_string(alfa_sol);// alfa da solucao GRASP
            estatistica_str += "\t";
            estatistica_str += to_string(numero_barras_total);
            estatistica_str += '\t' + M + '\t' + R;



            N_saida.clear();

            teste.open("estatistica.txt", ios::app);
            if (!teste.good()) {
                cout << "o arquivo de saida nao pode ser aberto." << endl;
                return 0;
            }
            teste << estatistica_str << endl;
            teste.close();

            estatistica_str.clear();


            return 0;

        }  /* END main */

    
