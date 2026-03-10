#include "set.hpp"

set::set(searchable_bag &sbag) : bag(sbag) {}

set::~set() {}

bool set::has(int n) const {return bag.has(n);}

void set::insert(int n) 
{
	if (!(this->has(n)))
		return bag.insert(n);
}

void set::print() const {return bag.print();}

void set::clear() {return bag.clear();}

searchable_bag &set::get_bag() const {return this->bag;}

void set::insert(int *data, int size)
{
	for (int i = 0; i < size; i++)
		this->insert(data[i]);
}