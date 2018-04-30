#include <bits/stdc++.h>

#define INS_SIZE 16

#define A0 00
#define A1 01
#define A2 10
#define A3 11

#define STOP "00000"
#define LOAD "00001"
#define STORE "00010"
#define READ "00011"
#define WRITE "00100"
#define ADD "00101"
#define SUBTRACT "00110"
#define MULTIPLY "00111"
#define DIVIDE "01000"
#define JUMP "01001"
#define JMPZ "01010"
#define JMPN "01011"
#define MOVE "01100"
#define PUSH "01101"
#define POP "01110"
#define CALL "01111"
#define RETURN "1000000000000000"
#define LOAD_S "10001"
#define STORE_S "10010"
#define LOADC "10011"
#define LOADI "10100"
#define STOREI "10101"
#define COPYTOP "10110"

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
