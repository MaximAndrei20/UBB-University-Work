from src.domain.Assignment import Assignment, AssignmentValidator

class AssignmentService:
    def __init__(self, assignment_repository):
        self.__repository = assignment_repository

    def add_assignment(self, assignment_id, description, deadline):
        assignment = Assignment(assignment_id, description, deadline)
        AssignmentValidator.validate(assignment)
        self.__repository.store(assignment)

    def remove_assignment(self, assignment_id):
        self.__repository.delete(assignment_id)

    def list_assignments(self):
        for assignment in self.__repository.get_all():
            print(assignment)

    @property
    def repository(self):
        return self.__repository