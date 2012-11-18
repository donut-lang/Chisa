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

#include "World.h"
#include "Object.h"
#include "../Exception.h"

namespace chisa {
namespace donut {

const std::string TAG("DonutClosureObject");

DonutClosureObject::DonutClosureObject(World* const world, const Handler<Closure>& clos, const Handler<Object>& scope)
:DonutObject(world, "chisa::donut::DonutClosureObject")
,asm_(clos)
{
	if(scope){
		this->store(world, "__scope__", scope);
	}
}


}}
