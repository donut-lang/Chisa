/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <vector>
#include <algorithm>
#include <cinamo/Handler.h>
#include <cinamo/XVal.h>

#include "../Decl.hpp"
#include "../Exception.hpp"
#include "Closure.hpp"
#include "Inst.hpp"

namespace donut {
using namespace cinamo;

template <typename T>
class ConstTable final {
private:
	std::vector<T> table_;
	ConstTable(ConstTable const& other) = delete;
	ConstTable(ConstTable&& other) = delete;
	ConstTable& operator=(ConstTable const& other) = delete;
	ConstTable& operator=(ConstTable&& other) = delete;
public:
	ConstTable() {
		bootstrap();
	}
	void bootstrap() {
		this->table_.clear();
	}
	void load(XValue const& data) {
		for(XValue& v : *(data.as<XArray>())){
			table_.push_back(v.as<T>());
		}
	}
	XValue save() {
		Handler<XArray> top(new XArray);
		for(auto it : table_){
			top->append(it);
		}
		return top;
	}
	Instruction regist( T const& val ) {
		auto it = std::find(table_.begin(), table_.end(), val);
		if(it == table_.end()){
			table_.push_back(val);
			return table_.size()-1;
		}else{
			unsigned int idx = it-table_.begin();
			return idx;
		}
	}
	T get(std::size_t index) const
	{
		if(index >= table_.size()){
			DONUT_EXCEPTION(Exception, "Unknown const index: %d", index);
		}
		return table_.at(index);
	}
	std::size_t size() const
	{
		return this->table_.size();
	}
	bool operator==( ConstTable<T> const& other ) const noexcept{
		return table_ == other.table_;
	}
	bool operator!=( ConstTable<T> const& other ) const noexcept{
		return !operator ==(other);
	}
};

//この2つだけ特殊なので別扱い
template<> void ConstTable<Handler<Closure> >::load(XValue const& data);
template<> XValue ConstTable<Handler<Closure> >::save();
template<> bool ConstTable<Handler<Closure> >::operator==( ConstTable<Handler<Closure> > const& other ) const noexcept;

class Source final : public HandlerBody<Source> {
private:
	int id_;
	HandlerW<Heap> heap_;
private:
	ConstTable<int> intTable_;
	ConstTable<float> floatTable_;
	ConstTable<std::string> stringTable_;
	ConstTable<Handler<Closure> > closureTable_;
	int entrypoint_id_;
private:
	Source(Source const& other) = delete;
	Source(Source&& other) = delete;
	Source& operator=(Source const& other) = delete;
	Source& operator=(Source&& other) = delete;
public:
	Source(int id = -1);
	Source(XValue const& data);
	XValue save();
	virtual ~Source() noexcept = default;
	int id() const noexcept{ return this->id_; };
public:
	void onRegisterToHeap(Heap* const& heap, int const& id) noexcept;
	bool onFree() noexcept;
	template <typename T> Instruction constCode(T const& val);
	inline bool used() const noexcept{ return this->refcount() > 0; };
public:
	std::string disasm( Instruction inst );
	static inline void disasm( Instruction inst, Instruction& opcode, Instruction& constKind, int& constIndex ) {
		opcode = inst & Inst::OpcodeMask;
		constKind = inst & Inst::ConstKindMask;
		constIndex = inst & 0xffff;
		if(constIndex >= 0x8000) {
			constIndex -= 0x10000;
		}
	}
public:
	bool operator==( Source const& other ) const noexcept{
		return
				intTable_ == other.intTable_ &&
				floatTable_ == other.floatTable_ &&
				stringTable_ == other.stringTable_ &&
				closureTable_ == other.closureTable_ &&
				entrypoint_id_ == other.entrypoint_id_;
	}
	bool operator!=( Source const& other ) const noexcept{
		return !operator==(other);
	}
public:
	inline bool getBool(const unsigned int& idx) const noexcept{
		return (idx & 0xffff) == 0 ? false : true;
	}
	inline std::size_t numBool() const noexcept{
		return 2;
	}
	inline int getInt(const unsigned int& idx) const noexcept{
		return intTable_.get(idx & 0xffff);
	}
	inline std::size_t numInt() const noexcept{
		return intTable_.size();
	}
	inline float getFloat(const unsigned int& idx){
		return floatTable_.get(idx & 0xffff);
	}
	inline std::size_t numFloat() const noexcept{
		return floatTable_.size();
	}
	inline std::string getString(const unsigned int& idx){
		return stringTable_.get(idx & 0xffff);
	}
	inline std::size_t numString() const noexcept {
		return stringTable_.size();
	}
	inline Handler<Closure> getClosure(const unsigned int& index) {
		return this->closureTable_.get(index & 0xffff);
	}
	inline std::size_t numClosure() const noexcept
	{
		return this->closureTable_.size();
	}
	inline Handler<Closure> getEntrypoint()
	{
		if( this->entrypoint_id_ == -1 ){
			DONUT_EXCEPTION(Exception, "[BUG] Entrypoint ID is not set.");
		}
		return this->getClosure( this->entrypoint_id_ );
	}
	inline void setEntrypointID( unsigned int id ) noexcept
	{
		this->entrypoint_id_ = id;
	}
	inline unsigned int getEntrypointID() const noexcept
	{
		return this->entrypoint_id_;
	}
public:
	struct CompareById : std::binary_function<Source* const&,Source* const&,bool> {
		bool operator()(Source* const& a, Source* const& b) {
			return a->id() < b->id();
		}
		bool operator()(Source* const& a, int const& b) {
			return a->id() < b;
		}
		bool operator()(int const& a, Source* const& b) {
			return a < b->id();
		}
	};
};

}
