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
#include "../Element.h"

namespace chisa {
namespace tk {
namespace element {

class ElementGroup : public Element {
	CHISA_ELEMENT_SUBKLASS_FINAL(ElementGroup);
private:
	std::vector<Handler<Element> > child_;
public:
	inline std::size_t getChildCount() const noexcept { return child_.size(); };
	inline Handler<Element> getChildAt( std::size_t const& idx ) const noexcept { return child_.at(idx); };
	virtual void addChild(Handler<Element> const& h);
	virtual void addChild(std::size_t const& idx, Handler<Element> const& h);
	virtual Handler<Element> removeChild(std::size_t const& idx);
	virtual Handler<Element> removeChild(Handler<Element> const& h);
	virtual Handler<Element> lastChild() const noexcept;
	virtual Handler<Element> frontChild() const noexcept;
	virtual std::size_t bringChildToLast(Handler<Element> const& e);
	virtual std::size_t bringChildToFront(Handler<Element> const& e);
public: /* ツリー操作 */
	virtual Handler<Element> findElementById(std::string const& id) override final;
	virtual Handler<Element> findElementByPoint(geom::Vector const& screenPoint) override final;
public: /* バックグラウンドタスク */
	virtual void idle(const float delta_ms) override;
public: /* 実装メソッド */
	virtual std::string toString() const override;
};


}}}
