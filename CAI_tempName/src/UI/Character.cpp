#include"caipch.h"
#include "Character.h"
Font::Font() noexcept
{
	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;

	}
	if (FT_New_Face(ft, "resources/fonts/Source_Han_Serif_SC_Light_Light.otf", 0, &face)) {
	
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	fontSize =48;
	VAO = 0;
	VBO = 0;
	glGenVertexArrays(1, &VAO); 
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Font::~Font() noexcept
{
	// 释放Face对象
	FT_Done_Face(face);
	// 释放库
	FT_Done_FreeType(ft);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1,&VBO);
	for (auto& chr : characters) {
		glDeleteTextures(1, &(chr.second.textureID));
	}
}
void Font::Load(const wchar_t& ch)
{
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	//缓存字符已经有了该字符
	if (characters.find(ch) != characters.end())
		return;
	//只缓存单个字体
	if (FT_Load_Char(face, ch, FT_LOAD_RENDER)) {
		std::cout << "wor";
		return;
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindVertexArray(VAO);
	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer
	);	
	// 设置纹理选项
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Character chr = {
			texture,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x
	};
	characters[ch] = chr;
	glBindVertexArray(0);
}

void Font::Load()
{
	//将所有字体全部缓存
	wchar_t  charcode;
	FT_UInt   gindex;
	charcode =  FT_Get_First_Char(face, &gindex);
	glBindVertexArray(VAO);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	unsigned int texture;
	while (gindex) {
		
		FT_Load_Glyph(face, gindex, FT_LOAD_RENDER);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character chr = {
			texture,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x
		};
		characters[charcode] = chr;
		charcode=FT_Get_Next_Char(face, charcode, &gindex);
	}
	glBindVertexArray(0);
}

Character& Font::character(unsigned int unicode)  noexcept
{
	//缓存字符已经有了该字符
	if (characters.find(unicode) == characters.end())
		Load(unicode);
	return characters[unicode];;
}


