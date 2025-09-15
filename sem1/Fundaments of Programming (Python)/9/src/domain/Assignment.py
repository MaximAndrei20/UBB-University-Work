from src.domain.validator_exception import ValidatorException

class Assignment(object):
    def __init__(self, assignment_id, description, deadline):
        self._id = assignment_id
        self.__description = description
        self.__deadline = deadline

    @property
    def id(self):
        return self._id

    @id.setter
    def id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Assignment ID must be a positive integer")
        self._id = value

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, value):
        if not isinstance(value, str) or not value.strip():
            raise ValueError("Description must be a non-empty string")
        self.__description = value

    @property
    def deadline(self):
        return self.__deadline

    @deadline.setter
    def deadline(self, value):
        if not isinstance(value, str) or not value.strip():
            raise ValueError("Deadline must be a non-empty string")
        self.__deadline = value

    def __eq__(self, other):
        return self.id == other.id

    def __str__(self):
        return f"ID: {self.id}, Description: {self.description}, Deadline: {self.deadline}"

class AssignmentValidator(object):
    @staticmethod
    def validate(assignment):
        if not isinstance(assignment, Assignment):
            raise TypeError("Not an assignment")
        _errors = []
        if assignment.id <= 0:
            _errors.append("Invalid id")
        if not assignment.description.strip() and not isinstance(assignment.description, str):
            _errors.append("Invalid description")
        if not assignment.deadline.strip() and not isinstance(assignment.deadline, str):
            _errors.append("Invalid deadline")
        if _errors:
            raise ValueError(_errors)


