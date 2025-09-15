# src/repository/memory_repository.py
from texttable import Texttable
from src.domain.student import Student

class MemoryRepository(object):
    """
    Repository class for managing students in memory.
    """

    def __init__(self):
        """
        Initialize the repository with an empty list of students.
        """
        self.__students = []

    def add_student(self, stud_id, name, group):
        """
        Add a new student to the repository.

        :param stud_id: The ID of the student.
        :param name: The name of the student.
        :param group: The group of the student.
        :raises ValueError: If a student with the same ID already exists.
        """
        student = Student(stud_id, name, group)
        for s in self.__students:
            if s.student_id == stud_id:
                raise ValueError("Student with this ID already exists")
        self.__students.append(student)

    @property
    def students(self):
        """
        Get the list of students.

        :return: A list of students.
        """
        return self.__students

    @students.setter
    def students(self, students):
        """
        Set the list of students.

        :param students: A list of students.
        """
        self.__students = students

    def __str__(self):
        """
        Return a string representation of the students in a table format.

        :return: A string representation of the students.
        """
        if not self.__students:
            return "No students"
        texttable = Texttable()
        texttable.add_row(["ID", "Name", "Group"])
        for student in self.__students:
            texttable.add_row([student.student_id, student.name, student.group])
        return texttable.draw()