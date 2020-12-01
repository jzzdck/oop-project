#include "Settings.h"
#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Settings::Settings(std::string const& FileName,std::string const& KeyWord):m_FileName(FileName),m_KeyWord(KeyWord),m_divisor("------------------"),m_BackUpFile("/res/configuration-files/Global_Config_Backup.conf")
{
	LoadFile();
	
}
void Settings::LoadFile()
{
	std::ifstream archi(m_FileName);
	if(!archi.is_open())
	{
		archi.open(m_BackUpFile);
		std::vector<std::string> v_aux;
		std::string linea;
		while(getline(archi,linea))
		{
			v_aux.push_back(linea);
		}
		archi.close();
		std::string KeyWordType=m_KeyWord.substr(0,m_KeyWord.find_first_of("=")-1);
		//al player=0 le sacamos =0
		int first_appearence=-1,last_appearence=-1;
		for(size_t i=0;i<v_aux.size();++i) 
		{
			if(v_aux[i].find(KeyWordType)!=std::string::npos)
			{
				if(first_appearence==-1)first_appearence=i;
				last_appearence=i;
			}
		}
		//La primera vez que aparece la palabra calve (ej jugador) y la ultima
		if(first_appearence!=-1)
		{
			std::vector<std::string>::iterator it,ite;
		it=std::next(v_aux.begin()+first_appearence);
		ite=std::find(std::next(v_aux.begin(),last_appearence),v_aux.end(),m_divisor);
		std::advance(ite,1);
		std::ofstream archo(m_FileName);
		for(;it!=next(ite);++it)
			archo<<*it+"\n";
		archo.close();
		//ite va a estar despues del divisor de la ultima vez que aparece la palabra clave
		}
		archi.open(m_FileName);
	}
	std::vector<std::string> v_aux;
	std::string linea;
	while(getline(archi,linea))
	{
		v_aux.push_back(linea);
	}
	archi.close();
	std::vector<std::string>::iterator it,ite;
	it=std::next(std::find(v_aux.begin(),v_aux.end(),m_KeyWord));
	// no queremos el identificador de player= ni el divisor, solo los datos de en medio
	ite=std::find(it,v_aux.end(),m_divisor);
	for(;it!=ite;++it)
		m_lines.push_back(*it); 

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
			value=x.substr(x.find('='),x.size());
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
	std::ifstream archi(m_BackUpFile);
	std::vector<std::string> v_aux;
	std::string linea;
	while(getline(archi,linea))
	{
		v_aux.push_back(linea);
	}
	archi.close();
	std::vector<std::string>::iterator it,ite;
	it=std::find(v_aux.begin(),v_aux.end(),m_KeyWord);
	ite=std::find(it,v_aux.end(),m_divisor);
	for(;it!=ite;++it)
	{
		if((*it).find(field)!=std::string::npos)
		{
			std::string value;
			value=(*it).substr((*it).find('='),(*it).size());
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
