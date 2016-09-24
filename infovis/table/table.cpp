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
#include <infovis/table/table.hpp>
#include <infovis/table/column.hpp>
#include <boost/config.hpp>
#include <stdexcept>
#include <algorithm>
#undef min
#undef max

namespace infovis {

table::table()
{ }

table::table(const table& other)
{
  for (int i = 0; i < other.column_count(); i++) {
    add_column(other.get_column(i)->clone());
  }
}

table::~table()
{ }

column *
table::get_column(unsigned int index) const
{
  if (index < column_.size())
    return column_[index];
  else
    return 0;
}

void
table::set_column(unsigned int index, column * c)
{
  if (index > column_.size())
    throw std::out_of_range("column out of range");
  column * old = column_[index];
  column_[index] = c;
  //delete old;
}

void
table::add_column(column * c)
{
  column_.push_back(c);
  c->resize(row_count());
}

void
table::remove_column(unsigned int index)
{
  column * c = get_column(index);
  column_.erase(column_.begin()+index);
  //delete c;
}

int
table::index_of(const string& name) const
{
  for (unsigned int i = 0; i < column_count(); i++) {
    if (get_column(i)->get_name() == name)
      return i;
  }
  return -1;
}

column *
table::find_column(const string& name) const
{
  for (unsigned int i = 0; i < column_count(); i++) {
    if (get_column(i)->get_name() == name)
      return get_column(i);
  }
  return 0;
}

unsigned int
table::column_count() const
{
  return column_.size();
}

unsigned int
table::row_count() const
{
  int c = 0;
  for (unsigned i = 0; i < column_count(); i++) {
    c = std::max(c, int(get_column(i)->size()));
  }
  return c;
}

struct name_cmp {
  bool operator () (const column * c1, const column * c2) const {
    return c1->get_name() < c2->get_name();
  }
};

void
table::sort_columns()
{
  std::sort(column_.begin(), column_.end(), name_cmp());
}

void
table::resize(unsigned sz)
{
  for (unsigned i = 0; i < column_count(); i++) {
    get_column(i)->resize(sz);
  }
}

void
table::reserve(unsigned sz)
{
  for (unsigned i = 0; i < column_count(); i++) {
    get_column(i)->reserve(sz);
  }
}

bool
table::defined(unsigned int index) const
{
  for (unsigned i = 0; i < column_count(); i++) {
    if (! get_column(i)->defined(index))
      return false;
  }
  return true;
}

void
table::clear()
{
  column_.clear();
}

void
table::print(std::ostream& out) const
{
  for (unsigned int i = 0; i < column_count(); i++) {
    column * c = get_column(i);
    if (i != 0)
      out << "; ";
    out << c->get_name();
  }
  out << std::endl;
  bool finished = false;
  for (unsigned int j = 0; ! finished; j++) {
    finished = true;
    for (unsigned int i = 0; i < column_count(); i++) {
      column * c = get_column(i);
      if (i != 0)
	out << "; ";
      if (j < c->size()) {
	if (c->defined(j))
	  out << c->get_value(j);
	if ((j+1) != c->size())
	  finished = false;

      }
    }
    out << std::endl;
  }
}

void
table::read(std::istream& )
{
}

} // namespace infovis
