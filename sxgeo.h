/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#ifndef _INCLUDE_SOURCEMOD_EXTENSION_SXGEO_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_SXGEO_H_

#include "sxgeo/db.h"

class CSxGeo
{
public:
	CSxGeo();
	~CSxGeo();

	bool load();
	bool is_load() const;
	bool open(const char *path);

	sxgeo::dbptr_t &operator->()
	{
		return m_HandleDB;
	}

private:
	sxgeo::dbptr_t m_HandleDB;
};

extern CSxGeo g_sxgeo;

#endif
