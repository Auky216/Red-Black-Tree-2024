import matplotlib.pyplot as plt

class Node:
    def __init__(self, key, color='black'):
        self.key = key
        self.left = None
        self.right = None
        self.parent = None
        self.color = color

class RedBlackTree:
    def __init__(self):
        self.nil = Node(None, color='black')
        self.root = self.nil

    def insert(self, key):
        new_node = Node(key, color='red')
        parent = None
        current = self.root

        while current != self.nil:
            parent = current
            if key < current.key:
                current = current.left
            else:
                current = current.right

        new_node.parent = parent

        if parent == None:
            self.root = new_node
        elif key < parent.key:
            parent.left = new_node
        else:
            parent.right = new_node

        new_node.left = self.nil
        new_node.right = self.nil
        new_node.color = 'red'
        self.fix_insert(new_node)

    def fix_insert(self, node):
        # Implementación del método de corrección de inserción
        pass

    def visualize(self):
        positions = {}
        levels = {}

        def traverse(node, level=0, position=0):
            if node != self.nil:
                traverse(node.left, level + 1, position - 1)
                positions[node.key] = (position, -level)
                levels[node.key] = level
                traverse(node.right, level + 1, position + 1)

        traverse(self.root)

        for key, (x, y) in positions.items():
            plt.text(x, y, str(key), ha='center', va='center', bbox=dict(facecolor='white', edgecolor='black'))

        for key, (x, y) in positions.items():
            if key != self.root.key:
                parent_key = node.parent.key
                plt.plot([x, positions[parent_key][0]], [y, positions[parent_key][1]], color='black')

        plt.gca().invert_yaxis()
        plt.axis('off')
        plt.show()

# Ejemplo de uso
rbt = RedBlackTree()
keys = [10, 20, 30, 15, 25, 5]
for key in keys:
    rbt.insert(key)

rbt.visualize()
