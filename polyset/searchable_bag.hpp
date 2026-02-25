#ifndef SEARCHABLE_BAG
#define SEARCHABLE_BAG

#include "bag.hpp"

class searchable_bag : virtual public bag
{
	public:
		virtual bool has(int) const = 0;
};

#endif