#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &src) : tree_bag(src) {}

searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &src)
{
	if (this != &src)
		tree_bag::operator=(src);
	return *this;
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::search(tree_bag::node *node, int n) const
{
	if (node == NULL)
		return false;
	if (node->value == n)
		return true;
	else if (n < node->value)
		return search(node->l, n);
	else
		return search(node->r, n);
}

bool searchable_tree_bag::has(int n) const {return search(tree, n);}