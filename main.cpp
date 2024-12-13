#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>   
#include <algorithm>
using namespace std;

int main(); // prototipação da função

struct tarefa { // struct com as propriedades da tarefa
    
    string nomeTarefa;
    string codTarefa;
    string statusTarefa;
    string prioriTarefa;
    string descricaoTarefa;
    string dataDeCriacao;

};


void menu() //interface de opções para o usuário
{

    cout << "1 - Verificar Lista de Tarefas" << endl;
    cout << "2 - Adicionar Tarefa" << endl;
    cout << "3 - Buscar Tarefa (código)" << endl;
    cout << "4 - Editar Tarefa" << endl;
    cout << "5 - Excluir Tarefa" << endl;
    cout << "0 - Sair" << endl;

}

void Enter() //espera o input de "enter" do usuário e retorna a função main() e consequentemente ao menu
{
    cout << "Aperte enter para continuar";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(cin.get() == '\n')
    {
        main();
    }

}

void ordenarTarefas() //organiza as tarefas em ordem alfabética e consequentemente por prioridades, armazenando todas as linhas do arquivo principal em um vetor, que é ordenado, e depois e armazenado em outro arquivo (por meio de um for) que muda de nome e se torna o principal
{
    ofstream arquivoAux("minhasTarefasAux1.txt", ios::out);

    if (!arquivoAux.is_open()) {  //verifica se o arquivo foi aberto adequadamente, caso constrário fornece uma mensagem de erro
        throw runtime_error("Erro ao abrir arquivo!");
    }

    try{ //faz o procedimento descrito no comentário da função
        int cont = 0;

        const char* nomeAtual = "minhasTarefasAux1.txt";
        const char* novoNome = "minhasTarefas1.txt";

        ifstream arquivo("minhasTarefas1.txt");
        string linha;

        vector<string> linhas;

        while(getline(arquivo, linha))
        {      
            linhas.push_back(linha);
            cont += 1;
        }

        sort(linhas.begin(), linhas.end());

        for (int i = 0; i < cont; i++)
        {
            arquivoAux << linhas[i] << endl;
        }

        remove("minhasTarefas1.txt");
        rename(nomeAtual, novoNome);
    } catch (const exception& e) //caso algum erro com o arquivo ocorra, retorna a mensagem fornecida pelo throw e fecha o arquivo caso esteja aberto
    {
        cout << "Erro: " << e.what() << endl;
        if (arquivoAux.is_open()) {
            arquivoAux.close();
        }
    }
    
}    

void verificarTarefas(){ //mostra as tarefas escritas anteriormente pelo usuário, utilizando a estrutura de repetição while e a função cout para escrever as linhas do arquivo no terminal
    
    ifstream arquivo("minhasTarefas1.txt");
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir arquivo!");
    }
    
    string linha;
    try 
    {
        while (getline(arquivo, linha))
        {
            cout << linha << endl;
        }

        Enter();
    } 
    catch (const exception& e)
    {
        cout << "Erro: " << e.what() << endl;
        if (arquivo.is_open()) {
            arquivo.close();
        }
    }

}

void adicionarTarefa() //cadastro de tarefas é feito a partir da interação do programa com o usuário. Suas respostas são gravadas diretamente no arquivo, após isso chama-se a função ordenar lista, para manter a organização da lista de tarefas
{
    ofstream arquivo("minhasTarefas1.txt", ios::app);

    if (!arquivo.is_open())
    {
        throw runtime_error("Erro ao abrir arquivo!");
    }

    try
    { 
        int opStatus;
        int opPriori;

        tarefa novaTarefa;

        cout << "Insira o nome da tarefa: " << endl;
        cin >> novaTarefa.nomeTarefa;

        cout << "Insira o código da tarefa: " << endl;
        cin >> novaTarefa.codTarefa;

        cout << "Status da tarefa: " << endl;
        cout << "1 - Fazer| 2 - Fazendo | 3 - Completa" << endl;

        cout << "Indique o status da tarefa: ";
        cin >> opStatus;

        if (opStatus > 3 or opStatus < 1)
        {
            cout << "Número Inválido! Tente novamente" << endl;
            cin >> opStatus;
        }
        if (opStatus == 1)
        {
            novaTarefa.statusTarefa = "Fazer";
        }
        else if (opStatus == 2)
        {
            novaTarefa.statusTarefa = "Fazendo";
        }
        else if (opStatus == 3)
        {
            novaTarefa.statusTarefa = "Completa";
        }

        cout << "Indique a prioridade da tarefa: " << endl;

        cout << "1 - Muito importante | 2 - Importante | 3 - Adiável" << endl;
        cin >> opPriori;

        if (opPriori > 3 or opPriori < 1)
        {
            cout << "Opção inválida! Tente Novamente:";
            cin >> opPriori;
        }
        if (opPriori == 1)
        {
            novaTarefa.prioriTarefa = "Muito importante";
        }
        else if (opPriori == 2)
        {
            novaTarefa.prioriTarefa = "Importante";
        }
        else if (opPriori == 3)
        {
            novaTarefa.prioriTarefa = "Adiável";
        }

        cout << "Descreva a tarefa: " << endl;
        cin >> novaTarefa.descricaoTarefa;

        cout << "Data de Criação: " << endl;
        cin >> novaTarefa.dataDeCriacao;
        
        arquivo << novaTarefa.prioriTarefa << "|";
        arquivo << novaTarefa.codTarefa << "|" ;
        arquivo << novaTarefa.nomeTarefa << "|";
        arquivo << novaTarefa.statusTarefa << "|" ;
        arquivo << novaTarefa.descricaoTarefa << "|";
        arquivo << novaTarefa.dataDeCriacao << "|"  << endl;

        ordenarTarefas();
        Enter();
    }
    catch (const exception& e)
    {
        cout << "Erro: " << e.what() << endl;
        if (arquivo.is_open()) {
            arquivo.close();
        }
    }
    

}

void exibirTarefa() //função responsável por exibir uma tarefa a partir do identificador da mesma. Para isso foi necessário criar substrings a partir dos marcadores "|", identificando o intervalo correto é possivel guardar o valor específico do código, comparando com o input do usuário, e se for igual a tarefa é exibida
{

    string code;

    cout << "Insira o código da tarefa que quer exibir: " << endl;
    cin >> code;

    ifstream arquivo("minhasTarefas1.txt");
    if (!arquivo.is_open())
    {
        throw runtime_error("Erro ao abrir arquivo!");
    }

    string linha;
    try
    {
        while(getline(arquivo, linha))
        {
            size_t posCod1 = linha.find("|");
            size_t posCod2 = linha.find("|", posCod1 + 1); //identifica o primeiro marcador "|" e o segundo "|", o código da tarefa estará nesse intervalo

            string codigo = linha.substr(posCod1 + 1, posCod2 - posCod1 - 1); //quarda o valor no intevalo entre as duas "|", que corresponde ao código

            if (codigo == code)
            {
                cout << linha << endl;
            }
        }

        Enter();
    }
    catch (const exception& e)
    {
        cout << "Erro: " << e.what() << endl;
        if (arquivo.is_open()) {
            arquivo.close();
        }
    }
    
}

void excluirTarefa() //a tarefa é excluida a partir do código, o procedimento para encontrar e comparar o código é o mesmo da função de exibirTarefa() e para alterar o arquivo o procedimento é o mesmo de ordenar, porém se o código for igual ao input do usuário, a tarefa não é gravada novamente
{
    ofstream arquivoAux("minhasTarefasAux1.txt", ios::out);
    if (!arquivoAux.is_open())
    {
        throw runtime_error("Erro ao abrir arquivo!");
    }
    string code;

    const char* nomeAtual = "minhasTarefasAux1.txt";
    const char* novoNome = "minhasTarefas1.txt";

    try
    {
        cout << "Insira o código da tarefa que deseja excluir: " << endl;
        cin >> code;

        ifstream arquivo("minhasTarefas1.txt");
        if (!arquivo.is_open())
        {
            throw runtime_error("Erro ao abrir arquivo!");
        }

        try
        {
            string linha;

            while(getline(arquivo, linha))
            {
                size_t posCod1 = linha.find("|");
                size_t posCod2 = linha.find("|", posCod1 + 1);

                string codigo = linha.substr(posCod1 + 1, posCod2 - posCod1 - 1);

                if(codigo != code)
                {
                    arquivoAux << linha << endl;
                }
            }
        
            remove("minhasTarefas1.txt");
            rename(nomeAtual, novoNome);

            Enter();
        }
        catch (const exception& e)
    {
        cout << "Erro: " << e.what() << endl;
        if (arquivo.is_open()) {
            arquivo.close();
        }
    }
        
        
    }
    catch (const exception& e)
    {
        cout << "Erro: " << e.what() << endl;
        if (arquivoAux.is_open()) {
            arquivoAux.close();
        }
    }
    
}

void editarTarefa() //para editar a tarefa é feito o mesmo procedimento anterior, porém o usuário não apenas apaga a tarefa antiga, mas cria uma nova logo depois usando o mesmo procedimento de adcionarTarefa() gravando as propriedades no arquivo auxiliar, e reordenando a lista com a função ordenarTarefas()
{
    ofstream arquivoAux("minhasTarefasAux1.txt", ios::out);
    if (!arquivoAux.is_open())
    {
        throw runtime_error("Erro ao abrir arquivo!");
    }

    try
    {
        string code;
    
        const char* nomeAtual = "minhasTarefasAux1.txt";
        const char* novoNome = "minhasTarefas.txt";

        cout << "Insira o código da tarefa que quer editar: " << endl;
        cin >> code;

        ifstream arquivo("minhasTarefas1.txt");
        if (!arquivoAux.is_open())
        {
            throw runtime_error("Erro ao abrir arquivo!");
        }

        try 
        {
            string linha;
            while(getline(arquivo, linha))
            {
                size_t posCod1 = linha.find("|");
                size_t posCod2 = linha.find("|", posCod1 + 1);

                string codigo = linha.substr(posCod1 + 1, posCod2 - posCod1 - 1);

                if (codigo != code)
                {
                    arquivoAux << linha << endl;
                } 

                if (codigo == code)
                {
                    int opStatus;
                    int opPriori;

                    tarefa novaTarefa;

                    cout << "Insira o nome da tarefa: " << endl;
                    cin >> novaTarefa.nomeTarefa;

                    cout << "Insira o código da tarefa: " << endl;
                    cin >> novaTarefa.codTarefa;

                    cout << "Status da tarefa: " << endl;
                    cout << "1 - Fazer | 2 - Fazendo | 3 - Completa" << endl;
                    cout << "Indique o status da tarefa: ";
                    cin >> opStatus;

                    if (opStatus > 3 or opStatus < 1)
                    {
                        cout << "Número Inválido! Tente novamente" << endl;
                        cin >> opStatus;
                    }
                    if (opStatus == 1)
                    {
                        novaTarefa.statusTarefa = "Fazer";
                    }
                    else if (opStatus == 2)
                    {
                        novaTarefa.statusTarefa = "Fazendo";
                    }
                    else if (opStatus == 3)
                    {
                        novaTarefa.statusTarefa = "Completa";
                    }

                    cout << "Indique a prioridade da tarefa: " << endl;

                    cout << "1 - Muito importante | 2 - Importante | 3 - Adiável" << endl;
                    cin >> opPriori;

                    if (opPriori > 3 or opPriori < 1)
                    {
                        cout << "Opção inválida! Tente Novamente:";
                        cin >> opPriori;
                    }
                    if (opPriori == 1)
                    {
                        novaTarefa.prioriTarefa = "Muito importante";
                    }
                    else if (opPriori == 2)
                    {
                        novaTarefa.prioriTarefa = "Importante";
                    }
                    else if (opPriori == 3)
                    {
                        novaTarefa.prioriTarefa = "Adiável";
                    }

                    cout << "Descreva a tarefa: " << endl;
                    cin >> novaTarefa.descricaoTarefa;

                    cout << "Data de Criação: " << endl;
                    cin >> novaTarefa.dataDeCriacao;

                    arquivoAux << novaTarefa.prioriTarefa << "|";
                    arquivoAux << novaTarefa.codTarefa << "|" ;
                    arquivoAux << novaTarefa.nomeTarefa << "|";
                    arquivoAux << novaTarefa.statusTarefa << "|" ;
                    arquivoAux << novaTarefa.descricaoTarefa << "|";
                    arquivoAux << novaTarefa.dataDeCriacao << "|"  << endl;
                }
            }
            remove("minhasTarefas1.txt");
            rename(nomeAtual, novoNome);

            ordenarTarefas();
            Enter();
            }
            catch (const exception& e)
        {
            cout << "Erro: " << e.what() << endl;
            if (arquivoAux.is_open()) 
            {
                arquivoAux.close();
            }
        }
            
        
    }
    catch (const exception& e)
    {
        cout << "Erro: " << e.what() << endl;
        if (arquivoAux.is_open()) {
            arquivoAux.close();
        }
    }
}


int main() //função main() funciona como gerenciador das funções a partir de um switch
{

    int opcao;

    menu();

    cin >> opcao;

    switch(opcao) {
        case 1:
            verificarTarefas();
            break;
        case 2:
            adicionarTarefa();
            break;
        case 3:
            exibirTarefa();
            break;
        case 4:
            editarTarefa();
            break;
        case 5:
            excluirTarefa();
            break;
        case 0:
            cout << "Encerrando programa..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
    }
} 