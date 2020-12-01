#include "Controls.h"
#include <map>
using namespace std;

Controls::Controls()
{
	
}

bool Controls::KeyState(string const& key)
{
	return sf::Keyboard::isKeyPressed(m_keys[key]);
}
void Controls::BindKey(string const& function_name,sf::Keyboard::Key new_key)
{
	map<string,sf::Keyboard::Key>::iterator pos=m_keys.find(function_name);
	if(pos==m_keys.end())
	{
		m_keys.insert({function_name,new_key});
	}
	else
	{
		m_keys[function_name]=new_key;
	}
}
sf::Keyboard::Key Controls::StringToKey(std::string const& str_key)
{
	if(str_key=="Left")return sf::Keyboard::Key::Left;
	if(str_key=="Right")return sf::Keyboard::Key::Right ;
	if(str_key=="Up")return sf::Keyboard::Key::Up ;
	if(str_key=="Down")return sf::Keyboard::Key::Down;
	if(str_key=="A")return sf::Keyboard::Key::A;
	if(str_key=="B")return sf::Keyboard::Key::B;
	if(str_key=="C")return sf::Keyboard::Key::C;
	if(str_key=="D")return sf::Keyboard::Key::D;
	if(str_key=="E")return sf::Keyboard::Key::E;
	if(str_key=="F")return sf::Keyboard::Key::F;
	if(str_key=="G")return sf::Keyboard::Key::G;
	if(str_key=="H")return sf::Keyboard::Key::H;
	if(str_key=="I")return sf::Keyboard::Key::I;
	if(str_key=="J")return sf::Keyboard::Key::J;
	if(str_key=="K")return sf::Keyboard::Key::K;
	if(str_key=="L")return sf::Keyboard::Key::L;
	if(str_key=="M")return sf::Keyboard::Key::M;
	if(str_key=="N")return sf::Keyboard::Key::N;
	if(str_key=="O")return sf::Keyboard::Key::O;
	if(str_key=="P")return sf::Keyboard::Key::P;
	if(str_key=="Q")return sf::Keyboard::Key::Q;
	if(str_key=="R")return sf::Keyboard::Key::R;
	if(str_key=="S")return sf::Keyboard::Key::S;
	if(str_key=="T")return sf::Keyboard::Key::T;
	if(str_key=="U")return sf::Keyboard::Key::U;
	if(str_key=="V")return sf::Keyboard::Key::V;
	if(str_key=="W")return sf::Keyboard::Key::W;
	if(str_key=="X")return sf::Keyboard::Key::X;
	if(str_key=="Y")return sf::Keyboard::Key::Y;
	if(str_key=="Z")return sf::Keyboard::Key::Z;
	if(str_key=="Numpad0")return sf::Keyboard::Key::Numpad0;
	if(str_key=="Numpad1")return sf::Keyboard::Key::Numpad1;
	if(str_key=="Numpad2")return sf::Keyboard::Key::Numpad2;
	if(str_key=="Numpad3")return sf::Keyboard::Key::Numpad3;
	if(str_key=="Numpad4")return sf::Keyboard::Key::Numpad4;
	if(str_key=="Numpad5")return sf::Keyboard::Key::Numpad5;
	if(str_key=="Numpad6")return sf::Keyboard::Key::Numpad6;
	if(str_key=="Numpad7")return sf::Keyboard::Key::Numpad7;
	if(str_key=="Numpad8")return sf::Keyboard::Key::Numpad8;
	if(str_key=="Numpad9")return sf::Keyboard::Key::Numpad9;
	if(str_key=="Space ")return sf::Keyboard::Key::Space ;
	if(str_key=="Enter")return sf::Keyboard::Key::Enter;
	if(str_key=="Add ")return sf::Keyboard::Key::Add ;
	if(str_key=="Subtract")return sf::Keyboard::Key::Subtract;
	if(str_key=="Multiply ")return sf::Keyboard::Key::Multiply ;
	if(str_key=="Divide ")return sf::Keyboard::Key::Divide ;
	///si no es ninguna de estas, devuevle Unknown
	return sf::Keyboard::Key::Unknown ;
}
