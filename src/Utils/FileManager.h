#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <map>

/// @brief The most useful class of all time
class FileManager 
{
public:
	std::string GetValue(std::string const& field)const;
	void ChangeValue(std::string const& field,std::string const& value);
	void LoadFile();
	void Reload(std::string const& FileName,std::string const& KeyWord);
	void RestoreAllToDef(std::vector<std::string> const& backup);
	void RestoreThisToDef(std::string const&  field);
	void SaveChanges();
	
	std::string operator[](std::string const& field) const;
	FileManager(std::string const& FileName,std::string const& KeyWord);
private:
	std::vector<std::string> FileToString(std::string filename);
	int m_start, m_end;
	std::string m_filepath, m_filename, m_KeyWord;
	std::map<std::string, std::string> m_map;
};

#endif

