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
#define JUMP "01001000"
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
map <string, int> table; //Tabela de rotulos
map <string, int>::iterator it;
int ILC=0, elements=0, address=0;

vector<string> memoria; //vetor que possui todas as instruções .hex
vector<string> instrucao; //vetor para manipular instrucao

char* f_name;

//Transforma string hexadecimal em decimal
int hexToDecimal(string hexa)
{
    int x;
    stringstream ss;
    ss << hex << hexa;
    ss >> x;

    return x;
}

//Transforma decimal string hexadecimal
string decimalToHex(int decimal)
{
    stringstream sstream;
    sstream << hex << decimal;
    string temp = sstream.str();
    return temp;
}

//Realiza CheckSum
string checkSum(string toCheck){
    int result=0;
    for(int i=1; i<11; i+=2){
        result+=hexToDecimal(toCheck.substr(i, 2));
    }
    return decimalToHex(256-result);
}

//Transforma string binaria em hexadecimal
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

string DecToBin(int number)
{
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return DecToBin(number / 2) + "0";
    else
        return DecToBin(number / 2) + "1";
}

void criaHex(string traducao, string posicao){
    string toCheck = ":01" + posicao + "00" + GetHexFromBin(traducao);
    memoria.push_back(toCheck+checkSum(toCheck));
    address++;
}

string formataIncrementaAddress(){
    string temp = decimalToHex(address);
    string result="";
    while(result.length()<4-temp.length()) result+='0';
    result+=temp;
    address++;
    return result;
}

//Realiza a primeira passada
bool pass_one(){
    string line;

    if(!getline(file, line)) return false; //Le a linha

    for(int i=0; i<line.length(); i++) {
        if(line[i]=='_'){ //Label
            string line_sub=line.substr(line.find('_'),line.find(':')); //Remove '_' e ':'
            table.insert(make_pair(line_sub, ILC)); //adiciona na tabela hash
            i+=line_sub.length();
        }

        else if(line[i]==';') break; //Se for um commentario pare


        /*Partindo do pressuposto de que não haverão erros no arquivo de entrada então este if deve funcionar para reconhecer os comandos*/
        else if(line[i]>=97 && line[i]<=122){ //Caso encontre algum caracter de a-z
            elements++; //Encontro uma instrução
            break;
        }
    }

    if(elements){ //Caso tenha encontrado uma instrução
        elements=0; //Faça a variavel Falsa
        ILC+=2; //Incremente o intruction location counter
    }

    return true;
}

//Realiza a segunda passada
int pass_two(){
    string line, token;
    size_t pos=0;
    int n=0;

    if(!getline(file, line)) {
        while(address<128) { // Imprimi os hex que estão faltando
            stringstream sstream;
            sstream << hex << address;
            string temp = sstream.str();
            string result;

            while(result.length()<4-temp.length()) result+='0';
            result+=temp;
            string toCheck = ":01" + result + "0000";
            memoria.push_back(toCheck+checkSum(toCheck));
            address++;
        }
        //cout << ":00000001FF" << endl; //Imprimi end of file
        memoria.push_back(":00000001FF");
        return false;
    }

    while (pos != EOF) { //Enquanto não chegou no fim da linha
        pos = line.find(' '); //separa as palavras aonde tem espaço ' '
        if(pos==-1)  pos = line.find(EOF); //Se não encontra mais espaço procure o fim da linha
        n++;
        token = line.substr(0, pos); //Pega uma palavra da linha
        line.erase(0, pos + 1); //Apaga a palavra pra continuar iterando


        //Realiza Desvio e pega os valores do .data (num_bytes e endereço)
        if(token[0]=='_' && n==1) continue;
        //Concatena com desvio
        else if(token[0]=='_' && n>1) instrucao.push_back(DecToBin(table[token]));
        //numero direto
        else if(token[0]>=48 && token[0]<57) instrucao.push_back(DecToBin(atoi(token.c_str())));
        //codigo de maquina das instruções
        else if(!token.compare("stop")) instrucao.push_back(STOP);
        else if(!token.compare("load")) instrucao.push_back(LOAD);
        else if(!token.compare("store")) instrucao.push_back(STORE);
        else if(!token.compare("read")) instrucao.push_back(READ);
        else if(!token.compare("write")) instrucao.push_back(WRITE);
        else if(!token.compare("add")) instrucao.push_back(ADD);
        else if(!token.compare("subtract")) instrucao.push_back(SUBTRACT);
        else if(!token.compare("multiply")) instrucao.push_back(MULTIPLY);
        else if(!token.compare("divide")) instrucao.push_back(DIVIDE);
        else if(!token.compare("jump")) instrucao.push_back(JUMP);
        else if(!token.compare("jmpz")) instrucao.push_back(JMPZ);
        else if(!token.compare("jmpn")) instrucao.push_back(JMPN);
        else if(!token.compare("move")) instrucao.push_back(MOVE);
        else if(!token.compare("push")) instrucao.push_back(PUSH);
        else if(!token.compare("pop")) instrucao.push_back(POP);
        else if(!token.compare("call")) instrucao.push_back(CALL);
        else if(!token.compare("return")) instrucao.push_back(RETURN);
        else if(!token.compare("load_s")) instrucao.push_back(LOAD_S);
        else if(!token.compare("store_s")) instrucao.push_back(STORE_S);
        else if(!token.compare("loadc")) instrucao.push_back(LOADC);
        else if(!token.compare("loadi")) instrucao.push_back(LOADI);
        else if(!token.compare("storei")) instrucao.push_back(STOREI);
        else if(!token.compare("copytop")) instrucao.push_back(COPYTOP);
        //concatena o codigo das instruções com dos operandos registradores
        else if(!token.compare("A0")) instrucao.push_back(A0);
        else if(!token.compare("A1")) instrucao.push_back(A1);
        else if(!token.compare("A2")) instrucao.push_back(A2);
        else if(!token.compare("A3")) instrucao.push_back(A3);
    }

    string result, traducao, traducao_2;

    cout <<"t:"<< instrucao[0] << endl;

    //Monta instrução
    if(instrucao[0]==STOP) {
        result=formataIncrementaAddress();

        traducao="00000000";
        criaHex(traducao, result);


        result=formataIncrementaAddress();

        traducao_2="00000000";
        criaHex(traducao_2, result);
    }
   // else if(instrucao[0].compare("load")) instrucao.push_back(LOAD);
    //else if(instrucao[0].compare("store")) instrucao.push_back(STORE);
    if(!instrucao[0].compare(READ)) {
        result=formataIncrementaAddress();

        traducao=instrucao[0]+"000";
        criaHex(traducao, result);

        result=formataIncrementaAddress();

        traducao_2="000000"+instrucao[1];
        criaHex(traducao_2, result);
    }
    //else if(instrucao[0].compare("write")) instrucao.push_back(WRITE);
    else if(!instrucao[0].compare(ADD)){
        result=formataIncrementaAddress();

        traducao=instrucao[0]+instrucao[1]+"0";
        criaHex(traducao, result);

        result=formataIncrementaAddress();

        traducao_2="000000"+instrucao[2];
        criaHex(traducao_2, result);
    }
    //else if(instrucao[0].compare("subtract")) instrucao.push_back(SUBTRACT);
    //else if(instrucao[0].compare("multiply")) instrucao.push_back(MULTIPLY);
    //else if(instrucao[0].compare("divide")) instrucao.push_back(DIVIDE);
    else if(!instrucao[0].compare(JUMP)) {
        result=formataIncrementaAddress();

        traducao=instrucao[0]+"000";
        criaHex(traducao, result);

        result=formataIncrementaAddress();

        //if(instrucao[1]!="A0" && instrucao[1]!="A1" && instrucao[1]!="A2" && instrucao[1]!="A3") traducao_2="000000"+DecToBin(atoi(instrucao[1].c_str()));

        traducao_2.clear();
        while(traducao_2.length()+instrucao[1].length()<8) traducao_2+="0";
        traducao_2+=instrucao[1];
        criaHex(traducao_2, result);
    }
    //else if(instrucao[0].compare("jmpz")) instrucao.push_back(JMPZ);
    //else if(instrucao[0].compare("jmpn")) instrucao.push_back(JMPN);
    else if(!instrucao[0].compare(MOVE)) {
        result=formataIncrementaAddress();

        traducao=instrucao[0]+instrucao[1]+"0";
        criaHex(traducao, result);

        result=formataIncrementaAddress();

        traducao_2="000000"+instrucao[2];
        criaHex(traducao_2, result);
    }
    /*else if(instrucao[0].compare("push")) instrucao.push_back(PUSH);
    else if(instrucao[0].compare("pop")) instrucao.push_back(POP);
    else if(instrucao[0].compare("call")) instrucao.push_back(CALL);
    else if(instrucao[0].compare("return")) instrucao.push_back(RETURN);
    else if(instrucao[0].compare("load_s")) instrucao.push_back(LOAD_S);
    else if(instrucao[0].compare("store_s")) instrucao.push_back(STORE_S);
    else if(instrucao[0].compare("loadc")) instrucao.push_back(LOADC);
    else if(instrucao[0].compare("loadi")) instrucao.push_back(LOADI);
    else if(instrucao[0].compare("storei")) instrucao.push_back(STOREI);
    else if(instrucao[0].compare("copytop")) instrucao.push_back(COPYTOP);*/

    instrucao.clear();

    return true;
}

int main(int argc, char *argv[]){
    f_name=argv[1];
    //f_name="entrada_teste.a";
    file.open(f_name);

    while(pass_one());
    file.close();
    file.open(f_name);
    while(pass_two());

    //Imptime tabela de rotulos
    /*for(it=table.begin(); it!=table.end(); it++)
        cout << it->first << ' ' << "ILC: " << it->second << endl;*/

    //Imprime memoria
    for(int i=0; i<memoria.size(); i++) cout << memoria[i] <<endl;
}
