import psycopg2 as pg
import datetime
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import sys
import numpy as np

def main():
    
    # parse command line arguments
    if len(sys.argv) > 1:
        year = int(sys.argv[1])
        month = int(sys.argv[2])
        day = int(sys.argv[3])
    else:
        # default values for year, month and day
        year = 2019
        month = 1
        day = 20

    #
    # POSTGRESQL
    #
        
    conn = pg.connect("host='localhost' user='postgres' password='monrepo' dbname='terkas'")
    cur = conn.cursor()

    cur.execute("SELECT * FROM statistics.f_get_sector_hour_ct('{}') WHERE _sector_pid < 41".format(datetime.datetime(year, month, day).strftime("%Y-%m-%d")))
    rdcrows = cur.fetchall()

    cur.execute("SELECT * FROM statistics.f_get_sector_hour_ct('{}') WHERE _sector_pid >= 41".format(datetime.datetime(year, month, day).strftime("%Y-%m-%d")))
    adcrows = cur.fetchall()

    cur.execute(f"SELECT pid,label,color FROM dblink('dbname=gis', 'SELECT pid,label,color FROM fir.vw_sector') AS (pid integer, label text, color text)")
    secs = cur.fetchall()

    conn.close()


    # Creating hours list
    hours = [hour for hour in range(1,25)]
    # Insert 0-es value for double first values
    hours.insert(0, 0)

    #
    # PLOTTING
    #

    plt.style.use('seaborn-whitegrid')

    fig = plt.figure(figsize=(15, 8))
    fig.suptitle("Статистика секторов МЦ АУВД (часовая)\n" + datetime.datetime(year, month, day).strftime("%d %B %Y"))

    axs1 = fig.add_axes([0.1, 0.5, 0.8, 0.4], 
                        xticks=np.arange(0, 25, 1), 
                        yticks=np.arange(0, 80, 10),
                        xlim=(-1, 25),
                        ylim=(-5, 80),
                        ylabel='Количество ВС')
    axs2 = fig.add_axes([0.1, 0.1, 0.8, 0.4],
                        xticks=np.arange(0, 25, 1), 
                        yticks=np.arange(0, 80, 10),
                        xlim=(-1, 25),
                        ylim=(-5, 80),
                        ylabel='Количество ВС')

    for row in rdcrows:
        vals = list(row[1:])
        vals.insert(0, row[1])
        secinfo = [item for item in secs if item[0] == row[0]]
        secinfo = list(secinfo[0])
        axs1.plot(hours, vals, color=secinfo[2], drawstyle='steps', label=secinfo[1])

    for row in adcrows:
        vals = list(row[1:])
        vals.insert(0, row[1])
        secinfo = [item for item in secs if item[0] == row[0]]
        secinfo = list(secinfo[0])
        axs2.plot(hours, vals, color=secinfo[2], drawstyle='steps', label=secinfo[1])

    axs1.plot(hours, np.zeros(25), color='black', drawstyle='steps')
    axs2.plot(hours, np.zeros(25), color='black', drawstyle='steps')

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

    plt.xlabel("Суточное время в часах (UTC)")
    plt.show()
 
 
if __name__ == "__main__":
    main()
