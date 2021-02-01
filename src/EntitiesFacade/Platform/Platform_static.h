#ifndef PLATFORM_STATIC_H
#define PLATFORM_STATIC_H
#include "Platform.h"

class Platform_static : public Platform {
public:
	Platform_static(std::string key);
	void Move()override;
	void Update()override;
	
	void LoadData(FileManager const& s_aux,float const& win_width,float const& win_height  )override;
private:
};

#endif

