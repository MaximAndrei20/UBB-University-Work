import copy

from functions import *
from texttable import Texttable


def display_commands():
    print("Available commands:")
    print("  add <apartment> <type> <amount> - Add a new expense")
    print("  remove <apartment> | remove <start apartment> to <end apartment> | remove <type> - Remove expenses")
    print("  replace <apartment> <type> with <amount> - Replace an expense")
    print("  list | list <apartment> | list <operator> <amount> - List expenses")
    print("  filter <type> | filter <operator> <amount> - Filter expenses")
    print("  undo - Undo the last operation")
    print("  exit - Exit the program")


def handle_add(expenses, history, command):
    try:
        parts = command.split()
        if len(parts) == 4:
            _, apartment, expense_type, amount = command.split()
            apartment, amount = int(apartment), int(amount)
            history.append(copy.deepcopy(expenses))
            add_expense(expenses, apartment, amount, expense_type)
        else:
            print("Invalid input for add command. Usage: add <apartment> <type> <amount>")
    except ValueError:
        print("Invalid input for add command. Usage: add <apartment> <type> <amount>")


def handle_remove(expenses, history, command):
    parts = command.split()
    try:
        if len(parts) == 2:
            _, apartment = parts
            apartment = int(apartment)
            history.append(copy.deepcopy(expenses))
            remove_expense_by_apartment(expenses, apartment)
        elif len(parts) == 4:
            _, start_apartment, _, end_apartment = parts
            start_apartment, end_apartment = int(start_apartment), int(end_apartment)
            history.append(copy.deepcopy(expenses))
            remove_expense_by_range(expenses, start_apartment, end_apartment)
        elif len(parts) == 2:
            _, expense_type = parts
            history.append(copy.deepcopy(expenses))
            remove_expense_by_type(expenses, expense_type)
        else:
            print(
                "Invalid input for remove command. Usage: remove <apartment> | remove <start apartment> to <end apartment> | remove <type>")
    except ValueError:
        print(
            "Invalid input for remove command. Usage: remove <apartment> | remove <start apartment> to <end apartment> | remove <type>")


def handle_replace(expenses, history, command):
    try:
        parts = command.split()
        if len(parts) == 5:
            _, apartment, expense_type, _, new_amount = parts
            apartment, new_amount = int(apartment), int(new_amount)
            history.append(copy.deepcopy(expenses))
            replace_expense(expenses, apartment, expense_type, new_amount)
        else:
            print("Invalid input for replace command. Usage: replace <apartment> <type> with <amount>")
    except ValueError:
        print("Invalid input for replace command. Usage: replace <apartment> <type> with <amount>")


def handle_list(expenses, command):
    parts = command.split()
    table = Texttable()
    table.header(['Apartment', 'Amount', 'Type'])
    try:
        valid_input = True
        if len(parts) == 1:
            for e in list_expenses(expenses):
                row = e.split(': ')
                if len(row) == 3:
                    table.add_row(row)
                else:
                    print(f"Skipping invalid row: {e}")
        elif len(parts) == 2:
            _, apartment = parts
            apartment = int(apartment)
            for e in list_expenses_by_apartment(expenses, apartment):
                row = e.split(': ')
                if len(row) == 3:
                    table.add_row(row)
                else:
                    print(f"Skipping invalid row: {e}")
        elif len(parts) == 3:
            _, operator, amount = parts
            amount = int(amount)
            for e in list_expenses_by_amount(expenses, operator, amount):
                row = e.split(': ')
                if len(row) == 3:
                    table.add_row(row)
                else:
                    print(f"Skipping invalid row: {e}")
        else:
            valid_input = False
            print("Invalid input for list command. Usage: list | list <apartment> | list <operator> <amount>")
        if valid_input:
            print(table.draw())
    except ValueError:
        print("Invalid input for list command. Usage: list | list <apartment> | list <operator> <amount>")


def handle_filter(expenses,history, command):
    parts = command.split()
    try:
        if len(parts) == 2:
            _, expense_type = parts
            history.append(copy.deepcopy(expenses))
            expenses[:] = filter_expenses_by_type(expenses, expense_type)
            handle_list(expenses, "list")
            handle_undo(expenses, history)
        elif len(parts) == 3:
            _, operator, amount = parts
            amount = int(amount)
            history.append(copy.deepcopy(expenses))
            expenses[:] = filter_expenses_by_amount(expenses, amount)
            handle_list(expenses, "list")
            handle_undo(expenses, history)
        else:
            print("Invalid input for filter command. Usage: filter <type> | filter <operator> <amount>")
    except ValueError:
        print("Invalid input for filter command. Usage: filter <type> | filter <operator> <amount>")


def handle_undo(expenses, history):
    try:
        undo(expenses, history)
    except IndexError:
        print("No more actions to undo.")
