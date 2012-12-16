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

#include "Vector.h"
#include "Area.h"
#include "../util/XArchiver.h"

namespace chisa {
namespace util {

using namespace chisa::geom;
template <>
void XSerializer<Area>::deserialize(Area& val, XValue const& xval)
{
	Handler<XObject> obj(xval.as<XObject>());
	val.x(obj->get<decltype(val.x())>("x"));
	val.y(obj->get<decltype(val.y())>("y"));
	val.width(obj->get<decltype(val.width())>("width"));
	val.height(obj->get<decltype(val.height())>("height"));
}
template <>
XValue XSerializer<Area>::serialize(Area& val)
{
	Handler<XObject> obj(new XObject);
	obj->set("x", val.x());
	obj->set("y", val.y());
	obj->set("width", val.width());
	obj->set("height", val.height());
	return obj;
}

template <>
XValue XSerializer<Vector>::serialize(Vector& val)
{
	Handler<XObject> obj(new XObject);
	obj->set("x", val.x());
	obj->set("y", val.y());
	return obj;
}

template <>
void XSerializer<Vector>::deserialize(Vector& val, XValue const& xval)
{
	Handler<XObject> obj(xval.as<XObject>());
	val.x(obj->get<decltype(val.x())>("x"));
	val.y(obj->get<decltype(val.y())>("y"));
}

template <>
XValue XSerializer<IntVector>::serialize(IntVector& val)
{
	Handler<XObject> obj(new XObject);
	obj->set("x", val.x());
	obj->set("y", val.y());
	return obj;
}

template <>
void XSerializer<IntVector>::deserialize(IntVector& val, XValue const& xval)
{
	Handler<XObject> obj(xval.as<XObject>());
	val.x(obj->get<decltype(val.x())>("x"));
	val.y(obj->get<decltype(val.y())>("y"));
}

template <>
void XSerializer<Space>::deserialize(Space& val, XValue const& xval)
{
	Handler<XObject> obj(xval.as<XObject>());
	val.top(obj->get<decltype(val.top())>("top"));
	val.left(obj->get<decltype(val.left())>("left"));
	val.right(obj->get<decltype(val.right())>("right"));
	val.bottom(obj->get<decltype(val.bottom())>("bottom"));
}

template <>
XValue XSerializer<Space>::serialize(Space& val)
{
	Handler<XObject> obj(new XObject);
	obj->set("right", val.right());
	obj->set("left", val.left());
	obj->set("top", val.top());
	obj->set("bottom", val.bottom());
	return obj;
}

}}


