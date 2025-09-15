from src.domain.Student import Student, StudentValidator

class StudentService:
    def __init__(self, student_repository):
        self.__repository = student_repository

    @property
    def repository(self):
        return self.__repository

    def add_student(self, student_id, name, group):
        student = Student(student_id, name, group)
        StudentValidator.validate(student)
        self.__repository.store(student)

    def remove_student(self, student_id):
        self.__repository.delete(student_id)

    def list_students(self):
        for student in self.__repository.get_all():
            print(student)

    def update_student(self, student_id, name, group):
        student = Student(student_id, name, group)
        StudentValidator.validate(student)
        self.__repository.update(student)