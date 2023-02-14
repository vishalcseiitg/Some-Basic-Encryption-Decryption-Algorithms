import networkx as nx
import random

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
    for _ in range(rounds):
        for transformation in key:
            G = transformation(G)
    return G

def decrypt(G, key, rounds):
    key = key[::-1]
    for _ in range(rounds):
        for transformation in key:
            G = transformation(G)
    return G

if __name__ == '__main__':
    message = "hello"
    G = nx.Graph()
    for i, c in enumerate(message):
        G.add_node(i, label=c)
    for i in range(len(message) - 1):
        G.add_edge(i, i + 1)

    key = [permute_nodes, reverse_edges]
    rounds = 100
    encrypted_graph = encrypt(G, key, rounds)
    decrypted_graph = decrypt(encrypted_graph, key, rounds)

    decrypted_message = "".join([decrypted_graph.nodes[i]['label'] for i in decrypted_graph.nodes()])
    print("Decrypted message:", decrypted_message)
