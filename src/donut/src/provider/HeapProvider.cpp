/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#include <sstream>
#include <cinamo/String.h>
#include <donut/object/Heap.hpp>
#include <donut/object/Object.hpp>
#include <donut/provider/Provider.hpp>

namespace donut {
using namespace cinamo;

static const std::string TAG("HeapProvider");

HeapProvider::HeapProvider( Handler<Heap> const& heap, std::string const& name )
:Provider(heap, name)
{
	this->registerPureNativeClosure("opEq", [this](Object* self, Object* other) {
		return self == other;
	});
	this->registerPureNativeClosure("opNe", [this](Object* self, Object* other) {
		return self != other;
	});
}

}
