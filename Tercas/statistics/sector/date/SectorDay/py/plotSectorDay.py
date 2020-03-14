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
        month = int(sys.argv[2])
    else:
        # default values for year, month and day
        year = 2019
        month = 1

    #
    # POSTGRESQL
    #
        
    conn = pg.connect("host='localhost' user='postgres' password='monrepo' dbname='terkas'")
    cur = conn.cursor()

    cur.execute(f"SELECT * FROM statistics.f_get_sector_date_ct({year}, {month}) WHERE _sector_pid < 41")
    rdcrows = cur.fetchall()
    cur.execute(f"SELECT * FROM statistics.f_get_sector_date_ct({year}, {month}) WHERE _sector_pid >= 41")
    adcrows = cur.fetchall()
    cur.execute(f"SELECT pid,label,color FROM dblink('dbname=gis', 'SELECT pid,label,color FROM fir.vw_sector') AS (pid integer, label text, color text)")
    secs = cur.fetchall()

    conn.close()

    x, ndays = monthrange(year, month)
    days = [day for day in range(1,ndays+1)]

    #
    # PLOTTING
    #

    plt.style.use('seaborn-whitegrid')

    fig = plt.figure(figsize=(15, 8))
    fig.suptitle("Статистика секторов МЦ АУВД (дневная)\n" + datetime.datetime(year, month, 1).strftime("%B %Y"))

    axs1 = fig.add_axes([0.1, 0.5, 0.8, 0.4], 
                        xticks=np.arange(1, ndays+1, 1), 
                        yticks=np.arange(0, 1200, 100),
                        xlim=(0, ndays+1),
                        ylim=(-100, 1200),
                        ylabel='Количество ВС')
    axs2 = fig.add_axes([0.1, 0.1, 0.8, 0.4],
                        xticks=np.arange(1, ndays+1, 1), 
                        yticks=np.arange(0, 1200, 100),
                        xlim=(0, ndays+1),
                        ylim=(-100, 1200),
                        ylabel='Количество ВС')

    for row in rdcrows:
        vals = list(row[1:])
        secinfo = [item for item in secs if item[0] == row[0]]
        secinfo = list(secinfo[0])
        axs1.plot(days, vals, color=secinfo[2], label=secinfo[1])

    for row in adcrows:
        vals = list(row[1:])
        secinfo = [item for item in secs if item[0] == row[0]]
        secinfo = list(secinfo[0])
        axs2.plot(days, vals, color=secinfo[2], label=secinfo[1])

    axs1.plot(days, np.zeros(ndays), color='black')
    axs2.plot(days, np.zeros(ndays), color='black')

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

    plt.xlabel("Число месяца")
    plt.show()
 
 
if __name__ == "__main__":
    main()
