#pragma once

#include "nospread/nospread.h"

class c_features {
public:
	c_features();
	~c_features();

public:
	std::unique_ptr<c_aimbot>            aimbot            = { };
	std::unique_ptr<c_engine_prediction> engine_prediction = { };
	std::unique_ptr<c_esp>               esp               = { };
	std::unique_ptr<c_menu>              menu              = { };
	std::unique_ptr<c_misc>              misc              = { };
	std::unique_ptr<c_nospread>          nospread          = { };
};

inline c_features features;