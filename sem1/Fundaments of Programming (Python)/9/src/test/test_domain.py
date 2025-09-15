import unittest
from src.domain.Assignment import Assignment, AssignmentValidator
from src.domain.Grade import Grade, GradeValidator
from src.domain.validator_exception import ValidatorException
from src.domain.Student import Student, StudentValidator

class TestAssignment(unittest.TestCase):
    def test_assignment_creation(self):
        assignment = Assignment(1, "Description", "2023-12-31")
        self.assertEqual(assignment.id, 1)
        self.assertEqual(assignment.description, "Description")
        self.assertEqual(assignment.deadline, "2023-12-31")

    def test_assignment_validation(self):
        assignment = Assignment(1, "Description", "2023-12-31")
        AssignmentValidator.validate(assignment)
        with self.assertRaises(ValueError):
            invalid_assignment = Assignment(-1, "", "")
            AssignmentValidator.validate(invalid_assignment)

class TestGrade(unittest.TestCase):
    def test_grade_creation(self):
        grade = Grade(1, 1, 1, 10)
        self.assertEqual(grade.id, 1)
        self.assertEqual(grade.student_id, 1)
        self.assertEqual(grade.assignment_id, 1)
        self.assertEqual(grade.grade, 10)

    def test_grade_validation(self):
        grade = Grade(1, 1, 1, 10)
        GradeValidator.validate(grade)
        with self.assertRaises(ValidatorException):
            invalid_grade = Grade(1, -1, -1, 11)
            GradeValidator.validate(invalid_grade)

class TestStudent(unittest.TestCase):
    def test_student_creation(self):
        student = Student(1, "John Doe", 101)
        self.assertEqual(student.id, 1)
        self.assertEqual(student.name, "John Doe")
        self.assertEqual(student.group, 101)

    def test_student_validation(self):
        student = Student(1, "John Doe", 101)
        StudentValidator.validate(student)
        with self.assertRaises(ValueError):
            invalid_student = Student(-1, "", -1)
            StudentValidator.validate(invalid_student)

if __name__ == '__main__':
    unittest.main()