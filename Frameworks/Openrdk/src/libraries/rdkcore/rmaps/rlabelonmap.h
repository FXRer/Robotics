/*
 *    OpenRDK : OpenSource Robot Development Kit
 *    Copyright (C) 2007, 2008  Daniele Calisi, Andrea Censi (<first_name>.<last_name>@dis.uniroma1.it)
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RDK2_RMAPS_RLABELTODRAW
#define RDK2_RMAPS_RLABELTODRAW

#include <rdkcore/object/object.h>
#include <rdkcore/geometry/point.h>
#include <rdkcore/container/container.h>
#include <rdkcore/rgraphics/color.h>

#include "ritemonmapvector.h"

namespace RDK2 { namespace RMaps {

using RDK2::RGraphics::RgbColor;

struct RLabelOnMap : public RItemOnMap, public RDK2::Geometry::Point2d {
	RgbColor color;
	double size;
	std::string text;

	RLabelOnMap(double x = 0, double y = 0, 
		RgbColor color = 0x000000, double size = 1.0, const std::string& text = "null") 
	:
		RDK2::Geometry::Point2d(x, y), color(color), size(size), text(text) { }
	
	void read(Reader* r) throw (ReadingException);
	void write(Writer* w) const throw (WritingException);
	virtual bool hasStringRepresentation() const;
	virtual std::string getStringRepresentation() const;
	virtual bool loadFromStringRepresentation(const std::string&);
	
	RDK2_DEFAULT_CLONE(RLabelOnMap);
};

}} // namespace

#endif
