#include "Settings.h"
#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Settings::Settings(std::string const& FileName,std::string const& KeyWord):m_FileName(std::string("res/configuration-files/"+FileName)),m_KeyWord(KeyWord),m_divisor("------------------"),m_BackUpFile_name("res/configuration-files/Global_Config_Backup.conf")
{
	LoadFile();
	
}
void Settings::LoadFile()
{
	std::ifstream archi(m_BackUpFile_name);
	std::vector<std::string> v_back_aux;
	std::string linea;
	while(getline(archi,linea))
	{
		v_back_aux.push_back(linea);
	}
	archi.close();
	std::string KeyWordType=m_KeyWord.substr(0,m_KeyWord.find_first_of("="));
	//al player=0 le sacamos =0
	int first_appearence=-1,last_appearence=-1;
	for(unsigned i=0;i<v_back_aux.size();++i) 
	{
		if(v_back_aux[i].find(KeyWordType)!=std::string::npos)
		{
			if(first_appearence==-1)first_appearence=i;
			last_appearence=i;
		}
	}
	//La primera vez que aparece la palabra calve (ej jugador) y la ultima
	if(first_appearence!=-1)
	{
		std::vector<std::string>::iterator it,ite;
		it=std::next(v_back_aux.begin()+first_appearence-1);
		ite=std::find(std::next(v_back_aux.begin(),last_appearence),v_back_aux.end(),m_divisor);
		//it va desde player=0 hasta el ultimo(incluido) divisor de un player 	for(;it!=next(ite);++it)
		   m_default.push_back(*it);
	}	
	
	
	archi.open(m_FileName);
	if(!archi.is_open())
	{
		std::ofstream archo(m_FileName);
		for(std::string &x:m_default)
			archo<<x+"\n";
		archo.close();
		archi.open(m_FileName);
	}
	std::vector<std::string> v_lines_aux;
	while(getline(archi,linea))
	{
		v_lines_aux.push_back(linea);
	}
	archi.close();
	std::vector<std::string>::iterator it,ite;
	it=std::find(v_lines_aux.begin(),v_lines_aux.end(),m_KeyWord);
	std::advance(it,1);
	ite=std::find(it,v_lines_aux.end(),m_divisor);
	// no queremos el identificador de player= ni el divisor, solo los datos de en medio
	for(;it!=ite;++it){
		m_lines.push_back(*it); 
	}
}

void Settings::SaveChanges()
{
	std::ofstream arch(m_FileName);
	for(std::string &x:m_lines)
	{
		arch<<x+"\n";
	}
	arch.close();
}

 std::string Settings::GetValue(std::string const& field)const
{
	std::string value="Invalid";
	for(std::string x:m_lines)
	{
		if(x.find(field)!=std::string::npos){
			value=x.substr(x.find('=')+1,x.size());
			break;
		}
	}
	return value;
}
void Settings::ChangeValue(std::string const& field,std::string const& value)
{
	for(std::string &x:m_lines)
	{
		if(x.find_first_of(field)!=std::string::npos)
		{
			x.resize(x.find('='));
			x+=value;
			break;
		}
	}
}
void Settings::RestoreThisToDef(std::string const& field)
{
	for(std::string &x:m_default)
	{
		if(x.find(field)!=std::string::npos)
		{
			std::string value;
			value=x.substr(x.find('='),x.size());
			ChangeValue(field,value);
			break;
		}
	}
}
void Settings::RestoreAllToDef()
{
	for(std::string &x:m_lines)
		RestoreThisToDef(x);
}
