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
#include <memory>
#include <tinyxml2.h>
#include "../Layout.h"

namespace chisa {
namespace tk {
namespace layout {
class LayoutFactory;

class EmptyLayout : public Layout {
	CHISA_LAYOUT_SUBKLASS_FINAL(EmptyLayout);
public:
	virtual std::weak_ptr<Layout> getChildAt(const std::size_t index) const override;
	virtual std::size_t getChildCount() const override;
	virtual std::string toString() const override;
private:
	virtual void renderImpl(gl::Canvas& canvas, const geom::Area& screenArea, const geom::Area& area) override;
	virtual geom::Box onMeasure(const geom::Box& constraint) override;
	virtual void onLayout(const geom::Box& size) override;
	virtual void loadXMLimpl(layout::LayoutFactory* const factory, tinyxml2::XMLElement* const element) override;
	virtual std::weak_ptr<Layout> getLayoutByIdImpl(const std::string& id) override;
};

}}}
