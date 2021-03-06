/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#include <algorithm>
#include <cinamo/PairFunctor.h>
#include <cinamo/String.h>
#include <donut/Clock.hpp>
#include <donut/object/Heap.hpp>
#include <donut/object/ReactiveNativeObject.hpp>

namespace donut {

const std::string TAG("ReactiveNativeObject");

std::string ReactiveNativeObject::reprImpl(Handler<Heap> const& heap) const {
	return format("(ReactiveNativeObject for \"%s\" %p)", this->provider()->name().c_str(), this);
}

}
