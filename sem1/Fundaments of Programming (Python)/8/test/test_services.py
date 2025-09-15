import unittest
from src.services.AssignmentServices import AssignmentService
from src.services.GradeServices import GradeService
from src.services.StudentServices import StudentService
from src.repository.MemoryRepository import MemoryRepository
from src.domain.Assignment import Assignment
from src.domain.Grade import Grade
from src.domain.Student import Student
from src.repository.Repository_Exception import RepositoryException

class TestAssignmentService(unittest.TestCase):
    def setUp(self):
        self.repo = MemoryRepository()
        self.service = AssignmentService(self.repo)
        self.assignment = Assignment(1, "Description", "2023-12-31")

    def test_add_assignment(self):
        self.service.add_assignment(1, "Description", "2023-12-31")
        self.assertEqual(len(self.repo), 1)
        self.assertEqual(self.repo.find(1), self.assignment)

    def test_add_duplicate_assignment(self):
        self.service.add_assignment(1, "Description", "2023-12-31")
        with self.assertRaises(RepositoryException):
            self.service.add_assignment(1, "Description", "2023-12-31")

    def test_remove_assignment(self):
        self.service.add_assignment(1, "Description", "2023-12-31")
        self.service.remove_assignment(1)
        self.assertEqual(len(self.repo), 0)
        self.assertIsNone(self.repo.find(1))

    def test_remove_nonexistent_assignment(self):
        with self.assertRaises(RepositoryException):
            self.service.remove_assignment(1)


class TestGradeService(unittest.TestCase):
    def setUp(self):
        self.repo = MemoryRepository()
        self.service = GradeService(self.repo)
        self.grade = Grade(1, 1, 1, 10)

    def test_add_grade(self):
        self.service.add_grade(1, 1, 1, 10)
        self.assertEqual(len(self.repo), 1)
        self.assertEqual(self.repo.find(1), self.grade)

    def test_add_duplicate_grade(self):
        self.service.add_grade(1, 1, 1, 10)
        with self.assertRaises(RepositoryException):
            self.service.add_grade(1, 1, 1, 10)

    def test_remove_grade_for_student(self):
        self.service.add_grade(1, 1, 1, 10)
        self.service.remove_grade_for_student(1)
        self.assertEqual(len(self.repo), 0)
        self.assertIsNone(self.repo.find(1))

    def test_remove_grade_for_assignment(self):
        self.service.add_grade(1, 1, 1, 10)
        self.service.remove_grade_for_assignment(1)
        self.assertEqual(len(self.repo), 0)
        self.assertIsNone(self.repo.find(1))

    
    def test_update_grade(self):
        self.service.add_grade(1, 1, 1, 10)
        self.service.update_grade(1, 2, 2, 9)
        updated_grade = self.repo.find(1)
        self.assertEqual(updated_grade.student_id, 2)
        self.assertEqual(updated_grade.assignment_id, 2)
        self.assertEqual(updated_grade.grade, 9)

class TestStudentService(unittest.TestCase):
    def setUp(self):
        self.repo = MemoryRepository()
        self.service = StudentService(self.repo)
        self.student = Student(1, "John Doe", 101)

    def test_add_student(self):
        self.service.add_student(1, "John Doe", 101)
        self.assertEqual(len(self.repo), 1)
        self.assertEqual(self.repo.find(1), self.student)

    def test_add_duplicate_student(self):
        self.service.add_student(1, "John Doe", 101)
        with self.assertRaises(RepositoryException):
            self.service.add_student(1, "John Doe", 101)

    def test_remove_student(self):
        self.service.add_student(1, "John Doe", 101)
        self.service.remove_student(1)
        self.assertEqual(len(self.repo), 0)
        self.assertIsNone(self.repo.find(1))

    def test_remove_nonexistent_student(self):
        with self.assertRaises(RepositoryException):
            self.service.remove_student(1)


if __name__ == '__main__':
    unittest.main()