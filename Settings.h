#ifndef SETTINGS_H
#define SETTINGS_H
#include <vector>
#include "Controls.h"
#include <SFML/Graphics/Color.hpp>
struct Element
{
	std::string field,value;
};
class Settings {
public:
	std::string GetValue(std::string const& field)const;
	void ChangeValue(std::string const& field,std::string const& value);
	void LoadFile();
	void LoadBackUp();
	void RestoreAllToDef();
	void RestoreThisToDef(std::string const&  field);
	void SaveChanges();
	
	std::string operator[](std::string const& field) const;
	Settings(std::string const& FileName,std::string const& KeyWord);
private:
	std::string m_FileName,m_KeyWord,m_divisor,m_NameSign;
	std::vector<std::string> m_lines,m_default,m_fields_to_change;
	std::string m_BackUpFile_name;
};

#endif

