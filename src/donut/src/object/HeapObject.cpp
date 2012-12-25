/**
 * Donut
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

#include <donut/Exception.h>
#include <donut/object/Heap.h>
#include <donut/object/Object.h>
namespace donut {

HeapObject::HeapObject(HeapProvider* const provider)
:provider_(provider)
,id_(0)
,erased_(0)
,color_(0)
{
}

std::string HeapObject::providerNameImpl(Handler<Heap> const& heap) const
{
	return this->provider_->name();
}

}
