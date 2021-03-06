#include "cTexture.h"

cTexture::cTexture(void)
{
}

cTexture::~cTexture(void)
{
}

void cTexture::initilize()
{
	ilInit();
	iluInit();
}

bool cTexture::loadTexture(ILenum fileType, string fileName)
{
	char * fName = (char*)malloc(sizeof(char) * fileName.size());
	strcpy(fName, fileName.c_str());
	ilLoad(fileType, (const wchar_t *)fName);
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);

	imageData = ilGetData();

	ilEnable(IL_CONV_PAL);

	unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, width, height, type, GL_UNSIGNED_BYTE, imageData);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	return false;
}

void cTexture::drawTexture(float x, float y)
{
	drawTexture(x, y, width, height);
}
void cTexture::drawTexture(float x, float y, float width, float height)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(x + -width / 2, y + -height / 2, 0);
	glTexCoord2f(1, 1); glVertex3f(x + width / 2, y + -height / 2, 0);
	glTexCoord2f(1, 0); glVertex3f(x + width / 2, y + height / 2, 0);
	glTexCoord2f(0, 0); glVertex3f(x + -width / 2, y + height / 2, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
int cTexture::getID()
{
	return id;
}
pair<GLuint, GLuint> cTexture::getSize()
{
	return{ width, height };
}