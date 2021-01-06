#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
/// @brief The most useful class of all time
class FileManager 
{
public:
	std::string GetValue(std::string const& field)const;
	void ChangeValue(std::string const& field,std::string const& value);
	void LoadFile();
	void LoadBackUp();
	void Reload(std::string const& FileName,std::string const& KeyWord);
	void RestoreAllToDef();
	void RestoreThisToDef(std::string const&  field);
	void SaveChanges();
	
	std::string operator[](std::string const& field) const;
	FileManager(std::string const& FileName,std::string const& KeyWord);
private:
	struct Element	{ std::string field, value;};
	std::string m_FileName,m_KeyWord,m_divisor,m_NameSign;
	std::vector<std::string> m_lines,m_default, m_fields_to_change;
	std::string m_BackUpFile_name;
};

#endif

