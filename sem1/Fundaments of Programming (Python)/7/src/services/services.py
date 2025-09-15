import copy

from src.repository.text_file_repository import TextFileRepository
from src.repository.binary_file_repository import BinaryFileRepository

class Services:
    def __init__(self, repo):
        self.repository = repo
        self.__undo_stack = []

    def add_student(self, student_id, name, group):
        if not isinstance(group, int):
            raise ValueError("Group must be an integer")
        self.__undo_stack.append(copy.deepcopy(self.repository))
        self.repository.add_student(student_id, name, group)

    def print_students(self):
        return self.repository.__str__()

    def filter_students(self, group):
        self.__undo_stack.append(copy.deepcopy(self.repository))
        self.repository.students = [student for student in self.repository.students if student.group != group]
        print(self.print_students())
        self.undo_last_operation()

    def undo_last_operation(self):
        if not self.__undo_stack:
            raise ValueError("No more undos")
        self.repository = self.__undo_stack.pop()
        if isinstance(self.repository, TextFileRepository):
            self.repository.save_to_file()
        if isinstance(self.repository, BinaryFileRepository):
            self.repository.save_to_file()


    def get_all_students(self):
        return self.repository.students
