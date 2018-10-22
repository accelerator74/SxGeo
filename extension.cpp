#define _USE_MATH_DEFINES

#include "extension.h"
#include "sxgeo.h"

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */
SxGeo_Extension g_SxGeo;

SMEXT_LINK(&g_SxGeo);

bool SxGeo_Extension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	g_sxgeo.load();

	g_pShareSys->AddNatives(myself, SxGeo_natives);
	g_pShareSys->RegisterLibrary(myself, "SxGeo");

	return true;
}

void SxGeo_Extension::SDK_OnUnload()
{
	g_sxgeo.unload();
}

/*******************************
*                              *
* SxGeo NATIVE IMPLEMENTATIONS *
*                              *
*******************************/

inline void StripPort(char *ip)
{
	char *tmp = strchr(ip, ':');
	if (!tmp)
		return;
	*tmp = '\0';
}

static cell_t sm_SxGeo_Code(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	if (unlikely(ip == nullptr || ip[0] == '\0'))
	{
		return pCtx->ThrowNativeError("ip can't be an empty string");
	}

	auto loc = g_sxgeo->find(ip);
	if (unlikely(loc == nullptr))
	{
		return 0;
	}

	ccode = loc->getRegionIso().chars();

	pCtx->StringToLocal(params[2], 3, ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_SxGeo_Country(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	if (unlikely(ip == nullptr || ip[0] == '\0'))
	{
		return pCtx->ThrowNativeError("ip can't be an empty string");
	}

	auto loc = g_sxgeo->find(ip);
	if (unlikely(loc == nullptr))
	{
		return 0;
	}

	ccode = loc->getCountryName(lang).chars();
	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_SxGeo_City(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	if (unlikely(ip == nullptr || ip[0] == '\0'))
	{
		return pCtx->ThrowNativeError("ip can't be an empty string");
	}

	auto loc = g_sxgeo->find(ip);
	if (unlikely(loc == nullptr))
	{
		return 0;
	}

	ccode = loc->getCityName(lang).chars();
	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_SxGeo_Region(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	if (unlikely(ip == nullptr || ip[0] == '\0'))
	{
		return pCtx->ThrowNativeError("ip can't be an empty string");
	}

	auto loc = g_sxgeo->find(ip);
	if (unlikely(loc == nullptr))
	{
		return 0;
	}

	ccode = loc->getRegionName(lang).chars();
	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_SxGeo_Latitude(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	if (unlikely(ip == nullptr || ip[0] == '\0'))
	{
		return pCtx->ThrowNativeError("ip can't be an empty string");
	}

	auto loc = g_sxgeo->find(ip);
	if (unlikely(loc == nullptr))
	{
		return 0;
	}

	return sp_ftoc(loc->getLat());
}

static cell_t sm_SxGeo_Longitude(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	if (unlikely(ip == nullptr || ip[0] == '\0'))
	{
		return pCtx->ThrowNativeError("ip can't be an empty string");
	}

	auto loc = g_sxgeo->find(ip);
	if (unlikely(loc == nullptr))
	{
		return 0;
	}

	return sp_ftoc(loc->getLon());
}

static cell_t sm_SxGeo_Distance(IPluginContext *pCtx, const cell_t *params)
{
	float earthRadius = params[5] ? 3958.0 : 6370.997; // miles / km

	float lat1 = sp_ctof(params[1]) * (M_PI / 180);
	float lon1 = sp_ctof(params[2]) * (M_PI / 180);
	float lat2 = sp_ctof(params[3]) * (M_PI / 180);
	float lon2 = sp_ctof(params[4]) * (M_PI / 180);

	return sp_ftoc(earthRadius * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1)));
}

const sp_nativeinfo_t SxGeo_natives[] = 
{
	{"SxGeoCode",			sm_SxGeo_Code},
	{"SxGeoCountry",		sm_SxGeo_Country},
	{"SxGeoCity",			sm_SxGeo_City},
	{"SxGeoRegion",			sm_SxGeo_Region},
	{"SxGeoLatitude",		sm_SxGeo_Latitude},
	{"SxGeoLongitude",		sm_SxGeo_Longitude},
	{"SxGeoDistance",		sm_SxGeo_Distance},
	{NULL,					NULL},
};

