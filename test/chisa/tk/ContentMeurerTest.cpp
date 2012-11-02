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

#include "../../TestCommon.h"
#include "../../src/chisa/tk/widget/Content/NodeReader.h"
#include "../../src/chisa/tk/widget/Content/Node.h"
#include "../../src/chisa/tk/widget/ContentRender/RenderCommand.h"
#include "../../src/chisa/tk/widget/ContentRender/RenderContext.h"
#include "../../src/chisa/tk/widget/ContentMeasure/ContentMeasurer.h"
#include <tinyxml2.h>
#include <typeinfo>

namespace chisa {
namespace tk {
namespace widget {

TEST(ContentMeasurerTest, TextWrapTest)
{
	auto docTree = parse(R"delimiter(
<?xml version="1.0" encoding="UTF-8"?>
<doc>Kitty on your lap.</doc>
)delimiter");
	NodeReader reader;
	Handler<gl::FontManager> fontManager( new gl::FontManager(log_trace, MATERIAL_DIR"/font") );
	std::shared_ptr<Document> doc = reader.parseTree(docTree->RootElement());
	RenderContext context(log_err);
	ContentMeasurer(log_trace, fontManager, context, 1000).start(doc);
	ASSERT_STREQ(typeid(Text).name(), typeid(*(doc->at(0))).name());
	Text* text = dynamic_cast<Text*>(doc->at(0));
	ASSERT_EQ(1, text->objectCount());

	Handler<RenderCommand> set = text->objectAt(0);
	float const width = set->area().width();

	ContentMeasurer(log_trace, fontManager, context, width/2).start(doc);
	ASSERT_LE(2, text->objectCount());

	ContentMeasurer(log_trace, fontManager, context, width/5).start(doc);
	ASSERT_LE(5, text->objectCount());
}


}}}

