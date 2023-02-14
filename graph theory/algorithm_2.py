import networkx as nx
import random

def permute_nodes(G):
    nodes = list(G.nodes())
    random.shuffle(nodes)
    node_map = {nodes[i]: i for i in range(len(nodes))}
    H = nx.relabel_nodes(G, node_map)
    return H

def encrypt(G, key):
    for transformation in key:
        G = transformation(G)
    return G

def decrypt(G, key):
    key = key[::-1]
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

    key = [permute_nodes]
    encrypted_graph = encrypt(G, key)
    decrypted_graph = decrypt(encrypted_graph, key)

    decrypted_message = "".join([decrypted_graph.nodes[i]['label'] for i in decrypted_graph.nodes()])
    print("Decrypted message:", decrypted_message)
