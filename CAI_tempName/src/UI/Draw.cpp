#include "caipch.h"
#include "Draw.h"
#include "stbimge/stb_image.h"
Draw::Brush::Brush() noexcept :bColor(Color::BLACK), texturePath("") 
{
}
Draw::Brush::Brush(uint32_t color_v) noexcept : bColor(color_v), texturePath("") {

}

Draw::Brush::Brush(const std::string& filePath) noexcept :bColor(Color::BLACK),texturePath(filePath)
{
}

Draw::Brush::~Brush() noexcept
{
}

Draw::Brush::Brush(const Brush& other) noexcept
{
	bColor = other.bColor;
	texturePath = other.texturePath;
}

void Draw::Brush::SetTexturePath(const std::string& filePath)
{
	texturePath = filePath;
}

bool Draw::Brush::HasTexture()
{
	if(texturePath.empty())
		return false;
	return true;
}


Draw::Brush& Draw::Brush::operator=(const Brush& other) noexcept
{
	if (this == &other)
		return *this;
	bColor = other.bColor;
	texturePath = other.texturePath;
	return *this;
}

Draw::Brush& Draw::Brush::operator=(const Color& color) noexcept
{
	bColor = bColor;
	return *this;
}
