from src.repository.MemoryRepository import MemoryRepository
from src.ui.ui import UI
from src.services.StudentServices import StudentService
from src.services.AssignmentServices import AssignmentService
from src.services.GradeServices import GradeService
from src.repository.TextFileRepository import TextFileRepository
from src.domain.Student import Student
from src.domain.Assignment import Assignment
from src.domain.Grade import Grade
from src.repository.BinaryFileRepository import BinaryFileRepository
import pickle
from src.services.undo_services import UndoService

def add_data(students_service, assignments_service, grades_service):
    students_service.add_student(1, "Alice", 1)
    students_service.add_student(2, "Bob", 2)
    students_service.add_student(3, "Charlie", 1)
    students_service.add_student(4, "David", 2)
    students_service.add_student(5, "Eve", 1)


    assignments_service.add_assignment(1, "Assignment 1", "10.10.2021")
    assignments_service.add_assignment(2, "Assignment 2", "11.10.2021")
    assignments_service.add_assignment(3, "Assignment 3", "12.10.2021")
    assignments_service.add_assignment(4, "Assignment 4", "13.10.2021")

    grades_service.add_grade(1, 1, 1, 10)
    grades_service.add_grade(2, 2, 1, 9)
    grades_service.add_grade(3, 3, 1, 8)
    grades_service.add_grade(4, 4, 1, 7)
    grades_service.add_grade(5, 5, 1, 6)
    grades_service.add_grade(6, 1, 2, 10)
    grades_service.add_grade(7, 2, 2, 9)
    grades_service.add_grade(8, 3, 2, 8)

def add_students_from_textfile_to_repo(students_repo, filename):
    # format: Student ID: 1, Name: Alice, Group: 1
    with open(filename, "rt") as file:
        lines = file.read().splitlines()
        for line in lines:
            line = line.split(", ")
            student_id = int(line[0].split(": ")[1])
            name = line[1].split(": ")[1]
            group = int(line[2].split(": ")[1])
            student = Student(student_id, name, group)
            students_repo.store(student)

def add_assignments_from_textfile_to_repo(assignments_repo, filename):
    #format: ID: 1, Description: Assignment 1, Deadline: 10.10.2021
    with open(filename, "rt") as file:
        lines = file.read().splitlines()
        for line in lines:
            line = line.split(", ")
            assignment_id = int(line[0].split(": ")[1])
            description = line[1].split(": ")[1]
            deadline = line[2].split(": ")[1]
            assignment = Assignment(assignment_id, description, deadline)
            assignments_repo.store(assignment)

def add_grades_from_textfile_to_repo(grades_repo, filename):
    #format: Student ID: 1, Assignment ID: 1, Grade: 10
    #note: grade.id will be hardcoded using a variable that increases each time a grade is added
    grade_id = 1
    with open(filename, "rt") as file:
        lines = file.read().splitlines()
        for line in lines:
            line = line.split(", ")
            student_id = int(line[0].split(": ")[1])
            assignment_id = int(line[1].split(": ")[1])
            grade = int(line[2].split(": ")[1])
            grades_repo.store(Grade(grade_id, student_id, assignment_id, grade))
            grade_id += 1

def add_students_from_binaryfile_to_repo(students_repo, filename):
    with open(filename, "rb") as file:
        content = pickle.load(file)
        for student in content:
            student_id = student["id"]
            name = student["name"]
            group = student["group"]
            student_obj = Student(student_id, name, group)
            students_repo.store(student_obj)

def add_assignments_from_binaryfile_to_repo(assignments_repo, filename):
    with open(filename, "rb") as file:
        content = pickle.load(file)
        for assignment in content:
            assignment_id = assignment["id"]
            description = assignment["description"]
            deadline = assignment["deadline"]
            assignment_obj = Assignment(assignment_id, description, deadline)
            assignments_repo.store(assignment_obj)

def add_grades_from_binaryfile_to_repo(grades_repo, filename):
    grade_id = 1
    with open(filename, "rb") as file:
        content = pickle.load(file)
        for grade in content:
            student_id = grade["student_id"]
            assignment_id = grade["assignment_id"]
            grade_value = grade["grade"]
            grade_obj = Grade(grade_id, student_id, assignment_id, grade_value)
            grades_repo.store(grade_obj)
            grade_id += 1


def main():
    with open("settings.properties", "rt") as file:
        properties = file.read().splitlines()
        properties = [property.split("=") for property in properties]
        properties = {property[0].strip(): property[1].strip().strip('""') for property in properties}

    if properties["repository"] == "inmemory":
        students_repo = MemoryRepository()
        assignments_repo = MemoryRepository()
        grades_repo = MemoryRepository()
        undo_service = UndoService()
        grades_service = GradeService(grades_repo, students_repo, assignments_repo, undo_service)
        students_service = StudentService(students_repo, undo_service, grades_service)
        assignments_service = AssignmentService(assignments_repo, undo_service, grades_service)

        add_data(students_service, assignments_service, grades_service)

        ui = UI(students_service, assignments_service, grades_service, undo_service)
        ui.run()

    elif properties["repository"] == "textfiles":
        #print(properties["students"])
        student_repo = TextFileRepository(properties["students"])
        assignment_repo = TextFileRepository(properties["assignments"])
        grade_repo = TextFileRepository(properties["grades"])
        undo_service = UndoService()
        grades_service = GradeService(grade_repo, student_repo, assignment_repo, undo_service)
        students_service = StudentService(student_repo, undo_service, grades_service)
        assignments_service = AssignmentService(assignment_repo, undo_service, grades_service)


        add_students_from_textfile_to_repo(student_repo, properties["students"])
        add_assignments_from_textfile_to_repo(assignment_repo, properties["assignments"])
        add_grades_from_textfile_to_repo(grade_repo, properties["grades"])

        ui = UI(students_service, assignments_service, grades_service, undo_service)
        ui.run()
        student_repo.save_to_file()
        assignment_repo.save_to_file()
        grade_repo.save_to_file()

    elif properties["repository"] == "binaryfiles":
        students_repo = BinaryFileRepository(properties["students"])
        assignments_repo = BinaryFileRepository(properties["assignments"])
        grades_repo = BinaryFileRepository(properties["grades"])
        undo_service = UndoService()
        grades_service = GradeService(grades_repo, students_repo, assignments_repo, undo_service)
        students_service = StudentService(students_repo, undo_service, grades_service)
        assignments_service = AssignmentService(assignments_repo, undo_service, grades_service)

        #add_students_from_binaryfile_to_repo(students_repo, properties["students"])
        #add_assignments_from_binaryfile_to_repo(assignments_repo, properties["assignments"])
        #add_grades_from_binaryfile_to_repo(grades_repo, properties["grades"])

        ui = UI(students_service, assignments_service, grades_service, undo_service)
        ui.run()


if __name__ == "__main__":
    main()
    