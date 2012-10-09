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

#include "LayoutFactory.h"
#include "../Layout.h"
#include "../../logging/Exception.h"
#include <memory>
#include <tinyxml2.h>
#include "SplitLayout.h"
#include "EmptyLayout.h"
#include "WidgetWrapperLayout.h"

namespace chisa {
namespace tk {
namespace layout {

using std::shared_ptr;
using std::weak_ptr;
using std::auto_ptr;
using std::string;
using namespace tinyxml2;
using namespace logging;

const std::string LayoutFactory::ElemName::World("world");
const std::string LayoutFactory::ElemName::Vertical("vertical");
const std::string LayoutFactory::ElemName::Horizontal("horizontal");
const std::string LayoutFactory::ElemName::Empty("empty");
const std::string LayoutFactory::ElemName::WidgetWrapper("widget");
const std::string LayoutFactory::ElemName::Tab("tab");

const std::string LayoutFactory::AttrName::Id("id");

LayoutFactory::LayoutFactory(logging::Logger& log, weak_ptr<World> world, const string& filename)
:log_(log)
,world_(world)
,filename_(filename)
,doc_(new XMLDocument())
,doc_free_by_me_(true)
{
	init();
	const int code = doc_->LoadFile(filename.c_str());
	if(code != XML_NO_ERROR){
		throw Exception(__FILE__, __LINE__, "Failed to read xml (%d): %s", code, filename.c_str());
	}
	this->root_ = doc_->RootElement();
	if(!this->root_ && ElemName::World == this->root_->Name()){
		throw Exception(__FILE__, __LINE__, "%s was parsed, but \"world\" element not found.", filename.c_str());
	}
}

LayoutFactory::LayoutFactory(logging::Logger& log, weak_ptr<World> world, const string& filename, XMLDocument* document, bool doc_free_by_me)
:log_(log)
,world_(world)
,filename_(filename)
,doc_(document)
,doc_free_by_me_(doc_free_by_me)
{
	init();
	this->root_ = doc_->RootElement();
	if(!this->root_ && ElemName::World == this->root_->Name()){
		throw Exception(__FILE__, __LINE__, "%s was parsed, but \"world\" element not found.", filename.c_str());
	}
}

LayoutFactory::LayoutFactory(logging::Logger& log, weak_ptr<World> world, const string& filename, const char* buffer, size_t lenb)
:log_(log)
,world_(world)
,doc_()
,doc_free_by_me_(true)
{
	init();
	const int code = doc_->Parse(buffer, lenb);
	if(code != XML_NO_ERROR){
		throw Exception(__FILE__, __LINE__, "Failed to read xml (%d): %s", code, filename.c_str());
	}
	this->root_ = doc_->RootElement();
}

void LayoutFactory::init()
{
	this->registerLayout(ElemName::Horizontal, std::bind(SplitLayout::constructorProxy, SplitLayout::Horizontal, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	this->registerLayout(ElemName::Vertical, std::bind(SplitLayout::constructorProxy, SplitLayout::Vertical, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	this->registerLayout<EmptyLayout>(ElemName::Empty);
	this->registerLayout<WidgetWrapperLayout>(ElemName::WidgetWrapper);
	//this->registerLayout<TabLayout>(ElemName::Tab);
}

LayoutFactory::~LayoutFactory()
{
	if(doc_free_by_me_){
		delete this->doc_;
	}
	this->doc_ = nullptr;
}

void LayoutFactory::registerLayout(const std::string& layoutName, std::function<shared_ptr<Layout>(logging::Logger& log, weak_ptr<World> world, weak_ptr<Layout> root, weak_ptr<Layout> parent)> constructor)
{
	this->layoutMap_.insert(std::make_pair(layoutName, constructor));
}

shared_ptr<Layout> LayoutFactory::parseTree(weak_ptr<Layout> root, weak_ptr<Layout> parent, XMLElement* top)
{
	const char* name = top->Name();
	auto it = this->layoutMap_.find(name);
	if(this->layoutMap_.end() == it){
		throw logging::Exception(__FILE__,__LINE__, "Unknwon Layout: %s", name);
	}
	shared_ptr<Layout> layout(it->second(this->log(), this->world(), root, parent));
	layout->loadXML(this, top);
	return layout;
}

shared_ptr<Layout> LayoutFactory::parseTree(const string& layoutname)
{
	for(XMLElement* elem = this->root_->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
		const char* id = elem->Attribute(AttrName::Id.c_str(), nullptr);
		if(id && layoutname == id){
			return this->parseTree(weak_ptr<Layout>(), weak_ptr<Layout>(), elem);
		}
	}
	throw logging::Exception(__FILE__, __LINE__, "Layout \"%s\" not found in %s", layoutname.c_str(), this->filename_.c_str());
}

}}}
