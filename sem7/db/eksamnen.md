
# TODO

  - Lav opgave 2.3 i distributed thing

# Words and Things

  - **ROLAP**: Relational Online Analytical Processing
  - *Summarizability* on page 52 in DW book.
  - *Data marts* is a subset of a data wareshouse, containing only as single subject such as sales.

# Nice Spatial SQL Commands

  - `ST_GeometryType(thing)` finds the type of `thing`.
  - `ST_Boundary(thing)` finds the boundary of `thing`. There is probably a interior version too.
  - `ST_DWithin(a, b, distance)` returns true if `a` and `b` are within `distance` of each other.
  - `ST_MakeBox2D(a, b)` create a box from two points.


One can find nearest neighbour with:

```sql
select l.*,
ST_Distance (l.geo , ST_Point (5, 5)) as dist
from landscape as l
order by dist
limit 5
```

# Introduction Spatial Queries

**Range queries** are the most simple, as we just query inside a square.
This is very similar to something like

```sql
SELECT * WHERE salary BETWEEN 10 AND 20
```

Only with range queries we often look in two dimensions instead of one.

**Directional relationships** is stuff like north, west or south, and can the done with `ST_Azimuth`.
However this does not make much sense in 3D.

## Topological Relationships

We first define boundary and interior.
**Boundary** are the pixels that are adjendant to a pixel outside the object.
While **Interior** is the space inside the object not occupied by the boundary.

If we consider two shapes, we can say that they either *intersects* and *disjoint*.
We they are disjoint we cannot really say more than that, but if they *intersect* they can either be

  - *equal* if their boundaries and interior are equal,
  - *inside* if the one interior is completely inside the other,
  - *contains* is the reverse of *inside*
  - *adjendant* if their borders share pixels, but not their interior,
  - *overlaps* if they share interior pixels, but they each have pixels which are not in the other.

```sql
ST_Contains (b.geo , y.geo)
ST_Within (b.geo , y.geo)
ST_Touches (b.geo , y.geo)
ST_Equals (b.geo , y.geo)
ST_Overlaps (b.geo , y.geo)
```

## Points, Linestring and Polygons

These are used to represent the different things in the 2d database.
This is nicely explained [here](https://help.arcgis.com/en/geodatabase/10.0/sdk/arcsde/concepts/geometry/shapes/types.htm).

Points
: A single point represented by coordinates. It boundary is empty and the interior is just the point.

Linestring
: A line between a sequence of at least two points.
  Can either be closed, where the begin point is also the end.
  The line between the points is the interior, and the boundary are the outer points.

Polygon
: Define by an exterior closed linestring and zero og more interior closed linestrings.
  The exterior ring must be defined against the clock and the interior with the clock, such that the right side of the linestring is always outside.
  See #c6fd for a nice figure.

# Spatial Database Indexing

We can specify the indexing method in sql like this.

```sql
-- Creation of the table
create table landscape (
geo_name varchar (20) primary key ,
geo geometry not null
);

-- With B+ tree
create index landscape_geo_name
on landscape ( geo_name );

-- With R-tree, GIST, generalized search trees
create index landscape_geo
on landscape using gist (geo );
```

## Space Filling Curves

*Also refered to as SFC.*

If is often more convenient to store points in a specific 1d ordering, as we can then use existing indexing methods.
However the spatial stuff we want to store and search is 2d.
Therefore we map this 2d data to 1d, making search and inserting much easier.

We do this by splitting the 2d space into smaller chunks, and then we find a ordering of these chunks.
The ordering of the chunks is determined by a space filling curve, which there are many different.

A good spacefilling curve is one where points that are close in 2d space, are also close to each other on the curve.

However because we have many points in the same chunk, we can not know for sure whether they overlap just because they are in the same chunk.
This is therefore only used for finding candidates.

Using space filling curves allows us to reuse the B+tree indexing structure, which is well supported by postgresql.
However they can also be combined with other quadtrees or R-trees which work in 2d by themselves.

## Trees

Here we will introduce *minimum-bounding rectangles* or MBRs, which is a axis aligned rectange.
These are used to give an estimate of an object, which can lead to false positives (but not false negatives).

We will then insert those bounding boxes into a into nodes, with a maximum of M boxes per tree node.
When more than M nodes are to be inserted in a box we split it in two.

Again when deleting we should combine nodes if they are smaller than `m * M`.
Here it's often hard to get the right clusterings of boxes, as we want to mimimize the deadspace.

`m` is often `0.4` and `M` is often set according to page size etc.

When searching we use a two step filtering process.
First we check fast intersections with boxes and then the expensive geometric intersection.

What now refine R trees as *R+trees* which require that there is no overlap between the node regions.
We will therefore have to insert some objects twice.
However this eliminates the need to do multi-path searching.

# Introduction to Parallel Databases

Lets start with some important definitions.

Distributed Database
: Software system that permits management of the distributed database and makes the distribution transparent to the user.
Scale-up
: Adding more CPU cores etc hardware.
Scale-out
: Adding more smaller machines and connecting them.
Throughput
: Time from query start to last row received.
Response Time
: Time from query start to first row received.

There is a nice slide about transistency in this lecture.
It does not really make sense to repeat it here.

## Performance

When performing a query we have many choices for where to do this.
**Inter-query** is when we have many smaller queries that are performed in parallel,
while **intra-query** is a very large query that is queried concurrently.

## Design of Distributed Database

Often done in a *3-tier* architecture, with a client layer, application layer, and database server layer.
Each layer can then have many different interconnected computers, with communication to adjendant layers via a network.

## Partitioning

**Horizontal partitioning** (also called *sharding*) is when we have different sets of rows of the same table on different sites.
We therefore preserve the whole scheme at each site.
We can partition these in different ways:

  - **Range partitioning**, by partitioning on some column such as timestamps.
  - **List partitioning** such as using *round-robin*.
  - **Hash partitioning**.

Here we should watch out for getting a *data-skew*, where data is partitioned unbalanced.
This could for example be if we partition on a name column.

**Vertical partitioning** is where each site has each row, but the partitioning happens on the columns.
This allows for better compressions, but we must repeat primary key rows accross all sites for identification.

We must be able to say something about partitioning.
Such as **completeness** which states that all rows in the originals, should still be present in at least one of the partitions.
Or **reconstruction** which states that the original table can be recovered by applying some operator to all partitions.
And lastly **disjointness** which states that the partitions should not share rows.

# Just Parallel Databases (what)

Scaling up as explained before, is often much harder.
This is also called *vertical scaling* as is associated with *tight coupling*.

Scaling out is easier and often gives a more losely coupled thing, however this comes at the cost of complexity.
Scaling out is also called *horizontal scaling*.

**Shared memory** is a architecture where we have a shared memory between processors.
Here each CPU can see the whole memory space, and they all run the same OS instance.
Often used for *inter-query parallelism* or *load balancing*.
However not very common for databases.

**Shared disk** is very common for databases in cloud computing such as Amazon S3.
Here many processors, each with their own memory, shares a set of disks via an interconnect.
Therefore disks and CPU's can be shared independently.

**Shared nothing :-(** very common with NoSQL.
Here many computers are connected with an interconnect and share nothing, such like *scale-out*.
This is harder to scale than shared-disk but can give better performance.

**Symmetric algorithm** whether the processing of incomming tuples can be pipelined with own tuples.
See page 368 for a better explanation.

## ACID and CAP

ACID stands for

  - Atomicity
  - Consistency
  - Isolation
  - Durability

While CAP stands for

  - Consistent (same as in ACID)
  - Always Available
  - Partitioned

With CAP we are only allowed to have two of the three *things*.

## Amdahl's Law

The more of our computation we can do in parallel, the better.
If we can do all of it (which is impossible) we get a linear grow in performance as we add more units.
However if we cannot it will have a curve down :-(.

There is a nice formula for this in the slides, but i can try to write it here.

```haskell
MaxSpeedUp seq p = 1 / (seq + ( (1-seq) / p))
```

We are interested in parallising sorting and joining.
These operate on rows that are all over the place, and it is beneficial to do as much as possible on the device where stuff is stored, before sending it.

# Summary of Parallel Databases

This repeats some things in a nicer way.
I will just write what can be found in the slides, instead of repeating it.

  - Comparison between partitioning techniques, such as advantages of hash etc.
  - Interquery parallism

    Multiple queries in parallel. Easiest to implement on shared-memory.

  - Intraquery parallism

    - **Intraoperation parallism** parallizes the execution of each operation in query.
    - **Interoperation parallism** execute different query operations in parallel.

# Intro Data Warehousing and Multidimensional Modeling

Reasons for data warehousing

  - Often data quality is bad (different formats, inconsistent data)
  - Data is not permanent (deleted after 30 days, or overwritten by changes)

This makes it hard to answer more bussiness oriented queries.

If we consider the example of a single sale, then this sale would be a *fact* in the database, and the sales value would be called a *measure*.
Then this sales fact is associated with a set of *dimensions* such as the product type, the store and the sale time.

Each of these dimensions are oriented in a hierarchy, such that we can "zoom in" or out for more or less detail.
For example with a timestamp, we can only be interested in week or year, but also zoom into specific days.

Therefore we divide data into dimensions and facts.

Facts
: an important entity such as a sale. Often contain a *measures* which are things that can be aggregated, such as sales price.
Dimensions
: describes a fact such that we can search for different things. For example where did the sale happen, who bought it etc.
  Dimensions can also hold *level properties* which hold simple non-hierarchical information.

We can then say that facts live a *cube* with many dimensions (yeah that does not make such sense, so *hypercube* is also sometimes used).
Often these cubes have around 4-12 dimensions, but often 2 or 3 can be shown due to our stupid brains.
We denote a *sparse cube* as a cube with many empty cells and the opposite as a *dense cube*.

The slides have a nice todo list of things todo when designing a data warehouse.

## Types of Facts

Event fact
: or an *transaction fact* is a bussiness event such as a sale.
Measureless fact
: without a numerical measure, so just something that happened for some combination of dimensions.
State fact
: captures the current status at some timestamp, such as inventory.

## Granularity

What does a single fact mean, like the *level of detail*, "is a single fact the total sales in a day, or every single sale?".
We often let the granularity be a single business transaction, such as a sale, however we can aggregate this for scalability.

## More on Measures

This is something that a user might want to study for optimize for.
Each measure has two components, namely a *numerical value* and a *aggregation formula*.

There are different forms of measures:

  - **Additive measure** can be aggregated for all dimensions. A good example is the sale price.
  - **Semi-additive** can be aggregated over some dimensions, but not all.
    A good example is inventory, which cannot be aggregated over time (we would count stuff twice), but we can over aggregate over store to get total inventory.
  - **Non-additive** cannot be aggregated over anything. For example if it is a average sales price.

## Implementation

Here the granuality is avery important to consider, "what does a single row represent".

It is not very nice to store the whole dimension stuff with each fact, so instead we use *star schemas* and *snowflake schemas*,
with work with *fact tables* and *dimension tables*.

A **fact table** stores facts, and facts only, with references to the dimension values in the *dimension tables*.
Here we use a *surrogate key* to reference dimension values, which should be meaningless.

A **Star schema** has one fact table, and then one de-normalized dimension table for each dimension containing all levels.
This elliminates a lot of the foreign key usage, making stuff faster, however it hides the levels from the user and takes up more storage.

A **snowflake schema** stores the dimensions normalized, in that each level has its own dimension table.

In regards to *redundancy*, this is something we want to avoid, as it allows for inconsistent data and complexities with updating.

# Advanced Multidimensional Modeling

*warning: very very advanced*

## Querying

There are different ways to query DM, and they are often described with fancy and confusing words and cutting of cubes.

  - **roll-up** is when we want a less detailed view in a dimension. We then group by some higher hierarchy and use the aggregation of the measures.
  - **drill-down** is the opposite of rolling up, such that we get more detailed information in a dimension.
  - **drill-out** is when we add a new dimension to the cube (wow thats a super confusing name WTF).
  - **slice** is when we only want to consider a specific value of a dimension, thus creating a subset of the cube.
  - **slice/dice** is when we slice on multiple dimensions (jesus christ the naming).
  - **drill across** here we combine some cubes by some shared dimensions. This creates a new cube with the shared dimensions, and the non-shared dimensions rolled up.

Okay lets continue to the *advanced* stuff.

## Changing Dimensions

We assumme that the information in the dimensions is slowly chainging, and that the schema is fixed.
Such changes can then be handled in some different ways.

  - **No special handling**, just update it.
    This creates problems when facts created before the change refer to it, and we then lose context for the fact.
  - **Versioning of values**, insert a new dimension value with updated values, and use this for future facts.
    This uses up much more space, but is otherwise rather nice. Expecially if we include a timestamp.
  - **Capture previous and current value**, with the columns.
    Well this is better than nothing, but still sucks in many of the same ways.
  - **Split into changing and constant**, this works in much the same way as versioning, but we keep changing attributes in another table.
    Therefore we do not waste space on storing constant or slowly changing things, while fast changing values can easily be changed.

## Outrigger

*No this has nothing to do with oil drilling.*

A dimension that is refered from a another dimension table is called an *outrigger*.
An outrigger can also function as a normal dimension on the side.

## Degenerate Dimensions

What if we want to denote values that are together, such as orders, without attaching properties.
We could do this with a table with only a number, thereby creating a **degenerate dimension**.
However this is pointless, and we can just use this value directly in facts, without creating a dimension for it.

## Junk Dimensions

These are dimensions that collect otherwise small dimensions together.
Here the attributes do not have anything to do with each other.

## Role Playing Dimensions

*What is up with the funky names.*

These are tables that can serve multiple purposes, such as a Date dimension for Order date and Ship date.
Here we will often only have one table, and use it multiple times.

## Advanced Hierachies

*[Advanced.](https://youtu.be/50m2Q7wPUFg?t=861)*

Until now we assumed that the dimension hierachies are

  - **balanced** in that all instances belong to the lowest level,
  - **covering** in that non-T level belongs directly to the level above (we do not skip level)
  - **strict** no dimension value has more than one parent. (For example multiple authors for a book is non-strict)

One example of a dimensions that breaks this would be a *parent-child* hierachy such as a Employee dimension.
Each employee can also be a manager for other employees.

This can be represented with **bridge tables**, which joins employees to other employees.
This tables will then only be used when navigating employee relationsships and not when just quering a single employee.

A bridge table contains the following values:

  - *Ancestor* is the parent.
  - *Descendant* is the child.
  - *Distance* is the distance from parent to child.
  - *Top* is true if the ancester is a the top of the tree (and distance is 1, what?? I can't make sense of the examples.).
  - *Bottom* is true if the descendant is a the bottom of the tree.


We can also have **multiple hierachies**, for example different calendar systems for days.
Here it makes no sense to use both in the same query.

When two hierachies have different analytical purposes, we call them **parallel hierachies**.

# ETL: Extract Transform Load

The **Data staging area** or DSA, functions as transit storage for ETL, where data cleaning opearations are done.
This should therefore not be used for user queries.
Here large sequential operations are done to transform data, in a process that should be easy to restart etc.
When done data can be copied to data marts.

## Extract

Data can either be copied from **cooperative sources** such as replication mechanism, or call backs.
Data can also come from **non-cooperative sources** via database snapshots, legacy systems, logs or a query language.

We should only load data that has changes since last update, as extraction can otherwise take days or weeks.
These changes or *deltas* can be calculated each time.
However it can be beneficial to store an audit timestamp on all rows in the source.
This process of finding deltas is called **changed data capture** (CDC), where other methods are discussed in slide 10.

## Transform

This can be data convertions such as string encoding or data/time representation.

