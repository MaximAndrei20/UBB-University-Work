from src.repository.MemoryRepository import MemoryRepository
from src.repository.Repository_Exception import RepositoryException

class TextFileRepository(MemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.filename = file_name

    def save_to_file(self):
        """
        Save the current list of students to the text file.
        """
        with open(self.filename, 'w') as file:
            for obj in self._objects:
                file.write(str(obj) + '\n')


