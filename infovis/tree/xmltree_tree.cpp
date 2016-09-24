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
#include <infovis/tree/tree.hpp>
#include <expat.h>
#include <zlib.h>
#include <vector>
#include <cstdlib>

namespace infovis {
typedef tree Tree;
typedef tree_traits<Tree>::node_descriptor node_descriptor;

struct xmltree_tree_builder
{
  Tree& tree_;
  StringColumn * tag_;
  std::vector<node_descriptor> node_stack_;
  bool first_;
  bool bad_dtd_;

  static void startElement(void *userData,
			   const char *name, const char **atts) {
    xmltree_tree_builder * builder = static_cast<xmltree_tree_builder*>(userData);
    builder->start(name, atts);
  }
  static void endElement(void *userData, const char *name) {
    xmltree_tree_builder * builder = static_cast<xmltree_tree_builder*>(userData);
    builder->end(name);
  }

  node_descriptor current() const {
    return node_stack_.back();
  }
  node_descriptor push() {
    node_descriptor n = add_node(current(), tree_);
    node_stack_.push_back(n);
    return n;
  }

  void add_attribute(const char * name, const char * value) {
    StringColumn * str;
    FloatColumn  * flt;
    column * c = tree_.find_column(name);
    node_descriptor n = current();
    if (c == 0) {
      char * end = const_cast<char*>(value);
      float v = strtod(end, &end);
      if (end == value || *end != 0) { // not a float
	str = new StringColumn(name);
	tree_.add_column(str);
	(*str)[n] = value;
      }
      else {
	flt = new FloatColumn(name);
	tree_.add_column(flt);
	(*flt)[n] = v;
      }
    }
    else if ((flt = FloatColumn::cast(c)) != 0) {
      float v = strtod(value, 0);
      (*flt)[n] = v;
    }
    else if ((str = StringColumn::cast(c)) != 0) {
      (*str)[n] = value;
    }
  }
  void pop() {
    node_stack_.pop_back();
  }
  void start(const char *name, const char **atts) {
    if (first_ && strcmp(name, "tree") != 0) {
      bad_dtd_ = true;
      return;
    }
    if (strcmp(name, "branch") == 0 || strcmp(name, "leaf") == 0) {
      node_descriptor n = push();
    }
    else if (strcmp(name, "attribute") == 0) {
      const char* name = NULL;
      const char* value = NULL;
      for (const char ** a = atts; *a != 0; a += 2) {
	if (strcmp(a[0], "name") == 0)
	  name = a[1];
	else if (strcmp(a[0], "value") == 0)
	  value = a[1];
      }
      if (name != NULL && value != NULL) {
	add_attribute(name, value);
      }
    }
  }

  void end(const char *name) {
    if (strcmp(name, "branch") == 0 || strcmp(name, "leaf") == 0) {
      pop();
    }
  }

  void build(const std::string& filename) {
    char buf[1024];
    gzFile input;
    const char * fname = filename.c_str();

    first_ = true;
    bad_dtd_ = false;

    input = gzopen(fname, "rb");
    if (input == NULL) {
      return;
    }
    node_stack_.push_back(root(tree_));
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
    } while (!done || bad_dtd_);
    gzclose(input);
    XML_ParserFree(parser);
    pop();
  }
  xmltree_tree_builder(Tree& t, StringColumn * n)
    : tree_(t), tag_(n) { }
};

unsigned xmltree_tree(const std::string& filename, tree& t)
{
  StringColumn * tag = StringColumn::find("tag", t);

  (*tag)[root(t)] = filename;
  xmltree_tree_builder builder(t, tag);
  builder.build(filename);
  return num_nodes(t);
}

} // namespace infovis 
