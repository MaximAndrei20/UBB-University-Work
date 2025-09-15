import pickle
from src.domain.student import Student
import texttable as tt

class BinaryFileRepository:
    """
    Repository class for managing students using binary file storage.
    """

    def __init__(self, filename):
        """
        Initialize the repository with a binary file.

        :param filename: The name of the binary file.
        """
        self.filename = filename
        self.students = self._load_from_file()
        self.clear_binary_file()

    def _load_from_file(self):
        """
        Load students from the binary file.

        :return: A list of students.
        """
        try:
            with open(self.filename, 'rb') as file:
                return pickle.load(file)
        except (FileNotFoundError, EOFError):
            return []

    def clear_binary_file(self):
        """
        Clear the contents of the binary file.
        """
        with open(self.filename, 'wb') as file:
            file.truncate(0)

    def save_to_file(self):
        """
        Save the current list of students to the binary file.
        """
        with open(self.filename, 'wb') as file:
            pickle.dump(self.students, file)

    def add_student(self, student_id, name, group):
        """
        Add a new student to the repository.

        :param student_id: The ID of the student.
        :param name: The name of the student.
        :param group: The group of the student.
        """
        student = Student(student_id, name, group)
        self.students.append(student)
        self.save_to_file()

    def __str__(self):
        """
        Return a string representation of the students in a table format.

        :return: A string representation of the students.
        """
        table = tt.Texttable()
        table.add_row(["ID", "Name", "Group"])
        for student in self.students:
            table.add_row([student.student_id, student.name, student.group])
        return table.draw()