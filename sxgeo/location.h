/*
* Copyright by Vyatcheslav Suharnikov and contributors.
* See contributors list in AUTHORS.
*
* Licensed under the MIT license, see license text in LICENSE file.
*/

#ifndef _INCLUDE_SOURCEMOD_EXTENSION_SXLOC_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_SXLOC_H_

#include "sxgeo/uint24_t.h"
#include "sxgeo/raw_country_access.h"
#include "sxgeo/raw_region_access.h"
#include "sxgeo/raw_city_access.h"

class Location
{
public:
	explicit Location(RawCountryAccess country, RawRegionAccess region, RawCityAccess city);
	explicit Location(RawCountryAccess country);

	Location();
	~Location();

	double getLat() const;
	double getLon() const;

	const std::uint8_t   getCountryId()                          const;
	const ke::AString&   getCountryIso()                         const;
	const ke::AString&   getCountryName(const char *lang = "en") const;

	const std::uint32_t  getRegionId()                           const;
	const ke::AString&   getRegionIso()                          const;
	const ke::AString&   getRegionName(const char *lang = "en")  const;

	const std::uint32_t  getCityId()                             const;
	const ke::AString&   getCityName(const char *lang = "en")    const;

private:
	double        latitude;
	double        longitude;

	std::uint8_t  country_id;
	ke::AString   country_iso;
	ke::AString   country_name_ru;
	ke::AString   country_name_en;

	std::uint24_t region_id;
	ke::AString   region_iso;
	ke::AString   region_name_ru;
	ke::AString   region_name_en;

	std::uint24_t city_id;
	ke::AString   city_name_ru;
	ke::AString   city_name_en;
};

#endif
