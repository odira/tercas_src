#!/usr/local/bin/python3

import psycopg2 as pg
import datetime
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import sys
import numpy as np
from calendar import monthrange

def main():
    
    # parse command line arguments
    if len(sys.argv) > 1:
        year = int(sys.argv[1])
    else:
        # default values for year, month and day
        year = 2019

    #
    # POSTGRESQL
    #
        
    conn = pg.connect("host='localhost' user='postgres' password='monrepo' dbname='terkas'")
    cur = conn.cursor()

    cur.execute(f"SELECT * FROM statistics.f_get_sector_month_ct({year}) WHERE _sector_pid < 41")
    rdcrows = cur.fetchall()
    cur.execute(f"SELECT * FROM statistics.f_get_sector_month_ct({year}) WHERE _sector_pid >= 41")
    adcrows = cur.fetchall()
    cur.execute(f"SELECT pid,label,color FROM dblink('dbname=gis', 'SELECT pid,label,color FROM fir.vw_sector') AS (pid integer, label text, color text)")
    secs = cur.fetchall()

    conn.close()

    nmonths = 12
    months = [datetime.datetime(year, month, 1).strftime("%b") for month in range(1, nmonths+1)]

    #
    # PLOTTING
    #

    plt.style.use('seaborn-whitegrid')

    fig = plt.figure(figsize=(15, 8))
    fig.suptitle("Статистика секторов МЦ АУВД\n" + datetime.datetime(year, 1, 1).strftime("%Y"))

    axs1 = fig.add_subplot(211)
    axs1.set(xlabel='Месяц', ylabel='Количество ВС',
             xticks=np.arange(0, nmonths, 1), yticks=np.arange(0, 36000, 5000),
             xlim=(-0.5, nmonths-0.5), ylim=(-1000, 38000))

    for row in rdcrows:
        vals = list(row[1:])
        secinfo = [item for item in secs if item[0] == row[0]]
        secinfo = list(secinfo[0])
        axs1.plot(months, vals, color=secinfo[2], label=secinfo[1])
 
    axs2 = fig.add_subplot(212)
    axs2.set(xlabel='Месяц', ylabel='Количество ВС',
             xticks=np.arange(0, nmonths, 1), yticks=np.arange(0, 36000, 5000),
             xlim=(-0.5, nmonths-0.5), ylim=(-1000, 38000))

    for row in adcrows:
        vals = list(row[1:])
        secinfo = [item for item in secs if item[0] == row[0]]
        secinfo = list(secinfo[0])
        axs2.plot(months, vals, color=secinfo[2], label=secinfo[1])
 
    axs1.plot(months, np.zeros(nmonths), color='black')
    axs2.plot(months, np.zeros(nmonths), color='black')

    axs1.set_xticklabels(months, rotation=30, horizontalalignment='right')
    axs2.set_xticklabels(months, rotation=30, horizontalalignment='right')
 
    axs1.legend(bbox_to_anchor=(1.0, 1.0), 
                loc='upper left',
                title='Сектора РДЦ',
                facecolor='white', edgecolor='black',
                fontsize='x-small',
                borderaxespad=0.5)

    axs2.legend(bbox_to_anchor=(1.0, 1.0), 
                loc='upper left',
                title='Сектора АДЦ',
                facecolor='white', edgecolor='black',
                fontsize='x-small',
                borderaxespad=0.5)

    plt.show()
 
 
if __name__ == "__main__":
    main()
