
from src.repository.Repository_Exception import RepositoryException

class UI(object):
    def __init__(self, serviceStudents, serviceAssignments, serviceGrades):
        self.__studentServices = serviceStudents
        self.__assignmentServices = serviceAssignments
        self.__gradeServices = serviceGrades

    @staticmethod
    def print_menu():
        print("\nMenu:")
        print("1. Add student")
        print("2. Remove student")
        print("3. Update student")
        print("4. List students")
        print("5. Add assignment")
        print("6. Remove assignment")
        print("7. Update assignment")
        print("8. List assignments")
        print("9. Give assignment to student")
        print("10. Give assignment to group")
        print("11. Grade student for assignment")
        print("12. List grades")
        print("13. Exit")

    def run(self):
        gradeidcounter = len(self.__gradeServices.repository.get_all())+1
        while True:
            self.print_menu()
            option = input("Enter option: ")
            match option:
                case "1":
                    try:
                        student_id = input("Enter student ID: ")
                        try:
                            student_id = int(student_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        name = input("Enter student name: ")
                        group = input("Enter student group: ")
                        try:
                            group = int(group)
                        except ValueError:
                            print("Invalid input")
                            continue
                        self.__studentServices.add_student(student_id, name, group)
                    except Exception as e:
                        print(e)
                case "2":
                    try:
                        student_id = input("Enter the ID of which student you want to remove: ")
                        try:
                            student_id = int(student_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        self.__studentServices.remove_student(student_id)
                        self.__gradeServices.remove_grade_for_student(student_id)
                    except Exception as e:
                        print(e)
                case "3":
                    try:
                        student_id = input("Enter the ID of which student you want to update: ")
                        try:
                            student_id = int(student_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        name = input("Enter the new name: ")
                        group = input("Enter the new group: ")
                        try:
                            group = int(group)
                        except ValueError:
                            print("Invalid input")
                            continue
                        self.__studentServices.update_student(student_id, name, group)
                    except Exception as e:
                        print(e)
                case "4":
                    self.__studentServices.list_students()
                case "5":
                    try:
                        assignment_id = input("Enter assignment ID: ")
                        try:
                            assignment_id = int(assignment_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        description = input("Enter assignment description: ")
                        deadline = input("Enter assignment deadline: ")
                        self.__assignmentServices.add_assignment(assignment_id, description, deadline)
                    except Exception as e:
                        print(e)
                case "6":
                    try:
                        assignment_id = input("Enter the ID of which assignment you want to remove: ")
                        try:
                            assignment_id = int(assignment_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        self.__assignmentServices.remove_assignment(assignment_id)
                        self.__gradeServices.remove_grade_for_assignment(assignment_id)
                    except Exception as e:
                        print(e)
                case "7":
                    try:
                        assignment_id = input("Enter the ID of which assignment you want to update: ")
                        try:
                            assignment_id = int(assignment_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        description = input("Enter the new description: ")
                        deadline = input("Enter the new deadline: ")
                        self.__assignmentServices.update_assignment(assignment_id, description, deadline)
                    except Exception as e:
                        print(e)
                case "8":
                    self.__assignmentServices.list_assignments()
                case "9":
                    try:
                        student_id = input("Enter student ID: ")
                        try:
                            student_id = int(student_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        assignment_id = input("Enter assignment ID: ")
                        try:
                            assignment_id = int(assignment_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        for student in self.__studentServices.repository.get_all():
                            if student.id == student_id:
                                for assignment in self.__assignmentServices.repository.get_all():
                                    if assignment.id == assignment_id:
                                        self.__gradeServices.add_grade(gradeidcounter, student_id, assignment_id, 0)
                                        gradeidcounter += 1
                    except Exception as e:
                        print(e)
                case "10":
                    try:
                        group = input("Enter group: ")
                        try:
                            group = int(group)
                        except ValueError:
                            print("Invalid input")
                            continue
                        assignment_id = input("Enter assignment ID: ")
                        try:
                            assignment_id = int(assignment_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        for student in self.__studentServices.repository.get_all():
                            if student.group == group:
                                for assignment in self.__assignmentServices.repository.get_all():
                                    if assignment.id == assignment_id:
                                        #if assignment if not already assigned to this student
                                        if not any(grade.student_id == student.id and grade.assignment_id == assignment_id for grade in self.__gradeServices.repository.get_all()):
                                            self.__gradeServices.add_grade(gradeidcounter, student.id, assignment_id, 0)
                                            gradeidcounter += 1


                    except Exception as e:
                        print(e)
                case "11":
                    try:
                        student_id = input("Enter student ID: ")
                        try:
                            student_id = int(student_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        assignment_id = input("Enter assignment ID: ")
                        try:
                            assignment_id = int(assignment_id)
                        except ValueError:
                            print("Invalid input")
                            continue
                        newGrade = input("Enter grade: ")
                        try:
                            newGrade = int(newGrade)
                        except ValueError:
                            print("Invalid input")
                            continue
                        for grade in self.__gradeServices.repository.get_all():
                            if grade.student_id == student_id and grade.assignment_id == assignment_id:
                                grade.grade = newGrade
                    except Exception as e:
                        print(e)
                case "12":
                    self.__gradeServices.list_grades()
                case "13":
                    print("Exiting...")
                    break