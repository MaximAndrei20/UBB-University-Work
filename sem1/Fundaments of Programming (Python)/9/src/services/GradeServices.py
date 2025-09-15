from src.domain.Grade import Grade, GradeValidator
from src.services.undo_services import FunctionCall, Operation, CascadedOperation
from datetime import datetime

class GradeService:
    def __init__(self, grade_repository, student_repository, assignment_repository, undo_service):
        self.__repository = grade_repository
        self._student_repository = student_repository
        self._assignment_repository = assignment_repository

        self._undoController = undo_service


    def add_grade(self, grade_id, student_id, assignment_id, grade):
        grade = Grade(grade_id, student_id, assignment_id, grade)
        GradeValidator.validate(grade)

        isGrade = False
        for newGrade in self.__repository.get_all():
            if newGrade.student_id == student_id and newGrade.assignment_id == assignment_id:
                isGrade = True
                break

        if not isGrade:
            self.__repository.store(grade)
        else:
            raise ValueError("Grade already exists")


        functionRedo = FunctionCall(self.__repository.store, grade)
        functionUndo = FunctionCall(self.__repository.delete, grade_id)

        self._undoController.recordUndo(Operation(functionUndo, functionRedo))
        return grade




    def remove_grade_for_student(self, student_id):
        repo = self.__repository.get_all()
        for grade in repo:
            if grade.student_id == student_id:
                self.__repository.delete(grade.id)

    def remove_grade(self, grade_id):
        grade = self.__repository.find(grade_id)
        if grade is None:
            raise ValueError("Grade not found")

        self.__repository.delete(grade_id)

        """
        functionRedo = FunctionCall(self.__repository.delete, grade_id)
        functionUndo = FunctionCall(self.__repository.store, grade)

        self._undoController.recordUndo(Operation(functionUndo, functionRedo))
        """
        return grade_id

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

    def filter_grades(self, student=None, assignment=None):
        result = []
        for grade in self.__repository.get_all():
            if student is not None and grade.student_id != student.id:
                continue
            if assignment is not None and grade.assignment_id != assignment.id:
                continue
            result.append(grade)
        return result
    @property
    def repository(self):
        return self.__repository

    def delete_grade(self, grade_id):
        self.__repository.delete(grade_id)
        return grade_id

    def get_students_by_assignment(self, assignment_id):
        grades = [grade for grade in self.__repository.get_all() if grade.assignment_id == assignment_id]
        grades.sort(key=lambda x: x.grade, reverse=True)
        students_with_grades = [(self._student_repository.find(grade.student_id), grade.grade) for grade in grades]
        return students_with_grades

    def string_to_date(self, date):
        return datetime.strptime(date, "%d.%m.%Y")

    def get_all_late_students(self):
        late_students = []
        for grade in self.__repository.get_all():
            assignment = self._assignment_repository.find(grade.assignment_id)
            if self.string_to_date(assignment.deadline) < datetime.now() and grade.grade == 0:
                student = self._student_repository.find(grade.student_id)
                if student not in late_students:
                    late_students.append(student)
        return late_students

    def get_best_students(self):
        student_grades = {}
        for grade in self.__repository.get_all():
            assignment = self._assignment_repository.find(grade.assignment_id)
            if grade.grade > 0 or self.string_to_date(assignment.deadline) < datetime.now():
                if grade.student_id not in student_grades:
                    student_grades[grade.student_id] = []
                student_grades[grade.student_id].append(grade.grade)

        student_averages = {student_id: sum(grades) / len(grades) for student_id, grades in student_grades.items()}
        sorted_students = sorted(student_averages.items(), key=lambda x: x[1], reverse=True)

        students_with_averages = [(self._student_repository.find(student_id), avg) for student_id, avg in sorted_students]
        return students_with_averages
