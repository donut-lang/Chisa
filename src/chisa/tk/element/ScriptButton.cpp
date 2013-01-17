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

#include <tinyxml2.h>
#include <tarte/Exception.h>

#include "ScriptButton.h"
#include "../../gl/Canvas.h"
#include "../../gl/DrawableManager.h"
#include "../World.h"

namespace chisa {
namespace tk {

static std::string const TAG("ScriptButton");
const std::string ScriptButton::AttrName::DonutMachineName("donut");

CHISA_ELEMENT_SUBKLASS_CONSTRUCTOR_DEF_DERIVED(ScriptButton, ClickButton)
,donutMachineName_()
,script_(nullptr)
{
	this->addAttribute(AttrName::DonutMachineName, this->donutMachineName_);
}

ScriptButton::~ScriptButton() noexcept
{
}

std::string ScriptButton::toString() const
{
	return ::tarte::format("(ScriptButton text:\"%s\" %p)", this->text().c_str(), this);
}

void ScriptButton::loadXmlImpl(ElementFactory* const factory, tinyxml2::XMLElement* const element)
{
	const char* src = element->GetText();;
	if( src ) {
		Handler<World> world( this->world().lock() );
		if( unlikely(!world) ) {
			TARTE_EXCEPTION(Exception, "[BUG] Oops. World is already dead.");
		}
		this->script_ = world->donut()->parse(src, "Button-Innnter", 0);
	}
}

void ScriptButton::onClick()
{
	if(this->script_){
		if(this->log().d()){
			this->log().d(TAG, "Executing script.");
		}
		Handler<World> world( this->world().lock() );
		if( unlikely(!world) ) {
			TARTE_EXCEPTION(Exception, "[BUG] Oops. World is already dead.");
		}
		Handler<Donut> donut(world->donut());
		Handler<Machine> vm(donut->queryMachine(this->donutMachineName_));
		if(this->log().d()){
			this->log().d(TAG, "Execute script on: %s", this->donutMachineName_.c_str());
		}
		vm->start(this->script_);
	}else{
		if(this->log().d()){
			this->log().d(TAG, "Button script is empty.");
		}
	}
}

}}