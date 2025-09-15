from src.Services.Controller import Controller
from src.Domain.Graph import Graph

import random

class UI:
    def __init__(self, controller):
        self._controller = controller
        self._running = True

    def __del__(self):
        del self._controller

    def run(self):
        while self._running:
            self._print_menu()
            option = input("Choose an option: ")
            if option == '0':
                break
            self._handle_option(option)

    @staticmethod
    def _print_menu():
        print("\nMenu:")
        print("1. Get the number of vertices")
        print("2. Parse the set of vertices")
        print("3. Check if there is an edge between two vertices and retrieve Edge_id")
        print("4. Get the in-degree and out-degree of a vertex")
        print("5. Parse the set of outbound edges of a vertex")
        print("6. Parse the set of inbound edges of a vertex")
        print("7. Get the endpoints of an edge by Edge_id")
        print("8. Get cost of an edge (usage: [u v]/[Edge_id] )")
        print("9. Modify an edge (usage: [u v new_cost]/[Edge_id new_cost])")
        print("10. Add an edge (usage: [u v weight])")
        print("11. Remove an edge (usage: [u v]/[Edge_id])")
        print("12. Add a vertex")
        print("13. Remove a vertex")
        print("14. Copy the graph")
        print("15. Return to the original graph")
        print("16. Read the graph from a text file")
        print("17. Write the graph to a text file")
        print("18. Create a random graph")
        print("19. Check deepcopy")
        print("0. Exit\n")

    def _handle_option(self, option):
        if option == "print":
            self._controller.print_graph()
        try:
            option = int(option)
        except ValueError:
            print("Invalid option!")
            return
        if not 1 <= option <= 19:
            print("Invalid option!")
            return
        match option:
            case 1:
                print(self._controller.get_number_of_vertices())
            case 2:
                vertices = self._controller.get_parsed_vertices()
                for vertex in vertices:
                    print(vertex, end=' ')
                print()
            case 3:
                u = input("Enter the first vertex: ")
                v = input("Enter the second vertex: ")
                try:
                    u = int(u)
                    v = int(v)
                except ValueError:
                    print("Invalid vertices!")
                    return
                try:
                    edge_id = self._controller.get_edge_id(u, v)
                    _, _, w = self._controller.get_edge_by_edge_id(edge_id)
                except ValueError:
                    edge_id = None

                if edge_id is not None:
                    print(f"There is an edge between {u} and {v} with cost {w} and Edge_id {edge_id}")
                else:
                    print(f"There is no edge between {u} and {v}")
            case 4:
                vertex = input("Enter the vertex: ")
                try:
                    vertex = int(vertex)
                except ValueError:
                    print("Invalid vertex!")
                    return
                try:
                    in_degree = self._controller.get_in_degree(vertex)
                    out_degree = self._controller.get_out_degree(vertex)
                except ValueError as e:
                    print(e)
                    return

                print(f"The in-degree of vertex {vertex} is {in_degree} and the out-degree is {out_degree}")
            case 5:
                vertex = input("Enter the vertex: ")
                try:
                    vertex = int(vertex)
                except ValueError:
                    print("Invalid vertex!")
                    return
                try:
                    edge_ids = self._controller.parse_outbound_edges(vertex)
                    print(f"Outbound edges of vertex {vertex}: {edge_ids}")
                except ValueError as e:
                    print(e)
            case 6:
                vertex = input("Enter the vertex: ")
                try:
                    vertex = int(vertex)
                except ValueError:
                    print("Invalid vertex!")
                    return
                try:
                    edge_ids = self._controller.parse_inbound_edges(vertex)
                    print(f"Inbound edges of vertex {vertex}: {edge_ids}")
                except ValueError as e:
                    print(e)
            case 7:
                edge_id = input("Enter the Edge_id: ")
                try:
                    edge_id = int(edge_id)
                except ValueError:
                    print("Invalid Edge_id!")
                    return
                try:
                    u, v, w = self._controller.get_edge_by_edge_id(edge_id)
                except ValueError as e:
                    print(e)
                    return
                print(f"Edge with Edge_id {edge_id} has endpoints {u} and {v} and cost {w}")
            case 8:
                edge = input("Enter the edge: ")
                edge = edge.split()
                if len(edge) == 2:
                    try:
                        u, v = map(int, edge)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        edge_id = self._controller.get_edge_id(u, v)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        _, _, w = self._controller.get_edge_by_edge_id(edge_id)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    print(f"Cost of edge {u} {v} is {w}")
                elif len(edge) == 1:
                    try:
                        edge_id = int(edge[0])
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        _, _, w = self._controller.get_edge_by_edge_id(edge_id)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    print(f"Cost of edge with Edge_id {edge_id} is {w}")
                else:
                    print("Invalid edge!")
                    return
            case 9:
                edge = input("Enter the edge and the new cost: ")
                edge = edge.split()
                if len(edge) == 3:
                    try:
                        u, v, new_cost = map(int, edge)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        edge_id = self._controller.get_edge_id(u, v)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        self._controller.set_edge_info(edge_id, new_cost)
                    except ValueError as e:
                        print(e)
                elif len(edge) == 2:
                    try:
                        edge_id, new_cost = map(int, edge)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        self._controller.set_edge_info(edge_id, new_cost)
                    except ValueError as e:
                        print(e)
                else:
                    print("Invalid edge!")
                    return
                print("Edge modified successfully!")
            case 10:
                edge = input("Enter the edge ([u v weight]): ")
                try:
                    u, v, w = map(int, edge.split())
                except ValueError:
                    print("Invalid edge!")
                    return
                try:
                    self._controller.add_edge(u, v, w)
                except ValueError as e:
                    print(e)
                    return
                print("Edge added successfully!")
            case 11:
                edge = input("Enter the edge ([u v]/[Edge_id]): ")
                edge = edge.split()
                if len(edge) == 2:
                    try:
                        u, v = map(int, edge)
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        edge_id = self._controller.get_edge_id(u, v)
                        self._controller.remove_edge(edge_id)
                    except Exception as e:
                        print(e)
                        return

                elif len(edge) == 1:
                    try:
                        edge_id = int(edge[0])
                    except ValueError:
                        print("Invalid edge!")
                        return
                    try:
                        self._controller.remove_edge(edge_id)
                    except Exception as e:
                        print(e)
                        return
                else:
                    print("Invalid edge!")
                    return
                print("Edge removed successfully!")
            case 12:
                try:
                    self._controller.add_vertex()
                except ValueError as e:
                    print(e)
                    return
                print("Vertex added successfully!")
            case 13:
                vertex = input("Enter the vertex: ")
                try:
                    vertex = int(vertex)
                except ValueError:
                    print("Invalid vertex!")
                    return
                try:
                    self._controller.remove_vertex(vertex)
                except Exception as e:
                    print(e)
                    return
                print("Vertex removed successfully!")
            case 14:
                copy = self._controller.copy_graph()
                new_controller = Controller(copy)
                ui = UI(new_controller)
                ui.run()
                #print("The graph can be copied using the controller\n")
            case 15:
                self._running = False
                del self
                return
            case 16:
                file_name = input("Enter the file name: ")
                try:
                    self._controller.read_from_file(file_name)
                except FileNotFoundError:
                    print("File not found!")
                except ValueError as e:
                    print(e)
                print("Graph read successfully!")
            case 17:
                file_name = input("Enter the file name: ")
                try:
                    self._controller.write_to_file(file_name)
                except ValueError as e:
                    print(e)
                print("Graph written successfully!")
            case 18:
                n = input("Enter the number of vertices: ")
                m = input("Enter the number of edges: ")
                try:
                    n = int(n)
                    m = int(m)
                except ValueError:
                    print("Invalid input!")
                    return
                del self._controller
                self._controller = Controller(Graph(n))
                for _ in range(m):
                    u = random.randint(0, n-1)
                    v = random.randint(0, n-1)
                    w = random.randint(1, 100)
                    res = True
                    try:
                        self._controller.add_edge(u, v, w)
                    except ValueError:
                        res = False
                    while res is False:
                        res = True
                        u = random.randint(0, n-1)
                        v = random.randint(0, n-1)
                        w = random.randint(1, 100)
                        try:
                            res = self._controller.add_edge(u, v, w)
                        except ValueError:
                            res = False
                print("Random graph created successfully!")
            case 19:
                copy = self._controller.copy_graph()
                copycontroller = Controller(copy)
                print("Removing 2 vertices from the original graph")
                copycontroller.remove_vertex(1)
                copycontroller.remove_vertex(2)
                print("Original graph:")
                self._controller.print_graph()
                print("Copy:")
                copycontroller.print_graph()
