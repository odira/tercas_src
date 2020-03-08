from PyQt5.QtGui import QGuiApplication
from PyQt5.QtCore import ( Qt, QObject, pyqtSignal, pyqtSlot )
from PyQt5.QtQml import QQmlApplicationEngine
import sys

from QueueModel import QueueModel


class Queue(QObject):
    def __init__(self):
        QObject.__init__(self)

        # List of Arrivals Models for airports
        self._models = []

    @pyqtSlot()
    def process_models(self):
        for model in self._models:
            model.update()

    @pyqtSlot(str, result=QObject)
    def create_model(self, arg1):
        model = QueueModel(arg1)
        self._models.append(model)
        return model


if __name__ == "__main__":

    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()

    queue = Queue()
    engine.rootContext().setContextProperty("queue", queue)

    engine.load("main.qml")
    engine.quit.connect(app.quit)

    sys.exit(app.exec_())
