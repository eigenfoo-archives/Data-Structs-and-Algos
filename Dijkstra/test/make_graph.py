import random


num_vertices = 1000
with open('biggraph.txt', 'w') as outfile:
    for vertex in range(num_vertices):
        num_neighbors = random.randint(0, num_vertices/10)
        for _ in range(num_neighbors):
            neighbor = random.randint(0, num_vertices-1)
            cost = random.randint(1, 999999)
            outfile.write('v' + str(vertex)
                          + ' v' + str(neighbor)
                          + ' ' + str(cost) + '\n')
