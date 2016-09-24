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

struct xml_tree_builder
{
  Tree& tree_;
  StringColumn * tag_;
  std::vector<node_descriptor> node_stack;

  static void startElement(void *userData,
			   const char *name, const char **atts) {
    xml_tree_builder * builder = static_cast<xml_tree_builder*>(userData);
    builder->start(name, atts);
  }
  static void endElement(void *userData, const char *name) {
    xml_tree_builder * builder = static_cast<xml_tree_builder*>(userData);
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
    StringColumn * str;
    FloatColumn  * flt;
    node_descriptor n = push();
    (*tag_)[n] = name;
    for (const char ** a = atts; *a != 0; a += 2) {
      column * c = tree_.find_column(*a);
      if (c == 0) {
	char * end = const_cast<char*>(a[1]);
	float v = strtod(end, &end);
	if (end == a[1] || *end != 0) { // not a float
	  str = new StringColumn(a[0]);
	  tree_.add_column(str);
	  (*str)[n] = a[1];
	}
	else {
	  flt = new FloatColumn(a[0]);
	  tree_.add_column(flt);
	  (*flt)[n] = v;
	}
      }
      else if ((flt = FloatColumn::cast(c)) != 0) {
	float v = strtod(a[1], 0);
	(*flt)[n] = v;
      }
      else if ((str = StringColumn::cast(c)) != 0) {
	(*str)[n] = a[1];
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
  }
  xml_tree_builder(Tree& t, StringColumn * n)
    : tree_(t), tag_(n) { }
};

unsigned xml_tree(const std::string& filename, tree& t)
{
  StringColumn * tag = StringColumn::find("tag", t);

  (*tag)[root(t)] = filename;
  xml_tree_builder builder(t, tag);
  builder.build(filename);
  return num_nodes(t);
}

} // namespace infovis 
