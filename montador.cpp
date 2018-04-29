#include <bits/stdc++.h>

#define INS_SIZE 16

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

void pass_two(){
}

int main(int argc, char *argv[]){
    file.open(argv[1]);

    while(pass_one());

    for(it=table.begin(); it!=table.end(); it++)
        cout << it->first << ' ' << it->second << endl;
}
