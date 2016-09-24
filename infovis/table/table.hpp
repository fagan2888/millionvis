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
#ifndef INFOVIS_TABLE_TABLE_HPP
#define INFOVIS_TABLE_TABLE_HPP

#include <infovis/alloc.hpp>
#include <vector>
#include <string>

namespace infovis {

using std::string;

class column;
template <class T> class column_of;

/**
 * Base container for all MillionVis data types.
 * A <b>table</b> manages a list of <b>column</b>s.
 */
class table : public gc
{
protected:
  std::vector<column*> column_;
public:
  enum {
    internal_prefix = '#'	/// Prefix for names of internal columns
  };
  /**
   * Create an empty table.
   */
  table();

  /**
   * Copy an existing table.
   */
  table(const table&);

  /**
   * Destructor, since the table has virtual methods.
   */
  virtual ~table();

  /**
   * Get the column at a specified index.
   *
   * @param index the column index
   * @return the column or null.
   */
  virtual column * get_column(unsigned int index) const;

  /**
   * Set the column at a specified index.
   *
   * @param index the column index
   * @param c the column
   */
  virtual void set_column(unsigned int index, column * c);

  /**
   * Add a column.
   *
   * @param c the column
   */
  virtual void add_column(column * c);

  /**
   * Remove a column at a specified index.
   *
   * @param index the index.
   */
  virtual void remove_column(unsigned int index);

  /**
   * Return the index of a column by name.
   *
   * @param name the name of the column.
   * @return the index of the first column with that name or -1.
   */
  virtual int index_of(const string& name) const;

  /**
   * Return the column with a given name.
   *
   * @param name the name of the column.
   * @return the first column with that name or null.
   */
  virtual column * find_column(const string& name) const;

  /**
   * Return the number of columns in this table.
   * @return the number of columns in this table.
   */
  virtual unsigned column_count() const;

  /**
   * Sort the columns by name in the table.
   */
  virtual void sort_columns();

  /**
   * Return the maximum number of rows of the columns in the table.
   * @return the maximum number of rows of the columns in the table.
   */
  virtual unsigned row_count() const;

  /**
   * Change the size of each column in the table.
   * @param size the new size.
   */
  virtual void resize(unsigned size);

  /**
   * Reserve space to store more data in columns.
   * @para size the size to reserve.
   */
  virtual void reserve(unsigned size);

  /**
   * Check if all the values are defined at a specified row.
   * @param index the row index
   * @return true if all the values are defined.
   */
  virtual bool defined(unsigned int index) const;

  /**
   * Clears the table.
   */
  virtual void clear();

  /**
   * Prints the table on a stream for debugging.
   * @param out the output stream.
   */
  virtual void print(std::ostream& out) const;

  /**
   * Reads the table from an input stream. (NOT IMPLEMENTED).
   * @param in the input stream.
   */
  virtual void read(std::istream& in);
};

/**
 * Shortcut to print a table for debugging.
 */
inline std::ostream&
operator << (std::ostream& out, const table& t)
{
  t.print(out);
  return out;
}

} // namespace infovis

#endif // INFOVIS_TABLE_TABLE_HPP
