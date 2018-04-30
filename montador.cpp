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
map <string, int> table; //Tabela de rotulos
map <string, int>::iterator it;
int ILC=0, elements=0, address=0;

vector<string> memoria; //vetor que possui todas as instruções .hex

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
    string line, token, traducao;
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
        else if(token[0]=='_' && n>1){


           /* ifstream file2;
            string line2, token2, num_bytes, endereco;
            size_t pos2;
            int n2=0;
            file2.open(f_name);
            for(int i=0; i<=table[token.substr(token.find('_'),token.find(':'))]; i++) getline(file2, line2);
            while (pos2!=EOF) {
                pos2 = line2.find(' ');
                if(pos2==-1)  pos2 = line2.find(EOF);
                token2 = line2.substr(0, pos2);
                line2.erase(0, pos2 + 1);
                if(token2.length()) n2++;
                if(n2==3) num_bytes=token2;
                if(n2==4) endereco=token2;

            }
            cout << num_bytes << ' ' << endereco << endl;
            file2.close();*/
        }
        //codigo de maquina das instruções
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
        //concatena o codigo das instruções com dos operandos registradores
        else if(token=="A0") traducao+=A0;
        else if(token=="A1") traducao+=A1;
        else if(token=="A2") traducao+=A2;
        else if(token=="A3") traducao+=A3;
        //else posição de memoria direta
    }

    string temp = decimalToHex(address);
    string result;

    //Adiciona '0s' a esquerda para completar 4 caracteres
    while(result.length()<4-temp.length()) result+='0';

    result+=temp;

    //Imprime o resultado
    if(traducao.length()<8) {
        while(traducao.length()<8) traducao+='0';
        string toCheck = ":01" + result + "00" + GetHexFromBin(traducao);
        memoria.push_back(toCheck+checkSum(toCheck));
        address++;

        temp = decimalToHex(address);
        result="";
        while(result.length()<4-temp.length()) result+='0';
        result+=temp;
        toCheck = ":01" + result + "0000";
        memoria.push_back(toCheck+checkSum(toCheck));
        address++;
    }
    else if(traducao.length()>8) {
        string toCheck = ":01" + result + "00" + GetHexFromBin(traducao.substr(0,8));
        memoria.push_back(toCheck+checkSum(toCheck));
        address++;

        temp = decimalToHex(address);
        result="";
        while(result.length()<4-temp.length()) result+='0';
        result+=temp;
        while(traducao.length()<16) traducao+='0';
        toCheck = ":01" + result + "00" + GetHexFromBin(traducao.substr(8,16));
        memoria.push_back(toCheck+checkSum(toCheck));
        address++;
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

    //Imptime tabela de rotulos
   /* for(it=table.begin(); it!=table.end(); it++)
        cout << it->first << ' ' << "ILC: " << it->second << endl;*/

    //Imprime memoria
    //for(int i=0; i<memoria.size(); i++) cout << memoria[i] <<endl;
}
