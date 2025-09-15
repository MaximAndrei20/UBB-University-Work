import unittest
from src.functions import *


class TestFunctions(unittest.TestCase):
    def setUp(self):
        self.expenses = [
            Expense(1, 100, 'water'), Expense(2, 200, 'heating'), Expense(3, 150, 'electricity')
        ]
        self.history = []

    def test_add_expense(self):
        add_expense(self.expenses, 4, 120, 'gas')
        self.assertEqual(len(self.expenses), 4)
        self.assertEqual(self.expenses[-1].apartment, 4)
        self.assertEqual(self.expenses[-1].amount, 120)
        self.assertEqual(self.expenses[-1].expense_type, 'gas')

    def test_remove_expense_by_apartment(self):
        remove_expense_by_apartment(self.expenses, 2)
        self.assertEqual(len(self.expenses), 2)
        self.assertTrue(all(e.apartment != 2 for e in self.expenses))

    def test_remove_expense_by_range(self):
        remove_expense_by_range(self.expenses, 1, 2)
        self.assertEqual(len(self.expenses), 1)
        self.assertTrue(all(e.apartment not in [1, 2] for e in self.expenses))

    def test_remove_expense_by_type(self):
        remove_expense_by_type(self.expenses, 'heating')
        self.assertEqual(len(self.expenses), 2)
        self.assertTrue(all(e.expense_type != 'heating' for e in self.expenses))

    def test_replace_expense(self):
        replace_expense(self.expenses, 1, 'water', 200)
        self.assertEqual(self.expenses[0].amount, 200)


if __name__ == '__main__':
    unittest.main()
