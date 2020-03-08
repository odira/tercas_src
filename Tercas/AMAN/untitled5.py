#import flightradar24
#flight_id = 'FV5862' # Turkish Airlines' Istanbul - New York flight
#fr = flightradar24.Api()
#flight = fr.get_flight(flight_id)
#print(flight)

from opensky_api import OpenSkyApi
api = OpenSkyApi()
s = api.get_states()
print(s)
