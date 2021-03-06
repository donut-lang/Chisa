/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <cinamo/functional/Maybe.h>
#include <cinamo/XArchiver.h>
#include "ObjectDecl.hpp"

namespace donut {

class ReactionRecord {
	DISABLE_COPY_AND_ASSIGN(ReactionRecord);
protected:
	ReactionRecord() noexcept = default;
	virtual ~ReactionRecord() noexcept = default;
};
class ReactiveNativeObject : public NativeObject {
protected:
	ReactiveNativeObject(HeapProvider* const provider):NativeObject(provider){}
	virtual ~ReactiveNativeObject() noexcept = default;
protected:
	std::string reprImpl(Handler<Heap> const& heap) const override;
public:
	virtual ReactionRecord* reactionRecorde() = 0;
};

template <typename __AntiSideEffect>
class ReactionRecordT : public ReactionRecord {
protected:
	ReactionRecordT() noexcept = default;
	virtual ~ReactionRecordT() noexcept = default;
public:
	virtual void registerReaction( Handler<HeapObject> const& obj, timestamp_t time, __AntiSideEffect const& v ) = 0;
};

template <typename __AntiSideEffect, typename _Self>
class ReactiveNativeObjectAspectT final : public ReactionRecordT<__AntiSideEffect>{
private:
	std::vector<std::pair<timestamp_t, __AntiSideEffect> > reactions_;
	int index_; //次に順方向で挿入されるべきインデックスを示す。0なら戻るものがないのを示す。
public:
	typedef Maybe<__AntiSideEffect> ResultType;
	ReactiveNativeObjectAspectT():index_(0){};
	virtual ~ReactiveNativeObjectAspectT() noexcept = default;
private:
	int inline findUpperIndex( timestamp_t const& t );
	int findLowerIndex( timestamp_t const& t );
public:
	inline void onBackNotify(_Self& self, Handler<Heap> const& heap);
	inline void onForwardNotify(_Self& self, Handler<Heap> const& heap);
	inline void onDiscardHistoryNotify(_Self& self, Handler<Heap> const& heap);
	inline void onDiscardFutureNotify(_Self& self, Handler<Heap> const& heap);
public:
	virtual void registerReaction( Handler<HeapObject> const& obj, timestamp_t time, __AntiSideEffect const& v ) override final;
public:
	XValue save();
	void load(XValue const& data );
};

#define INJECT_REACTIVE_OBJECT_ASPECT(__AntiSideEffect__, __Self__) \
public:\
	typedef __AntiSideEffect__ AntiSideEffect;\
	typedef typename ReactiveNativeObjectAspectT<__AntiSideEffect__, __Self__>::ResultType ResultType;\
private:\
	friend class ReactiveNativeObjectAspectT<__AntiSideEffect__, __Self__>;\
	ReactiveNativeObjectAspectT<__AntiSideEffect__, __Self__> __reactive_aspect__;\
private:\
	virtual ReactionRecord* reactionRecorde() override final{\
		return &this->__reactive_aspect__;\
	}\
	virtual XValue save( Handler<Heap> const& heap ) override final {\
		Handler<XObject> top(new XObject);\
		top->set("base", this->NativeObject::save(heap));\
		top->set("reactions", __reactive_aspect__.save());\
		top->set("impl", this->saveImpl(heap));\
		return top;\
	}\
	virtual void load( Handler<Heap> const& heap, XValue const& data ) override final {\
		Handler<XObject> top(data.as<XObject>());\
		this->NativeObject::load(heap, top->get<XValue>("base"));\
		this->__reactive_aspect__.load(top->get<XValue>("reactions"));\
		this->loadImpl(heap, top->get<XValue>("impl"));\
	}\
	virtual void onBackNotifyImpl(Handler<Heap> const& heap) override final {\
		this->__reactive_aspect__.onBackNotify(static_cast<__Self__&>(*this), heap);\
	}\
	virtual void onForwardNotifyImpl(Handler<Heap> const& heap) override final {\
		this->__reactive_aspect__.onForwardNotify(static_cast<__Self__&>(*this), heap);\
	}\
	virtual void onDiscardHistoryNotifyImpl(Handler<Heap> const& heap) override final {\
		this->__reactive_aspect__.onDiscardHistoryNotify(static_cast<__Self__&>(*this), heap);\
	}\
	virtual void onDiscardFutureNotifyImpl(Handler<Heap> const& heap) override final {\
		this->__reactive_aspect__.onDiscardFutureNotify(static_cast<__Self__&>(*this), heap);\
	}
//public;
	//void onFutureDiscarded(Handler<Heap> const& heap);
	//void onHistoryDiscarded(Handler<Heap> const& heap);
	//ResultType onBack(Handler<Heap> const& heap, AntiSideEffect const& val);
	//ResultType onForward(Handler<Heap> const& heap, AntiSideEffect const& val);
	//XValue saveImpl( Handler<Heap> const& heap ) override final;
	//void loadImpl( Handler<Heap> const& heap, XValue const& data ) override final;

template <typename __Derived, typename __Provider, typename __AntiSideEffect=XValue>
class ReactiveNativeObjectBaseT : public ReactiveNativeObject {
	typedef ReactiveNativeObjectBaseT<__Derived, __Provider, __AntiSideEffect> __Self__;
	INJECT_REACTIVE_OBJECT_ASPECT(__AntiSideEffect, __Derived);
	//static_assert(std::is_same<__AntiSideEffect, typename __Provider::AntiSideEffect>::value, "Oops. AntiSideEffect of provider and object must be the same.");
protected:
	typedef ReactiveNativeObjectBaseT<__Derived, __Provider, __AntiSideEffect> Super;
	ReactiveNativeObjectBaseT(HeapProvider* const provider)
	:ReactiveNativeObject(provider){}
	virtual ~ReactiveNativeObjectBaseT() noexcept = default;
};
}
