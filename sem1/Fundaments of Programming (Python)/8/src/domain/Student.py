class Student(object):
    def __init__(self, _id, name, group):
        self._id = _id
        self.name = name
        self.group = group

    @property
    def id(self):
        return self._id

    @id.setter
    def id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Student ID must be a positive integer")
        self._id = value

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        if not isinstance(value, str) or not value.strip():
            raise ValueError("Name must be a non-empty string")
        self.__name = value

    @property
    def group(self):
        return self.__group

    @group.setter
    def group(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Group must be a positive integer")
        self.__group = value

    def __eq__(self, other):
        if not isinstance(other, Student):
            return False
        return self._id == other._id

    def __str__(self):
        return f"Student ID: {self._id}, Name: {self.name}, Group: {self.group}"

    def __repr__(self):
        return str(self)

class StudentValidator:
    @staticmethod
    def validate(student):
        if not isinstance(student, Student):
            raise TypeError("Not a student")
        _errors = []
        if student.id <= 0:
            _errors.append("Invalid id")
        if not student.name.strip() and not isinstance(student.name, str):
            _errors.append("Invalid name")
        if student.group <= 0:
            _errors.append("Invalid group")
        if _errors:
            raise ValueError(_errors)