#pragma once

#include "Stra/Common/Common.h"

class LeafData : public Singleton < INIReader > {
	friend class Singleton < INIReader >;
};

typedef LeafData TheLeafData;
