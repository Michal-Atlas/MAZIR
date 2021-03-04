use crate::ma_djikstra::{Edge, Node};
use std::io;
use std::io::BufRead;

mod ma_djikstra;
mod ma_heap;

fn main() {
    let stdin = io::stdin();
    let mut node_count: String = String::from("");
    stdin.lock().read_line(&mut node_count);
    let node_count: usize = node_count.trim().parse().unwrap();
    let mut nodes: Vec<Node> = vec![Node { edges: vec![] }; node_count];
    for l in stdin.lock().lines() {
        let numbers: Result<Vec<u64>, _> = l.unwrap().split_whitespace().map(str::parse).collect();
        let unumbers = numbers.unwrap();
        nodes[unumbers[0] as usize].edges.push(Edge {
            src: unumbers[0] as usize,
            target: unumbers[1] as usize,
            dist: unumbers[2],
        });
    }
    let path = ma_djikstra::traverse(&nodes, 0, node_count - 1);

    println!("{:#?}", path);
}
