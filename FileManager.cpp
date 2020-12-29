#include "FileManager.h"


FileManager::FileManager(std::string const& FileName,std::string const& KeyWord) :
	m_FileName(std::string("res/configuration-files/"+FileName)),
	m_KeyWord(KeyWord),
	m_divisor("------------------"),
	m_NameSign("[###]"),
	m_BackUpFile_name(std::string("res/configuration-files/BackUpConf/B_"+FileName))
{
	LoadBackUp();
	LoadFile();
	
}
void FileManager::LoadBackUp()
{
	std::ifstream archi(m_BackUpFile_name);
	std::string linea;
	while(getline(archi,linea))
	{
		m_default.push_back(linea);
	}
	archi.close();
}
void FileManager::LoadFile()
{
	
	std::vector<std::string> v_lines_aux;
	std::ifstream archi(m_FileName);
	if(!archi.is_open())
	{
		RestoreAllToDef();
	}
	else
	{
		std::string linea;
		while(getline(archi,linea))
		{
			v_lines_aux.push_back(linea);
		}
		archi.close();
	}
	std::vector<std::string>::iterator it,ite;
	it=std::find(v_lines_aux.begin(),v_lines_aux.end(),m_NameSign+m_KeyWord);
	if(it!=v_lines_aux.end())
	{
		std::advance(it,1);
		ite=std::find(it,v_lines_aux.end(),m_divisor);
		// no queremos el singo ni el divisor, solo los datos de en medio
		for(;it!=ite;++it){
			m_lines.push_back(*it); 
		}
	}
	else std::cerr<<"La palabra clave "<<m_KeyWord<<" no encontrada";
}

void FileManager::SaveChanges()
{
	std::vector<std::string> v_saved=m_default;
	int inicio=0,fin;
	for(size_t j=0;j<v_saved.size();j++)
	{
		if(v_saved[j]==m_NameSign+m_KeyWord)
		   break;
		++inicio;
	}
	inicio=fin;
	for(size_t j=0;j<v_saved.size();j++)
	{
		if(v_saved[j]==m_divisor)
			break;
		++fin;
	}
	for(std::string &x:m_fields_to_change)
	{
		for(int i=inicio;i<fin;++i)
		{
			if(v_saved[i].find(x)!=std::string::npos)
			{
				std::string line;
				line=x+"="+GetValue(x);
				v_saved[i]=line;
			}
		}
	}
	std::ofstream archo(m_FileName,std::ios::trunc);
	for(std::string &x:v_saved)
		archo<<x+"\n";
	archo.close();
}

 std::string FileManager::GetValue(std::string const& field)const
{
	std::string value="Invalid";
	for(std::string x:m_lines)
	{
		if(x.find(field)!=std::string::npos){
			value=x.substr(x.find('=')+1,x.size());
			break;
		}
	}
	if(value=="Invalid")std::cerr<<field<<" is not a valid field";
	return value;
}
void FileManager::ChangeValue(std::string const& field,std::string const& value)
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
void FileManager::RestoreThisToDef(std::string const& field)
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
	m_fields_to_change.push_back(field);
	///this function stores witch values must me changed, if you wanne save them, call SaveChanges()
}
void FileManager::RestoreAllToDef()
{
	std::ofstream archo(m_FileName,std::ios::trunc);
	for(std::string &x:m_default)
		archo<<x+"\n";
	archo.close();
	
}
std::string FileManager::operator[](std::string const& field)const
{
	return GetValue(field);
}
void FileManager::Reload(std::string const& FileName,std::string const& KeyWord)
{
	m_default.erase(m_default.begin(),m_default.end());
	m_lines.erase(m_lines.begin(),m_lines.end());
	m_fields_to_change.erase(m_fields_to_change.begin(),m_fields_to_change.end());
	m_FileName="res/configuration-files/"+FileName;
	m_KeyWord=KeyWord;
	m_BackUpFile_name="res/configuration-files/BackUpConf/B_"+FileName;
	//reset all variables
	
	LoadBackUp();
	LoadFile();
	
	
}
