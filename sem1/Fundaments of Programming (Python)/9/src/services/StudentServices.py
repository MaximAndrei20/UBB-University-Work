from random import randint

from src.domain.Student import Student, StudentValidator
from src.services.undo_services import FunctionCall, Operation, CascadedOperation

class StudentService:
    def __init__(self, student_repository, undo_service, grade_service):
        self.__repository = student_repository
        self._undo_service = undo_service
        self._grade_service = grade_service

    @property
    def repository(self):
        return self.__repository

    def generate_id(self):
        id = randint(1, 1000)
        while self.__repository.find(id) is not None:
            id = randint(1, 1000)
        return id

    def add_student(self, student_id, name, group):
        if student_id == -1:
            student_id = self.generate_id()
        student = Student(student_id, name, group)
        StudentValidator.validate(student)
        self.__repository.store(student)


        functionRedo = FunctionCall(self.__repository.store, student)
        functionUndo = FunctionCall(self.__repository.delete, student_id)

        self._undo_service.recordUndo(Operation(functionUndo, functionRedo))
        return student

    def remove_student(self, student_id):
        student = self.__repository.delete(student_id)


        grades = self._grade_service.filter_grades(student, None)
        for grade in grades:
            self._grade_service.delete_grade(grade.id)

        functionRedo = FunctionCall(self.__repository.delete, student_id)
        functionUndo = FunctionCall(self.__repository.store, student)
        operations = [Operation(functionUndo, functionRedo)]

        gradeRepo = self._grade_service.repository
        for grade in grades:
            functionRedo = FunctionCall(gradeRepo.delete, grade.id)
            functionUndo = FunctionCall(gradeRepo.store, grade)

            operations.append(Operation(functionUndo, functionRedo))

        self._undo_service.recordUndo(CascadedOperation(*operations))
        return student

    def list_students(self):
        for student in self.__repository.get_all():
            print(student)

    def update_student(self, student_id, name, group):
        old_student = self.__repository.find(student_id)
        if old_student is None:
            raise ValueError("Student not found")

        new_student = Student(student_id, name, group)
        StudentValidator.validate(new_student)
        self.__repository.update(new_student)

        functionRedo = FunctionCall(self.__repository.update, new_student)
        functionUndo = FunctionCall(self.__repository.update, old_student)

        self._undo_service.recordUndo(Operation(functionUndo, functionRedo))