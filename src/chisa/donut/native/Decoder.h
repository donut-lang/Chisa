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

#pragma once
#include "../object/Object.h"
#include "../Exception.h"


namespace chisa {
namespace donut {
class Heap;

namespace native {

template <typename T>
T decode(Heap* heap, Handler<chisa::donut::Object> obj);

//-----------------------------------------------------------------------------

template <typename T, bool = IsBaseOf<T, Object>::result >
struct PointerDecoder {
	static T* exec(Heap* heap, Handler<chisa::donut::Object> obj) {
		return decode<T*>( heap, obj );
	}
};

template <typename T>
struct PointerDecoder<T, true> {
	static T* exec(Heap* heap, Handler<chisa::donut::Object> obj)
	{
		return obj.cast<T>().get();
	}
};

//-----------------------------------------------------------------------------

template <typename T, bool = IsBaseOf<T, Object>::result, bool = IsBaseOf<Object, T>::result >
struct HandlerDecoder {
	static Handler<T> exec(Heap* heap, Handler<chisa::donut::Object> obj)
	{
		return decode<Handler<T> >( heap, obj );
	}
};

template <typename T>
struct HandlerDecoder<T, true, false> {
	static Handler<T> exec(Heap* heap, Handler<chisa::donut::Object> obj)
	{
		return obj.cast<T>();
	}
};

template <typename T>
struct HandlerDecoder<T, true, true> {
	static Handler<T> exec(Heap* heap, Handler<chisa::donut::Object> obj)
	{
		return obj;
	}
};

//-----------------------------------------------------------------------------

template <typename T>
struct Decoder {
	static T exec(Heap* heap, Handler<Object> obj)
	{
		return decode<T>(heap, obj);
	}
};

template <typename T>
struct Decoder<T*> {
	static T* exec(Heap* heap, Handler<chisa::donut::Object> obj)
	{
		return PointerDecoder<T>::exec(heap, obj);
	}
};

template <typename T>
struct Decoder< Handler<T> > {
	static Handler<T> exec(Heap* heap, Handler<Object> obj)
	{
		return HandlerDecoder<T>::exec(heap, obj);
	}
};

}}}
