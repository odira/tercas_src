from PyQt5.QtCore import ( Qt, QModelIndex, QAbstractTableModel )
from pyflightdata import FlightData
import json
import datetime
import sys

import acft_details


class QueueModel(QAbstractTableModel):

    # Roles definitions
    #
    QueueTypeRole   = Qt.UserRole + 1
    LiveRole        = Qt.UserRole + 2
    FlightIATARole  = Qt.UserRole + 3
    FlightICAORole  = Qt.UserRole + 4
    ICAODEPRole     = Qt.UserRole + 5
    ACFTRole        = Qt.UserRole + 6
    ETARole         = Qt.UserRole + 7
    ETAUTCRole      = Qt.UserRole + 8
    ETAUTCHourRole  = Qt.UserRole + 9
    GroundSpeedRole = Qt.UserRole + 10

    _roleNames = { QueueTypeRole:   b"queue_type",
                   LiveRole:        b"live",
                   FlightIATARole:  b"flight_iata",
                   FlightICAORole:  b"flight_icao",
                   ICAODEPRole:     b"icao_dep",
                   ACFTRole:        b"acft",
                   ETARole:         b"eta",
                   ETAUTCRole:      b"eta_utc",
                   ETAUTCHourRole:  b"eta_utc_hour",
                   GroundSpeedRole: b"ground_speed" }


    def __init__(self, codeIATA, parent = None):
        super(QueueModel, self).__init__(parent)

        self._QUEUE = []
        self._codeIATA = codeIATA

        self._fapi = FlightData()
        try:
            self._fapi.login('odira@mail.ru', 'monrepo1')
            print('Logged in seccesfully...')
            self.update()
        except:
            print('Logged in failed.')
            sys.exit(0)


    def roleNames(self):
        return self._roleNames


    def flags(self, index):
        return Qt.ItemIsEditable | Qt.ItemIsEnabled


    def columnCount(self, parent = QModelIndex()):
        return len(self._roleNames)


    def rowCount(self, parent = QModelIndex()):
        return len(self._QUEUE)


    def data(self, index, role = Qt.DisplayRole):
        if not index.isValid():
            return QVariant()

        row = index.row()
        col = role - Qt.UserRole - 1
        return self._QUEUE[row][col]


    def update(self):
        self.beginResetModel()

        self._QUEUE = []

        self.updateARR()
        print('(' + self._codeIATA + ') Arrival Queue updated succesfully.')
        print(self._QUEUE)

#        self.updateDEP()
#        print('(' + self._codeIATA + ') Departure Queue updated seccesfully.')

        self._QUEUE.sort(key = lambda row: row[7])

        self.endResetModel()


    def updateARR(self):
        arrs = self._fapi.get_airport_arrivals(self._codeIATA)
        arrs = json.loads(json.dumps(arrs))
        arrs = sorted(arrs, key=lambda k: k['flight']['time']['other']['eta'], reverse=True)
        arrs = arrs[::-1]


        for arr in arrs:
            live = arr['flight']['status']['live']

            if bool(live) is False:
                pass
            else:
                queue_type = 'ARR'

                flight_iata = arr['flight']['identification']['number']['default']  # IATA flight code
                flight_icao = arr['flight']['identification']['callsign']           # ICAO flight code

                dep_icao = arr['flight']['airport']['origin']['code']['icao']  # ICAO departure airport code

                if arr['flight']['aircraft'] == 'None':
                    acft = 'None'
                else:
                    acft = arr['flight']['aircraft']['model']['code']  # ACFT code

                eta = arr['flight']['status']['text']  # ETA local time
                eta_utc = arr['flight']['time']['estimated']['arrival']  # ETA UTC
                if eta_utc == 'None':
                    eta_utc = '0'

                if arr['flight']['airline'] == 'None':
                    airline_icao = 'None'
                else:
                    airline_icao = arr['flight']['airline']['code']['icao']

                if (eta.find('Estimated') != -1):
#                    ground_speed = acft_details.get_ground_speed(flight_icao, airline_icao)
                    ground_speed = 0

                    arr = [ queue_type,
                            live,
                            flight_iata,
                            flight_icao,
                            dep_icao,
                            acft,
                            str(eta),
                            int(eta_utc),
                            datetime.datetime.utcfromtimestamp(int(eta_utc)).hour,
                            ground_speed ]


                    self.beginInsertRows(QModelIndex(), self.rowCount(), self.rowCount())
                    self._QUEUE.append(arr)
                    self.endInsertRows()


    def updateDEP(self):
        deps = self._fapi.get_airport_departures(self._codeIATA)
        deps = json.loads(json.dumps(deps))
        deps = sorted(deps, key=lambda k: k['flight']['time']['other']['eta'], reverse=True)
        deps = deps[::-1]

        for dep in deps:
            queue_type = 'DEP'
            live = dep['flight']['status']['live']
            if bool(live) is True:
                flight_iata = dep['flight']['identification']['number']['default'] # IATA flight code
                flight_icao = dep['flight']['identification']['callsign'] # ICAO flight code
#                dep_icao = dep['flight']['airport']['origin']['code']['icao'] # ICAO departure airport code
                dep_icao = None

            if dep['flight']['aircraft'] == 'None':
               acft = 'None'
            else:
               acft = dep['flight']['aircraft']['model']['code'] # ACFT code

            eta = dep['flight']['status']['text'] # ETA local time
            eta_utc = dep['flight']['time']['estimated']['departure'] # ETA UTC
            if eta_utc == 'None':
                eta_utc = '0'

            if dep['flight']['airline'] == 'None':
                airline_icao = 'None'
            else:
                airline_icao = dep['flight']['airline']['code']['icao']

            if (eta.find('Estimated') != -1):
                ground_speed = 0
                dep = [ queue_type,
                        live,
                        flight_iata,
                        flight_icao,
                        dep_icao,
                        acft,
                        str(eta),
                        int(eta_utc),
                        datetime.datetime.utcfromtimestamp(int(eta_utc)).hour,
                        ground_speed ]

                self.beginInsertRows(QModelIndex(), self.rowCount(), self.rowCount())
                self._QUEUE.append(dep)
                self.endInsertRows()
