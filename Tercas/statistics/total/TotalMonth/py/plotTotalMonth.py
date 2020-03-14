#!/usr/bin/env python3
# coding: utf-8

# In[1]:


import psycopg2 as pg
import numpy as np
import pandas as pd


# In[2]:


try:
    conn = pg.connect(host='localhost', user='postgres', password='monrepo', database='terkas')
except:
    print("Unable to connect to database")


# In[3]:


import datetime


# In[4]:


start_date = datetime.date(2020, 1, 1)
end_date = datetime.date(2020, 1, 31)

sql_statement = """
SELECT date,load FROM statistics.total_date
WHERE date BETWEEN '{}' AND '{}'
""".format(start_date.isoformat(), end_date.isoformat())

load_2020 = pd.read_sql_query(sql_statement, conn)

start_date = datetime.date(2019, 1, 1)
end_date = datetime.date(2019, 1, 31)

sql_statement = """
SELECT date,load FROM statistics.total_date
WHERE date BETWEEN '{}' AND '{}'
""".format(start_date.isoformat(), end_date.isoformat())

load_2019 = pd.read_sql_query(sql_statement, conn)

start_date = datetime.date(2018, 1, 1)
end_date = datetime.date(2018, 1, 31)

sql_statement = """
SELECT date,load FROM statistics.total_date
WHERE date BETWEEN '{}' AND '{}'
""".format(start_date.isoformat(), end_date.isoformat())

load_2018 = pd.read_sql_query(sql_statement, conn)

start_date = datetime.date(2017, 1, 1)
end_date = datetime.date(2017, 1, 31)

sql_statement = """
SELECT date,load FROM statistics.total_date
WHERE date BETWEEN '{}' AND '{}'
""".format(start_date.isoformat(), end_date.isoformat())

load_2017 = pd.read_sql_query(sql_statement, conn)


# In[5]:


conn.close()


# In[6]:


import matplotlib
import matplotlib.pyplot as plt


# In[7]:


# labels = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP', 'OCT', 'NOV', 'DEC']
# ax.set_xticklabels(labels)

x = np.arange(1, 32)  # the label locations
width = 0.20          # the width of the bar

# fig=plt.figure(figsize=(18, 16), dpi= 80, facecolor='w', edgecolor='k')

fig, ax = plt.subplots()

rects2017 = ax.bar(x - width*1.5, load_2017.iloc[:, 1], width, label='2017')
rects2018 = ax.bar(x - width/2, load_2018.iloc[:, 1], width, label='2018')
rects2019 = ax.bar(x + width/2, load_2019.iloc[:, 1], width, label='2019')
rects2020 = ax.bar(x + width*1.5, load_2020.iloc[:, 1], width, label='2020')

# plt.plot(x, load_2017.iloc[:, 1])
# plt.plot(x, load_2018.iloc[:, 1])
# plt.plot(x, load_2019.iloc[:, 1])
# plt.plot(x, load_2020.iloc[:, 1])

fig.tight_layout()

ax.set_title('Количество ВС в сутки (2017, 2018, 2019, 2020 г.г.)')
ax.set_ylabel('Количество ВС (месяц)')
ax.set_xlabel('День месяца')
ax.set_xticks(x)

ax.legend()

plt.show()

