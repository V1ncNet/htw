import java.util.LinkedList;

class Graph {
    private LinkedList<Integer> adjList[];
    private boolean visited[];

    Graph(final int vertices) {
        this.adjList = new LinkedList[vertices];
        this.visited = new boolean[vertices];

        for (int i = 0; i < vertices; i++) {
            adjList[i] = new LinkedList<>();
        }
    }

    void addEdge(final int src, final int dest) {
        adjList[src].add(dest);
    }

    void dfs(final int vertex) {
        visited[vertex] = true;
        System.out.println(vertex + " ");

        for (Integer adj : adjList[vertex]) {
            if (!visited[adj]) {
                dfs(adj);
            }
        }
    }
    
    void bfs(int vertex) {
        final LinkedList<Integer> queue = new LinkedList<Integer>();
        visited[vertex] = true;
        queue.add(vertex);

        while (!queue.isEmpty()) {
            vertex = queue.poll();
            System.out.println(vertex + " ");

            for (Integer adj : adjList[vertex]) {
                if (!visited[adj]) {
                    visited[adj] = true;
                    queue.add(adj);
                }
            }
        }
    }

    public static void main(final String args[]) {
        /*
         * Adjacency List
         * Array(List(1,3),
         *       List(0,2,4),
         *       List(1,5),
         *       List(0,4,6),
         *       List(1,3,5,7),
         *       List(2,4,8),
         *       List(3,7),
         *       List(6,4,8),
         *       List(5,7))
         */

        final Graph g = new Graph(9);

        g.addEdge(0, 1);
        g.addEdge(0, 3);

        g.addEdge(1, 0);
        g.addEdge(1, 2);
        g.addEdge(1, 4);

        g.addEdge(2, 1);
        g.addEdge(2, 5);

        g.addEdge(3, 0);
        g.addEdge(3, 4);
        g.addEdge(3, 6);

        g.addEdge(4, 1);
        g.addEdge(4, 3);
        g.addEdge(4, 5);
        g.addEdge(4, 7);

        g.addEdge(5, 2);
        g.addEdge(5, 4);
        g.addEdge(5, 8);

        g.addEdge(6, 3);
        g.addEdge(6, 7);

        g.addEdge(7, 6);
        g.addEdge(7, 4);
        g.addEdge(7, 8);

        g.addEdge(8, 5);
        g.addEdge(8, 7);

        System.out.println("Following is Depth First Traversal");

        // Result might be wrong, I got 0 1 2 5 8 7 6 4 3
        g.dfs(0);

        final Graph h = new Graph(9);

        h.addEdge(0, 1);
        h.addEdge(0, 3);

        h.addEdge(1, 0);
        h.addEdge(1, 2);
        h.addEdge(1, 4);

        h.addEdge(2, 1);
        h.addEdge(2, 5);

        h.addEdge(3, 0);
        h.addEdge(3, 4);
        h.addEdge(3, 6);

        h.addEdge(4, 1);
        h.addEdge(4, 3);
        h.addEdge(4, 5);
        h.addEdge(4, 7);

        h.addEdge(5, 2);
        h.addEdge(5, 4);
        h.addEdge(5, 8);

        h.addEdge(6, 3);
        h.addEdge(6, 7);

        h.addEdge(7, 6);
        h.addEdge(7, 4);
        h.addEdge(7, 8);

        h.addEdge(8, 5);
        h.addEdge(8, 7);

        
        System.out.println("Following is Breadth First Traversal");

        h.bfs(0);
    }
}
