from src.Domain.Graph import Graph
from src.Services.Controller import Controller
from task03.UI03.UI03 import UI03

def add_test_graph1(graph):
    # Add a test graph that contains a negative cycle
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_edge(0, 1, 4)
    graph.add_edge(1, 2, -10)
    graph.add_edge(2, 3, 4)
    graph.add_edge(3, 1, -2)

def add_test_graph2(graph):
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_edge(0, 1, 5)
    graph.add_edge(1, 3, 2)
    graph.add_edge(1, 2, 1)
    graph.add_edge(2, 4, 1)
    graph.add_edge(4, 3, -1)

def main():
    graph = Graph(0)
    add_test_graph2(graph)
    controller = Controller(graph)
    ui = UI03(controller)
    ui.run()
    #TODO: Next assignment: 2)

if __name__=="__main__":
    main()