#TODO: Given an undirected graph, find a vertex coloring with minimum number of colors.
from src.Domain.Graph import Graph
from src.Services.Controller import Controller
from task06.UI05.UI05 import UI05

def add_undirected_graph1(graph):
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()

    graph.add_edge(0, 1, 1)
    graph.add_edge(1, 0, 1)

    graph.add_edge(0, 2, 1)
    graph.add_edge(2, 0, 1)

    graph.add_edge(0, 3, 1)
    graph.add_edge(3, 0, 1)

    graph.add_edge(1, 3, 1)
    graph.add_edge(3, 1, 1)

    graph.add_edge(2, 3, 1)
    graph.add_edge(3, 2, 1)

    graph.add_edge(3, 4, 1)
    graph.add_edge(4, 3, 1)

def add_undirected_graph2(graph):
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()
    graph.add_vertex()

    graph.add_edge(0, 1, 1)
    graph.add_edge(1, 0, 1)

    graph.add_edge(2, 5, 1)
    graph.add_edge(5, 2, 1)

    graph.add_edge(3, 4, 1)
    graph.add_edge(4, 3, 1)



def main():
    graph = Graph(0)
    add_undirected_graph2(graph)
    controller = Controller(graph)
    ui = UI05(controller)
    ui.run()

if __name__ == "__main__":
    main()