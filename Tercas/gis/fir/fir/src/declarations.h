#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define PGSQL
#define PGSQL_DATABASE "gis"
#define PGSQL_TABLENAME "fir.vw_fir"

enum Columns {

    fir_pid,
    fir_fir,
    fir_fullname,
    fir_geog,
    fir_nodepidarr,

    ColumnsNumber
};

#endif // DECLARATIONS_H
