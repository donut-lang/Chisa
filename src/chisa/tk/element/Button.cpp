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

#include "Button.h"
#include <tinyxml2.h>
#include "../../gl/Canvas.h"
#include "../World.h"
#include "../../logging/Exception.h"
#include "../../gl/DrawableManager.h"

namespace chisa {
namespace tk {
namespace element {

const std::string Button::AttrName::Text("text");
const std::string Button::AttrName::ForegroundColor("foreground-color");
const std::string Button::AttrName::BackgroundColor("background-color");
const std::string Button::AttrName::ShadowColor("shadow-color");

CHISA_ELEMENT_SUBKLASS_CONSTRUCTOR_DEF_DERIVED(Button, LeafElement)
,text_()
,textImage_()
,vertical_(false)
,pushedCnt_(0)
{
}

Button::~Button() noexcept
{
}

std::string Button::toString() const
{
	return util::format("(Button text:\"%s\")", this->text_.c_str());
}

void Button::renderImpl(gl::Canvas& canvas, geom::Area const& screenArea, geom::Area const& area)
{
	this->textImage_->draw(canvas, geom::Area(screenArea.point()+this->renderOffset_, area.box()));
}
Handler<gl::TextDrawable> Button::textImage()
{
	if(!this->textImage_){
		if( std::shared_ptr<World> w = this->world().lock()){
			//TODO: 色とか
			if(vertical_){
				this->textImage_ = w->drawableManager()->queryVerticalText(this->text());
			}else{
				this->textImage_ = w->drawableManager()->queryText(this->text());
			}
		}
	}
	return this->textImage_;
}
geom::Box Button::onMeasure(geom::Box const& constraint)
{
	return this->textImage()->size();
}

void Button::onLayout(geom::Box const& size)
{
	//中心になるようにオフセットを設定する。
	this->renderOffset_ = (size-this->textImage_->size())/2;
}

void Button::loadXMLimpl(element::ElementFactory* const factory, tinyxml2::XMLElement* const element)
{
	if(const char* text = element->Attribute(AttrName::Text.c_str())){
		this->text(text);
	}
}

void Button::text(std::string const& text)
{
	this->text_ = text;
	this->textImage_.reset();
}

void Button::onClick()
{

}

bool Button::onDownRaw(const float timeMs, geom::Point const& ptInScreen)
{
	++this->pushedCnt_;
	return false;
}

bool Button::onUpRaw(const float timeMs, geom::Point const& ptInScreen)
{
	--this->pushedCnt_;
	return false;
}


bool Button::onSingleTapUp(const float timeMs, geom::Point const& ptInScreen)
{
	geom::Area a(this->drawnArea().point()+this->renderOffset_, this->textImage()->size());
	if(a.contain(ptInScreen)){
		this->onClick();
	}
	return true;
}

}}}
