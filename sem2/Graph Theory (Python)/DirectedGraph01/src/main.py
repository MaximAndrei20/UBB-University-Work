from src.Domain.Graph import Graph
from src.UI.UI import UI
from src.Services.Controller import Controller

def main():
    graph = Graph(0)
    graph.read_from_file("input.txt")
    controller = Controller(graph)
    ui = UI(controller)
    ui.run()

if __name__ == "__main__":
    main()