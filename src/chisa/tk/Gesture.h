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
#include <tarte/Handler.h>
#include <tarte/ClassUtil.h>
#include <tarte/Logger.h>
#include "../geom/Vector.h"

namespace chisa {
using namespace tarte;

namespace tk {
class World;
class Element;

class GestureListener {
	DISABLE_COPY_AND_ASSIGN(GestureListener);
public:
	GestureListener() = default;
	virtual ~GestureListener() noexcept = default;
public:
	virtual bool onDownRaw(float const& timeMs, geom::Point const& ptInScreen){return false;};
	virtual bool onUpRaw(float const& timeMs, geom::Point const& ptInScreen){return false;};
	virtual bool onMoveRaw(float const& timeMs, geom::Point const& ptInScreen){return false;};
	virtual bool onSingleTapUp(float const& timeMs, geom::Point const& ptInScreen){return false;};
	virtual bool onFling(float const& timeMs, geom::Point const& start, geom::Point const& end, geom::Velocity const& velocity){return false;};
	virtual bool onScroll(float const& timeMs, geom::Point const& start, geom::Point const& end, geom::Distance const& distance){return false;};
	virtual bool onZoom(float const& timeMs, geom::Point const& center, const float ratio){return false;};
	virtual void onFocusGained(float const& timeMs){};
	virtual void onFocusLost(float const& timeMs){};
	virtual void onTextInput(float const& timeMs, std::string const& text){};
	virtual void onTextEdit(float const& timeMs, std::string const& text, int const start, int const length){};
	// 実装用
	//	virtual bool onDownRaw(float const& timeMs, geom::Point const& ptInScreen) override;
	//	virtual bool onUpRaw(float const& timeMs, geom::Point const& ptInScreen) override;
	//	virtual bool onMoveRaw(float const& timeMs, geom::Point const& ptInScreen) override;
	//	virtual bool onSingleTapUp(float const& timeMs, geom::Point const& ptInScreen) override;
	//	virtual bool onFling(float const& timeMs, geom::Point const& start, geom::Point const& end, geom::Velocity const& velocity) override;
	//	virtual bool onScroll(float const& timeMs, geom::Point const& start, geom::Point const& end, geom::Distance const& distance) override;
	//	virtual bool onZoom(float const& timeMs, geom::Point const& center, const float ratio) override;
	// virtual bool onFocusGained(float const& timeMs) override;
	// virtual bool onFocusLost(float const& timeMs) override;
	// virtual void onTextInput(float const& timeMs, std::string const& text) override;
	// virtual void onTextEdit(float const& timeMs, std::string const& text, int const start, int const length) override;
};

class GestureSession {
	DISABLE_COPY_AND_ASSIGN(GestureSession);
	DEFINE_MEMBER_REF(private, Logger, log)
public:
	GestureSession(Logger& log, const unsigned int pointerIndex, HandlerW<Element> targetElement, geom::Point const& startPoint, const float startTimeMs);
	virtual ~GestureSession();
private:
	//static constexpr float MaxFlingVelocity=4000;
	static constexpr float MinFlingVelocity=500.0f/1000;
private:
	HandlerW<Element> target_;
	std::vector<HandlerW<Element> > elementChain_;
	typedef std::vector<HandlerW<Element> >::iterator ElementIterator;
	const unsigned int pointerIndex_;
	const geom::Point startPoint_;
	const float startTimeMs_;
	geom::Point lastPoint_;
	float lastTimeMs_;
private:
	geom::Distance totalMoved_;
public:
	void onTouchUp(float const& timeMs, geom::Point const& pt);
	void onTouchMove(float const& timeMs, geom::Point const& pt);
	void onScroll(float const& timeMs, float const ratio);
	void onFocusGained(float const& timeMs);
	void onFocusLost(float const& timeMs);
	void onTextInput(float const& timeMs, std::string const& text);
	void onTextEdit(float const& timeMs, std::string const& text, int const& start, int const& length);
private:
	void invokeDownRaw(float const& timeMs, geom::Point const& pt);
	void invokeUpRaw(float const& timeMs, geom::Point const& pt);
	void invokeMoveRaw(float const& timeMs, geom::Point const& pt);
	void invokeFling(float const& timeMs, geom::Point const& start, geom::Point const& end, geom::Velocity const& velocity);
	void invokeScroll(float const& timeMs, geom::Point const& start, geom::Point const& end, geom::Distance const& distance);
	void invokeZoom(float const& timeMs, geom::Point const& center, const float ratio);
	void invokeFocusGained(float const& timeMs);
	void invokeFocusLost(float const& timeMs);
	void invokeTextInput(float const& timeMs, std::string const& text);
	void invokeTextEdit(float const& timeMs, std::string const& text, int const start, int const length);
};

class GestureMediator {
	DISABLE_COPY_AND_ASSIGN(GestureMediator);
	DEFINE_MEMBER_REF(private, Logger, log)
	DEFINE_MEMBER_CONST(private, HandlerW<World>, world)
private:
	static constexpr std::size_t MaxTouxhPoint = 5;
	GestureSession* session_[MaxTouxhPoint];
	GestureSession* lastSession_;
private:
	void releaseSession(float const& timeMs, unsigned int const pointerIndex);
public:
	GestureMediator(Logger& log, const HandlerW<World> world);
	virtual ~GestureMediator();
public:
	void onTouchDown(float const& timeMs, const unsigned int pointerIndex, geom::Point const& screenPoint);
	void onTouchUp(float const& timeMs, const unsigned int pointerIndex, geom::Point const& screenPoint);
	void onTouchMove(float const& timeMs, const unsigned int pointerIndex, geom::Point const& screenPoint);
	void onScroll(float const& timeMs, const float ratio);
	void onTextInput(float const& timeMs, std::string const& text);
	void onTextEdit(float const& timeMs, std::string const& text, int const start, int const length);
};

}}
