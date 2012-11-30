// basic things without pointer 1 to 5 and multiple file
#include <iostream>
#include <cstdio>
#include <cstring>
#include<vector>
#include <utility>
#include "hash.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;
bool fileEnd=false;
FILE* fp; 
hash h;
vector <pair <int,string> > instructions;
vector<string> filerange,funcrange,classrange;
int start=0,end=0,fileStart=0;
string functionName,filename;
int ifFirst=0;

void evaluate(string word);// which takes word and identifies it's type
void functionHandler(string word);
void whileHandler(string word);
void doHandler(string word);
void forHandler(string word);

void printIns() //Prints all instructions in file
{
	int l = instructions.size(); //instructions is a vector which stores instructions
	int i =0;
	ofstream fileins;
	fileins.open ("instructions.txt");
	while(i<l)
		{
			cout<<instructions[i].first<<"@"<<instructions[i].second<<endl; 
			fileins<<instructions[i].first<<"@"<<instructions[i].second<<endl; 
			i++;
		}
	fileins.close();
}


void printfileRangeMap() // Prints filename and starting and ending index of instructions of that file
{
	ofstream filerng;
	filerng.open ("filerange.txt");
	for (int i=0;i<filerange.size(); i++ )
   {
    filerng<< filerange[i]<<endl;
    cout<<filerange[i]<<endl;
   }
   filerng.close();
}

void printrangemap() // Prints starting and ending index of instructions of each and every function after its filename
{
	ofstream filefns;
	filefns.open ("functionsrange.txt");
	for (int i=0;i<funcrange.size(); i++ )
   {
    filefns<< funcrange[i]<<endl;
    cout<<funcrange[i]<<endl;
   }
   filefns.close();
}	

void printclassrange()// Prints starting and ending index of instructions of each and every class after its filename
{
	ofstream classrng;
	classrng.open ("classrange.txt");
	for (int i=0;i<classrange.size(); i++ )
   {
    classrng<< classrange[i]<<endl;
    cout<<classrange[i]<<endl;
   }
   classrng.close();
}	


bool separator(char c)// word is read upto separator 
{
	return ((c=='*')||(c=='=')||(c==';')||(c=='+')||(c=='-')||(c=='(')||(c==')')||(c=='/')||(c=='%')||(c=='^')||(c=='&')||(c=='<')||(c=='>')||(c=='!')||(c=='}')||(c==' ')||(c=='\n')||(c=='\t')||(c=='"')||(c==',')||(c=='{')||(c==':')||(c=='.'));
}

string getWord()//reads till any separator * ,=,;,+,-,(,),/,%,^,&,>,<,! when u encounter EOF  make fileEnd true
{	
	char c;
	string word;
	c=fgetc(fp);
	
	while(1)
	{
		if(!separator(c) && c!=EOF)
		{
			word.append(1,c);		
			c=fgetc(fp);
		}
		else 
			break;
	}
	if(c==EOF )
		fileEnd=true;
	else
		word.append(1,c);
	return word;
}

void unformattedIOHandler(string word)//reads upto ';' after word
{
	char c;
	bool quotes=0;
	c= fgetc(fp);
	while(c!=';')
	{
		if(c=='"')
			quotes = !quotes;
		word.append(1,c);	
		c=fgetc(fp);	
	}
	pair <int,string> command;
	command = make_pair(9,word);
	instructions.push_back(command);
	command = make_pair(5,"a");
	instructions.push_back(command);
}

void formattedIOHandler(string word) //reads upto ';' after word
{
	char c;
	bool quotes=0;
	c= fgetc(fp);
	while((quotes==1)||(c!=';' && quotes==0))
	{
		if(c=='"')
			quotes = !quotes;
		word.append(1,c);	
		c=fgetc(fp);	
	}
	pair <int,string> command;
	command = make_pair(9,word);
	instructions.push_back(command);
	command = make_pair(5,"a");
	instructions.push_back(command);
}

void fileHandler(string word) //reads upto ';' after word
{
	char c;
	bool quotes=0;
	c= fgetc(fp);
	while((quotes==1)||(c!=';' && quotes==0))
	{
		if(c=='"')
			quotes = !quotes;
		word.append(1,c);	
		c=fgetc(fp);	
	}
	pair <int,string> command;
	command = make_pair(1,word);
	instructions.push_back(command);
	command = make_pair(5,"a");
	instructions.push_back(command);
}


void returnHandler(string word)//reads upto ';' after word
{
	char c;	
	while((c=fgetc(fp))!= ';')
		word.append(1,c);
	
	pair <int,string> command;
	command = make_pair(2,word);
	instructions.push_back(command);
}

void namespaceHandler(string word) //reads upto ';' after word
{
	char c;
	while((c=fgetc(fp)) != ';')
		word.append(1,c);
	
	pair <int,string> command;
	command = make_pair(1,word);//to draw rectanular box
	instructions.push_back(command);
	command = make_pair(5,"a");//to draw line 
	instructions.push_back(command);
}

void declarationHandler(string word) //whenever word of declarationtype encouners this function is called. it identifies whether declaration is of function or variable. if its variable declaration, it will read upto ';' else it will call function handler
{
	
	char c=word.at(word.length()-1);
	string nextword;
	short int flag =0;
	while(c==' '|| c=='\t' || c=='\n') 
		c=fgetc(fp);
	
	ungetc(c,fp);
	nextword= getWord();
	c = nextword.at(nextword.length() - 1);
	if(c == ' '|| c=='\t' || c=='\n')
	{
		while(c==' '|| c=='\t' || c=='\n') {c=fgetc(fp);}
		ungetc(c,fp);
		flag = 1;
	}
	if(c=='(' && flag==1)
		functionHandler(nextword.append(1,'('));
	else if(flag==0 && c=='(')
		functionHandler(nextword);
	
	else
	{
		if(c==';'||c==':')
		{
			if(c==':')
			{
				while((c=fgetc(fp))!='(')
				{	
					nextword.append(1,c);
					
				}
				nextword.append(1,'(');
				functionHandler(nextword);
			
			}
			else
			{
				pair <int,string> command;
				command = make_pair(1,word.append(nextword));//to draw rectangle
				instructions.push_back(command);
				command = make_pair(5,"a");//to draw line 
				instructions.push_back(command);
			}	
		}
		else
		{
		
			while((c=fgetc(fp))!=';'&&c!=':')
			{	
				nextword.append(1,c);
			}
			if(c==':')
			{
				while(c!='(')
				{	
					nextword.append(1,c);
					c=fgetc(fp);
				}
				nextword.append(1,'(');
				functionHandler(nextword);
			
			}
			else
			{
				pair <int,string> command;
				command = make_pair(1,word.append(nextword));//to draw rectangle
				instructions.push_back(command);
				command = make_pair(5,"a");//to draw line 
				instructions.push_back(command);
			}
		}
	}
}

void functionHandler(string word)//evaluates body of function
{
	char c;
	string str,definitions,str1="Input ";
	start = instructions.size();
	int brackets = 1;
	pair <int,string> command;
	while(brackets!=0)
	{
		c=fgetc(fp);
		if(c==')')
		{
			brackets--;
			if(brackets==0)
				break;
			else
				definitions.append(1,c);
		}
		else if(c=='(')
		{
			brackets++;
			definitions.append(1,c);
		}
		else
			definitions.append(1,c);
	}
	while(!(definitions.empty()) &&( definitions.at(0) == ' '|| definitions.at(0) == '\t'||definitions.at(0) == '\n'))
		definitions = definitions.substr(1,definitions.length());
	brackets=1;
	str=getWord();
	while(str == " "||str == "\t"|| str == "\n")
			str = getWord();
	if(str==";")
	{
		command = make_pair(1,word.append(definitions.append(")")));//to draw rectanular box
		instructions.push_back(command);
		command = make_pair(5,"a");//to draw rectanular box
		instructions.push_back(command);
	}
	else
	{
		start=instructions.size();
		command = make_pair(2,word.substr(0,word.length()-1));//to draw ellipse of function declaration
		instructions.push_back(command);
		if(!definitions.empty())
		{
			command = make_pair(9,str1.append(definitions));//to draw rectangle
			instructions.push_back(command);
		}
		command = make_pair(5,"a");//to draw rectangle
		instructions.push_back(command);
		
		while(brackets!=0)
		{
			if(str.at(str.length()-1)=='}')
				brackets=0;
			if(brackets!=0)
			{
				evaluate(str);//,fp);
			}
			str=getWord();
		}
		string str,str2;
		str=str.append(word.substr(0,word.length()-1));
		str=str.append(1,':');
		str2 = static_cast<ostringstream*>( &(ostringstream() << start) )->str();
		str.append(str2);
		str2.clear();
		str=str.append(1,':');
		str2 = static_cast<ostringstream*>( &(ostringstream() << (instructions.size() - 1)) )->str();
		str.append(str2);
		str2.clear();
		str=str.append(1,':');
		funcrange.push_back(str);
	}
}

void preprocessorHandler(string word)//reads upto ';' after word
{
	char c;
	while((c=fgetc(fp)) != '\n')
		word.append(1,c);
	
	pair <int,string> command;
	command = make_pair(1,word);//to draw rectanular box
	instructions.push_back(command);
	command = make_pair(5,"a");//to draw line 
	instructions.push_back(command);
}

void ifHandler(string word) 
{
	char lastLetter = word.at(word.length()-1);	
	int brackets =0;
	string condition;
	while(lastLetter != '(')//read till you encounter (
	{
		word.append(lastLetter,1);
		lastLetter = fgetc(fp);
	}
	brackets = 1;
	while(brackets !=0)//read the condition till a matching ) is found
	{
		lastLetter = fgetc(fp);
		if(lastLetter == ')')
		{
			brackets--;
			if(brackets != 0)
				condition.append(1,lastLetter);
			else
				break;
		}
			
		else if(lastLetter == '(')
		{
			brackets++;
			condition.append(1,lastLetter);
		}
		else
			condition.append(1,lastLetter);
	}	
	pair <int,string> command;
	command = make_pair(6,"a");
	instructions.push_back(command);
	command = make_pair(3,condition);//draw a rhombus for condition
	instructions.push_back(command);
	
	command = make_pair(5,"a");//draw a line
	instructions.push_back(command);
	while ((lastLetter=fgetc(fp)) == ' ' || lastLetter == '\t' || lastLetter == '\n'){}//now you have to remove unwanted before if body 
	if(1)
	{
		string ifbody;
		if(lastLetter != '{')//if not { then start to read(single line
		{
			while(lastLetter != ';')//read till ;
			{
				ifbody.append(1,lastLetter);
				lastLetter = fgetc(fp);
			}
			command = make_pair(1,ifbody);//make ractangle box
			instructions.push_back(command);
			command = make_pair(5,"a");//make ractangle box
			instructions.push_back(command);
		}
		else //when multiple line if body is there
		{
			brackets = 1;
			while(brackets !=0)//read till you find a matching closing bracket
			{
				string str;
				str=getWord();
				if(str.at(str.length() -1) != '}')
				{
					evaluate(str);
				}
				else
				{
					brackets--;
					if(brackets != 0)
						evaluate (str);//this seems redundant to me
					else
						break;
				}
			}
		}
	}
	command = make_pair(7,"a");
	instructions.push_back(command);
	bool flag = 0;
	while ((lastLetter=fgetc(fp)) == ' ' || lastLetter == '\t'|| lastLetter == '\n')//remove spaces before detecting else
	{	
		flag =1;
	}
	if(flag ==1)
		ungetc(lastLetter,fp);
	word = getWord();
	char c;
	c = word.at(word.length()-1);
	ungetc(c,fp);
	if((word.substr(0,word.length()-1)).compare("else") != 0)//check that else appears after if
	{
		short int i= word.length()-1;//put back the word in the file
		while(i>0)
		{
			c=word.at(i-1);
			
			ungetc(c,fp);
			i--;
		}
	}
	else
	{
		
		command = make_pair(4,"a");//to draw rectangle
		instructions.push_back(command);
		
		command = make_pair(15,"a");//side line
		instructions.push_back(command);
		
		flag = 0;
		lastLetter = c;
		if(!(lastLetter == ' ' || lastLetter == '\t'|| lastLetter == '\n'))//suppose else{ is there,put back '{'
			ungetc(c,fp);
		while (lastLetter == ' ' || lastLetter == '\t'|| lastLetter == '\n')//remove redundant space
		{	
			lastLetter=fgetc(fp);
			flag =1;
		}
		if(flag ==1)
			ungetc(lastLetter,fp);
		word = getWord();
		c = word.at(word.length()-1);
		if((word.substr(0,word.length()-1)).compare("if") == 0)//check if next if is there ie "else if"
		{
			evaluate(word);
			//!!!!!!!!!!!!!
			
		}
		else//else body encountered
		{
			ungetc(c,fp);
			if(1)
			{
					string elsebody;
					if(lastLetter != '{')
					{
						while(lastLetter != ';')
						{
								elsebody.append(1,lastLetter);
								lastLetter = fgetc(fp);
						}
						command = make_pair(1,elsebody);
						instructions.push_back(command);
						command = make_pair(5,"a");//parent shape is rectangle
						instructions.push_back(command);
					}	
					else
					{
						brackets = 1;
						while(brackets !=0)
						{
							string str;
							str=getWord();
							if(str.at(str.length() -1) != '}')
							{
								evaluate(str);
							}
							else
							{
								brackets--;
								if(brackets != 0)
									evaluate (str);//this seems redundant to me
								else
									break;
							}
						}
					}
								
				}
				
		}
		command = make_pair(16,"a");//else 
		instructions.push_back(command);
	}
}

void loopHandler(string word)
{
	string loopType = word.substr(0,word.length()-1);
	if(loopType =="while")
		whileHandler(word);
	else if(loopType =="do")
		doHandler(word);
	else if(loopType =="for")
		forHandler(word);
}
	
void switchHandler(string word)
{
	char c;
	bool endflag = 0,flage=0;
	int single=0,flagsingle=0;
	string condition="switch condition ",nextword; 
	c = word.at(word.length()-1);
	while(c!='(')
		c= fgetc(fp);
	while((c=fgetc(fp))!=')')
		condition.append(1,c);
	
	pair <int,string> command;
	command = make_pair(1,condition);//rectangle
	instructions.push_back(command);	
	
	command = make_pair(5,"a");//line
	instructions.push_back(command);	
	while(c!='{')
		c=fgetc(fp);
	nextword = getWord();
	while(nextword != "}")
	{
		while(nextword == " "|| nextword == "\t" || nextword == "\n" )
			nextword=getWord();
		
		p: 
		if(nextword.substr(0,nextword.length()-1) == "case")
		{
			while((c = fgetc(fp)) != ':')
				nextword.append(1,c);
		}
		
		command = make_pair(3,nextword);//rhombus of case
		instructions.push_back(command);	
		command = make_pair(5,"a");//rectangle
		instructions.push_back(command);	
		
		while (nextword != "case(" && nextword != "case " && nextword != "default " && nextword != "default:" && nextword != "}")		
		{
			evaluate(nextword);
			nextword = getWord();
			flagsingle=1;
		}
		if(flagsingle==1)
			single++;
		if(single>=2)
		{	
			command = make_pair(16,"a");//define parent
			instructions.push_back(command);
		}	
		if(nextword == "}")
		{	
			flage=1;
			nextword = getWord();
			while(nextword == " " || nextword == "\n" || nextword == "\t")
			nextword = getWord();
		}
		if(nextword == "case " || nextword == "case(")
		{
			flage=0;
			endflag = 1;
			command = make_pair(4,"a");//to draw rectangle
			instructions.push_back(command);
			command = make_pair(15,"a");//sideline
			instructions.push_back(command);
				
			goto p;
		}
		
		else if(nextword == "default:" || nextword == "default ")
		{
			flage=0;
			endflag = 1;
			string body;
			command = make_pair(4,"a");//to draw rectangle
			instructions.push_back(command);
			command = make_pair(15,"a");//sideline
			instructions.push_back(command);	
			command = make_pair(3,nextword);//rhombus of case
			instructions.push_back(command);
			command = make_pair(5,"a");//rectangle
			instructions.push_back(command);	
			while (nextword != "}")		
			{
				evaluate(nextword);
				nextword = getWord();
			}	
			command = make_pair(16,"a");//else 
			instructions.push_back(command);
	
		}
		if(flage == 1)
		{
			short int i= nextword.length();//put back the word in the file
			while(i>0)
			{
				c=nextword.at(i-1);
				ungetc(c,fp);
				i--;
			}
			break;
		}
	}
	
}

void doHandler(string word)
{
	char c = word.at(word.length()-1);
	string nextword,condition;
	int brackets = 1;
	while(c!='{')
		c = fgetc(fp);
	nextword = getWord();
	pair <int,string> command;
	while(nextword != "}")
	{
		evaluate(nextword);
		nextword = getWord();
	}
	command = make_pair(12,"a");
	instructions.push_back(command);
	while(nextword.substr(0,nextword.length()-1) != "while")
		nextword = getWord();
	c=nextword.at(nextword.length()-1);
	while(c!='(')
		c = fgetc(fp);
	c = fgetc(fp);
	while(brackets !=0)
	{
		if(c=='(')
			brackets++;
		else if(c==')')
		{
			brackets--;
			if(brackets == 0)
				break;
		}
		condition.append(1,c);
		c=fgetc(fp);
	}
	command = make_pair(3,condition);
	instructions.push_back(command);
	command = make_pair(4,"a");//to draw rectangle
	instructions.push_back(command);
	command = make_pair(8,"a");
	instructions.push_back(command);
}

void whileHandler(string word)
{
	
	char c=word.at(word.length()-1);
	string condition;
	string nextword;
	short int brackets = 1;
	if(c == ' ' || c== '\t' || c=='\n')
	{
		while(c!='(')
			c = fgetc(fp);
	}
	
	c=fgetc(fp);
	while(brackets !=0)
	{
		if(c=='(')
			brackets++;
		else if(c==')')
		{
			brackets--;
			if(brackets == 0)
				break;
		}
		condition.append(1,c);
		c=fgetc(fp);
	}
	pair <int,string> command;
	command = make_pair(3,condition);
	instructions.push_back(command);
	command = make_pair(12,"a");
	instructions.push_back(command);
	command = make_pair(5,"a");
	instructions.push_back(command);
	c= fgetc(fp);
	while(c==' ' || c== '\n' || c=='\t')
		c= fgetc(fp);
	if(c!='{')
	{
		ungetc(c,fp);
		nextword =getWord();		
		while(!(nextword == ";" || nextword == "\n" || nextword == "\t"|| nextword == " ") )
		{
			evaluate(nextword);
			nextword = getWord();
		}
		command = make_pair(8,"a");//this is side upper line upto stored coordinate
		instructions.push_back(command);
	}
	else
	{
		nextword =getWord();
		while(nextword != "}")
		{
			evaluate(nextword);
			nextword = getWord();
								
		}
		command = make_pair(8,"a");//this is side upper line upto stored coordinate
		instructions.push_back(command);
	}
}

void forHandler(string word)
{
	char c=word.at(word.length()-1);
	short int brackets =1;
	string condition,nextword,initialization,updation;
	if(c == ' ' || c== '\t' || c=='\n')
	{
		while(c!='(')
			c = fgetc(fp);
	}
	while((c=fgetc(fp)) != ';')
		initialization.append(1,c);
	pair <int,string> command;
	command = make_pair(1,initialization);
	instructions.push_back(command);
	command = make_pair(5,"a");
	instructions.push_back(command);
	command = make_pair(12,"a");
	instructions.push_back(command);
	while((c=fgetc(fp)) != ';')
		condition.append(1,c);
	command = make_pair(3,condition);
	instructions.push_back(command);
	
	command = make_pair(5,"a");
	instructions.push_back(command);
	while(brackets!=0)
	{
		c=fgetc(fp);
		if(c==')')
		{
			brackets--;
			if(brackets==0)
				break;
			else
				updation.append(1,c);
		}
		else if(c=='(')
		{
			brackets++;
			updation.append(1,c);
		}
		else
			updation.append(1,c);
	}
	while((c=fgetc(fp)) == ' ' || c=='\t' || c=='\n'){}
	if(c!= '{')
	{
		ungetc(c,fp);
		while((nextword = getWord()) != ";"&& nextword!= " " &&  nextword!= "\t" && nextword!= "\n")
			evaluate (nextword);
	}
	else
	{
		while((nextword = getWord()) != "}")
			evaluate (nextword);
	}
	command = make_pair(1,updation);
	instructions.push_back(command);
	command = make_pair(5,"a");
	instructions.push_back(command);
	command = make_pair(8,"a");
	instructions.push_back(command);
	command = make_pair(10,"a");
	instructions.push_back(command);
}

void commentHandler(string word)
{
	string comment;
	char c;
	pair <int,string> command;
	if(word.at(word.length()-1) == '/')
	{
		while((c=fgetc(fp)) != '\n')
		{	
			comment.append(1,c); 
		}	
	}
	else
	{
		c=fgetc(fp);
		while(1)
		{
			if(c== '*' && fgetc(fp) == '/' )
				break;
			else
				comment.append(1,c);
			c = fgetc(fp);
		}
	}
	command = make_pair(11,comment);
	instructions.push_back(command);
}
void conditionHandler(string word)
{
}

void expressionHandler(string word)
{
	char c=fgetc(fp);
	
	if(c=='/'||c=='*')
		commentHandler(word.append(1,c));
	else
	{
		
		while(c!= ';')
		{
			word.append(1,c);		
			c=fgetc(fp);
		}
		
		pair <int,string> command;
		command = make_pair(1,word);
		instructions.push_back(command);
		command = make_pair(5,"a");
		instructions.push_back(command);
	}
}

void classHandler(string word)
{
	string nextword,name;
	int start,end;
	char c;
	nextword=getWord();
	while(nextword==" "||nextword=="\t"||nextword=="\n")
		nextword=getWord();
		
	name=nextword.substr(0,nextword.length()-1);
	h.insert(name, DECLARATION);
	c=nextword.at(nextword.length()-1);
	start=instructions.size();
	while(c==' '||c=='\t'||c=='\n')
		c=fgetc(fp);
	if(c == '{')
	{
		while(nextword != "}")
		{
			nextword = getWord();
			evaluate(nextword);
		
		}
		string str,cname,str2;
		cname = filename.append(1,':');
		cname = cname.append(name);
		str.append(cname);
		str.append(1,':');
		str2 = static_cast<ostringstream*>( &(ostringstream() << start) )->str();
		str.append(str2);
		str2.clear();
		str.append(1,':');
		str2 = static_cast<ostringstream*>( &(ostringstream() << (instructions.size()-1)) )->str();
		str.append(str2);
		str2.clear();
		str.append(1,':');
		classrange.push_back(str);	
	}
	else if(c == ';')
	{
		nextword = word.append(name);
		pair <int,string> command;
		command = make_pair(1,nextword);
		instructions.push_back(command);
	}
	else if(c == ',')
	{
		nextword = word.append(name);
		while((c=fgetc(fp)) != ';')
			nextword.append(1,c);		
		pair <int,string> command;
		command = make_pair(1,nextword);
		instructions.push_back(command);
	}
	else
	{
		nextword = word.append(name);
		nextword = nextword.append(1,' ');
		while(c!= ';')
		{
			nextword.append(1,c);		
			c = fgetc(fp);
		}
		pair <int,string> command;
		command = make_pair(1,nextword);
		instructions.push_back(command);
	}
}

void structHandler(string word)
{
	string nextword,name;
	int start,end;
	char c;
	nextword=getWord();
	while(nextword==" "||nextword=="\t"||nextword=="\n")
		nextword=getWord();
		
	name=nextword.substr(0,nextword.length()-1);
	h.insert(name, DECLARATION);
	c=nextword.at(nextword.length()-1);
	while(c==' '||c=='\t'||c=='\n')
		c=fgetc(fp);
	if(c == '{')
	{
		while(nextword != "}")
		{
			nextword = getWord();
			evaluate(nextword);
		
		}
	}
	else if(c == ';')
	{
		nextword = word.append(name);
		pair <int,string> command;
		command = make_pair(1,nextword);
		instructions.push_back(command);
	}
	else if(c == ',')
	{
		nextword = word.append(name);
		while((c=fgetc(fp)) != ';')
			nextword.append(1,c);		
		pair <int,string> command;
		command = make_pair(1,nextword);
		instructions.push_back(command);
	}
	else
	{
		nextword = word.append(name);
		nextword = nextword.append(1,' ');
		while(c!= ';')
		{
			nextword.append(1,c);		
			c = fgetc(fp);
		}
		pair <int,string> command;
		command = make_pair(1,nextword);
		instructions.push_back(command);
	}
}


void evaluate(string word)//identifies type of word and calls corresponding handler 
{
	int handler;char c;
	handler=h.giveHandler(word.substr(0,word.length()-1));
	
	if(handler==DECLARATION)
		declarationHandler(word);//here it checks for function handler too
	else if(handler == RETURN)
		returnHandler(word);//,fp);
	else if(handler == FORMATTEDIO)
		formattedIOHandler(word);
	else if(handler == UNFORMATTEDIO)
		unformattedIOHandler(word);
	else if(handler==PREPROCESSOR)//includes,define type
		preprocessorHandler(word);
	else if(handler==IF)//detects if
		ifHandler(word); //NO TYPE CONDITIONHANDLER,
	else if(handler==LOOP)
		loopHandler(word);
	else if(handler==NAMESPACE)
		namespaceHandler(word);
	else if(handler==CLASS)
		classHandler(word);
	else if(handler==STRUCT)
		structHandler(word);
	else if(handler==FILETYPE)
		fileHandler(word);
	else  if(handler==NOTYPE)
	{
		if(word == "(")
			expressionHandler(word);
		else if(word.at(0) == '#')
			preprocessorHandler(word);
		else
		{
			if(!((word==" ")||(word=="\n")||(word=="\t") ))
			{
				char lastLetter = word.at(word.length()-1);
				if(lastLetter==' ')
				{
					while((c=fgetc(fp))==' '){}
					lastLetter = c;
					word.append(1,c);
				}
				
				if( (lastLetter == '+') || (lastLetter == '-') || (lastLetter == '*') || (lastLetter == '/') || (lastLetter == '%') || (lastLetter == '^')||(lastLetter == '.'))
					expressionHandler(word);
				else if((lastLetter == '!') || (lastLetter == '>') || (lastLetter == '<') )
					conditionHandler(word);
				else if(lastLetter == '=')
				{
					char c = fgetc(fp);
					if (c  != '=')
					{
						ungetc(c,fp);
						expressionHandler(word);//,fp);
					}
					else
					{
						ungetc(c,fp);
						conditionHandler(word);
					}
				}
				else if(lastLetter == ';')//dont know what is the need
				{
					//expressionHandler(word,fp);
				}
				//i have left (,),{,} separator because as of now i dont think there is a need
			}
		}
	}
}

int main()
{
	string str,str1,str2;
	cout<<"Enter files (-1 to terminate): "<<endl;
	cin >> filename;
	str1=filename;
	str1=str1.append(1,':');
	while(filename != "-1")
	{	
		if (!(fp=fopen (filename.c_str(),"r")))
		 {
		 	printf("Error opening file.\n");
		 	return (1);
		 }
		while(!feof(fp))
		{	
			str=getWord();	
			if(fileEnd==false )
			{
				evaluate(str);
			}
		}
		fileEnd = false;
		
		pair <int,int> file;
		file.first = fileStart;
		file.second = instructions.size()-1;
		str2 = static_cast<ostringstream*>( &(ostringstream() << fileStart) )->str();
		str1.append(str2);
		str2.clear();
		str1.append(1,':');
		str2 = static_cast<ostringstream*>( &(ostringstream() << (instructions.size()-1)) )->str();
		str1.append(str2);
		str2.clear();
		str1.append(1,':');
		filerange.push_back(str1);
		str1.clear();
		fileStart = instructions.size();
				
		cin>> filename;
		str1=filename;
		str1=str1.append(1,':');
	}
	printIns();
	printrangemap();
	printfileRangeMap();
	printclassrange();
	return 0;
}

