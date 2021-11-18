# Questions

> What can be said about privacy and confidentiality in blockchains? Which kind of identity privacy can be kept? Can data be kept confidential, and how?

Because transactions are stored immutably in the blockchain, it is possible to see all previous interactions for a specific public key.
If i where to use the same key for everything, that would not give me much privacy as my friends would probably also know that identity.

If i want to keep my transactions private, i would have to make new identities for each purpose.
This would require alot of managing of resources, as each identity has it's own wallet.


> Is it possible to remove all the "transaction data" of a block from the disk, and keep only the Merkle tree head? In which cases?

Yes it is possible, especially if all the money contained in it is spent.
Because the hash of the block only covers the Merkle tree head, one can remove the rest from disk.

However this is stupid if one want's to keep historical data of transactions.

> Why is the miner protected from a "while(true) {...}" Denial of Service attach in Ethereum / Solidity?

The program can't run forever before reaching the computation limit, which i think is galled gas.
That way a while loop would quickly run out of gas, and the execution will stop.
In that way it is only the owner of the contract who wastes their money.
