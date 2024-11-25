#include "caipch.h"
#include "VisualCollection.h"
#include <algorithm>
void VisualCollection::SortByZindex()
{
	std::sort(childs.begin(), childs.end(), [](Visual*& a, Visual*& b) {
		return a->zIndex.get() > b->zIndex.get();
		});
}
