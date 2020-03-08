import psycopg2

sepline = '+-------------------------------------------------------+'
namenum = 1

conn = psycopg2.connect(dbname='terkas',
        user='postgres',
        password='monrepo',
        host='localhost')
cursor = conn.cursor()
cursor.execute("SELECT surname,name,middlename FROM person.vw_person WHERE shiftnum ilike '%4%' AND sectorspool ilike '%пенза%' AND uservalid is true")

names = cursor.fetchall()

for name in names:

    if 'Зыбина' in name:
        continue 

    print(sepline)
    print('| {:2}. {:49} |'.format(namenum, ' '.join(name)))
    namenum += 1
    print(sepline)

    cursor.execute("SELECT activity_note,start_date,end_date,duration FROM shedule.vw_empl_shedule WHERE period <@ daterange('2020-01-01', '2020-12-31', '[]') AND activity_abbr ilike 'пер' AND person_fullname ilike '{} %'"
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
