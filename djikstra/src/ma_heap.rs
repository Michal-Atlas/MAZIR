use crate::ma_djikstra::Edge;
use std::fs::read;

#[derive(Clone, Debug)]
pub struct Heap(std::vec::Vec<Edge>);

fn parent(i: usize) -> usize {
    ((i + 1) / 2) - 1
}

fn left_child(i: usize) -> usize {
    ((i + 1) * 2) - 1
}

fn right_child(i: usize) -> usize {
    left_child(i) + 1
}

impl Heap {
    pub fn new() -> Heap { Heap(std::vec::Vec::new()) }
    pub fn empty(&self) -> bool { self.0.is_empty() }
    pub fn contains(&self, key: usize) -> bool { self.0.iter().any(|&e| { e.target == key }) }
    pub fn extract_min(&mut self) -> Option<Edge> {
        if self.0.is_empty() {
            return None;
        }
        if self.0.len() <= 2 {
            return self.0.pop();
        }
        let ret = self.0[0].clone();
        self.0[0] = self.0.pop().unwrap();

        let index = 0;
        let mut cont = true;
        while cont && index > 0 {
            cont = false;
            if self.0[left_child(index)].dist > self.0[index].dist {
                self.switch(index, left_child(index));
            } else if self.0[right_child(index)].dist > self.0[index].dist {
                self.switch(index, right_child(index));
            }
        }
        Some(ret)
    }
    fn switch(&mut self, x: usize, y: usize) {
        let former = self.0[x];
        self.0[x] = self.0[y];
        self.0[y] = former;
    }
    pub fn insert(&mut self, p: Edge) {
        self.0.push(p);
        let mut index = self.0.len() - 1;
        while index > 0 && self.0[parent(index)].dist > self.0[index].dist {
            self.switch(index, parent(index));
            index = parent(index);
        }
    }
    pub fn decrease(&mut self, key: usize, dist: u64) {
        self.0.iter_mut().find(|e| { e.target == key }).unwrap().dist = dist;
    }
}
