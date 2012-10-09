/**
 * Chisa
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <GL/gl.h>
#include "Sprite.h"
#include "Canvas.h"

namespace chisa {
namespace gl {

static constexpr unsigned int MAGIC=0xDEADBEEF;

Sprite::Sprite(Canvas* const canvas, const int width, const int height)
:canvas_(canvas)
,refcount_(0)
,origWidth_(getPower2Of(width))
,origHeight_(getPower2Of(height))
,width_(origWidth_)
,height_(origHeight_)
,texId_(MAGIC)
,locked_(false)
{
	glGenTextures(1, &this->texId_);
	glBindTexture(GL_TEXTURE_2D, this->texId_);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->origWidth(), this->origHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	const GLenum err = glGetError();
	if(err != GL_NO_ERROR){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Failed to transfer texture: %d", err);
	}
}
Sprite::~Sprite()
{
	if(this->texId_ != MAGIC){
		glDeleteTextures(1, &this->texId_);
	}
}

unsigned int Sprite::requestTexture()
{
	return this->texId_;
}

void Sprite::resize(int width, int height)
{
	if(width > this->origWidth() || height > this->origHeight()){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] You can't resize Sprite bigger than original.");
	}
	this->width(width);
	this->height(height);
}

//-----------------------------------------------------------------------------

void Sprite::incref()
{
	this->refcount_++;
}
void Sprite::decref()
{
	this->refcount_--;
	if(this->refcount_ < 0){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Sprite::Handler refcount = %d < 0", this->refcount_);
	}else if(this->refcount_ == 0){
		this->width_ = this->origWidth_;
		this->height_ = this->origHeight_;
		this->canvas()->backSprite(this);
	}
}

Buffer* Sprite::lock()
{
	if(this->locked()){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Sprite already locked!");
	}
	this->locked(true);

	return this->canvas()->queryBuffer(this->origWidth(), this->height());
}
void Sprite::unlock(Buffer* const buffer)
{
	if(!this->locked()){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Sprite already unlocked!");
	}
	this->locked(false);

	{
		glBindTexture(GL_TEXTURE_2D, this->texId_);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0,0, this->origWidth(), this->origHeight(), GL_RGBA, GL_UNSIGNED_BYTE, buffer->data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		const GLenum err = glGetError();
		if(err != GL_NO_ERROR){
			throw logging::Exception(__FILE__, __LINE__, "[BUG] Failed to transfer texture: %d", err);
		}
	}

	this->canvas()->backBuffer(buffer);
}

//-----------------------------------------------------------------------------

Sprite::Handler::Handler()
:gl::Handler<Sprite>(nullptr)
{

}

Sprite::Handler::Handler(Sprite* const obj, int width, int height)
:gl::Handler<Sprite>(obj)
{
	obj->resize(width, height);
}

Sprite::Handler::~Handler()
{
}

//-----------------------------------------------------------------------------

Sprite::Session::Session(Sprite::Handler parent)
:parent_(parent)
{
	this->buffer_ = this->parent_->lock();
}
Sprite::Session::~Session()
{
	this->parent_->unlock(this->buffer_);
}

}}
