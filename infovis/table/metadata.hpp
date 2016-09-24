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
#ifndef INFOVIS_TABLE_METADATA_HPP
#define INFOVIS_TABLE_METADATA_HPP

#include <infovis/alloc.hpp>
#include <infovis/table/column.hpp>

namespace infovis {

/**
 * Metadata properties are associated with columns and describe their
 * semantic.
 */
namespace metadata {

extern const string type;/// key for the visualization type
extern const string type_nominal; /// nominal data type
extern const string type_categorical; /// categorical data type
extern const string type_ordinal; /// ordinal data type 

extern const string aggregate;/// key for aggregation type
extern const string aggregate_sum; /// aggregate by sum hierarchically
extern const string aggregate_average; /// aggregate by average hierarchically
extern const string aggregate_min; /// aggregate by min value hierarchically
extern const string aggregate_max; /// aggregate by max value hierarchically

extern const string user_type; /// key for the user-visible type
extern const string user_type_unix_time; /// user-visible type is unix date

} // namespace metadata

} // namespace infovis

#endif // INFOVIS_TABLE_METADATA_HPP
