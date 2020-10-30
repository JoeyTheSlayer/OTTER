#pragma once

#include "MeshBuilder.h"
#include "MeshFactory.h"

class OBJLoad {
public:
	static VertexArrayObject::sptr LoadFile(const std::string& filename);
protected: // added by Jose
    OBJLoad() = default;
    ~OBJLoad() = default;
};

/*      _______
       //  ||\ \
 _____//___||_\ \___
 )  _          _    \
 |_/ \________/ \___|
___\_/________\_/______ */
