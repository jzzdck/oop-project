#ifndef PLATAFORM_STATIC_H
#define PLATAFORM_STATIC_H
#include "Plataform.h"

class Plataform_static : public Plataform {
public:
	Plataform_static(std::string key);
	void Move()override;
	void Update()override;
	
	void LoadData(FileManager const& s_aux,float const& win_width,float const& win_height  )override;
private:
};

#endif

