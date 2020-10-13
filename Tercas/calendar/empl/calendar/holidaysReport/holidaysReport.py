import psycopg2

sepline = '+---------------------------------------------------------------------+'
namenum = 1

conn = psycopg2.connect(dbname='terkas',
        user='postgres',
        password='monrepo',
        host='localhost')
cursor = conn.cursor()
cursor.execute("SELECT surname,name,middlename FROM person.vw_person WHERE shift_num=4 AND sectors_pool ILIKE '%пенза%' AND valid IS true")

names = cursor.fetchall()

for name in names:

    if 'Степанова' in name:
        continue 

    print(sepline)
    print('| {:2}. {:63} |'.format(namenum, ' '.join(name)))
    namenum += 1
    print(sepline)

    cursor.execute("SELECT activity_note,start_date,end_date,duration FROM calendar.vw_empl_period "
		   "WHERE daterange(start_date,end_date,'[]') && daterange('2021-01-01','2021-12-31','[]') AND activity_abbr ILIKE 'опг' AND person_surname ILIKE '{}%'"
		   # "WHERE daterange(start_date,end_date,'[]') <@ daterange('2021-01-01','2021-12-31','[]') AND activity_abbr ILIKE 'опг' AND person_surname ILIKE '{}%'"
            .format(name[0]))
    holidays = cursor.fetchall()
    for holiday in holidays:
        activity_note = holiday[0]
        start_date = holiday[1]
        end_date = holiday[2]
        duration = holiday[3]
        print('| {} | {} | {} | Продолжительность: {:2} |'.format(activity_note, start_date.strftime("%d.%m.%Y"), end_date.strftime("%d.%m.%Y"), duration))

    print(sepline)

    cursor.execute("SELECT SUM(duration) FROM calendar.vw_empl_period WHERE daterange(start_date,end_date,'[]') <@ daterange('2021-01-01','2021-12-31','[]') AND activity_abbr ILIKE 'опг' AND person_surname ILIKE '{}%'"
            .format(name[0]))
    for row in cursor:
        print('| Общая продолжительность: {} \t\t\t\t\t      |'.format(row[0]))

    print(sepline)
    print('\n')


cursor.close()
conn.close()
