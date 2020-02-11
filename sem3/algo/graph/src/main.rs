
mod graph;

use graph::Graph;

fn main() {

    let mut g = Graph::new();

    g.edge("a", "b", 10);
    g.edge("a", "c", 10);
    g.edge("a", "d", 10);

    // Ahh this is hard
    let v = g.borrow_vertex("a").unwrap();
    let v23 = v.borrow();
    let mut it = v23.adj.iter();
    for e in it {
        println!("{}", e.borrow());
    }

    println!("Hello, world!");
}
