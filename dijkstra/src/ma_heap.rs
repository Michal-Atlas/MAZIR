use crate::ma_dijkstra::Edge;

#[derive(Clone, Debug)]
pub struct Heap(std::vec::Vec<Edge>);

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
        if self.0.len() == 1 {
            return self.0.pop();
        } // Algorithm is unneeded when only 1 item would remain

        let ret = self.0[0].clone(); // Save returned value
        self.0[0] = self.0.pop().unwrap(); // Move last item to first
        self.bubble_down(0);

        Some(ret)
    }
    fn bubble_up(&mut self, index: usize) {
        let mut index = index;
        while index > 0 && self.0[Heap::parent(index)].dist > self.0[index].dist {
            self.switch(index, Heap::parent(index)); // Keeps checking if Heap::parent is bigger and switching
            index = Heap::parent(index);
        }
    }
    fn bubble_down(&mut self, index: usize) {
        let mut index = index;
        while index < self.0.len() {
            // Make sure that sm_index is the smaller of the children so that they may be checked in order
            let l_val = self.0.get(Heap::left_child(index));
            let r_val = self.0.get(Heap::right_child(index));
            let (sm_index, lg_index) = if l_val.unwrap_or(&Edge::new()).dist < r_val.unwrap_or(&Edge::new()).dist {
                (Heap::left_child(index), Heap::right_child(index))
            } else {
                (Heap::right_child(index), Heap::left_child(index))
            };

            if self.0.len() > sm_index
                && self.0[sm_index].dist < self.0[index].dist
            {
                self.switch(index, sm_index);
                index = sm_index;
            } else if self.0.len() > lg_index
                && self.0[lg_index].dist < self.0[index].dist
            {
                self.switch(index, lg_index);
                index = lg_index;
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
        self.bubble_up(self.0.len() - 1);
    }
    /// Takes value with `key` and updates (by setting not decreasing) the `dist`
    pub fn decrease(&mut self, key: usize, dist: u64) {
        let index = self.0.iter_mut().position(|e| e.target == key).unwrap();
        self.0[index].dist = dist;
        self.bubble_up(index);
    }

    fn parent(i: usize) -> usize {
        ((i + 1) / 2) - 1
    }

    fn left_child(i: usize) -> usize {
        ((i + 1) * 2) - 1
    }

    fn right_child(i: usize) -> usize {
        Heap::left_child(i) + 1
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn heap_one() {
        let mut heap = Heap::new();
        heap.insert(Edge {
            src: 0,
            target: 0,
            dist: 0,
        });
        assert_eq!(0, heap.extract_min().unwrap().dist);
        assert_eq!(true, heap.extract_min().is_none());
    }

    #[test]
    fn heap_two() {
        let mut heap = Heap::new();
        let edge_template = Edge {
            src: 0,
            target: 0,
            dist: 0,
        };
        heap.insert(edge_template);
        heap.insert(Edge {
            dist: 20,
            ..edge_template
        });
        heap.insert(Edge {
            dist: 10,
            ..edge_template
        });
        heap.insert(Edge {
            dist: 15,
            ..edge_template
        });
        heap.insert(Edge {
            dist: 30,
            ..edge_template
        });
        heap.insert(Edge {
            dist: 18,
            ..edge_template
        });
        assert_eq!(0, heap.extract_min().unwrap().dist);
        assert_eq!(10, heap.extract_min().unwrap().dist);
        assert_eq!(15, heap.extract_min().unwrap().dist);
        assert_eq!(18, heap.extract_min().unwrap().dist);
        heap.insert(Edge {
            dist: 100,
            ..edge_template
        });
        assert_eq!(20, heap.extract_min().unwrap().dist);
        assert_eq!(30, heap.extract_min().unwrap().dist);
        assert_eq!(100, heap.extract_min().unwrap().dist);
        assert!(heap.extract_min().is_none());
    }
}
