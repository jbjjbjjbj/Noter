# GFS Design

Google workflow is optimized towards:

  - Large sequential reads, with few random reads
  - Frequent concurrent append, with few random writes.

    We therefore have many writers (fx. web crawlers) with a single readers (fx. indexer).

  - Sustained throughput is more important that latency.

## Appending

When crawlers append stuff to the file that the indexer reads, the location for appending does not matter.
So this is given up to allow for many writers at the same time.

## Chunking

The large files are split into chunks, which are replicated over to other chunkservers.

A *chunkhandle* is the index of a single chunk.
Then the *chunkmaster* holds a dictionary which maps file names and offsets to chunkhandle and list of servers.
The list of servers are the servers where the wanted chunk is replicated.

## Replication

**TODO: Read up on this.**

Ways of writing data to replicas:
  - *Passive replication* 

## Consistency

File creation and changes (*namespace mutations*) is done by the master, thus they are atomic.

A file region is consistent if
  - *Consistent* if all clients receive the same data
  - *Defined* if consistent and clients see written data in their entirety.
    So clients will not see a partial write. (**TODO** Not entirely sure about this)

Records are appended atomically *at least once somewhere*.

## Master Fault Tolerance

Master state is maintained in stable storage.

Can have multiple (read-only) *shadow masters*, which provide read access.

External program will detect master failure, and select a new master.

# Chubby

Locking service, that should be super reliable.

Locks are kept for a very long time, hours or days (This has something to do with the word *coarse*).
