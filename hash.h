//#define A 54059 /* a prime */
//#define B 76963 /* another prime */
//#define C 86969 /* yet another prime */
#include <iostream>
#include <vector>
#include <cstring>
#include <utility>
using namespace std;
namespace FunctionsTypeNames { enum FunctionsTypes {NOTYPE,DECLARATION,RETURN,PREPROCESSOR,IF,LOOP,SWITCH,TRY,NAMESPACE,INPUT,OUTPUT,FORMATTEDIO,UNFORMATTEDIO,CLASS,FILETYPE,STRUCT};}
using namespace FunctionsTypeNames;

#define  HTABLESIZE		600


class hash{
public:
	vector<pair <string,FunctionsTypes> > hasharray;
	hash();
	void insert(string str, FunctionsTypes function_of_that_str);
	FunctionsTypes giveHandler(string str);
	void replaceFunctionsType(string str, FunctionsTypes function_of_that_str);
	void remove(string str);
};

/*int hash_str(const char* s)
{	
   //unsigned h = 31 /* also prime ;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h % (C%HTABLESIZE);//h/10000; // or return h % C;
}*/

int hash_str(const string & s)
{
    double hashval = 0;
    int i = s.length();
    double weight = 1.0;
    while (i > 0)
    {
        hashval +=  weight * s[--i];
        weight *= 1.5;
    }       
    return (int) hashval % HTABLESIZE;
}

void hash::replaceFunctionsType(string str, FunctionsTypes function_of_that_str)
{
	int hashvalue = hash_str(str);	
	while(hasharray[hashvalue].first != str) {hashvalue++;}
	hasharray[hashvalue].second = function_of_that_str;
}

void hash::insert(string str, FunctionsTypes function_of_that_str)
{
	int hashvalue = hash_str(str);
	while(hasharray[hashvalue].second != 0) 
	{
		if(hashvalue == HTABLESIZE -1)
		hashvalue = 0;
		else
		hashvalue++;
	}
	hasharray[hashvalue] = make_pair(str,function_of_that_str);
}



FunctionsTypes hash::giveHandler(string str)
{
	int hashvalue = hash_str(str);	
	bool flag =0;
	while(hasharray[hashvalue].first != str) 
	{
		if(hashvalue == HTABLESIZE -1 && flag == 0)
		{
			hashvalue = 0;
			flag = 1;
		}
		else if(hashvalue == HTABLESIZE -1 && flag == 1)
			return NOTYPE;
		else
			hashvalue++;
	}
	return hasharray[hashvalue].second;
}

hash::hash()
{
	hasharray.resize(HTABLESIZE);
	
	for(int i=0; i<HTABLESIZE; i++)
	{
		hasharray[i] = make_pair ("no",NOTYPE);
	}
	insert("short" , DECLARATION);
	insert("string" , DECLARATION);
	insert("return" ,RETURN);
	insert("FILE" ,DECLARATION);
	insert("struct" , STRUCT);
	insert("friend" ,DECLARATION);
	insert("fclose" ,FILETYPE);
	insert("clearerr" ,FILETYPE);
	insert("fflush" ,FILETYPE);
	insert("fputc" ,FILETYPE);
	insert("gets" ,FILETYPE);
	insert("perror" ,FILETYPE);
	insert("fputs" ,FILETYPE);
	insert("vsscanf" ,FILETYPE);
	insert("vsnprintf" ,FILETYPE);
	insert("vsprintf" ,FILETYPE);
	insert("vprintf" ,FILETYPE);
	insert("vscanf" ,FILETYPE);
	insert("vfprintf" ,FILETYPE);
	insert("vfscan" ,FILETYPE);
	insert("ungetc" ,FILETYPE);
	insert("tmpnam" ,FILETYPE);
	insert("rewind" ,FILETYPE);
	insert("setbuf" ,FILETYPE);
	insert("setvbuf" ,FILETYPE);
	insert("snprintf" ,FILETYPE);
	insert("sprintf" ,FILETYPE);
	insert("sscanf" ,FILETYPE);
	insert("freopen" ,FILETYPE);
	insert("fseek" ,FILETYPE);
	insert("fgetpos" ,FILETYPE);
	insert("fwrite" ,FILETYPE);
	insert("cin" ,UNFORMATTEDIO);
	insert("scanf" ,FORMATTEDIO);
	insert("fscanf" ,FORMATTEDIO);
	insert("printf" ,FORMATTEDIO);
	insert("fprintf" ,FORMATTEDIO);
	insert("getline" ,UNFORMATTEDIO);
	insert("fgetc" ,UNFORMATTEDIO);
	insert("fgets" ,UNFORMATTEDIO);
	insert("stdin" ,UNFORMATTEDIO);
	insert("stdout" ,UNFORMATTEDIO);
	insert("putchar" ,UNFORMATTEDIO);
	insert("getchar" ,UNFORMATTEDIO);
	insert("getc" ,UNFORMATTEDIO);
	insert("char" ,DECLARATION);
	insert("putc" ,UNFORMATTEDIO);
	insert("getch" ,UNFORMATTEDIO);
	insert("putch" ,UNFORMATTEDIO);
	insert("getche" ,UNFORMATTEDIO);
	insert("cout" ,UNFORMATTEDIO);
	insert("using" ,NAMESPACE);
	insert("if" ,IF);
	insert("void" ,DECLARATION);
	insert("switch" ,SWITCH);
	insert("#include" ,PREPROCESSOR);
	insert("#" ,PREPROCESSOR);
	insert("for",LOOP);
	insert("while",LOOP);
	insert("do",LOOP);
	insert("signed", DECLARATION);
	insert("unsigned",DECLARATION);
	insert("int" , DECLARATION);
	insert("long",DECLARATION);
	insert("float",DECLARATION);
	insert("double",DECLARATION);
	insert("class",CLASS);
}
