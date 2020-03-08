#!/usr/local/bin/python3


import sys
from PyQt5.QtWidgets import QApplication, QWidget
import psycopg2
from psycopg2.extras import DictCursor
from contextlib import closing


cursor_string = "SELECT * FROM shedule.vw_empl_shedule_sector_time"


def db_connect():

	conn = psycopg2.connect(dbname='terkas', user='postgres', password='monrepo', host='localhost')

	cursor = conn.cursor()
	cursor.execute("SELECT * FROM shedule.vw_empl_shedule_sector_time")

	for row in cursor:
		print(row)

	#records = cursor.fetchall()

	cursor.close()
	conn.close()


if __name__ == "__main__":
	
	app = QApplication(sys.argv)

	
	with closing(psycopg2.connect(dbname='terkas', user='postgres', password='monrepo', host='localhost')) as conn:
		with conn.cursor(cursor_factory=DictCursor) as cursor:
			cursor.execute(cursor_string)
			for row in cursor:
				print(row)

	#db_connect()

	w = QWidget()
	w.resize(250, 200)
	w.move(300, 300)
	w.setWindowTitle('Sector Working Time Manager')
	w.show()

	sys.exit(app.exec_())
