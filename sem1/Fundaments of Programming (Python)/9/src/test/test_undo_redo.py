# test_undo_redo.py
import unittest
from src.services.GradeServices import GradeService
from src.repository.MemoryRepository import MemoryRepository
from src.services.undo_services import UndoService
from src.domain.Grade import Grade

class TestUndoRedo(unittest.TestCase):
    def setUp(self):
        self.grade_repository = MemoryRepository()
        self.student_repository = MemoryRepository()
        self.assignment_repository = MemoryRepository()
        self.undo_service = UndoService()
        self.grade_service = GradeService(self.grade_repository, self.student_repository, self.assignment_repository, self.undo_service)

    def test_undo_add_grade(self):
        # Add a grade
        self.grade_service.add_grade(1, 1, 1, 10)
        self.assertEqual(len(self.grade_repository.get_all()), 1)

        # Undo the add operation
        self.undo_service.undo()
        self.assertEqual(len(self.grade_repository.get_all()), 0)

    def test_redo_add_grade(self):
        # Add a grade
        self.grade_service.add_grade(1, 1, 1, 10)
        self.undo_service.undo()
        self.assertEqual(len(self.grade_repository.get_all()), 0)

        # Redo the add operation
        self.undo_service.redo()
        self.assertEqual(len(self.grade_repository.get_all()), 1)

if __name__ == "__main__":
    unittest.main()