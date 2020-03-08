#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MYSQL
#define MYSQL_DATABASE "aviation"
#define MYSQL_TABLENAME "AC"


enum Columns {
    AC_id,
    AC_ICAO,
    AC_IATA,
    AC_codeRu,
    AC_CS,
    AC_CSru,
    AC_AC,
    AC_ACru,
    AC_fleet,
    AC_note,
    AC_noteRu,
    AC_country_id,
    AC_point_id
};


#endif // DECLARATIONS_H
