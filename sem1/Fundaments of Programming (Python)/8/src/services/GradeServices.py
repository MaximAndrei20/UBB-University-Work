from src.domain.Grade import Grade, GradeValidator


class GradeService:
    def __init__(self, grade_repository):
        self.__repository = grade_repository

    def add_grade(self, grade_id, student_id, assignment_id, grade):
        grade = Grade(grade_id, student_id, assignment_id, grade)
        GradeValidator.validate(grade)
        self.__repository.store(grade)

    def remove_grade_for_student(self, student_id):
        for grade in self.__repository.get_all():
            if grade.student_id == student_id:
                self.__repository.delete(grade.id)

    def remove_grade_for_assignment(self, assignment_id):
        for grade in self.__repository.get_all():
            if grade.assignment_id == assignment_id:
                self.__repository.delete(grade.id)

    def list_grades(self):
        for grade in self.__repository.get_all():
            print(grade)

    def update_grade(self, grade_id, student_id, assignment_id, grade):
        grade = Grade(grade_id, student_id, assignment_id, grade)
        GradeValidator.validate(grade)
        self.__repository.update(grade)

    @property
    def repository(self):
        return self.__repository