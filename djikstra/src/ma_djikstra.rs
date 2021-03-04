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

pub fn traverse(graph: &Vec<Node>, origin: usize, dest: usize) -> Vec<Edge> {
    let mut crow_fly_paths: Vec<Edge> = std::vec::Vec::new();
    let mut node_distances = vec![std::u64::MAX; graph.len()];
    node_distances[origin] = 0;
    let mut heap = Heap::new();
    heap.insert(Edge {
        src: origin,
        target: origin,
        dist: 0,
    });
    while !heap.empty() {
        let processed_path = heap.extract_min().unwrap();
        for ed in &graph[processed_path.target].edges {
            if !(crow_fly_paths.iter().any(|e| { e.target == ed.target })) {
                if (heap.contains(ed.target)) {
                    if (node_distances[ed.src] + ed.dist < node_distances[ed.target]) {
                        heap.decrease(ed.target, node_distances[ed.src] + ed.dist);
                    }
                    node_distances[ed.target] = node_distances[ed.src] + ed.dist;
                } else {
                    heap.insert(Edge {
                        src: processed_path.src,
                        target: ed.target,
                        dist: node_distances[ed.src] + ed.dist,
                    });
                    node_distances[ed.target] = node_distances[ed.src] + ed.dist;
                }
            }
        }
        crow_fly_paths.push(processed_path);
    }
    eprintln!("{:?}", crow_fly_paths);
    crow_fly_paths
}
