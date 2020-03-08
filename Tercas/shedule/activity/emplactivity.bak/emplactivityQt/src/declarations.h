#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define PGSQL
#define PGSQL_DATABASE "terkas"
#define PGSQL_TABLENAME "shedule.vw_emplactivity"

enum Columns {

    emplactivity_pid,
    emplactivity_color,
    emplactivity_abbr,
    emplactivity_emplactivity,
    emplactivity_noteru,

    ColumnsCount
};

#endif // DECLARATIONS_H
