# src/tests/test_services.py
import unittest
from src.services.services import Services
from src.repository.memory_repository import MemoryRepository
from src.domain.student import Student
from io import StringIO
import sys

class TestServices(unittest.TestCase):
    def setUp(self):
        self.repository = MemoryRepository()
        self.services = Services(self.repository)
        self.services.add_student(1, "Ana", 911)
        self.services.add_student(2, "Andrei", 912)

    def test_add_student(self):
        self.services.add_student(3, "Maria", 913)
        students = self.services.repository.students
        self.assertEqual(len(students), 3)
        self.assertEqual(students[2].student_id, 3)
        self.assertEqual(students[2].name, "Maria")
        self.assertEqual(students[2].group, 913)

    def test_filter_students(self):
        captured_output = StringIO()
        original_stdout = sys.stdout
        sys.stdout = captured_output
        try:
            self.services.filter_students(911)
        finally:
            sys.stdout = original_stdout
        output = captured_output.getvalue().strip()
        expected_output = "+----+--------+-------+\n| ID | Name   | Group |\n+----+--------+-------+\n| 2  | Andrei | 912   |\n+----+--------+-------+"
        self.assertEqual(output, expected_output)

    def test_filter_students_no_match(self):
        captured_output = StringIO()
        original_stdout = sys.stdout
        sys.stdout = captured_output
        try:
            self.services.filter_students(999)
        finally:
            sys.stdout = original_stdout
        output = captured_output.getvalue().strip()
        expected_output = "+----+--------+-------+\n| ID | Name   | Group |\n+----+--------+-------+\n| 1  | Ana    | 911   |\n+----+--------+-------+\n| 2  | Andrei | 912   |\n+----+--------+-------+"
        self.assertEqual(output, expected_output)

if __name__ == "__main__":
    unittest.main()