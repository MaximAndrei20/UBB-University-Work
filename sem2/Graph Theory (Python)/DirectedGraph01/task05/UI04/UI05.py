class UI04:
    def __init__(self, service):
        self.service = service

    def run(self):
        while True:
            self._print_menu()
            command = input("Enter command: ")
            match command:
                case "0":
                    return
                case "1":
                    self.service.print_graph()
                case "2":
                    if self.service.is_dag():
                        print("The graph is a DAG")
                    else:
                        print("The graph is not a DAG")
                    self.service.topological_sort()
                case "3":
                    self.service.calculate_earliest_and_latest_start_times()
                    print(f"Total time of the project: {self.service.get_total_time()}")
                    self.service.print_earliest_and_latest_start_times()
                case "4":
                    critical_activities = self.service.get_critical_activities()
                    if critical_activities:
                        print("Critical activities:")
                        for activity in critical_activities:
                            print(activity)
                    else:
                        print("No critical activities found")
                case _:
                    print("Invalid command")

    def _print_menu(self):
        print("Task: Write a program that, given a list of activities with duration and list of prerequisites for each activity, does the following:\nverify if the corresponding graph is a DAG and performs a topological sorting of the activities using the algorithm based on predecessor counters;\nprints the earliest and the latest starting time for each activity and the total time of the project.\nprints the critical activities.\n")
        print("1. Display the graph")
        print("2. Verify if the corresponding graph is a DAG and performs a topological sorting of the activities using the algorithm based on predecessor counters;")
        print("3. Prints the earliest and the latest starting time for each activity and the total time of the project.")
        print("4. Prints the critical activities.")
        print("0. Exit")


    def display_info(self):
        pass