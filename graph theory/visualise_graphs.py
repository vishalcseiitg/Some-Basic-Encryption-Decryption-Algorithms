#This code generates a random graph with 5 nodes and a probability of 0.5 for each possible edge. The nodes of the graph are then labeled with characters from the message "hello". The graph is encrypted using the specified key and number of rounds. Finally, the encrypted graph is visualized using nx.draw and displayed using plt.show. You can run this code multiple times to see how different random graphs are encrypted.

import networkx as nx
import random
import matplotlib.pyplot as plt

def permute_nodes(G):
    nodes = list(G.nodes())
    random.shuffle(nodes)
    node_map = {nodes[i]: i for i in range(len(nodes))}
    H = nx.relabel_nodes(G, node_map)
    return H

def reverse_edges(G):
    H = nx.Graph()
    for node in G.nodes():
        H.add_node(node, label=G.nodes[node]['label'])
    for edge in G.edges():
        H.add_edge(edge[1], edge[0])
    return H

def encrypt(G, key, rounds):
    for i in range(rounds):
        for transformation in key:
            G = transformation(G)
    return G

if __name__ == '__main__':
    message = "hello"
    G = nx.gnp_random_graph(5, 0.5, seed=123)
    for i, node in enumerate(G.nodes()):
        G.nodes[node]['label'] = message[i % len(message)]
    key = [permute_nodes, reverse_edges]
    rounds = 10
    encrypted_graph = encrypt(G, key, rounds)
    nx.draw(encrypted_graph, with_labels=True)
    plt.show()
