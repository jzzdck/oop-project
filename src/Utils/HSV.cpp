#include "HSV.h"
#include <cmath>

namespace utils {
	void HSV::SetHue (float hue) {
		hue = std::fmod(hue, 360.f);
		m_hue = hue;
	}
	
	void HSV::SetSat (float sat) {
		sat = std::fmod(sat, 100.f);
		m_sat = sat;
	}
	
	void HSV::SetVal (float val) {
		val = std::fmod(val, 100.f);
		m_val = val;
	}
	
	HSV::HSV (float hue, float sat, float value) :
		m_hue(hue), m_sat(sat), m_val(value)
	{  }
	
	HSV::HSV (const sf::Color & col) {
		*this = MakeHSV(col);
	}
	
	HSV MakeHSV (const sf::Color & col) {
		float r = col.r/255.f;
		float g = col.g/255.f;
		float b = col.b/255.f;
		
		float max = std::max(r, (std::max(g, b)));
		float min = std::min(r, (std::min(g, b)));
		float dif = max - min; 
		
		float hue, val, sat;
		
		if (max == 0 && min == 0) 
			hue = 0;
		else if (max == r)
			hue = std::fmod((60*((g-b)/dif) + 360), 360.f);
		else if (max == g)
			hue = std::fmod((60*((b-r)/dif) + 120), 360.f);
		else if (max == b)
			hue = std::fmod((60*((r-g)/dif) + 240), 360.f);
		
		if (max == 0) 
			sat = 0;
		else 
			sat = (dif/max)*100;
		
		val = max*100;
		
		return HSV(hue, sat, val);
	}
	
	sf::Color HSV::MakeRGB() const {
		float r, g, b;
		
		float C = (m_val/100.f) * (m_sat/100.f);
		float X = C * (1 -  std::fabs(std::fmod(m_hue/60.f, 2.f) - 1));
		float m = m_val/100.f - C;
		
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
	
	HSV getColorHSV(std::string hsv) {
		int h, s, v;
		std::stringstream ss;
		
		ss << hsv;
		ss >> h >> s >> v;
		
		return HSV(h, s, v);
	}
	
}

