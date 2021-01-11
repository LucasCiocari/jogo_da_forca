#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

void desenha_jogo(int erros);
void descoberta_atual(const vector<bool> l_d, const string pal_at);
int comp_nova_letra(vector<bool>& l_d, const string pal_at, vector<char>& l_u, const char l_a);
void print_resultado_rodada(const int result);
void inicilizar_seed();
void nova_palavra(string& pal_at, vector<bool>& l_d);
void imprime_letras_usadas(const vector<char> l_u);
int conta_erros(int resultado, int &n_erros);
int menu_inicial();
void menu();
void jogo(int& erros, string& palavra_atual, vector<char>& letras_usadas, char& letra_atual, vector<bool>& letras_descobertas);
bool conta_acertos(vector<bool>& letras_descobertas);

int main()
{
	inicilizar_seed();
	menu();
}


void desenha_jogo(int erros)
{
switch(erros){
        case 1:
        cout << "___________________\n|      ________   |\n|    |        |   |\n|    |        |   |\n|    |       ---  |\n|    |        O   |\n|    |            |\n|    |            |\n| ___|___         |\n|_________________|\n";
            break;
        case 2:
        cout << "___________________\n|      ________   |\n|    |        |   |\n|    |        |   |\n|    |       ---  |\n|    |        O   |\n|    |        |   |\n|    |            |\n| ___|___         |\n|_________________|\n";
            break;
        case 3:
        cout << "___________________\n|      ________   |\n|    |        |   |\n|    |        |   |\n|    |       ---  |\n|    |        O   |\n|    |       /|   |\n|    |            |\n| ___|___         |\n|_________________|\n";
            break;
        case 4:
        cout << "___________________\n|      ________   |\n|    |        |   |\n|    |        |   |\n|    |       ---  |\n|    |        O   |\n|    |       /|\\  |\n|    |            |\n| ___|___         |\n|_________________|\n";
            break;
        case 5:
        cout << "___________________\n|      ________   |\n|    |        |   |\n|    |        |   |\n|    |       ---  |\n|    |        O   |\n|    |       /|\\  |\n|    |       /    |\n| ___|___         |\n|_________________|\n";
        break;
        case 6:
        cout << "___________________\n|      ________   |\n|    |        |   |\n|    |        |   |\n|    |       ---  |\n|    |        O   |\n|    |       /|\\  |\n|    |       / \\  |\n| ___|___         |\n|_________________|\n";
        break;
        default:
        cout << "___________________\n|      ________   |\n|    |        |   |\n|    |        |   |\n|    |       ---  |\n|    |            |\n|    |            |\n|    |            |\n| ___|___         |\n|_________________|\n";
        break;
    }
}

void descoberta_atual(const vector<bool> l_d, const string pal_at)
{
    string retorno = "";
    for (int i = 0; i < pal_at.size(); i++)
    {
        if(l_d[i])
        {
            retorno += pal_at[i];
        }
        else
        {
            retorno += "_ ";
        }
    }
	std::cout << retorno << endl ;
}

int comp_nova_letra (vector<bool>& l_d, const string pal_at, vector<char>& l_u, const char l_a)
{
    bool achou = false;

    for (int i = 0; i < l_u.size() && achou == false  && !l_u.empty(); i++)
    {
        if (l_a == l_u[i])
            {
                achou = true;
                return 2;
            }
    }
    if(!achou)
    {
        l_u.push_back(l_a);
        int procurar = pal_at.find(l_a);
        if(procurar == -1)
        {
            return 0;
        }
        else
        {
            for(int i = 0; i < pal_at.size(); i++)
            {
                if(pal_at[i] == l_a)
                {
                    l_d[i] = true;
                }
            }
            return 1;
        }
    }
}

void print_resultado_rodada(const int result)
{
    switch(result)
    {
        case 0: cout << "Palavra nao contem esta letra" << endl;
        break;
        case 1: cout << "Letra correta!" << endl;
        break;
        case 2: cout << "Esta letra ja foi utilizada" << endl;
        break;
        case 3: cout << "Fim de Jogo!" << endl;
        break;
    }
}

void inicilizar_seed()
{
    srand(time(NULL));
}

void nova_palavra(string& pal_at, vector<bool>& l_d)
{
    string palavra_base = "";
    ifstream dicionario;
    dicionario.open("dicionario.txt", ios::in);
    int numero_random = rand() % 29854;
    for (int i = 0; i <= numero_random; i++)
    {
        dicionario >> palavra_base;
    }
    for(int i = 0; i < palavra_base.size(); i++)
    {
        pal_at += tolower(palavra_base[i]);
    }
    for (int i = 0; i < pal_at.size(); i++)
    {
        if(isalpha(pal_at[i]))
            l_d.push_back(false);
        else
            l_d.push_back(true);
    }
}

void imprime_letras_usadas(const vector<char> l_u)
{
    cout << "Letras usadas: ";
    for(int i = 0; i < l_u.size(); i++)
    {
        cout << l_u[i] << " ";
    }
    cout << endl;
}

int conta_erros(int resultado, int &n_erros)
{
	if (resultado == 0)
	{
		n_erros += 1;
		return resultado;
	}
	else if(n_erros == 6)
        return 3;
	return resultado;
}

int menu_inicial()
{
	int opcoes;

	cout << "Bem-vindo ao jogo da forca!\n escolha a opção que deseja acessar:\n 1. Novo Jogo\n2. Sair" << endl;
	cin >> opcoes;
	if (opcoes < 1 || opcoes > 2)
		cout << "Esta opção não existe! Escolha outra por favor." << endl;
	while (opcoes < 1 || opcoes > 2)
		cin >> opcoes;


	return opcoes;
}

void menu()
{
	int erros = 0;
	string palavra_atual = "";
	vector<char> letras_usadas;
	char letra_atual;
	vector<bool> letras_descobertas;
	int opcao;
	opcao = menu_inicial();

	if (opcao == 1)
		jogo(erros, palavra_atual, letras_usadas, letra_atual, letras_descobertas);

}

void jogo(int& erros, string& palavra_atual, vector<char>& letras_usadas, char& letra_atual, vector<bool>& letras_descobertas)
{
	nova_palavra(palavra_atual, letras_descobertas);
	bool completo = false;
	while (erros < 6 && !completo)
	{
		cout << "Diga uma letra: ";
		cin >> letra_atual;

		print_resultado_rodada(conta_erros(comp_nova_letra(letras_descobertas, palavra_atual, letras_usadas, letra_atual), erros));
		imprime_letras_usadas(letras_usadas);
		descoberta_atual(letras_descobertas, palavra_atual);
		desenha_jogo(erros);
		completo = conta_acertos(letras_descobertas);
	}

	if (completo)
		print_resultado_rodada(3);

	menu();

}

bool conta_acertos(vector<bool>& letras_descobertas)
{
	bool completo = true;
	for (int i = 0; i < letras_descobertas.size() && completo == true; i++)
	{
		if (letras_descobertas[i] == false)
			completo = false;
	}
	return completo;
}


