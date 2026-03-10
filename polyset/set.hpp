#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
	private:
		searchable_bag &bag;
		set();
		set(const set &src);
		set &operator=(const set &src);

	public:
		set(searchable_bag &sbag);
		~set();

		void insert(int);
		void print() const;
		void clear();
		bool has(int) const;
		void insert(int *, int);
		searchable_bag &get_bag() const;

};

#endif