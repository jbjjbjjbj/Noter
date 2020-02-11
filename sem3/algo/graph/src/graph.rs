use std::rc::{Rc, Weak};
use std::cell::RefCell;
use std::vec::Vec;
use std::string::String;
use std::collections::HashMap;
use std::fmt;

type EdgeRef = RefCell<Edge>;
type VertexRef = RefCell<Vertex>;

pub struct Edge {
    from: Weak<VertexRef>,
    to: Weak<VertexRef>,
    weight: i32,
}

pub struct Vertex {
    name: String,
    pub adj: Vec<Rc<EdgeRef>>,
}

pub struct Graph {
    vertexes: HashMap<String, Rc<VertexRef>>,
    edges: Vec<Rc<EdgeRef>>,
}

impl Vertex {
    pub fn new(name: &str) -> VertexRef {
        RefCell::new( Vertex { name: String::from(name), adj: Vec::new() })
    }
}

impl Graph {
    pub fn new() -> Graph {
        Graph { vertexes: HashMap::new(), edges: Vec::new() }
    }

    pub fn edge(&mut self, from: &str, to: &str, weight: i32) {
        let from = match self.vertexes.get(from) {
            Some(rc) => Rc::clone(rc),
            None => self.add_vertex(from),
        };

        let to = match self.vertexes.get(to) {
            Some(rc) => Rc::clone(rc),
            None => self.add_vertex(to),
        };

        // Create edge
        let e = Rc::new(RefCell::new( Edge { from: Rc::downgrade(&from), to: Rc::downgrade(&to), weight } ));

        // Add to stuff
        from.borrow_mut().adj.push(Rc::clone(&e));
        self.edges.push(e);
        
    }

    pub fn borrow_vertex(&self, name: &str) -> Option<Rc<VertexRef>> {
        self.vertexes.get(name).and_then(|rc| Some(Rc::clone(rc)))
    }

    fn add_vertex(&mut self, name: &str) -> Rc<VertexRef> {
        let v = Rc::new( Vertex::new(name) );

        // Insert in hashmap
        self.vertexes.insert(String::from(name), Rc::clone(&v));

        // Return vertex
        v
    }

}

impl fmt::Display for Edge {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let rc = self.to.upgrade().unwrap();
        write!(f, "{}", Rc::clone(&rc).borrow())
    }
}

impl fmt::Display for Vertex {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.name)
    }
}
