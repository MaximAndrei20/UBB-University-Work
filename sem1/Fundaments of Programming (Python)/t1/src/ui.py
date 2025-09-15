from functions import *

def menu():
    print("1. Add a flight. Usage: add <code> <duration> <departure> <destination>")
    print("2. Delete a flight by code. Usage: delete <code>")
    print("3. Display all flights (sorted increasing by destination city). Usage: display")
    print("4. Because of strong winds, delay all flights departing from a given city. Usage: delay <departure> <duration>")

def handle_add_flight(command, flights):
    command = command.split(" ")
    if len(command) != 5:
        print("Invalid command!")
        return
    code = command[1]
    duration = command[2]
    departure = command[3]
    destination = command[4]
    try:
        add_flight(code, duration, departure, destination, flights)
        print("Flight added successfully!")
    except ValueError as ve:
        print(ve)

def handle_delete_flight(command, flights):
    command = command.split(" ")
    if len(command) != 2:
        print("Invalid command!")
        return
    code = command[1]
    delete_flight(code, flights)
    print("Flight deleted successfully!")

def handle_display_flights(command, flights):
    command = command.split(" ")
    if len(command) != 1:
        print("Invalid command!")
        return
    display_flights(flights)

def handle_delay_flights(command, flights):
    command = command.split(" ")
    if len(command) != 3:
        print("Invalid command!")
        return
    departure = command[1]
    time_delay = command[2]

    try:
        delay_flights(departure, time_delay, flights)
        print("Flights delayed succesfully")
    except ValueError as ve:
        print(ve)

