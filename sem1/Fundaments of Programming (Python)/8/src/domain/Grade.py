from src.domain.validator_exception import ValidatorException

class Grade(object):
    def __init__(self, grade_id, student_id, assignment_id, grade):
        self._id = grade_id
        self.__student_id = student_id
        self.__assignment_id = assignment_id
        self.__grade = grade

    @property
    def id(self):
        return self._id

    @property
    def student_id(self):
        return self.__student_id

    @student_id.setter
    def student_id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Student ID must be a positive integer")
        self.__student_id = value

    @property
    def assignment_id(self):
        return self.__assignment_id

    @assignment_id.setter
    def assignment_id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Assignment ID must be a positive integer")
        self.__assignment_id = value

    @property
    def grade(self):
        return self.__grade

    @grade.setter
    def grade(self, value):
        if not isinstance(value, int) or value < 0 or value > 10:
            raise ValueError("Grade must be an integer between 0 and 10")
        self.__grade = value

    def __eq__(self, other):
        return self.student_id == other.student_id and self.assignment_id == other.assignment_id

    def __str__(self):
        return f"Student ID: {self.student_id}, Assignment ID: {self.assignment_id}, Grade: {self.grade}"

class GradeValidator:
    @staticmethod
    def validate(grade):
        if not isinstance(grade, Grade):
            raise TypeError("Not a grade")
        _errors = []
        if grade.student_id <= 0:
            _errors.append("Invalid student id")
        if grade.assignment_id <= 0:
            _errors.append("Invalid assignment id")
        if grade.grade < 0 or grade.grade > 10:
            _errors.append("Invalid grade")
        if _errors:
            raise ValidatorException(_errors)
