#include <bits/stdc++.h>

#define INS_SIZE 16

#define A0 00
#define A1 01
#define A2 10
#define A3 11

#define 00000 STOP
#define 00001 LOAD
#define 00010 STORE
#define 00011 READ
#define 00100 WRITE
#define 00101 ADD
#define 00110 SUBTRACT
#define 00111 MULTIPLY
#define 01000 DIVIDE
#define 01001 JUMP
#define 01010 JMPZ
#define 01011 JMPN
#define 01100 MOVE
#define 01101 PUSH
#define 01110 POP
#define 01111 CALL
#define 1000000000000000 RETURN
#define 10001 LOAD_S
#define 10010 STORE_S
#define 10011 LOADC
#define 10100 LOADI
#define 10101 STOREI
#define 10110 COPYTOP

using namespace std;

ifstream file;
map <string, int> table;
map <string, int>::iterator it;
int ILC=0, elements=0;

bool pass_one(){
    string line;

    if(!getline(file, line)) return false;

    for(int i=0; i<line.length(); i++) {
        if(line[i]=='_'){ //Label
            string line_sub=line.substr(line.find('_'),line.find(':'));
            table.insert(make_pair(line_sub, ILC));
            i+=line_sub.length();
        }

        else if(line[i]==';') break;


        /*Partindo do pressuposto de que não haverão erros no arquivo de entrada então este if deve funcionar para reconhecer os comandos*/
        else if(line[i]>=97 && line[i]<=122){
            elements++;
            break;
        }
    }

    if(elements){
        elements=0;
        ILC+=INS_SIZE;
    }

    return true;
}

int pass_two(){

    return false;
}

int main(int argc, char *argv[]){
    file.open(argv[1]);

    while(pass_one());
    file.close();
    file.open(argv[1]);
    while(pass_two);

    for(it=table.begin(); it!=table.end(); it++)
        cout << it->first << ' ' << it->second << endl;
}
