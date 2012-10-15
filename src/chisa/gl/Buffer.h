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

#ifndef CXX_CHISA_GL_BUFFER_H_
#define CXX_CHISA_GL_BUFFER_H_

#include "../util/ClassUtil.h"

namespace chisa {
namespace gl {

class Buffer{
	DISABLE_COPY_AND_ASSIGN(Buffer);
	DEFINE_MEMBER_CONST(public, unsigned char*, data);
	DEFINE_MEMBER_CONST(public, int, width);
	DEFINE_MEMBER_CONST(public, int, height);
	DEFINE_MEMBER_CONST(public, int, stride);
public:
	Buffer(const int width, const int height);
	virtual ~Buffer();
};

}}

#endif /* INCLUDE_GUARD */
