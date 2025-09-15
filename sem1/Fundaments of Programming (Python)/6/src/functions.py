class Expense:
    def __init__(self, apartment, amount, expense_type):
        self.apartment = apartment
        self.amount = amount
        self.expense_type = expense_type

    def __str__(self):
        return f"{self.apartment}: {self.amount}: {self.expense_type}"


def add_expense(expenses, apartment, amount, expense_type):
    """
    Adds a new expense to the list.

    :param expenses: List of expenses
    :param apartment: Apartment number
    :param amount: Amount of money
    :param expense_type: Type of expense
    """
    expense = Expense(apartment, amount, expense_type)
    expenses.append(expense)


def remove_expense_by_apartment(expenses, apartment):
    """
    Removes all expenses for a given apartment.

    :param expenses: List of expenses
    :param apartment: Apartment number
    """
    expenses[:] = [e for e in expenses if e.apartment != apartment]


def remove_expense_by_range(expenses, start_apartment, end_apartment):
    """
    Removes all expenses for apartments in a given range.

    :param expenses: List of expenses
    :param start_apartment: Start apartment number
    :param end_apartment: End apartment number
    """
    expenses[:] = [e for e in expenses if not (start_apartment <= e.apartment <= end_apartment)]


def remove_expense_by_type(expenses, expense_type):
    """
    Removes all expenses of a given type.

    :param expenses: List of expenses
    :param expense_type: Type of expense
    """
    expenses[:] = [e for e in expenses if e.expense_type != expense_type]


def replace_expense(expenses, apartment, expense_type, new_amount):
    """
    Replaces the amount of an expense for a given apartment and type.

    :param expenses: List of expenses
    :param apartment: Apartment number
    :param expense_type: Type of expense
    :param new_amount: New amount of money
    """
    for e in expenses:
        if e.apartment == apartment and e.expense_type == expense_type:
            e.amount = new_amount

def list_expenses(expenses):
    """
    Lists all expenses.

    :param expenses: List of expenses
    :return: List of expense strings
    """
    return [str(e) for e in expenses]


def list_expenses_by_apartment(expenses, apartment):
    """
    Lists all expenses for a given apartment.

    :param expenses: List of expenses
    :param apartment: Apartment number
    :return: List of expense strings
    """
    return [str(e) for e in expenses if e.apartment == apartment]


def list_expenses_by_amount(expenses, operator, amount):
    """
    Lists all expenses by amount with a given operator.

    :param expenses: List of expenses
    :param operator: Comparison operator ('<', '=', '>')
    :param amount: Amount of money
    :return: List of expense strings
    """
    if operator == '<':
        return [str(e) for e in expenses if e.amount < amount]
    elif operator == '=':
        return [str(e) for e in expenses if e.amount == amount]
    elif operator == '>':
        return [str(e) for e in expenses if e.amount > amount]


def filter_expenses_by_type(expenses, expense_type):
    """
    Filters expenses by type.

    :param expenses: List of expenses
    :param expense_type: Type of expense
    :return: Filtered list of expenses
    """
    return [e for e in expenses if e.expense_type == expense_type]


def filter_expenses_by_amount(expenses, amount):
    """
    Filters expenses by amount.

    :param expenses: List of expenses
    :param amount: Amount of money
    :return: Filtered list of expenses
    """
    return [e for e in expenses if e.amount < amount]


def undo(expenses, history):
    """
    Undoes the last operation.

    :param expenses: List of expenses
    :param history: History of expenses
    """
    if history:
        expenses[:] = history.pop()
