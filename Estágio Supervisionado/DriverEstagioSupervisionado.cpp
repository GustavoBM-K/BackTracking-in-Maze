#include <iostream>
#include <vector>
#include <fstream>
#include "EstagioSupervisionado.h"
using namespace std;
//Como posso modificar o labirinto? 1- Crie um arquivo .txt contendo o labirinto desejado. Você mesmo pode cria-lo utilizando qualquer caracter que desejar, basta modifica-lo nos defines à seguir.
//Então, após a criação do arquivo, modifique cada define que julgar necessário, sendo eles:
#define LINHA 10  //Quantidade de linhas da matriz.
#define COLUNA 10 //Quantidade de colunas da matriz. Ps: Não utilizada nesse código.
#define Comeco_X 1 //Posição inicial do programa no eixo X.
#define Comeco_Y 1  //Posição inicial do programa no eixo Y.
#define Fim_X 8    //Posição que deve ser encontrada no eixo X.
#define Fim_Y 4    //Posição que deve ser encontrada no eixo Y.
#define Caminho ' ' //Constante para quando for caminho permitido.
#define Parede '#'  //Constante para caminho não permitido, no caso, parede.
#define Marca '.'   //Constante para caminhos que já foram visitados.
#define NomeDoArquivo "labirinto.txt" //Nome do arquivo que está armazenado o labirinto.

//Struct para armazenar as cordenadas 
struct Cordenada{
    int x, y;
};
typedef struct Cordenada cord;


vector<Cordenada> Direcoes(cord posi){
    //Pré-Condição: Recebe a cordenada da posição atual.
    //Pós-Condição: Retorna todos os caminhos ao redor da posição atual.
    //Sequência original usada: direita, baixo, esquerda e cima.
    //Caso desejar, é possível modificar essa sequência alterando os valores de incremento e decremento. 
    //Vale lembrar, que por mais que as direções sejam modificadas, apenas a sequência de soluções encontradas para o labirinto seram diferentes, ou seja, ele continua com as mesmas soluções sempre.
    return {{posi.x , posi.y + 1}, {posi.x + 1, posi.y}, {posi.x, posi.y - 1}, {posi.x - 1, posi.y}};
}


void Carregando_Matriz(vector <string> &labirinto){
    //Pré-Condição: Receber um vetor/matriz de strings que será o labirinto. 
    //Pós-Condição: Carregar a matriz do arquivo .txt para o programa.
    //Caso crie um novo arquivo, não esqueça de mudar a Constante NomeDoArquivo nos defines iniciais.
    ifstream lab(NomeDoArquivo, ios::in);
    if(lab.good()){
        for(int i = 0; i < LINHA; i++){
            getline(lab, labirinto[i]);
        }
    }
    else{
        cout << "Erro ao abrir o arquivo." << endl;
        abort();
    }
}


void Printando_Matriz(vector <string> labirinto){
    //Pré-Condição: Receber um vetor/matriz de strings que será o labirinto. 
    //Pós-Condição: Printa esse labirinto na tela.
    for(int i = 0; i < LINHA; i++){
        cout << "    " << labirinto[i] << endl;
    }
}

bool Jogo(vector<string> &matriz, cord posi_player, cord final, Pia_Di &possibilidades, int cont, int &qtd_cmh){
    //Pré-Condição: Recebe uma matriz de strings, que é o nosso labirinto, a posição inicial/atual, a posição que deseja encontrar, uma ADT Pilha para armazenar as posições percorridas, e um simples contador de passos.
    //Ps: é preciso passar esse contador pela própria função por quê caso você crie uma variável dentro dela, sempre que uma nova recursão for chamada, essa variável será resetada para o valor atribuído inicialmente, o mesmo vale para o qtd_cmh.
    //Pós-Condição: Retorna todas as possibilidades de caminhos possíveis através da matriz e o caminho percorrido pelo programa, e o número de "passos" que foi dado até chegar a saída.
    int tempX, tempY;//variável apenas para armazenar os valores retirados pela função Pop da pilha.
    //Condição principal do programa, que verifica se a posição atual é igual a posição desejada.
    if(posi_player.x == final.x && posi_player.y == final.y){
        //caso for, é printado a matriz, o caminho percorrido e o número de passos.
        qtd_cmh++;
        cout << endl << "-Solucao Encontrada-" << endl;
        Printando_Matriz(matriz);
        cout << "Caminho percorrido (Final -> Inicial): ";
        possibilidades.print();
        cout << "-Numero de passos: " << cont << endl;
        
    }
    //Condição para verificar se a nova posição é um caminho possível ou se já foi visitado anteriormente.
    if(matriz[posi_player.x][posi_player.y] != Caminho || matriz[posi_player.x][posi_player.y] == Marca){
        return false;
    }
    //Caso a condição anterior esteja errada, é por que essa nova posição, é um caminho possível.
    else{
        //A posição atual é marcada como visitada, a cordenada é armazenada na pilha e o contador de passos é incrementado.
        matriz[posi_player.x][posi_player.y] = Marca;
        possibilidades.push(posi_player.x, posi_player.y);
        cont++;
        //Após isso, o programa faz um novo teste para cada 'caminho' retornado pela funcao Direcoes, da posição atual.
        for(auto caminhos : Direcoes(posi_player)){
            if(Jogo(matriz, caminhos, final, possibilidades, cont, qtd_cmh) != false){
                return true;
            }
        }
        
    }
    //Se o caminho atual não possuir mais possibilidades de direção aceitáveis, ele é retirado da pilha, o contador é decrementado e a posição volta a não ter nada. 
    possibilidades.pop(tempX, tempY);
    cont--;
    matriz[posi_player.x][posi_player.y] = ' ';

    return false; //condicao de parada, caso nao exista mais nenhuma saida possível. Essa devera ser a ULTIMA linha dessa funcao.

}

int main(){
    int contador = 0, qtd_cmh = 0;
    vector <string> labirinto(LINHA, ""); 
    Pia_Di possibilidades;
    cord ini, fim;
    ini.x = Comeco_X;
    ini.y = Comeco_Y;
    fim.x = Fim_X;
    fim.y = Fim_Y;
    Carregando_Matriz(labirinto);
    Jogo(labirinto, ini, fim, possibilidades, contador, qtd_cmh);
    cout << "======================================" << endl;
    cout << "            -FIM DO JOGO-" << endl << "Quantidade de solucoes encontradas: " << qtd_cmh << endl;
    cout << "======================================" << endl;
}