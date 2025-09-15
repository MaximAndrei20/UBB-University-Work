# src/repository/text_file_repository.py
import os
from src.domain.student import Student
import texttable as tt

class TextFileRepository:
    """
    Repository class for managing students using text file storage.
    """

    def __init__(self, filename):
        """
        Initialize the repository with a text file.

        :param filename: The name of the text file.
        """
        self.filename = filename
        self.students = self._load_from_file()
        self.clear_file()

    def clear_file(self):
        """
        Clear the contents of the text file.
        """
        with open(self.filename, 'w') as file:
            file.truncate(0)

    def _load_from_file(self):
        """
        Load students from the text file.

        :return: A list of students.
        """
        if not os.path.exists(self.filename):
            return []
        with open(self.filename, 'r') as file:
            students = []
            for line in file:
                student_id, name, group = line.strip().split(',')
                students.append(Student(int(student_id), name, int(group)))
            return students

    def save_to_file(self):
        """
        Save the current list of students to the text file.
        """
        with open(self.filename, 'w') as file:
            for student in self.students:
                file.write(f"{student.student_id},{student.name},{student.group}\n")

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