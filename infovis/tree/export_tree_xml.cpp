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
#include <infovis/tree/visitor.hpp>
#include <fstream>
#include <string>

namespace infovis {

typedef tree Tree;
typedef tree_traits<Tree>::node_descriptor node_descriptor;

static void
print_xml_qname(std::ostream& out, const string& name)
{
  out << name;			// 
}

static void
print_xmlchar(std::ostream& out, unsigned c)
{
  unsigned char lo = c&0xFF;
  unsigned char hi = c >> 8;
  if (c < 0x80) {
    out << lo;
  }
  else if (c < 0x700) {
    out << char((lo >> 6) | (hi << 2) | 0xc0)
	<< char((lo & 0x3f) | 0x80);
  }
  else if (c < 0xdb) {
    // +++ FIXME, unhandled UTF16
  }
  else {
    out << char((hi >> 4) | 0xe0)
	<< char(((hi & 0xf) << 2) | (lo >> 6) | 0x80)
	<< char((lo & 0x3f) | 0x80);
  }
}

void
print_xmlchar_quoted(std::ostream& out, unsigned c)
{
  switch(c) {
  case '<':
    out << "&lt;";
    break;
  case '>':
    out << "&gt;";
    break;
  case '&':
    out << "&amp;";
    break;
  case '\'':
    out << "&apos;";
    break;
  case '"':
    out << "&quot;";
    break;
  default:
    print_xmlchar(out, c);
  }
}

static void
print_xml_string(std::ostream& out, const string& str, char sep)
{
  out << sep;
  for (string::const_iterator i = str.begin(); i != str.end(); i++) {
    print_xmlchar_quoted(out, *i);
  }
  out << sep;
}

static void
print_xml_string(std::ostream& out, const string& str)
{
  char sep = '"';
  if (str.find(sep) != string::npos) {
    sep = '\'';
  }
  print_xml_string(out, str, sep);
}

struct xml_tree_exporter
{
  std::ostream& out_;
  const Tree& tree_;
  int indent_;
  column * tag_;

  xml_tree_exporter(std::ostream& out, const Tree& t)
    : out_(out), tree_(t), indent_(0)
  {
    tag_ = tree_.find_column("tag");
  }

  void tab(int i) {
    while (i-- != 0)
      out_ << ' ';
  }

  void preorder(node_descriptor n) {
    tab(indent_++);
    out_ << "<";
    if (tag_ != 0)
      print_xml_qname(out_, tag_->get_value(n));
    else
      out_ << "node";
    
    for (Tree::names_iterator name = tree_.begin_names();
	 name != tree_.end_names(); name++) {
      if ((*name)[0] == '$')
	continue;
      column * c = tree_.find_column(*name);
      if (c != tag_ && c->defined(n)) {
	out_ << " ";
	print_xml_qname(out_, *name);
	out_ << "=";
	string val(c->get_value(n));
	print_xml_string(out_, val);
      }
    }
    if (is_leaf(n, tree_))
      out_ << "/>\n";
    else
      out_ << ">\n";
  }
  void inorder(node_descriptor) { }
  void postorder(node_descriptor n) {
    --indent_;
    if (! is_leaf(n, tree_)) {
      tab(indent_);
      out_ << "</";
      if (tag_ != 0)
	print_xml_qname(out_, tag_->get_value(n));
      else
	out_ << "node";
      out_ << ">\n";
    }
  }
};
  


bool
export_tree_xml(const std::string& filename, const Tree& t)
{
  std::ofstream out(filename.c_str());

  if (out) {
    xml_tree_exporter exporter(out, t);
    traverse_tree(root(t), t, exporter);
    return true;
  }
  else
    return false;
}


} // namespace infovis
