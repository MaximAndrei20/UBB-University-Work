import unittest
from src.repository.MemoryRepository import MemoryRepository
from src.repository.Repository_Exception import RepositoryException

class TestEntity:
    def __init__(self, id):
        self.id = id

    def __str__(self):
        return f"Entity({self.id})"

class TestMemoryRepository(unittest.TestCase):
    def setUp(self):
        self.repo = MemoryRepository()
        self.entity = TestEntity(1)

    def test_store(self):
        self.repo.store(self.entity)
        self.assertEqual(len(self.repo), 1)
        self.assertEqual(self.repo.find(1), self.entity)

    def test_store_duplicate(self):
        self.repo.store(self.entity)
        with self.assertRaises(RepositoryException):
            self.repo.store(self.entity)

    def test_update(self):
        self.repo.store(self.entity)
        updated_entity = TestEntity(1)
        self.repo.update(updated_entity)
        self.assertEqual(self.repo.find(1), updated_entity)

    def test_update_nonexistent(self):
        with self.assertRaises(RepositoryException):
            self.repo.update(self.entity)

    def test_find(self):
        self.repo.store(self.entity)
        self.assertEqual(self.repo.find(1), self.entity)
        self.assertIsNone(self.repo.find(2))

    def test_delete(self):
        self.repo.store(self.entity)
        self.repo.delete(1)
        self.assertEqual(len(self.repo), 0)
        self.assertIsNone(self.repo.find(1))

    def test_delete_nonexistent(self):
        with self.assertRaises(RepositoryException):
            self.repo.delete(1)

    def test_get_all(self):
        self.repo.store(self.entity)
        self.assertEqual(self.repo.get_all(), [self.entity])

    def test_len(self):
        self.assertEqual(len(self.repo), 0)
        self.repo.store(self.entity)
        self.assertEqual(len(self.repo), 1)

    def test_str(self):
        self.repo.store(self.entity)
        self.assertEqual(str(self.repo), "Entity(1)\n")

if __name__ == '__main__':
    unittest.main()