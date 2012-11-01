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

#include "NodeReader.h"
#include "../../../logging/Exception.h"
#include <tinyxml2.h>
#include "Node.h"

namespace chisa {
namespace tk {
namespace widget {

const std::string NodeReader::RootElementName("doc");

template <typename N, typename... Args>
static NodeReader::ParseFunc createProxy(const Args&... args)
{
	NodeReader::TreeConstructor c = std::bind(Node::create<N, Args...>, std::placeholders::_1, std::placeholders::_2, args...);
	return std::bind(&NodeReader::parseTreeNode, std::placeholders::_1, c, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
}

NodeReader::NodeReader()
{
	using namespace std::placeholders;
	this->elementParser_.insert(std::make_pair("h1", createProxy<Heading>(1)));
	this->elementParser_.insert(std::make_pair("h2", createProxy<Heading>(2)));
	this->elementParser_.insert(std::make_pair("h3", createProxy<Heading>(3)));
	this->elementParser_.insert(std::make_pair("p", createProxy<Paragraph>()));
	this->elementParser_.insert(std::make_pair("br", createProxy<BreakLine>()));
	this->elementParser_.insert(std::make_pair("font", createProxy<Font>()));
	this->elementParser_.insert(std::make_pair("link", createProxy<Link>()));
}

#define NODE_FOREACH(it, node)\
for(auto it = (node)->FirstChild(); it; it = it->NextSibling())

std::shared_ptr<Document> NodeReader::parseTree(tinyxml2::XMLElement* elm)
{
	if(!elm){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] parsing null element.");
	}
	if(RootElementName != elm->Name()){
		throw logging::Exception(__FILE__, __LINE__, "Invalid document tag: %s",elm->Name());
	}
	std::shared_ptr<Document> doc(Node::createRootDocument());
	doc->parseAttribute(elm);
	NODE_FOREACH(it, elm) {
		doc->add(this->parseNode(doc.get(), doc.get(), it));
	}
	return doc;
}

Node* NodeReader::parseNode(Document* root, TreeNode* parent, tinyxml2::XMLNode* node)
{
	if(!node){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] parsing null node!");
	}
	if(tinyxml2::XMLElement* elm = node->ToElement()){
		auto it = this->elementParser_.find(elm->Name());
		if(it == this->elementParser_.end()){
			throw logging::Exception(__FILE__, __LINE__, "Unknwon document tag: %s", elm->Name());
		}
		const ParseFunc f = it->second;
		return f(*this, root, parent, elm);
	}else if(tinyxml2::XMLText* txt = node->ToText()){
		return this->parseText(root, parent, txt);
	}
	throw logging::Exception(__FILE__, __LINE__, "Unknwon document node: %s", node->Value());
}

TreeNode* NodeReader::parseTreeNode(TreeConstructor constructor, Document* root, TreeNode* parent, tinyxml2::XMLElement* elm)
{
	TreeNode* tree = constructor(root, parent);
	tree->parseAttribute(elm);
	NODE_FOREACH(it, elm) {
		tree->add(this->parseNode(root, tree, it));
	}
	return tree;
}

Node* NodeReader::parseText(Document* root, TreeNode* parent, tinyxml2::XMLText* txt)
{
	return Node::create<Text>(root, parent, txt->Value());
}

}}}
