class UI05:
    def __init__(self, controller):
        self.service = controller

    def run(self):
        while True:
            self.print_menu()
            command = input("Enter command: ")
            match command:
                case "0":
                    return
                case "1":
                    self.service.print_graph()
                case "2":
                    n, colors = self.service.find_vertex_coloring()
                    #vector of colors for each vertex
                    if colors:
                        print(f"Vertex coloring with minimum number of colors: {n}")
                        for vertex, color in enumerate(colors):
                            print(f"Vertex {vertex}: Color {color}")
                    else:
                        print("No valid coloring found")
                case _:
                    print("Invalid command")

    def print_menu(self):
        print("Task: Given an undirected graph, find a vertex coloring with minimum number of colors.")
        print("1. Display the graph")
        print("2. Find vertex coloring with minimum number of colors")
        print("0. Exit")