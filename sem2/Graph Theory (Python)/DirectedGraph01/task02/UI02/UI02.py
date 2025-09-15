class UI02:
    def __init__(self, controller):
        self._controller = controller
        self._running = True

    def run(self):
        while self._running:
            self._print_menu()
            command = input("Enter command: ")
            match command:
                case "0":
                    self._running = False
                    return
                case "1":
                    self._bfs()
                case "2":
                    self._controller.print_graph()
                case "3":
                    stc = self._controller.get_strongly_connected_components()
                    if len(stc) == 0:
                        print("No strongly connected components")
                    else:
                        print("The strongly connected components are: ")
                        for component in stc:
                            for i in range(len(component) - 1):
                                print(f"{component[i]} -> ", end="")
                case _:
                    print("Invalid command")

    def _bfs(self):
        inp = input("Enter the two vertices: ")
        try:
            u, v = map(int, inp.split())
        except Exception:
            print("Invalid input")
            return
        path = self._controller.bfs(u, v)
        if len(path) == 0:
            print("There is no path between the two vertices")
        else:
            print("The path is: ")
            for i in range(len(path) - 1):
                print(f"{path[i]} -> ", end="")
            print(path[-1])

    @staticmethod
    def _print_menu():
        print("1. Input the two vertices for the BFS")
        print("2. Print the graph")
        print("3. Get the number of strongly connected components")
        print("0. Exit")