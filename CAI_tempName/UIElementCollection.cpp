#include "UIElementCollection.h"
#include "UIElement.h"

UIElementCollection::UIElementCollection() noexcept : childs(new std::vector<UIElement*>()),m_data(nullptr),size(0)
{
}

UIElementCollection::~UIElementCollection() noexcept
{
	delete childs;
}

size_t UIElementCollection::Size() const noexcept
{
	return childs->size();
}

UIElementCollection::iterator UIElementCollection::begin()
{
	
	return childs->begin();
}

UIElementCollection::iterator UIElementCollection::end()
{
	return childs->end();
}

void UIElementCollection::addChild(UIElement* child)
{
	childs->emplace_back(child);
	++size;
}

