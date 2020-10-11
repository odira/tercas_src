import psycopg2

sepline = '+-------------------------------------------------------+'
namenum = 1

conn = psycopg2.connect(dbname='terkas',
        user='postgres',
        password='monrepo',
        host='localhost')
cursor = conn.cursor()
cursor.execute("SELECT surname,name,middlename FROM person.vw_person WHERE shift_num=4 AND sectors_pool ILIKE '%пенза%' AND valid IS TRUE")

names = cursor.fetchall()

for name in names:

    print(sepline)
    print('| {:2}. {:49} |'.format(namenum, ' '.join(name)))
    namenum += 1
    print(sepline)

    cursor.execute("SELECT activity_note,start_date,end_date,duration FROM calendar.vw_empl_period WHERE daterange(start_date,end_date,'[]') <@ daterange('2021-09-01','2021-09-30','[]') AND activity_abbr ILIKE 'дор' AND person_surname ILIKE '{}'"
            .format(name[0]))
    holidays = cursor.fetchall()
    for holiday in holidays:
        activity_note = holiday[0]
        start_date = holiday[1]
        end_date = holiday[2]
        duration = holiday[3]
        print('| {} | {} | {} |'.format(activity_note, start_date.strftime("%d.%m.%Y"), end_date.strftime("%d.%m.%Y")))

    print(sepline)
    print('\n')


cursor.close()
conn.close()
