#include "FileManager.h"

FileManager::FileManager(std::string const& FileName,std::string const& KeyWord) :
	m_filepath("../res/configuration-files/"), m_filename(FileName), m_KeyWord(KeyWord)
{
	LoadFile();	
}

void FileManager::LoadFile() 
{
	std::vector<std::string> v_lines_aux;
	std::ifstream archi(m_filepath + m_filename);
	if (!archi.is_open())
		RestoreAllToDef(FileToString(m_filepath + "BackUpConf/B" + m_filename));
	v_lines_aux = FileToString(m_filepath + m_filename);
	
	std::vector<std::string>::iterator begin, end;
	begin = std::find(v_lines_aux.begin(),v_lines_aux.end(),"[###]"+m_KeyWord);
	end = std::find(begin,v_lines_aux.end(),"------------------");
	
	if (begin != v_lines_aux.end()) 
	{
		m_start = begin - v_lines_aux.begin() + 1;
		m_end = end - v_lines_aux.begin();
		// no queremos el singo ni el divisor, solo los datos de en medio
		for(auto it = begin+1; it!=end; ++it) 
		{
			size_t divisor = it->find('=');
			if (!it->empty() && divisor != std::string::npos)
				m_map.insert({ it->substr(0, divisor), it->substr(divisor+1) }); 
		}
	} 
	else std::cerr<<"La palabra clave "<<m_KeyWord<<" no encontrada\n";
}

void FileManager::SaveChanges()
{
	std::vector<std::string> v_saved = FileToString(m_filepath + m_filename);
	std::ofstream archo(m_filepath + m_filename);
	
	for (int i=m_start;i<m_end;++i)
	{
		auto it = m_map.find(v_saved[i]);
		if (it != m_map.end())
			v_saved[i] = it->first + "=" + it->second;
	}
	
	for (std::string &x : v_saved)
		archo<<x+"\n";
	archo.close();
}

std::string FileManager::GetValue(std::string const& field)const
{
	auto it = m_map.find(field);
	std::string value = (it != m_map.end() ? it->second : "Invalid");
	
	if (value == "Invalid") 
		std::cerr << field << " is not a valid field" << std::endl;
	
	return value;
}

void FileManager::ChangeValue(std::string const& field,std::string const& value)
{
	auto it = m_map.find(field);
	if (it != m_map.end())
		it->second = value;

	///this function stores wich values must be changed, if you want to save them, call SaveChanges()
}

void FileManager::RestoreThisToDef(std::string const& field)
{
	auto backup = FileToString(m_filepath + "BackUpConf/B" + m_filename);
	auto it = std::find(backup.begin(),backup.end(), field);
	if (it != backup.end())
	{
		std::string value;
		value=it->substr(it->find('=') + 1);
		ChangeValue(field,value);
	}
}

void FileManager::RestoreAllToDef(std::vector<std::string> const& backup)
{
	std::ofstream archo(m_filepath + m_filename,std::ios::trunc);
	for(const std::string &x:backup)
		archo<<x+"\n";
	archo.close();
}

std::string FileManager::operator[](std::string const& field)const
{
	return GetValue(field);
}

void FileManager::Reload(std::string const& FileName,std::string const& KeyWord)
{
	m_map.clear();
	m_filename=FileName;
	m_KeyWord=KeyWord;
	//reset all variables
	
	LoadFile();
}

std::vector<std::string> FileManager::FileToString (std::string filename) 
{
	std::vector<std::string> file_data;
	std::ifstream archi(filename);
	std::string linea;
	while(getline(archi,linea))
		file_data.push_back(linea);
	return file_data;
}
