use crate::ma_heap::Heap;

#[derive(Debug, Clone)]
pub struct Node {
    pub edges: Vec<Edge>,
}

#[derive(Clone, Debug, Copy)]
pub struct Edge {
    pub src: usize,
    pub target: usize,
    pub dist: u64,
}

/// Returns a Vector of (Which node a path comes from, Length of given path from origin)
pub fn traverse(graph: &Vec<Node>, origin: usize) -> Vec<(Option<usize>, u64)> {
    let mut closed_nodes: Vec<usize> = vec![origin; 1];
    // This keeps track of the current shortest distance to each `Node` and where it came from
    let mut node_distances: Vec<(Option<usize>, u64)> = vec![(None, std::u64::MAX); graph.len()];
    node_distances[origin] = (Some(0), 0);
    let mut heap = Heap::new();
    heap.insert(Edge {
        src: origin,
        target: origin,
        dist: 0,
    });
    while let Some(processed_path) = heap.extract_min() {
        // For each path in current `Node`
        for ed in &graph[processed_path.target].edges {
            // Disregard if `Node` already closed
            if closed_nodes.contains(&ed.target) {
                continue;
            }

            if (heap.contains(ed.target)) {
                if (node_distances[ed.src].1 + ed.dist < node_distances[ed.target].1) {
                    heap.decrease(ed.target, node_distances[ed.src].1 + ed.dist);
                    node_distances[ed.target] = (Some(ed.src), node_distances[ed.src].1 + ed.dist);
                }
            } else {
                heap.insert(Edge {
                    src: ed.src,
                    target: ed.target,
                    dist: node_distances[ed.src].1 + ed.dist,
                });
                node_distances[ed.target] = (Some(ed.src), node_distances[ed.src].1 + ed.dist);
            }
        }
        closed_nodes.push(processed_path.src);
    }
    node_distances
}
