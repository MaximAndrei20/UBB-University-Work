from src.Domain import Graph

class Controller:
    def __init__(self, graph: Graph):
        self._graph = graph

    def __del__(self):
        del self._graph

    def add_edge(self, u, v, w):
        self._graph.add_edge(u, v, w)

    def print_graph(self):
        print(self._graph)

    def get_number_of_vertices(self):
        return self._graph.get_number_of_vertices()

    def get_parsed_vertices(self):
        return self._graph.parse_vertices()

    def get_edge_id(self, u, v):
        return self._graph.get_edge_id(u, v)

    def get_edge_by_edge_id(self, edge_id):
        return self._graph.get_edge_by_edge_id(edge_id)

    def get_in_degree(self, vertex):
        return self._graph.get_in_degree(vertex)

    def get_out_degree(self, vertex):
        return self._graph.get_out_degree(vertex)

    def parse_outbound_edges(self, vertex):
        return list(self._graph.parse_outbound_edges(vertex))

    def parse_inbound_edges(self, vertex):
        return list(self._graph.parse_inbound_edges(vertex))

    def set_edge_info(self, edge_id, new_info):
        self._graph.set_edge_info(edge_id, new_info)

    def remove_edge(self, edge_id):
        self._graph.remove_edge(edge_id)

    def add_vertex(self):
        self._graph.add_vertex()

    def remove_vertex(self, vertex):
        self._graph.remove_vertex(vertex)

    def copy_graph(self):
        return self._graph.copy_graph()

    def read_from_file(self, file_name):
        self._graph.read_from_file(file_name)

    def write_to_file(self, file_name):
        self._graph.write_to_file(file_name)

    def generate_random_graph(self, number_of_vertices, number_of_edges):
        self._graph.generate_random_graph(number_of_vertices, number_of_edges)

    def bfs(self, start, end):
        return self._graph.bfs(start, end)

    def get_strongly_connected_components(self):
        return self._graph.get_strongly_connected_components()

    def bellman_ford(self, start, end):
        return self._graph.bellman_ford(start, end)

    def is_dag(self):
        """
        Checks if the graph is a DAG
        :return: True if the graph is a DAG, False otherwise
        """
        is_dag, _ = self._graph.is_dag()
        return is_dag

    def topological_sort(self):
        """
        Performs topological sorting of the graph
        :return: list of vertices in topological order if graph is DAG, None otherwise
        """
        return self._graph.topological_sort()

    def calculate_earliest_and_latest_start_times(self):
        """
        Calculates earliest and latest start times for each activity
        :return: tuple of (earliest_start, latest_start, total_time)
        """
        return self._graph.calculate_earliest_and_latest_start_times()

    def get_total_time(self):
        """
        Gets the total time of the project
        :return: total time or None if graph is not DAG
        """
        _, _, total_time = self._graph.calculate_earliest_and_latest_start_times()
        return total_time

    def print_earliest_and_latest_start_times(self):
        """
        Prints earliest and latest start times for each vertex
        """
        earliest, latest, _ = self._graph.calculate_earliest_and_latest_start_times()
        if earliest is None:
            print("Graph is not a DAG, cannot calculate times")
            return

        print("Vertex\tEarliest\tLatest")
        for v in range(self._graph.get_number_of_vertices()):
            print(f"{v}\t\t\t{earliest[v]}\t\t{latest[v]}")


    def get_critical_activities(self):
        """
        Gets the critical activities
        :return: list of critical activities
        """
        return self._graph.get_critical_activities()

    def find_vertex_coloring(self):
        """
        Finds a vertex coloring with minimum number of colors
        :return: list of colors for each vertex
        """
        return self._graph.find_minimum_colors()
        #return self._graph.find_vertex_coloring()