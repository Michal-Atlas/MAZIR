#[derive(Copy, Clone, Debug)]
pub struct Pair {
    pub key: usize,
    pub value: u64,
}

impl Pair {
    fn new() -> Self {
        Pair { key: 0, value: 0 }
    }
}

#[derive(Clone, Debug)]
pub struct Heap(std::vec::Vec<Pair>);

impl Heap {
    pub fn new() -> Heap {
        Heap(std::vec::Vec::new())
    }
    pub fn empty(&self) -> bool {
        self.0.is_empty()
    }
    pub fn contains(&self, key: usize) -> bool {
        self.0.iter().any(|&e| e.key == key)
    }
    pub fn extract_min(&mut self) -> Option<Pair> {
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
        while index > 0 && self.0[Heap::parent(index)].value > self.0[index].value {
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
            let (sm_index, lg_index) = if l_val.unwrap_or(&Pair::new()).value < r_val.unwrap_or(&Pair::new()).value {
                (Heap::left_child(index), Heap::right_child(index))
            } else {
                (Heap::right_child(index), Heap::left_child(index))
            };

            if self.0.len() > sm_index
                && self.0[sm_index].value < self.0[index].value
            {
                self.switch(index, sm_index);
                index = sm_index;
            } else if self.0.len() > lg_index
                && self.0[lg_index].value < self.0[index].value
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
    pub fn insert(&mut self, p: Pair) {
        self.0.push(p);
        self.bubble_up(self.0.len() - 1);
    }
    /// Takes value with `key` and updates (by setting not decreasing) the `value`
    pub fn decrease(&mut self, key: usize, value: u64) {
        let index = self.0.iter_mut().position(|e| e.key == key).unwrap();
        self.0[index].value = value;
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
        heap.insert(Pair {
            key: 0,
            value: 0,
        });
        assert_eq!(0, heap.extract_min().unwrap().value);
        assert_eq!(true, heap.extract_min().is_none());
    }

    #[test]
    fn heap_two() {
        let mut heap = Heap::new();
        let pair_template = Pair {
            key: 0,
            value: 0,
        };
        heap.insert(pair_template);
        heap.insert(Pair {
            value: 20,
            ..pair_template
        });
        heap.insert(Pair {
            value: 10,
            ..pair_template
        });
        heap.insert(Pair {
            value: 15,
            ..pair_template
        });
        heap.insert(Pair {
            value: 30,
            ..pair_template
        });
        heap.insert(Pair {
            value: 18,
            ..pair_template
        });
        assert_eq!(0, heap.extract_min().unwrap().value);
        assert_eq!(10, heap.extract_min().unwrap().value);
        assert_eq!(15, heap.extract_min().unwrap().value);
        assert_eq!(18, heap.extract_min().unwrap().value);
        heap.insert(Pair {
            value: 100,
            ..pair_template
        });
        assert_eq!(20, heap.extract_min().unwrap().value);
        assert_eq!(30, heap.extract_min().unwrap().value);
        assert_eq!(100, heap.extract_min().unwrap().value);
        assert!(heap.extract_min().is_none());
    }
}
