import pickle
from src.repository.MemoryRepository import MemoryRepository

class BinaryFileRepository(MemoryRepository):
    def __init__(self, filename):
        super().__init__()
        self.filename = filename
        self._load_from_file()

    def _load_from_file(self):
        try:
            with open(self.filename, "rb") as file:
                self._entities = pickle.load(file)
        except (FileNotFoundError, EOFError, pickle.UnpicklingError, ValueError):
            self._entities = []

    def _save_to_file(self):
        with open(self.filename, "wb") as file:
            pickle.dump(self._entities, file)

    def store(self, entity):
        super().store(entity)
        self._save_to_file()

    def delete(self, entity_id):
        super().delete(entity_id)
        self._save_to_file()

    def update(self, updated_entity):
        super().update(updated_entity)
        self._save_to_file()