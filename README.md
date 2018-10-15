## [![SypexGeo](https://user-images.githubusercontent.com/5860435/39967335-72521fc0-56e3-11e8-8d33-174af01f7ca6.png)](https://sypexgeo.net)
<br />
SourceMod extension, using Sypex Geo API.

## Requirements
* SypexGeo API 2.2

## Installation
1. Extract file `sxgeo.ext.so` to folder `addons/sourcemod/extensions`; Extract file `sxgeo.inc` to folder `addons/sourcemod/scripting/include`.
2. Download last database [SxGeoCity.dat](https://sypexgeo.net/files/SxGeoCity_utf8.zip) and put to path `addons/sourcemod/configs/geoip/SxGeoCity.dat`
3. Install any sm-plugin that requires the sxgeo extension.
4. Restart server.

## Credits
[vsuharnikov/sypexgeo-node](../../../../vsuharnikov/sypexgeo-node) for part of the code parsing database<br />
[s1lentq/sxgeo](../../../../s1lentq/sxgeo) for original sxgeo AMXX Module<br />
[AlliedModders/geoip](../../../../alliedmodders/sourcemod/tree/master/extensions/geoip) for geoip extension

## Natives

```javascript
/**
 * @section IP addresses can contain ports, the ports will be stripped out.
 */

/**
 * Gets the two character country code from an IP address. (US, CA, etc)
 *
 * @param ip			Ip to determine the country code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no country found.
 */
native bool SxGeoCode(const char[] ip, char ccode[3]);

/**
 * Gets the full country name.
 *
 * @param ip			Ip to determine the country code.
 * @param name			Destination string buffer to store the country name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang       Which language to the output of result the sxgeo lookup.
 *                   Supported languages:
 *                   "ru", "en"
 *
 * @return				True on success, false if no country found.
 */
native bool SxGeoCountry(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the city name.
 *
 * @param ip			Ip to determine the city code.
 * @param name			Destination string buffer to store the city name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang       Which language to the output of result the sxgeo lookup.
 *                   Supported languages:
 *                   "ru", "en"
 *
 * @return				True on success, false if no city found.
 */
native bool SxGeoCity(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the full region name.
 *
 * @param ip			Ip to determine the region code.
 * @param name			Destination string buffer to store the region name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang       Which language to the output of result the sxgeo lookup.
 *                   Supported languages:
 *                   "ru", "en"
 *
 * @return				True on success, false if no region found.
 */
native bool SxGeoRegion(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the city's latitude
 *
 * @param ip			Ip to determine the city latitude.
 * @return				The result of the latitude, 0 if latitude is not found
 */
native float SxGeoLatitude(const char[] ip);

/**
 * Gets the city's longitude
 *
 * @param ip			Ip to determine the city longitude.
 * @return				The result of the longitude, 0 if longitude is not found
 */
native float SxGeoLongitude(const char[] ip);

/*
 * Calculate the distance between geographical coordinates, latitude and longitude.
 *
 * @param lat1       The first IP latitude.
 * @param lon1       The first IP longitude.
 * @param lat2       The second IP latitude.
 * @param lon2       The second IP longitude.
 * @param system     The system of measurement, 0 = Metric(kilometers) or 1 = English(miles).
 *
 * @return           The distance as result in specified system of measurement.
 */

#define SYSTEM_METRIC   0 // kilometers
#define SYSTEM_IMPERIAL 1 // statute miles

native float SxGeoDistance(float lat1, float lon1, float lat2, float lon2, system = SYSTEM_METRIC);
```
