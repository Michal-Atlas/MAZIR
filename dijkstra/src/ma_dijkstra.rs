use crate::ma_heap::{Heap, Pair};

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
impl Edge {
    pub(crate) fn new() -> Self {
        Edge { src: 0, target: 0, dist: 0 }
    }
}

/// Returns a Vector of (Which node a path comes from, Length of given path from origin)
pub fn traverse(graph: &Vec<Node>, origin: usize) -> Vec<(Option<usize>, u64)> {
    let mut closed_nodes: Vec<usize> = vec![];
    // This keeps track of the current shortest distance to each `Node` and where it came from
    let mut node_distances: Vec<(Option<usize>, u64)> = vec![(None, std::u64::MAX); graph.len()];
    node_distances[origin] = (Some(0), 0);
    let mut heap = Heap::new();
    heap.insert(Pair {
        key: origin,
        value: 0,
    });
    while let Some(processed_path) = heap.extract_min() {
        // For each path in current `Node`
        for ed in &graph[processed_path.key].edges {
            // Disregard if `Node` already closed
            if closed_nodes.contains(&ed.target) {
                continue;
            }
            if heap.contains(ed.target) {
                if node_distances[ed.src].1 + ed.dist < node_distances[ed.target].1 {
                    heap.decrease(ed.target, node_distances[ed.src].1 + ed.dist);
                    node_distances[ed.target] = (Some(ed.src), node_distances[ed.src].1 + ed.dist);
                }
            } else {
                heap.insert(Pair {
                    key: ed.target,
                    value: node_distances[ed.src].1 + ed.dist,
                });
                node_distances[ed.target] = (Some(ed.src), node_distances[ed.src].1 + ed.dist);
            }
        }
        closed_nodes.push(processed_path.key);
    }
    node_distances
}

pub fn backtrack_paths(traverse: &Vec<(Option<usize>, u64)>) -> Vec<Vec<usize>> {
    let mut ret: Vec<Vec<usize>> = Vec::new();
    for p in 0..traverse.len() {
        ret.push(vec![p]);
        let mut cursor = p;
        while cursor != 0 && cursor != usize::MAX {
            if (ret[p].len() > traverse.len()) {
                panic!("The Traversals contained a cycle")
            }
            let src = traverse[cursor].0.unwrap_or(usize::MAX);
            ret[p].push(src);
            cursor = src;
        }
    }
    ret
}
