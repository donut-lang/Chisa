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
#include "Object.h"
#include <functional>
#include "../native/Bind.h"

namespace chisa {
namespace donut {

class PureNativeClosureObject final : public NativeClosureObject {
public:
	typedef std::function<Handler<Object>(Handler<Heap> const& heap, Handler<Object> const& self, Handler<DonutObject> const& arg)> Signature;
private:
	Signature func_;
public:
	PureNativeClosureObject( std::string const& providerName):NativeClosureObject(providerName){}
	virtual ~PureNativeClosureObject() noexcept {};
	void bootstrap( std::string const& objectProviderName, std::string const& closureName, Signature f );
private:
	virtual util::XValue saveImpl( Handler<Heap> const& heap ) override final;
	virtual void loadImpl( Handler<Heap> const& heap, util::XValue const& data ) override final;
private:
	virtual Handler<Object> apply(Handler<Heap> const& heap, Handler<Object> const& self, Handler<DonutObject> const& arg) override final;
};

class ReactiveNativeClosureObject final : public NativeClosureObject {
public:
	typedef std::function<std::tuple<Handler<Object>, util::XValue>(Handler<Heap> const& heap, Handler<Object> const& self, Handler<DonutObject> const& arg)> Signature;
private:
	Signature func_;
public:
	ReactiveNativeClosureObject( std::string const& providerName):NativeClosureObject(providerName){}
	virtual ~ReactiveNativeClosureObject() noexcept {};
	void bootstrap( std::string const& objectProviderName, std::string const& closureName, Signature f );
private:
	virtual util::XValue saveImpl( Handler<Heap> const& heap ) override final;
	virtual void loadImpl( Handler<Heap> const& heap, util::XValue const& data ) override final;
private:
	virtual Handler<Object> apply(Handler<Heap> const& heap, Handler<Object> const& self, Handler<DonutObject> const& arg) override final;
};

}}