#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#

from ui import *


def main():
    display_commands()
    expenses = [
        Expense(1, 100, 'water'), Expense(2, 200, 'heating'), Expense(3, 150, 'electricity'),
        Expense(4, 120, 'gas'), Expense(5, 180, 'other'), Expense(6, 110, 'water'),
        Expense(7, 130, 'heating'), Expense(8, 140, 'electricity'), Expense(9, 160, 'gas'),
        Expense(10, 170, 'other')
    ]
    history = []
    while True:
        command = input("Enter command: ")
        if command.startswith("add"):
            handle_add(expenses, history, command)
        elif command.startswith("remove"):
            handle_remove(expenses, history, command)
        elif command.startswith("replace"):
            handle_replace(expenses, history, command)
        elif command.startswith("list"):
            handle_list(expenses, command)
        elif command.startswith("filter"):
            handle_filter(expenses, history, command)
        elif command == "undo":
            handle_undo(expenses, history)
        elif command == "exit":
            print("Closing program...")
            return
        else:
            print("Invalid command. Please try again.")


if __name__ == "__main__":
    main()
