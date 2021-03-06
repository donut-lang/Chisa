/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <vector>
#include "../object/Object.hpp"
#include "../object/Heap.hpp"
#include "../source/Source.hpp"

namespace donut {
typedef unsigned int pc_t;

/**
 * クロージャの実行状態
 */
struct Callchain final {
public: /* 値 */
	pc_t pc_; // Program counter
	unsigned int stackBase_; //戻るときはスタックをこの位置まで元に戻してね。
	Handler<Object> self_; //このクロージャのselfは何か？
	Handler<DonutClosureObject> closure_; //クロージャの実行コード本体
	Handler<DonutObject> local_; //ローカル変数の格納されるオブジェクト
public: /* 作成・破棄・セーブ */
	Callchain(pc_t pc, unsigned int const& stackBase, Handler<Object> const& self, Handler<DonutClosureObject> const& closure, Handler<DonutObject> const& scope)
	:pc_(pc), stackBase_(stackBase), self_(self), closure_(closure), local_(scope){
	}
	Callchain(Handler<Heap> const& heap, XValue const& data);
	XValue save();
};

/**
 * 機械の実行状態。
 * 命令実行とは、このコンテキストの状態が変化していくこと
 */
struct Context final {
public: /* 値 */
	unsigned int time_;
	Handler<Object> interrupt_;
	std::vector<Handler<Object> > stack_;
	std::vector<Callchain> callStack_;
public:
	enum State : unsigned int{

	};
public: /* 作成・破棄・セーブ */
	Context(Handler<Clock> const& clk);
	Context(Handler<Clock> const& clk, Context const& other);
	Context(Handler<Heap> const& heap, XValue const& data);
	~Context() noexcept = default;
	XValue save();
public:
	struct CompareByTime : std::binary_function<Context const&, Context const&, bool> {
		bool operator()(Context const& a, Context const& b) const noexcept
		{
			return a.time_ < b.time_;
		}
	};
};

class Machine final : public HandlerBody<Machine> {
	DEFINE_MEMBER_REF(private, Logger, log);
private: /* 何があっても不変なもの。*/
	Handler<Clock> const& clock_;
	Handler<Heap> const heap_;
private: /* 時とともに変わっていくもの */
	std::vector<Context> contextRevs_;
private: /* 実行時の一時的な変数 */
	bool running_;
	class RunLock{
		Machine* const m;
	public:
		inline RunLock(Machine* m)
		:m(m) {
			if(m->running_){
				DONUT_EXCEPTION(Exception, "[BUG] Oops. Already running!");
			}
			m->running_= true;
		}
		inline ~RunLock() {
			if(!m->running_){
				DONUT_EXCEPTION(Exception, "[BUG] Oops. Already unlocked!!");
			}
			m->running_ = false;
		}
	};
	inline bool running() const noexcept { return this->running_; };
private: /* 最新のコンテキストへのアクセサ */
	inline Handler<Object> const& self();
	inline Handler<DonutObject> const& local();
	inline Handler<DonutClosureObject> const& closureObject();
	inline Handler<Source> const& src();
	inline Handler<Closure> const& closure();
	inline std::vector<Handler<Object> >& stack();
	inline unsigned int stackBase();
	inline std::vector<Callchain>& callStack();
	inline pc_t& pc();
	inline void pushStack( Handler<Object> const& obj );
	inline Handler<Object> popStack();
	inline Handler<Object> topStack();
private:
	Handler<Object> const& interrupt() const noexcept;
	void interrupt(Handler<Object> const& obj);
	void releaseInterrupt();
	bool isInterruptedNow() const noexcept;
private:
	int findRevisionIndex(timestamp_t const& t) const;
public: /* 生成 */
	Machine(Logger& log, Handler<Clock> const& clock, Handler<Heap> const& heap);
	virtual ~Machine() noexcept = default;
	bool onFree() noexcept { return false; };
public: /* 外部からの実行指示 */
	Handler<Object> start( Handler<Source> const& src );
	Handler<Object> restart();
	Handler<Object> resume( Handler<Object> const& obj );
	bool isInterrupted() const noexcept;
	bool isCallstackEmpty() const noexcept;
private: /* 実行 */
	void enterClosure(Handler<Object> const& self, Handler<DonutClosureObject> const& clos, std::vector<Handler<Object> > const& args);
	bool leaveClosure();
	bool fetchPC( Instruction& inst );
	Handler<Object> run();
public: /* 処理系の保存・復帰をします。 */
	void bootstrap();
	XValue save();
	void load( XValue const& data);
public: /* 時間操作 */
	void onTickNotify();
	void onBackNotify();
	void onForwardNotify();
	void onDiscardFutureNotify();
	void onDiscardHistoryNotify();
};

}

#include "MachineImpl.hpp"
