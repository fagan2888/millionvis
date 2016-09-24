/* -*- C++ -*-
 *
 * Copyright (C) 2002 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * MillionVis is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 * 
 * MillionVis is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MillionVis; see the file COPYING.  If not, write to the
 * Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA. 
 */
#include <infovis/tree/property_tree.hpp>
#include <expat.h>
#include <zlib.h>
#include <vector>
#include <cstdlib>

namespace infovis {
typedef property_tree Tree;
typedef tree_traits<Tree>::node_descriptor node_descriptor;
typedef Tree::prop_id prop_id;

struct build_xml_tree {
  Tree& tree_;
  Tree::prop_id tag_;
  std::vector<node_descriptor> node_stack;

  static void startElement(void *userData,
			   const char *name, const char **atts) {
    build_xml_tree * builder = static_cast<build_xml_tree*>(userData);
    builder->start(name, atts);
  }
  static void endElement(void *userData, const char *name) {
    build_xml_tree * builder = static_cast<build_xml_tree*>(userData);
    builder->end(name);
  }

  node_descriptor current() const {
    return node_stack.back();
  }
  node_descriptor push() {
    node_descriptor n = add_node(current(), tree_);
    node_stack.push_back(n);
    return n;
  }
  void pop() {
    node_stack.pop_back();
  }
  void start(const char *name, const char **atts) {
    node_descriptor n = push();
    tree_.get_prop_string(tag_)[n] = name;
    for (const char ** a = atts; *a != 0; a += 2) {
      Tree::prop_id id = tree_.get_prop_id(*a);
      if (id.is_invalid()) {
	char * end = const_cast<char*>(a[1]);
	float v = strtod(end, &end);
	if (end == a[1] || *end != 0) { // not a float
	  id = tree_.add_property(a[0], Tree::type_string);
	  tree_.get_prop_string(id)[n] = a[1];
	}
	else {
	  id = tree_.add_property(a[0], Tree::type_numeric);
	  tree_.get_prop_numeric(id)[n] = v;
	}
      }
      else if (id.is_numeric()) {
	float v = strtod(a[1], 0);
	tree_.get_prop_numeric(id)[n] = v;
      }
      else {
	tree_.get_prop_string(id)[n] = a[1];
      }
    }
  }
  void end(const char *name) {
    pop();
  }

  void build(const std::string& filename) {
    char buf[1024];
    gzFile input;
    const char * fname = filename.c_str();

    input = gzopen(fname, "rb");
    if (input == NULL) {
      return;
    }
    node_stack.push_back(root(tree_));
    XML_Parser parser = XML_ParserCreate(NULL);
    int done;
    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, startElement, endElement);
    do {
      size_t len = gzread(input, buf, sizeof(buf));
      done = len < sizeof(buf);
      if (!XML_Parse(parser, buf, len, done)) {
	fprintf(stderr,
		"%s at line %d\n",
		XML_ErrorString(XML_GetErrorCode(parser)),
		XML_GetCurrentLineNumber(parser));
	done = 1;
      }
    } while (!done);
    gzclose(input);
    XML_ParserFree(parser);
    pop();
    if (tree_.size() < 2) return;
    for (property_tree::names_iterator n = tree_.begin_names();
	 n != tree_.end_names(); n++) {
      property_tree::prop_id iid = tree_.get_prop_id(*n);
      if (iid.is_numeric()) {
	property_tree::numeric_prop& prop = tree_.get_prop_numeric(iid);
	prop[root(tree_)] = prop[1];
      }
      else if (iid.is_string()) {
	property_tree::string_prop& prop = tree_.get_prop_string(iid);
	prop[root(tree_)] = prop[1];
      }
    }

  }
  build_xml_tree(Tree& t, Tree::prop_id n)
    : tree_(t), tag_(n) { }
};

unsigned xml_property_tree(const std::string& filename,
			   property_tree& t)
{
  Tree::prop_id tag = t.add_property("tag", Tree::type_string);

  if (num_nodes(t) == 0)
    add_node(root(t), t);
  t.get_prop_string(tag)[root(t)] = filename;
  build_xml_tree builder(t, tag);
  builder.build(filename);
  return num_nodes(t);
}

} // namespace infovis 
