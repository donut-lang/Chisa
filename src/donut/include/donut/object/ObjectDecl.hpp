/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <cstdint>
#include <unordered_map>
#include <cinamo/Handler.h>
#include <cinamo/ClassUtil.h>
#include <cinamo/XVal.h>
#include "../Exception.hpp"
#include "Slot.hpp"

namespace donut {
using namespace cinamo;

class Heap;
class ObjectWalker;

/**
 * すべての窓口となるクラス。
 */
class Object : public HandlerBody<Object> {
	DISABLE_COPY_AND_ASSIGN(Object);
public:
	enum Tag{
		TagShift = 2U,
		Mask=3U,
		Obj=0U,
		Int=1U,
		Bool=2U,
		Null=3U
	};
public:
	Object() = default;
	virtual ~Object() noexcept = default;
public: //すべてのオブジェクトに出来なければならないこと
	std::string repr(Handler<Heap> const& heap) const;
	std::string print(Handler<Heap> const& heap) const;
	int toInt(Handler<Heap> const& heap) const;
	float const& toFloat(Handler<Heap> const& heap) const;
	std::string const& toString(Handler<Heap> const& heap) const;
	bool toBool(Handler<Heap> const& heap) const;
	bool has(Handler<Heap> const& heap, std::string const& name) const;
	bool has(Handler<Heap> const& heap, int const& idx) const;
	bool hasOwn(Handler<Heap> const& heap, std::string const& name) const;
	bool hasOwn(Handler<Heap> const& heap, int const& idx) const;
	Handler<Object> set(Handler<Heap> const& heap, std::string const& name, Handler<Object> const& obj);
	Handler<Object> set(Handler<Heap> const& heap, int const& idx, Handler<Object> const& obj);
	Handler<Object> get(Handler<Heap> const& heap, std::string const& name) const;
	Handler<Object> get(Handler<Heap> const& heap, int const& idx) const;
	std::string providerName(Handler<Heap> const& heap) const;
	object_desc_t toDescriptor() const noexcept;
	Handler<NativeClosureObject> tryCastToNativeClosureObject();
	Handler<DonutClosureObject> tryCastToDonutClosureObject();
public:
	inline bool isObject() const noexcept { return Tag::Obj==tag(); };
	inline bool isNull() const noexcept { return Tag::Null==tag(); };
	inline bool isBool() const noexcept { return Tag::Bool==tag(); };
	inline bool isInt() const noexcept { return Tag::Int==tag(); };
	bool isString() const;
	bool isFloat() const;
	inline int tag() const noexcept { return static_cast<int>( reinterpret_cast<std::intptr_t>(this) ) & Tag::Mask; };
	inline void incref( bool check ) const { if(isObject()) { this->HandlerBody<Object>::incref(check); } }
	inline void decref() const { if(isObject()) { this->HandlerBody<Object>::decref(); } };
	inline void mark(Handler<Heap> const& heap, int color) { if(isObject()){ this->markImpl(heap, color); } }
	inline void onBackNotify(Handler<Heap> const& heap){ if(isObject()){ this->onBackNotifyImpl(heap); } };
	inline void onForwardNotify(Handler<Heap> const& heap){ if(isObject()){ this->onForwardNotifyImpl(heap); } };
	inline void onDiscardFutureNotify(Handler<Heap> const& heap){ if(isObject()){ this->onDiscardFutureNotifyImpl(heap); } };
	inline void onDiscardHistoryNotify(Handler<Heap> const& heap){ if(isObject()){ this->onDiscardHistoryNotifyImpl(heap); } };
protected: /* 実装すべきもの */
	virtual std::string reprImpl(Handler<Heap> const& heap) const = 0;
	virtual std::string printImpl(Handler<Heap> const& heap) const = 0;
	virtual Handler<const StringObject> toStringObjectImpl() const;
	virtual Handler<const FloatObject> toFloatObjectImpl() const;
	virtual Handler<NativeClosureObject> tryCastToNativeClosureObjectImpl();
	virtual Handler<DonutClosureObject> tryCastToDonutClosureObjectImpl();
	virtual std::string providerNameImpl(Handler<Heap> const& heap) const = 0;
	virtual bool hasImpl(Handler<Heap> const& heap, std::string const& name) const = 0;
	virtual bool hasOwnImpl(Handler<Heap> const& heap, std::string const& name) const = 0;
	virtual Handler<Object> setImpl(Handler<Heap> const& heap, std::string const& name, Handler<Object> const& obj) = 0;
	virtual Handler<Object> getImpl(Handler<Heap> const& heap, std::string const& name) const = 0;
	virtual void markImpl(Handler<Heap> const& heap, int color) = 0;
	virtual void onBackNotifyImpl(Handler<Heap> const& heap) = 0;
	virtual void onForwardNotifyImpl(Handler<Heap> const& heap) = 0;
	virtual void onDiscardHistoryNotifyImpl(Handler<Heap> const& heap) = 0;
	virtual void onDiscardFutureNotifyImpl(Handler<Heap> const& heap) = 0;
	virtual object_desc_t toDescriptorImpl() const noexcept = 0;
public:
	virtual bool onFree() noexcept = 0; //increfとdecrefの関係で、プリミティブの時にこれが呼ばれることはない
public:
	static inline constexpr bool isPrimitiveDescriptor( object_desc_t const& desc ) noexcept {
		return (desc & Object::Tag::Mask) != Object::Tag::Obj;
	};
	static inline objectid_t decodeObjectId( object_desc_t const& desc ) {
		if(Object::isPrimitiveDescriptor(desc)) {
			DONUT_EXCEPTION(Exception, "[BUG] Decoding primitive descriptor.");
		}
		return desc >> TagShift;
	};
	static inline constexpr object_desc_t encodeObjectId( objectid_t const& id ) {
		return (id << Object::TagShift) | Object::Tag::Obj;
	}
	static inline Object* castToPointer(object_desc_t const& desc) noexcept {
		return reinterpret_cast<Object*>(static_cast<intptr_t>(desc));
	};
	static inline object_desc_t castToDescriptor(Object* const& desc) noexcept {
		return static_cast<object_desc_t>(reinterpret_cast<intptr_t>(desc));
	};
};

}
//---------------------------------------------------------------------------------------------------------------------

namespace donut {
using namespace cinamo;

class HeapObject : public Object {
private:
	HeapProvider* const provider_;
	objectid_t id_;
	bool erased_;
	int color_;
	bool useLocked_;
public:
	HeapObject(HeapProvider* const provider);
	virtual ~HeapObject() noexcept = default;
public:
	inline objectid_t id() const noexcept { return this->id_; }
	virtual object_desc_t toDescriptorImpl() const noexcept override final { return Object::encodeObjectId(this->id_); };
	inline void id(objectid_t const& nid) noexcept { this->id_ = nid; }
public:
	virtual bool onFree() noexcept override { if(this->erased_||this->id_ <= 0){ return false; }else{ return true; } };
	inline void erase() noexcept { this->erased_ = true; if(!used()){ delete this; } };
	int color() noexcept { return this->color_; };
	inline bool used() { return this->refcount() > 0 || useLocked_; };
public:
	inline void useLock() { useLocked_=true; };
	inline void useUnlock() { useLocked_=false; };
	inline void setUseLock( bool inUse ) {useLocked_=inUse;};
public:
	virtual XValue save( Handler<Heap> const& heap ) = 0;
	virtual void load( Handler<Heap> const& heap, XValue const& data ) = 0;
protected:
	void color(const int color) noexcept { this->color_=color; };
	virtual XValue saveImpl( Handler<Heap> const& heap ) = 0;
	virtual void loadImpl( Handler<Heap> const& heap, XValue const& data ) = 0;
protected:
	inline HeapProvider* const& provider() const noexcept { return this->provider_; };
private:
	virtual std::string providerNameImpl(Handler<Heap> const& heap) const override final;
	virtual std::string printImpl(Handler<Heap> const& heap) const override { return reprImpl(heap); };
public:
	struct CompareById : std::binary_function<HeapObject* const&,HeapObject* const&,bool>{
		bool operator()(HeapObject* const& a, HeapObject* const& b){
			return a->id() < b->id();
		}
		bool operator()(HeapObject* const& a, objectid_t const& b){
			return a->id() < b;
		}
		bool operator()(objectid_t const& a, HeapObject* const& b){
			return a < b->id();
		}
	};
};

}
//---------------------------------------------------------------------------------------------------------------------

namespace donut {
using namespace cinamo;
/**
 * ドーナツ言語内でのクロージャやオブジェクトなどのクラス
 */
class DonutObject : public HeapObject {
	friend class DonutProvider;
private:
	std::unordered_map<std::string, Slot> slots_;
public:
	DonutObject(HeapProvider* const provider);
	virtual ~DonutObject() noexcept = default;
protected:
	virtual std::string reprImpl(Handler<Heap> const& heap) const override;
protected:
	virtual bool hasImpl(Handler<Heap> const& heap, std::string const& name) const override;
	virtual bool hasOwnImpl(Handler<Heap> const& heap, std::string const& name) const override;
	virtual Handler<Object> setImpl(Handler<Heap> const& heap, std::string const& name, Handler<Object> const& obj) override;
	virtual Handler<Object> getImpl(Handler<Heap> const& heap, std::string const& name) const override;
	virtual void markImpl(Handler<Heap> const& heap, int color) override;
public: /* time functions */
	virtual void onBackNotifyImpl(Handler<Heap> const& heap) override;
	virtual void onForwardNotifyImpl(Handler<Heap> const& heap) override;
	virtual void onDiscardHistoryNotifyImpl(Handler<Heap> const& heap) override;
	virtual void onDiscardFutureNotifyImpl(Handler<Heap> const& heap) override;
public:
	void bootstrap();
private:
	virtual XValue save( Handler<Heap> const& heap ) override;
	virtual void load( Handler<Heap> const& heap, XValue const& data ) override;
protected:
	virtual XValue saveImpl( Handler<Heap> const& heap ) override { return XValue(); };
	virtual void loadImpl( Handler<Heap> const& heap, XValue const& data ) override {};
};

}

//---------------------------------------------------------------------------------------------------------------------

namespace donut {
using namespace cinamo;

/**
 * StringやDoubleなどの組み込みオブジェクトと、
 * ユーザーの定義するネイティブクラスの元になるクラス
 */
class NativeObject : public HeapObject {
private:
	DonutObject* prototype_;
protected:
	NativeObject(HeapProvider* const provider);
public:
	virtual ~NativeObject() noexcept = default;
protected:
	virtual std::string reprImpl(Handler<Heap> const& heap) const override;
protected:
	virtual bool hasImpl(Handler<Heap> const& heap, std::string const& name) const override;
	virtual bool hasOwnImpl(Handler<Heap> const& heap, std::string const& name) const override;
	virtual Handler<Object> setImpl(Handler<Heap> const& heap, std::string const& name, Handler<Object> const& obj) override;
	virtual Handler<Object> getImpl(Handler<Heap> const& heap, std::string const& name) const override;
	virtual void markImpl(Handler<Heap> const& heap, int color) override;
protected:
	void bootstrap(Handler<Heap> const& heap);
	virtual XValue save( Handler<Heap> const& heap ) override;
	virtual void load( Handler<Heap> const& heap, XValue const& data ) override;
};

}

//---------------------------------------------------------------------------------------------------------------------

namespace donut {
using namespace cinamo;

class NativeClosureObject : public HeapObject {
private:
	std::string const objectProviderName_;
	std::string const closureName_;
public:
	NativeClosureObject(HeapProvider* const provider):HeapObject(provider){};
	virtual ~NativeClosureObject() noexcept = default;
	std::string objectProviderName() const noexcept { return this->objectProviderName_; };
	std::string closureName() const noexcept { return this->closureName_; };
protected:
	virtual std::string reprImpl(Handler<Heap> const& heap) const override = 0;
protected:
	virtual Handler<NativeClosureObject> tryCastToNativeClosureObjectImpl() override final;
	virtual bool hasImpl(Handler<Heap> const& heap, std::string const& name) const override final;
	virtual bool hasOwnImpl(Handler<Heap> const& heap, std::string const& name) const override final;
	virtual Handler<Object> setImpl(Handler<Heap> const& heap, std::string const& name, Handler<Object> const& obj) override final;
	virtual Handler<Object> getImpl(Handler<Heap> const& heap, std::string const& name) const override final;
	virtual void markImpl(Handler<Heap> const& heap, int color) override final;
	virtual void onBackNotifyImpl(Handler<Heap> const& heap) override final;
	virtual void onForwardNotifyImpl(Handler<Heap> const& heap) override final;
	virtual void onDiscardHistoryNotifyImpl(Handler<Heap> const& heap) override final;
	virtual void onDiscardFutureNotifyImpl(Handler<Heap> const& heap) override final;
public:
	virtual Handler<Object> apply(Handler<Heap> const& heap, Handler<Object> const& self, std::vector<Handler<Object> > const& arg) const = 0;
private:
	virtual XValue save( Handler<Heap> const& heap ) override final;
	virtual void load( Handler<Heap> const& heap, XValue const& data ) override final;
protected:
	void bootstrap( std::string const& objectProviderName, std::string const& closureName );
	virtual XValue saveImpl( Handler<Heap> const& heap ) override = 0;
	virtual void loadImpl( Handler<Heap> const& heap, XValue const& data ) override = 0;
};

}
