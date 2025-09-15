# test_statistics.py
import unittest
from datetime import datetime
from src.services.GradeServices import GradeService
from src.repository.MemoryRepository import MemoryRepository
from src.domain.Student import Student
from src.services.undo_services import UndoService

class TestStatistics(unittest.TestCase):
    def setUp(self):
        self.grade_repository = MemoryRepository()
        self.student_repository = MemoryRepository()
        self.assignment_repository = MemoryRepository()
        self.undo_service = UndoService()
        self.grade_service = GradeService(self.grade_repository, self.student_repository, self.assignment_repository, self.undo_service)

    def test_students_by_assignment(self):
        assignment_id = 1  # Example assignment ID
        students_with_grades = self.grade_service.get_students_by_assignment(assignment_id)
        self.assertIsInstance(students_with_grades, list)
        for student, grade in students_with_grades:
            self.assertIsInstance(student, Student)
            self.assertIsInstance(grade, int)

    def test_late_students(self):
        students = self.grade_service.get_all_late_students()
        self.assertIsInstance(students, list)
        for student in students:
            self.assertIsInstance(student, Student)

    def test_best_students(self):
        best_students = self.grade_service.get_best_students()
        self.assertIsInstance(best_students, list)
        for student, avg_grade in best_students:
            self.assertIsInstance(student, Student)
            self.assertIsInstance(avg_grade, float)

if __name__ == "__main__":
    unittest.main()