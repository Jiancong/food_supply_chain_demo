# Fast food supply and process system demo

## Build instructions
1. make clean
2. make
3. make test

## Run instrunctions
1. ./Kitchen <ingest count per second, default is 2>


## Overflow shelf moving explanation
Each order should be placed on a shelf that matches the order’s temperature. If that shelf is full, an order can
be placed on the overflow shelf. If the overflow shelf is full, an existing order of your choosing on the
overflow should be moved to an allowable shelf with room. If no such move is possible, a random order
from the overflow shelf should be discarded as waste (and will not be available for a courier pickup).

The moving and adding order to overflow shelf is based the underlying circular buffer management.


