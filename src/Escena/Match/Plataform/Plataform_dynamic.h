#ifndef PLATAFORM_DYNAMIC_H
#define PLATAFORM_DYNAMIC_H
#include "Plataform.h"

class Plataform_dynamic : public Plataform {
public:
	Plataform_dynamic(std::string key);
	void Move ();
	void Update ( );
	void LoadData (FileManager const& s_aux,float const& win_width,float const& win_height  );
private:
};

#endif

