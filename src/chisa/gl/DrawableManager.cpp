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

#include "DrawableManager.h"

namespace chisa {
namespace gl {

DrawableManager::DrawableManager(logging::Logger& log)
:log_(log)
{
	this->factories_.insert(std::make_pair("stretch:", StretchDrawable::create));
	this->factories_.insert(std::make_pair("repeat:", RepeatDrawable::create));
	this->factories_.insert(std::make_pair("image:", ImageDrawable::create));
	this->factories_.insert(std::make_pair("color:", ColorDrawable::create));
	this->factories_.insert(std::make_pair("none:", NullDrawable::create));
}

Handler<Sprite> DrawableManager::queryRawSprite(const int width, const int height)
{
	return this->spriteManager_->queryRawSprite(width, height);
}

Handler<Sprite> DrawableManager::queryImage(const std::string& filename)
{
	return this->imageManager_->queryImage(filename);
}

Handler<Drawable> DrawableManager::queryDrawable(const std::string& repl, const geom::Box& box)
{
	for(std::pair<std::string, constructor> p : this->factories_){
		if(util::startsWith(repl, p.first)){
			std::string const left = repl.substr(p.first.size());
			return p.second(this->self(), box, left);
		}
	}
	this->log().w("DrawableFactory", "oops. Invalid repl: %s", repl.c_str());
	return NullDrawable::create(this->self(), box, repl);
}

Handler<Font> DrawableManager::queryFont(const std::string& name)
{
	return this->fontManager_->queryFont(name);
}

Handler<TextDrawable> DrawableManager::queryText(const std::string& str, const float size, Handler<Font> font, TextDrawable::Style style, TextDrawable::Decoration deco, const gl::Color& color, const gl::Color& backColor)
{
	return TextDrawable::create(this->self(), str, false, size, font, style, deco, color, backColor);
}

Handler<TextDrawable> DrawableManager::queryVerticalText(const std::string& str, const float size, Handler<Font> font, TextDrawable::Style style, TextDrawable::Decoration deco, const gl::Color& color, const gl::Color& backColor)
{
	return TextDrawable::create(this->self(), str, true, size, font, style, deco, color, backColor);
}

}}