from src.Domain.Graph import Graph
from src.Services.Controller import Controller
from task02.UI02.UI02 import UI02

def add_test_graph(graph):
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_edge(0, 1, 1)
    graph.add_edge(1, 2, 2)
    graph.add_edge(2, 0, 3)
    graph.add_edge(2, 3, 4)
    graph.add_edge(3, 4, 5)



def main():
    graph = Graph(0)
    add_test_graph(graph)
    #graph.read_from_file("input.txt")
    controller = Controller(graph)
    #controller.generate_random_graph(10,20)
    ui = UI02(controller)
    ui.run()
    # TODO: Next assignment: 3)

if __name__ == "__main__":
    main()