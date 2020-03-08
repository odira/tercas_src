import flightradar24


fr24api = flightradar24.Api()

def get_ground_speed(flight_icao, airline_icao):
    flights = fr24api.get_flights(airline_icao)

    for i in flights:
        flight = flights[i]
        if isinstance(flight, list) == True:
            if flight[16] == flight_icao:
                return flight[5]

    return 0

