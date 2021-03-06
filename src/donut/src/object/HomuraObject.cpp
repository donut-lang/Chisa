/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#include <cinamo/String.h>
#include <cinamo/XVal.h>
#include <donut/object/Heap.hpp>
#include <donut/object/HomuraObject.hpp>

namespace donut {
using namespace cinamo;

const std::string TAG("HomuraObject");

HomuraObject::HomuraObject(HeapProvider* const provider)
:NativeObject(provider)
{
}

std::string HomuraObject::reprImpl(Handler<Heap> const& heap) const
{
	return format("Homura: %p", this);
}

void HomuraObject::onBackNotifyImpl(Handler<Heap> const& heap)
{

}
void HomuraObject::onForwardNotifyImpl(Handler<Heap> const& heap)
{

}

void HomuraObject::onDiscardHistoryNotifyImpl(Handler<Heap> const& heap)
{

}

void HomuraObject::onDiscardFutureNotifyImpl(Handler<Heap> const& heap)
{

}

void HomuraObject::bootstrap( Handler<Heap> const& heap )
{
	this->NativeObject::bootstrap(heap);
}


bool HomuraObject::hasImpl(Handler<Heap> const& heap, std::string const& name) const
{
	return this->slot_.find(name) != this->slot_.end() ? true : this->NativeObject::hasImpl(heap, name);
}
bool HomuraObject::hasOwnImpl(Handler<Heap> const& heap, std::string const& name) const
{
	return this->slot_.find(name) != this->slot_.end();
}
Handler<Object> HomuraObject::setImpl(Handler<Heap> const& heap, std::string const& name, Handler<Object> const& obj)
{
	this->slot_.update(name, obj.get());
	return obj;
}
Handler<Object> HomuraObject::getImpl(Handler<Heap> const& heap, std::string const& name) const
{
	auto it = this->slot_.find(name);
	return (it != this->slot_.end()) ?
				Handler<Object>::__internal__fromRawPointerWithoutCheck(it->second) :
				this->NativeObject::getImpl(heap, name);
}
void HomuraObject::markImpl(Handler<Heap> const& heap, int color)
{
	NativeObject::markImpl(heap, color);
	for(std::pair<std::string, Object*>& p : this->slot_){
		Object* const& pt = p.second;
		pt->mark(heap, color);
	}
}


/**********************************************************************************
 * save/load
 **********************************************************************************/

XValue HomuraObject::saveImpl( Handler<Heap> const& heap )
{
	Handler<XObject> xobj(new XObject);
	{
		Handler<XObject> xslot(new XObject);
		for(std::pair<std::string, Object*>& p : this->slot_){
			xslot->set(p.first, p.second->toDescriptor());
		}
		xobj->set("slot", xslot);
	}
	return xobj;
}
void HomuraObject::loadImpl( Handler<Heap> const& heap, XValue const& data )
{
	Handler<XObject> xobj(data.as<XObject>());
	for(std::pair<std::string, XValue> const& v : *(xobj->get<XObject>("slot"))){
		slot_.insert(v.first, heap->decodeDescriptor(v.second.as<object_desc_t>()).get());
	}
}

}
