# This Python file uses the following encoding: utf-8
import sys
from PySide2.QtWidgets import QApplication, QMainWindow
from PySide2.QtQuick import QQuickView
from PySide2.QtQml import QQmlApplicationEngine
from PySide2.QtCore import QUrl


if __name__ == "__main__":

	app = QApplication([])

	engine = QQmlApplicationEngine()
	url = QUrl("main.qml")
	engine.load(url)

	sys.exit(app.exec_())
