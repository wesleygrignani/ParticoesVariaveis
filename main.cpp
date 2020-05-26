#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <conio.h>
#include <windows.h>


using namespace std;
#define TAM 1024    //Tamanho da memoria configuravel

class processo{ //classe processo
public:
    int tamanho;
    int id;
    int tempo;
};

class bloco{ //bloco de memoria
public:
    int id;
    processo p;
    int tamanho;
};

class memoria{ //memoria com um array de blocos
public:
    list<bloco> p;
    int tamanho = TAM;
};

void gotoxy(short x, short y)           //definition of gotoxy function//
{
 COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void primeiroInsert(queue<processo> &processos, memoria &memoria){

    if(memoria.p.size()==0){
    bloco block;
    block.id=1;
    block.p = processos.front();
    block.tamanho = block.p.tamanho;
    processos.pop();

    memoria.p.push_back(block);
    memoria.tamanho -= block.tamanho;

    block.id = 2;
    block.p.id=0;
    block.p.tamanho=0;
    block.p.tempo=0;
    block.tamanho=memoria.tamanho;

    memoria.p.push_back(block);
    memoria.tamanho -= block.tamanho;


    }else{
        /*
        for (auto const& i : memoria.p) {
            cout << ;
        }*/
    }


};

void firstfit(queue<processo> &processos, memoria &memoria){ //primeiro bloco com tamanho suficiente

    list<bloco>::iterator it;
    it = memoria.p.begin();

        for (auto const& i : memoria.p) {
             processo processo = processos.front();

            if(i.tamanho == processo.tamanho && i.p.id == 0){  //i.p.tamanho == 0 quando nao tiver nenhum processo no bloco

                bloco block = i;
                block.p.id = processo.id;
                block.p.tempo = processo.tempo;
                block.p.tamanho = processo.tamanho;

                it = memoria.p.erase(it);
                it = memoria.p.insert(it,block);

                processos.pop();

                break;
            }
            else if(i.tamanho > processo.tamanho && i.p.id==0){

                bloco block = i;
                block.p.id = processo.id;
                block.p.tempo = processo.tempo;
                block.p.tamanho = processo.tamanho;
                block.tamanho = processo.tamanho;

                bloco block2 = i;
                block2.p.id = 0;
                block2.p.tempo = 0;
                block2.p.tamanho = 0;

                block2.tamanho -= processo.tamanho;

                it = memoria.p.erase(it);
                it = memoria.p.insert(it,block2);
                it = memoria.p.insert(it,block);
                //memoria.p.erase(it);

                processos.pop();

                break;
            }
            it++;
        }
}

void imprimir(memoria memoria){
int tam = 1,x=0,y=0;
    for (auto const& i : memoria.p) {
        bloco aux;
        aux.p = i.p;
        aux.id = i.id;
        aux.tamanho = i.tamanho;
        if(aux.p.id == 0 ){
            gotoxy(x,y);
            cout <<"|                    BLOCO DE MEMORIA                    |";
            y++;gotoxy(x,y);
            cout <<"|--------------------------------------------------------|";
            y++;gotoxy(x,y);
            cout <<"|Memoria     Tamanho(B)        Processos";
            y++;gotoxy(x,y);
            cout <<"|Bloco "<<tam<<":       "<<aux.tamanho<<"       |Processo: VAZIO"<<" Tempo:VAZIO        LIVRE";
            y++;gotoxy(x,y);
            cout <<"|--------------------------------------------------------|";
            y++;
        }else{
        gotoxy(x,y);
        cout <<"|                    BLOCO DE MEMORIA                    |";
        y++;gotoxy(x,y);
        cout <<"|--------------------------------------------------------|";
        y++;gotoxy(x,y);
        cout <<"|Memoria     Tamanho(B)        Processos\n";
        y++;gotoxy(x,y);
        cout <<"|Bloco "<<tam<<":      "<<aux.tamanho<<"        |Processo:"<<aux.p.id<<" Tempo:"<<aux.p.tempo<<"               OCUPADO";
        y++;gotoxy(x,y);
        cout <<"|--------------------------------------------------------|";
        y++;
        }
        tam++;
    }
}

void reduzirTempo(memoria &memoria){
    list<bloco>::iterator it;
    it = memoria.p.begin();
    for (auto const& i : memoria.p) {
            bloco block = i;

            if(block.p.tempo!=0){
                block.p.tempo -= 1;
                it = memoria.p.erase(it);
                it = memoria.p.insert(it,block);

            }else{
                block.p.id = 0;
                block.p.tempo = 0;
                block.p.tamanho = 0;
                it = memoria.p.erase(it);
                it = memoria.p.insert(it,block);
            }

            it++;
    }
}

void analisarBlocos(memoria &memoria){
    list<bloco>::iterator it,it2,it3;
    it = memoria.p.begin();
    vector<int> auxiliar,tamanho;
    for (auto const& i : memoria.p) {
        if(i.p.id==0){
            auxiliar.push_back(1);
            tamanho.push_back(i.tamanho);
        }else{
            auxiliar.push_back(0);
            tamanho.push_back(0);
        }
    }

    it = memoria.p.begin();
    it2 = memoria.p.begin();
    it3 = memoria.p.begin();
    for (int a=0; a<auxiliar.size(); a++) {
        if((a+1)>auxiliar.size()){
            break;
        }
        else if(auxiliar[a] ==1 && auxiliar[a+1]==1){
            bloco block;
            block.p.id=0;
            block.p.tempo=0;
            block.tamanho = tamanho[a] + tamanho[a+1];

            it = memoria.p.erase(it);
            it = memoria.p.erase(it);
            it = memoria.p.insert(it,block);

        }
        it++;
    }
}

void imprimirProcessos(queue<processo> p){
    int x=85,y=0;
    while(p.size()!=0){
        processo t = p.front();
        gotoxy(x,y);
        cout<<"|---------Processo----------|";
        y++;
        gotoxy(x,y);
        cout<<"|Id       Tamanho      Tempo|";
        y++;
        gotoxy(x,y);
        cout<<"  "<<t.id<<"         "<<t.tamanho<<"          "<<t.tempo;
        y++;
        p.pop();
    }
};



int main()
{
    queue<processo> processos;
    processo aux;

    memoria memoria;
    list<bloco>::iterator it;

    aux.id=1;
    aux.tempo=4;
    aux.tamanho=512;
    processos.push(aux);

    aux.id=2;
    aux.tempo=4;
    aux.tamanho=800;
    processos.push(aux);

    aux.id=3;
    aux.tempo=6;
    aux.tamanho=95;
    processos.push(aux);

    aux.id=4;
    aux.tempo=10;
    aux.tamanho=35;
    processos.push(aux);

    aux.id=5;
    aux.tempo=10;
    aux.tamanho=205;
    processos.push(aux);

    aux.id=6;
    aux.tempo=20;
    aux.tamanho=300;
    processos.push(aux);

    aux.id=7;
    aux.tempo=6;
    aux.tamanho=94;
    processos.push(aux);

    aux.id=8;
    aux.tempo=6;
    aux.tamanho=290;
    processos.push(aux);

    aux.id=9;
    aux.tempo=3;
    aux.tamanho=90;
    processos.push(aux);

    primeiroInsert(processos,memoria);
    imprimir(memoria);
    Sleep(1000);

    queue<processo> t = processos;
    imprimirProcessos(t);

    while(processos.size()!=0){
        firstfit(processos,memoria);
        Sleep(1500);
        system("cls");
        imprimir(memoria);

        queue<processo> t = processos;
        imprimirProcessos(t);

        reduzirTempo(memoria);
        system("cls");
        imprimir(memoria);

        imprimirProcessos(t);

        Sleep(1000);
        system("cls");
        analisarBlocos(memoria);
        imprimir(memoria);

        imprimirProcessos(t);

    }



    return 0;
}
