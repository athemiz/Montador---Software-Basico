#include <bits/stdc++.h>

#define INS_SIZE 16

#define A0 "00"
#define A1 "01"
#define A2 "10"
#define A3 "11"

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

char* f_name;

string GetHexFromBin(string sBinary)
{
	string rest,tmp;

	for (int i=0;i<sBinary.length();i+=4)
	{
		tmp = sBinary.substr(i,4);
		if (!tmp.compare("0000"))
		{
			rest = rest + "0";
		}
		else if (!tmp.compare("0001"))
		{
			rest = rest + "1";
		}
		else if (!tmp.compare("0010"))
		{
			rest = rest + "2";
		}
		else if (!tmp.compare("0011"))
		{
			rest = rest + "3";
		}
		else if (!tmp.compare("0100"))
		{
			rest = rest + "4";
		}
		else if (!tmp.compare("0101"))
		{
			rest = rest + "5";
		}
		else if (!tmp.compare("0110"))
		{
			rest = rest + "6";
		}
		else if (!tmp.compare("0111"))
		{
			rest = rest + "7";
		}
		else if (!tmp.compare("1000"))
		{
			rest = rest + "8";
		}
		else if (!tmp.compare("1001"))
		{
			rest = rest + "9";
		}
		else if (!tmp.compare("1010"))
		{
			rest = rest + "A";
		}
		else if (!tmp.compare("1011"))
		{
			rest = rest + "B";
		}
		else if (!tmp.compare("1100"))
		{
			rest = rest + "C";
		}
		else if (!tmp.compare("1101"))
		{
			rest = rest + "D";
		}
		else if (!tmp.compare("1110"))
		{
			rest = rest + "E";
		}
		else if (!tmp.compare("1111"))
		{
			rest = rest + "F";
		}
		else
		{
			continue;
		}
	}
	return rest;
}

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
        ILC++;
    }

    return true;
}

int pass_two(){
    string line, token, traducao;
    size_t pos=0;
    int n=0;

    if(!getline(file, line)) return false;

    while ((pos = line.find(' ')) != -1) {
        n++;
        token = line.substr(0, pos);
        //if(token.length())cout << token << endl;
        line.erase(0, pos + 1);

        if(token[0]=='_' && n==1) continue;
        else if(token[0]=='_' && n>1){
            //ifstream file2;
            //string line2;
            //file2.open(f_name);
            //for(int i=0; i<table[token.substr(token.find('_'),token.find(':'))]; i++) getline(file2, line2);
            continue;
        }
        else if(token=="stop") traducao=STOP;
        else if(token=="load") traducao=LOAD;
        else if(token=="store") traducao=STORE;
        else if(token=="read") traducao=READ;
        else if(token=="write") traducao=WRITE;
        else if(token=="add") traducao=ADD;
        else if(token=="subtract") traducao=SUBTRACT;
        else if(token=="multiply") traducao=MULTIPLY;
        else if(token=="divide") traducao=DIVIDE;
        else if(token=="jump") traducao=JUMP;
        else if(token=="jmpz") traducao=JMPZ;
        else if(token=="jmpn") traducao=JMPN;
        else if(token=="move") traducao=MOVE;
        else if(token=="push") traducao=PUSH;
        else if(token=="pop") traducao=POP;
        else if(token=="call") traducao=CALL;
        else if(token=="return") traducao=RETURN;
        else if(token=="load_s") traducao=LOAD_S;
        else if(token=="store_s") traducao=STORE_S;
        else if(token=="loadc") traducao=LOADC;
        else if(token=="loadi") traducao=LOADI;
        else if(token=="storei") traducao=STOREI;
        else if(token=="copytop") traducao=COPYTOP;
        else if(token=="A0") traducao+=A0;
        else if(token=="A1") traducao+=A1;
        else if(token=="A2") traducao+=A2;
        else if(token=="A3") traducao+=A3;
    }

    if(traducao.length()<8) {
        while(traducao.length()<8) traducao+='0';
        cout << GetHexFromBin(traducao) << endl;
    }
    else if(traducao.length()>8) {
        cout << GetHexFromBin(traducao.substr(0,8)) << endl;
        while(traducao.length()<16) traducao+='0';
        cout << GetHexFromBin(traducao.substr(8,16)) << endl;
    }


    return true;
}

int main(int argc, char *argv[]){
    f_name=argv[1];
    file.open(f_name);


    while(pass_one());
    file.close();
    file.open(argv[1]);
    while(pass_two());

    /*for(it=table.begin(); it!=table.end(); it++)
        cout << it->first << ' ' << it->second << endl;*/
}
