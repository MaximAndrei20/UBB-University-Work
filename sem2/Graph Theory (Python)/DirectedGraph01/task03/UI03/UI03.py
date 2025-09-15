class UI03:
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
                    self._controller.print_graph()
                case "2":
                    print(self._bellman_ford())
                case _:
                    print("Invalid command")

    def _bellman_ford(self):
        inp = input("Enter the two vertices: ")
        try:
            u, v = map(int, inp.split())
        except Exception:
            print("Invalid input")
            return
        msg = self._controller.bellman_ford(u, v)
        return msg

    @staticmethod
    def _print_menu():
        print("1. Display the graph")
        print("2. Find the lowest cost walk from 2 vertices (Using Bellman-Ford)")
        print("0. Exit")