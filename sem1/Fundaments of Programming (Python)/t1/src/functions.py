from texttable import Texttable

def get_code(flight):
    return flight[0]
def get_duration(flight):
    return flight[1]
def get_departure(flight):
    return flight[2]
def get_destination(flight):
    return flight[3]
def set_duration(duration, flight):
    flight[1] = duration

def add_flight(code, duration, departure, destination, flights):
    """
    add a flight to the list of flights

    :param code: the code of the flight
    :param duration: the duration of the flight
    :param departure: the departure city
    :param destination: the destination city
    :param flights: the list of flights
    """

    try:
        duration = int(duration)
    except ValueError:
        print("Duration not a number")
    flight = (code, duration, departure, destination)
    if len(get_code(flight)) < 3:
        raise ValueError("Invalid code!")
    if len(get_departure(flight)) < 3:
        raise ValueError("Invalid departure!")
    if len(get_destination(flight)) < 3:
        raise ValueError("Invalid destination!")
    if get_duration(flight) < 20:
        raise ValueError("Invalid duration!")
    for fl in flights:
        if get_code(fl) == get_code(flight):
            raise ValueError("Flight with this code already in the list")
    flights.append(flight)

def delete_flight(code, flights):
    """
    Delete a flight by code

    :param code: the code of the flight to be deleted
    :param flights: the list of flights
    """
    for flight in flights:
        if code == get_code(flight):
            flights.remove(flight)

def display_flights(flights):
    """Display all flights (sorted increasing by their destination city) using Texttable"""
    flights.sort(key=get_destination)
    t = Texttable()
    t.add_row(["Code", "Duration", "Departure", "Destination"])
    for flight in flights:
        t.add_row([get_code(flight), get_duration(flight), get_departure(flight), get_destination(flight)])
    print(t.draw())

def delay_flights(departure, time_delay, flights):
    try:
        time_delay = int(time_delay)
    except ValueError:
        print("Time is not a number")

    if time_delay < 10 or time_delay > 60:
        raise ValueError("Invalid time delay")

    """
    add <time_delay> to duration of all flights departing from <departure>
    """
    for i in range(len(flights)):
        if departure == get_departure(flights[i]):
            flights[i] = (get_code(flights[i]), get_duration(flights[i]) + time_delay, get_departure(flights[i]), get_destination(flights[i]))

