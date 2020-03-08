#!/usr/local/bin/python3

import psycopg2 as pg
import datetime
from calendar import monthrange
import matplotlib.pyplot as plt
import sys

def main():
    
    # parse command line arguments
    if len(sys.argv) > 1:
        year = int(sys.argv[1])
        month = int(sys.argv[2])
    else:
        # default values for year and month
        year = 2019
        month = 1
        
    x, ndays = monthrange(year, month)    
    
    conn = pg.connect("host='localhost' user='postgres' password='monrepo' dbname='terkas'")
    cur = conn.cursor()
    cur.execute(f"SELECT * FROM statistics.f_get_sector_month({year}, {month}) WHERE max > 0")
    rows = cur.fetchall()
    # conn.close()
    
    secs = []
    tots = []
    maxs = []
    avgs = []
    
    for sec,tot,max,avg in rows:
        secs.append(str(sec))
        tots.append(tot)
        maxs.append(max)
        avgs.append(avg)
    
    cur.execute(f"SELECT pid,label FROM dblink('dbname=gis', 'SELECT pid,label FROM fir.vw_sector') AS (pid integer, label text)")
    rows = cur.fetchall()

    i = 0
    for row in rows:
        for i in range(len(secs)):
            if secs[i]==str(row[0]):
                secs[i]=str(row[1])

    conn.close()


    fig, (axs1, axs2) = plt.subplots(2, figsize=(15, 9))
    fig.suptitle('Статистика за ' + datetime.datetime(year, month, 1).strftime("%B %Y"))
    
    axs1.bar(secs, tots, color='purple', label='Общее количество')
    axs1.set_ylim([0, 45000])    
    axs1.set(ylabel="Количество ВС",
             title="Суммарное количество ВС за месяц")
    
    axs2.bar(secs, maxs, color='orange', label='Максимальное кол-во')
    axs2.bar(secs, avgs, color='blue', label='Среднее кол-во')
    # axs2.annotate('local', xy=('18', 100), xytext=('7', 300), arrowprops=dict(facecolor='black', shrink=0.05),)
    axs2.set(xlabel="Наименование сектора",
             ylabel="Количество ВС",
             title="Максимальное и среднее количество ВС в сутки")
    
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
