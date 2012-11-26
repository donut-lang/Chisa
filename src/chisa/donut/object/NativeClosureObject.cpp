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

#include "NativeObject.h"
#include "../../util/StringUtil.h"
#include "../Exception.h"
#include "Heap.h"

namespace chisa {
namespace donut {
static const std::string TAG("NativeClosureObject");

std::string NativeClosureObject::toStringImpl(const Handler<Heap>& heap) const
{
	return util::format("(NativeClosureObject %p)", this);
}

int NativeClosureObject::toIntImpl(const Handler<Heap>& heap) const
{
	throw DonutException(__FILE__, __LINE__, "Failed to convert NativeClosureObject to int.");
}

float NativeClosureObject::toFloatImpl(const Handler<Heap>& heap) const
{
	throw DonutException(__FILE__, __LINE__, "Failed to convert NativeClosureObject to float.");
}

bool NativeClosureObject::toBoolImpl(const Handler<Heap>& heap) const
{
	throw DonutException(__FILE__, __LINE__, "Failed to convert NativeClosureObject to bool.");
}

bool NativeClosureObject::haveImpl(const Handler<Heap>& heap, const std::string& name) const
{
	return false;
}

bool NativeClosureObject::haveOwnImpl(const Handler<Heap>& heap, const std::string& name) const
{
	return false;
}

Handler<Object> NativeClosureObject::storeImpl(const Handler<Heap>& heap, const std::string& name, Handler<Object> obj)
{
	heap->log().w(TAG, "NativeClosureObject cannot have any property.");
	return obj;
}

Handler<Object> NativeClosureObject::loadImpl(const Handler<Heap>& heap, const std::string& name) const
{
	throw DonutException(__FILE__, __LINE__, "Native Closure does not have any properety.");
}

void NativeClosureObject::seekImpl(const Handler<Heap>& heap, timestamp_t time)
{

}
void NativeClosureObject::discardHistoryImpl(const Handler<Heap>& heap)
{

}

void NativeClosureObject::discardFutureImpl(const Handler<Heap>& heap)
{

}

}}


