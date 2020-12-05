#include "phutils.h"
#include <algorithm>
#include <cstdlib>
using namespace std;

namespace utils {
	sf::Vector2f getCenter(const sf::Rect<float> & of_this) {
		float x_center = of_this.left+of_this.width/2;
		float y_center = of_this.top+of_this.height/2;
		return { x_center, y_center };
	}
	
	sf::Color getColor(std::string rgb) {
		int r, g, b;
		std::stringstream ss;
		
		ss << rgb;
		ss >> r >> g >> b;
		
		return sf::Color(r, g, b);
	}
	
	HSV getColorHSV(std::string hsv) {
		int h, s, v;
		std::stringstream ss;
		
		ss << hsv;
		ss >> h >> s >> v;
		
		return HSV(h, s, v);
	}
	
	void HSV::SetHue (int hue) {
		hue %= 360;
		m_hue = hue;
	}
	
	void HSV::SetSat (int sat) {
		sat %= 100;
		m_sat = sat;
	}
	
	void HSV::SetVal (int val) {
		val %= 100;
		m_val = val;
	}
	
	HSV::HSV (int hue, int sat, int value) :
		m_hue(hue), m_sat(sat), m_val(value) {  }
	
	HSV::HSV (const sf::Color & col) {
		*this = MakeHSV(col);
	}
	
	HSV HSV::MakeHSV (const sf::Color & col) {
		int max = std::max(col.r, (std::max(col.g, col.b)));
		int min = std::min(col.r, (std::min(col.g, col.b)));
		int dif = max - min; 
		
		int hue, val, sat;
		
		if (max == 0 && min == 0) 
			hue = 0;
		else if (max == col.r)
			hue = (60*((col.g-col.b)/dif) + 360) % 360;
		else if (max == col.g)
			hue = (60*((col.b-col.r)/dif) + 120) % 360;
		else if (max == col.b)
			hue = (60*((col.r-col.g)/dif) + 240) % 360;
		
		if (max == 0) 
			sat = 0;
		else 
			sat = (dif/max)*100;
		
		val = max*100;
		
		return HSV(hue, sat, val);
	}
	
	sf::Color HSV::MakeRGB() {
		int r, g, b;
		
		int C = (m_val/100) * (m_sat/100);
		int X = C * (1 -  std::abs((m_hue/60)%2 - 1));
		int m = m_val/100 - C;
		
		if (m_hue < 60)
			r = C, g = X, b = 0;
		else if (m_hue < 120)
			r = X, g = C, b = 0;
		else if (m_hue < 180)
			r = 0, g = C, b = X;
		else if (m_hue < 240)
			r = 0, g = X, b = C;
		else if (m_hue < 300)
			r = X, g = 0, b = C;
		else
			r = C, g = 0, b = X;
		
		return sf::Color( (r+m)*255, (g+m)*255, (b+m)*255 );
	}
}

