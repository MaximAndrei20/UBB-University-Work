#
# Functions section
#


#
# User interface section
#

from ui import *
from functions import *
import testing_functions as test

def main():
    test.test_delete_flight()
    menu()
    list_of_initial_flights = [("123", 45, "cluj", "londra"), ("abc", 25, "bucuresti", "iasi"), ("xyz", 30, "iasi", "cluj"), ("def", 40, "iasi", "londra"), ("ghi", 35, "cluj", "iasi")]
    flights = list_of_initial_flights
    while True:
        command = input("Enter a command: ")
        if command.startswith("exit"):
            print("Exiting...")
            return
        elif command.startswith("add"):
            handle_add_flight(command, flights)
        elif command.startswith("delete"):
            handle_delete_flight(command, flights)
        elif command.startswith("display"):
            handle_display_flights(command, flights)
        elif command.startswith("delay"):
            handle_delay_flights(command, flights)
        else:
            print("Invalid command!")



if __name__=="__main__":
    main()
