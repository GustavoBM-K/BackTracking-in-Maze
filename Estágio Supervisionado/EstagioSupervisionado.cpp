#include <iostream>
#include "EstagioSupervisionado.h"
using namespace std;
//tem que ter um delete no pop
Pia_Di::Pia_Di(){
    //pré-condição: nenhuma
    //pós-condição: Pilha é criada e iniciada como vazia
    top = NULL;
};
Pia_Di::~Pia_Di(){
    //pré-condição: Pilha já tenha sido criada
    //pós-condição: Pilha é destruída
    int entrada1, entrada2;
    while(vazio() != true){
        pop(entrada1, entrada2);
    }
}
bool Pia_Di::vazio(){
    //pré-condição: Pilha já tenha sido criada
    //pós-condição: função retorna true se a pilha está vazia, false caso contrário
    if(top == NULL){
        return true;
    }
    else{
        return false;
    }


}
bool Pia_Di::cheio(){
    //pré-condição: Pilha já tenha sido criada
    //pós-condição: função retorna true se a pilha está cheia, false caso contrário
    return false;

}

void Pia_Di::push(int x, int y){
    //pré-condição: Pilha já tenha sido criada e não está cheia
    //pós-condição: Os itens x e y são armazenados no topo da pilha
    prox_pont p; 
    p = new StackNode;
    if(p == NULL){
        cout << "Pilha cheia." << endl;
        abort();
        
    }
    else{
        p->x = x;
        p->y = y;
        p->prox_endereco = top;
        top = p;
    }



};
void Pia_Di::pop(int &x, int &y){
    //pré-condição: Pilha já tenha sido criada e não está vazia
    //pós-condição: O item no topo da pilha é removido e seu valor é retornado nas variáveis x e y.
    if(vazio() == true){
        cout << "A pilha esta vazia, nao existe valores para serem retirados." << endl;

    }
    else{
        prox_pont p;
        x = top->x;
        y = top->y;
        p = top;
        top = p->prox_endereco;
        delete p;
    }


}


bool Pia_Di::print(){
    //pré-condição: Pilha já ter sido criada e possuir algum valor armazenado.
    //pós-condição: Printa na tela todos os valores armazenados na pilha, começando pelo top
    if(vazio() == true){
        cout << "Nao existe nada dentro da pilha." << endl;
        return false;
    }
    prox_pont p;
    p = top;    
    int i;
    for(i = 0; p != NULL; i++){
        cout << "(" << p->x << " " << p->y << ")" << "  ";
        p = p->prox_endereco;

    }
    return true;
}

