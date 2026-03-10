#include "searchable_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include <stdlib.h>
#include "set.hpp"

int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;
	searchable_bag *t = new searchable_tree_bag;
	searchable_bag *a = new searchable_array_bag;
	for (int i = 1; i < argc; i++) 
	{
		t->insert(atoi(argv[i]));
		a->insert(atoi(argv[i]));
	}
	t->print();
	a->print();
	for (int i = 1; i < argc; i++)
	{
		std::cout << t->has(atoi(argv[i])) << std::endl;
		std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
	}
	for (int i = 1; i < argc; i++)
	{
		std::cout << a->has(atoi(argv[i])) << std::endl;
		std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
	}
	t->clear();
	a->clear();
	const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
	tmp.print();
	std::cout << tmp.has(1) << std::endl;
	set sa(*a);
	set st(*t);
	for (int i = 1; i < argc; i++)
	{
		st.insert(atoi(argv[i]));
		sa.insert(atoi(argv[i]));
		std::cout << sa.has(atoi(argv[i])) << std::endl;
		sa.print();
		sa.get_bag().print();
		st.print();
		sa.clear();
		int arr[4] = {6, 7, 8, 9};
		sa.insert(arr, 4);
		std::cout << std::endl;
	}
}