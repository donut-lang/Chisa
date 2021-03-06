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

#include <math.h>
#include "DonutHelper.hpp"
#include <donut/object/ReactiveNativeObject.hpp>

namespace donut {
namespace {

class SampleProvider;
class SampleObject : public ReactiveNativeObjectBaseT<SampleObject, SampleProvider> {
public:
	bool futureDiscarded;
	bool historyDiscarded;
	bool backable_but_non_fowardable;
	int backable_and_forwardable;
	int backable_only_once;
	SampleObject(HeapProvider* const provider)
	:Super(provider)
	,futureDiscarded(false)
	,historyDiscarded(false)
	,backable_but_non_fowardable(false)
	,backable_and_forwardable(0)
	,backable_only_once(0)
	{}
public:
	void bootstrap(Handler<Heap> const& heap){
		this->Super::bootstrap(heap);
	}
public:
	Maybe<XValue> onBack(Handler<Heap> const& heap, XValue const& val)
	{
		std::string v(val.as<std::string>());
		if(v == "backable_but_non_fowardable"){
			backable_but_non_fowardable = true;
			return Nothing<XValue>();
		}else if(v == "backable_and_forwardable"){
			++backable_and_forwardable;
			return Just<XValue>(XValue("backable_and_forwardable"));
		}else if(v == "backable_only_once") {
			return Just<XValue>(XValue("backable_only_once"));
		}
		return Just<XValue>(XValue(2));
	}
	Maybe<XValue> onForward(Handler<Heap> const& heap, XValue const& val)
	{
		std::string v(val.as<std::string>());
		if(v == "backable_and_forwardable"){
			++backable_and_forwardable;
			return Just<XValue>(XValue("backable_and_forwardable"));
		}else if(v == "backable_only_once"){
			return Nothing<XValue>();//non-backwardable
		}
		return Just<XValue>(XValue(1));
	}
	void onFutureDiscarded(Handler<Heap> const& heap) {
		this->futureDiscarded = true;
	}
	void onHistoryDiscarded(Handler<Heap> const& heap) {
		this->historyDiscarded = true;
	}
	virtual XValue saveImpl( Handler<Heap> const& heap ) override {
		return XValue();
	}
	virtual void loadImpl( Handler<Heap> const& heap, XValue const& data ) override {

	}
};
class SampleProvider : public ReactiveProviderBaseT<SampleProvider, SampleObject, XValue>{
public:
	SampleProvider(Handler<Heap> const& heap ):Super(heap, "SampleObject"){
		this->registerReactiveNativeClosure("unrecoverable", std::function<std::tuple<std::string,Maybe<XValue> >(SampleObject*)>([](SampleObject* obj){
			return std::tuple<std::string, Maybe<XValue> >("hey!", Nothing<XValue>());
		}));
		this->registerReactiveNativeClosure("backable_but_non_fowardable", std::function<std::tuple<std::string,Maybe<XValue> >(SampleObject*)>([](SampleObject* obj){
			return std::tuple<std::string, Maybe<XValue> >("hey!", Just<XValue>(XValue("backable_but_non_fowardable")));
		}));
		this->registerReactiveNativeClosure("backable_and_forwardable", std::function<std::tuple<std::string,Maybe<XValue> >(SampleObject*)>([](SampleObject* obj){
			return std::tuple<std::string, Maybe<XValue> >("hey!", Just<XValue>(XValue("backable_and_forwardable")));
		}));
		this->registerReactiveNativeClosure("backable_only_once", std::function<std::tuple<std::string,Maybe<XValue> >(SampleObject*)>([](SampleObject* obj){
			return std::tuple<std::string, Maybe<XValue> >("hey!", Just<XValue>(XValue("backable_only_once")));
		}));
	}
};

class ReactiveObjectTest : public ::testing::Test
{
protected:
	Handler<Donut> donut;
	Handler<Clock> clock;
	Handler<Heap> heap;
	Handler<Machine> machine;
protected:
	Handler<SampleProvider> provider;
public:
	void SetUp(){
		init();
		boot();
	}
	void init(){
		donut.reset();
		machine.reset();
		clock.reset();
		heap.reset();
		provider.reset();
		donut = Handler<Donut>(new Donut(log_trace));
		machine = donut->queryMachine();
		clock = donut->clock();
		heap = donut->heap();

		provider = Handler<SampleProvider>(new SampleProvider(heap));
		heap->registerProvider(provider);
	}
	void boot(){
		donut->bootstrap();
	}
	void reload(XValue const& v){
		init();
		donut->load(v);
	}
	void TearDown(){
	}
};
TEST_F(ReactiveObjectTest, RegisterTest)
{
	Handler<SampleObject> obj( provider->newInstance(heap) );
	heap->setGlobalObject("sample", obj);
	ASSERT_TRUE( heap->hasGlobalObject("sample") );
	ASSERT_TRUE( heap->getGlobalObject("sample")->isObject() );
	Handler<Object> result = machine->start( donut->parse("sample.unrecoverable();") );
	ASSERT_TRUE(result->isObject());
	ASSERT_EQ("hey!", result->toString(heap));
}


TEST_F(ReactiveObjectTest, UnrecoverableTest)
{
	Handler<SampleObject> obj( provider->newInstance(heap) );
	heap->setGlobalObject("sample", obj);
	Handler<Object> result = machine->start( donut->parse("sample.unrecoverable();") );
	ASSERT_EQ( donut->nowTime(), donut->firstTime() );
	ASSERT_FALSE( obj->futureDiscarded );
	ASSERT_TRUE( obj->historyDiscarded );
}

TEST_F(ReactiveObjectTest, SaveLoadTest)
{
	heap->setGlobalObject("sample", provider->newInstance(heap));

	reload(donut->save());
	Handler<SampleObject> obj( heap->getGlobalObject("sample").cast<SampleObject>() );

	Handler<Object> result = machine->start( donut->parse("sample.unrecoverable();") );
	ASSERT_EQ( donut->nowTime(), donut->firstTime() );
	ASSERT_FALSE( obj->futureDiscarded );
	ASSERT_TRUE( obj->historyDiscarded );

	reload(donut->save());
}

TEST_F(ReactiveObjectTest, BackTest)
{
	Handler<SampleObject> obj( provider->newInstance(heap) );
	heap->setGlobalObject("sample", obj);
	unsigned int const t1 = donut->nowTime();
	Handler<Object> result = machine->start( donut->parse("sample.backable_but_non_fowardable();") );
	{ //結果と副作用の確認
		ASSERT_TRUE(result->isObject());
		ASSERT_EQ("hey!", result->toString(heap));
		ASSERT_LT( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_FALSE( obj->futureDiscarded );
		ASSERT_FALSE( obj->historyDiscarded );
	}
	//シーク
	ASSERT_FALSE( obj->backable_but_non_fowardable );
	donut->seek(t1);
	ASSERT_TRUE( obj->backable_but_non_fowardable ); //副作用の確認
	{//戻れるけど、先には進めない。
		ASSERT_EQ( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_EQ( t1, donut->lastTime() );
	}
}

TEST_F(ReactiveObjectTest, BackAndForwardTest)
{
	Handler<SampleObject> obj( provider->newInstance(heap) );
	heap->setGlobalObject("sample", obj);
	unsigned int const t1 = donut->nowTime();
	ASSERT_EQ(0, obj->backable_and_forwardable);
	Handler<Object> result = machine->start( donut->parse("sample.backable_and_forwardable();") );
	ASSERT_EQ(0, obj->backable_and_forwardable);
	unsigned int const t2 = donut->nowTime();
	{ //結果と副作用の確認
		ASSERT_LT( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_FALSE( obj->futureDiscarded );
		ASSERT_FALSE( obj->historyDiscarded );
	}
	//シーク
	ASSERT_EQ(0, obj->backable_and_forwardable);
	donut->seek(t1);
	{//戻れるし、先に進める
		ASSERT_EQ(1, obj->backable_and_forwardable);
		ASSERT_EQ( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_EQ( t2, donut->lastTime() );
	}
	donut->seek(t2);
	{//戻れるし、先に進める
		ASSERT_EQ(2, obj->backable_and_forwardable);
		ASSERT_EQ( t2, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_EQ( t2, donut->lastTime() );
	}
	donut->seek(t1);
	{//戻れるし、先に進める
		ASSERT_EQ(3, obj->backable_and_forwardable);
		ASSERT_EQ( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_EQ( t2, donut->lastTime() );
	}
	//打ち消しは起こらない。
	ASSERT_FALSE( obj->futureDiscarded );
	ASSERT_FALSE( obj->historyDiscarded );
}

TEST_F(ReactiveObjectTest, CombinedTest)
{
	Handler<SampleObject> obj( provider->newInstance(heap) );
	heap->setGlobalObject("sample", obj);
	unsigned int const t1 = donut->nowTime();
	ASSERT_EQ(0, obj->backable_and_forwardable);
	Handler<Object> result = machine->start( donut->parse("sample.backable_but_non_fowardable();sample.backable_and_forwardable();") );
	ASSERT_EQ(0, obj->backable_and_forwardable);
	{ //結果と副作用の確認
		ASSERT_LT( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_FALSE( obj->futureDiscarded );
		ASSERT_FALSE( obj->historyDiscarded );
	}
	//シーク
	ASSERT_EQ(0, obj->backable_and_forwardable);
	ASSERT_FALSE( obj->backable_but_non_fowardable );
	donut->seek(t1);
	ASSERT_TRUE( obj->backable_but_non_fowardable ); //副作用の確認
	ASSERT_EQ(1, obj->backable_and_forwardable);
	{//戻れるけど、先には進めない。
		ASSERT_EQ( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_EQ( t1, donut->lastTime() );
	}
	//未来の打ち消しが起こる
	ASSERT_TRUE( obj->futureDiscarded );
	ASSERT_FALSE( obj->historyDiscarded );
}

TEST_F(ReactiveObjectTest, BackableOnlyOnceTest)
{
	Handler<SampleObject> obj( provider->newInstance(heap) );
	heap->setGlobalObject("sample", obj);
	unsigned int const t1 = donut->nowTime();
	Handler<Object> result = machine->start( donut->parse("sample.backable_only_once();") );
	unsigned int const t2 = donut->nowTime();
	{ //結果と副作用の確認
		ASSERT_LT( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_FALSE( obj->futureDiscarded );
		ASSERT_FALSE( obj->historyDiscarded );
	}
	//シーク
	donut->seek(t1);
	{//戻れる
		ASSERT_EQ( t1, donut->nowTime() );
		ASSERT_EQ( t1, donut->firstTime());
		ASSERT_EQ( t2, donut->lastTime() );
		ASSERT_FALSE( obj->futureDiscarded );
		ASSERT_FALSE( obj->historyDiscarded );
	}
	donut->seek(t2);
	{//先に進める
		ASSERT_EQ( t2, donut->nowTime() );
		ASSERT_EQ( t2, donut->firstTime()); //もう戻れなくなる
		ASSERT_EQ( t2, donut->lastTime() );
		ASSERT_FALSE( obj->futureDiscarded );
		ASSERT_TRUE( obj->historyDiscarded );
	}
	ASSERT_ANY_THROW(donut->seek(t1)); //しかし、戻れない
	{
		ASSERT_EQ( t2, donut->nowTime() );
		ASSERT_EQ( t2, donut->firstTime());
		ASSERT_EQ( t2, donut->lastTime() );
	}
	//往復するとDiscardされる
	ASSERT_FALSE( obj->futureDiscarded );
	ASSERT_TRUE( obj->historyDiscarded );
}

}}
