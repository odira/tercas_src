#ifndef DECLARATIONS_H
#define DECLARATIONS_H

//#define MYSQL
//#define MYSQL_DATABASE "country"
//#define MYSQL_TABLENAME "country"

#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "country.vw_country"

//#define IMAGE_DIR "/usr/share/vyborg/country/"


enum Columns {
    country_pid,
    country_name,
    country_nameru,
    country_nameshort,
    country_nameshortru,
    country_iso3166code2,
    country_iso3166code3,
    country_iso3166coden,
    country_note,
    country_noteru,
    country_geog
};


#endif // DECLARATIONS_H
