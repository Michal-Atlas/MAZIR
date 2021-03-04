use crate::ma_djikstra::Edge;
use std::fs::read;

#[derive(Clone, Debug)]
pub struct Heap(std::vec::Vec<Edge>);

macro_rules! parent {
    ($i:expr) => {
        (($i + 1) / 2) - 1
    };
}

macro_rules! left_child {
    ($i:expr) => {
        (($i + 1) * 2) - 1
    };
}

macro_rules! right_child {
    ($i:expr) => {
        left_child!($i) + 1
    };
}

impl Heap {
    pub fn new() -> Heap {
        Heap(std::vec::Vec::new())
    }
    pub fn empty(&self) -> bool {
        self.0.is_empty()
    }
    pub fn contains(&self, key: usize) -> bool {
        self.0.iter().any(|&e| e.target == key)
    }
    pub fn extract_min(&mut self) -> Option<Edge> {
        if self.empty() {
            return None;
        } // Heap is empty
        if self.0.len() <= 2 {
            return self.0.pop();
        } // Algorithm is unneeded when only 1 item would remain
        let ret = self.0[0].clone(); // Save returned value
        self.0[0] = self.0.pop().unwrap(); // Move last item to first
        self.bubble_down(0);

        Some(ret)
    }
    fn bubble_up(&mut self, index: usize) {
        let mut index = index;
        while index > 0 {
            if (self.0[parent!(index)].dist > self.0[index].dist) {
                self.switch(index, parent!(index));
                index = parent!(index);
            } else {
                return;
            }
        }
    }
    fn bubble_down(&mut self, index: usize) {
        let mut index = index;
        while index < self.0.len() {
            if self.0[left_child!(index)].dist < self.0[index].dist {
                self.switch(index, left_child!(index));
                index = left_child!(index);
            } else if self.0[right_child!(index)].dist < self.0[index].dist {
                self.switch(index, right_child!(index));
                index = right_child!(index);
            } else {
                return;
            }
        }
    }
    /// Exchanges two items in the heap, **no questions asked**
    fn switch(&mut self, x: usize, y: usize) {
        let former = self.0[x];
        self.0[x] = self.0[y];
        self.0[y] = former;
    }
    pub fn insert(&mut self, p: Edge) {
        self.0.push(p);
        let mut index = self.0.len() - 1;
        while index > 0 && self.0[parent!(index)].dist > self.0[index].dist {
            self.switch(index, parent!(index)); // Keeps checking if parent! is bigger and switching
            index = parent!(index);
        }
    }
    /// Takes value with `key` and updates (by setting not decreasing) the `dist`
    pub fn decrease(&mut self, key: usize, dist: u64) {
        let index = self.0.iter_mut().position(|e| e.target == key).unwrap();
        self.0[index].dist = dist;
        self.bubble_up(index);
    }
}
