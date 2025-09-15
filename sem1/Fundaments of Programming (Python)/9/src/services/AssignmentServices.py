from src.domain.Assignment import Assignment, AssignmentValidator
from src.services.undo_services import FunctionCall, Operation, CascadedOperation

class AssignmentService:
    def __init__(self, assignment_repository, undo_service, grade_service):
        self.__repository = assignment_repository
        self._undo_service = undo_service
        self._grade_service = grade_service

    def add_assignment(self, assignment_id, description, deadline):
        assignment = Assignment(assignment_id, description, deadline)
        AssignmentValidator.validate(assignment)
        self.__repository.store(assignment)

        functionRedo = FunctionCall(self.__repository.store, assignment)
        functionUndo = FunctionCall(self.__repository.delete, assignment_id)

        self._undo_service.recordUndo(Operation(functionUndo, functionRedo))
        return assignment

    def remove_assignment(self, assignment_id):
        assignment = self.__repository.delete(assignment_id)

        grades = self._grade_service.filter_grades(None, assignment)
        for grade in grades:
            self._grade_service.delete_grade(grade.id)

        functionRedo = FunctionCall(self.__repository.delete, assignment_id)
        functionUndo = FunctionCall(self.__repository.store, assignment)
        operations = [Operation(functionUndo, functionRedo)]

        gradeRepo = self._grade_service.repository
        for grade in grades:
            functionRedo = FunctionCall(gradeRepo.delete, grade.id)
            functionUndo = FunctionCall(gradeRepo.store, grade)

            operations.append(Operation(functionUndo, functionRedo))

        self._undo_service.recordUndo(CascadedOperation(*operations))
        return assignment

    def list_assignments(self):
        for assignment in self.__repository.get_all():
            print(assignment)

    @property
    def repository(self):
        return self.__repository

    def update_assignment(self, assignment_id, description, deadline):
        old_assignment = self.__repository.find(assignment_id)
        if old_assignment is None:
            raise ValueError("Assignment not found")

        new_assignment = Assignment(assignment_id, description, deadline)
        AssignmentValidator.validate(new_assignment)
        self.__repository.update(new_assignment)

        functionRedo = FunctionCall(self.__repository.update, new_assignment)
        functionUndo = FunctionCall(self.__repository.update, old_assignment)

        self._undo_service.recordUndo(Operation(functionUndo, functionRedo))
        return new_assignment