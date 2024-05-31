## Foundry

**Foundry is a blazing fast, portable and modular toolkit for Ethereum application development written in Rust.**

Foundry consists of:

- **Forge**: Ethereum testing framework (like Truffle, Hardhat and DappTools).
- **Cast**: Swiss army knife for interacting with EVM smart contracts, sending transactions and getting chain data.
- **Anvil**: Local Ethereum node, akin to Ganache, Hardhat Network.
- **Chisel**: Fast, utilitarian, and verbose solidity REPL.

## Documentation

https://book.getfoundry.sh/

## Usage

### Build

```shell
$ forge build
```

### Test

```shell
$ forge test
```

### Format

```shell
$ forge fmt
```

### Gas Snapshots

```shell
$ forge snapshot
```

### Anvil

```shell
$ anvil
```

### Deploy

```shell
$ forge script script/Counter.s.sol:CounterScript --rpc-url <your_rpc_url> --private-key <your_private_key>
```

### Cast

```shell
$ cast <subcommand>
```

### Help

```shell
$ forge --help
$ anvil --help
$ cast --help
```

## Some notes taken during this course

- An EOA creates a contract by sending a transaction 'To' an empty address but with input data being the initialization code of the contract being created. In other words, this contract is created by sending 'nil' in the 'To' field of the transaction. Check Yellow paper section 7. for more details. This is why CREATE and CREATE2 opcodes do not appear in the bytecode when an EOA deploys a contract.
  CREATE and CREATE2 are how a contract can create another contract.
- The Metadata is an unaccessible code that can never be reached by any tx. Solidity puts this in place to make it easier to identify what version of the compiler is used, what optimisation, how was this compiled ...
- `ffi = true` allows you to execute an arbitrary shell command and capture the output. https://book.getfoundry.sh/forge/differential-ffi-testing
- `evm_version = 'shanghai'` : huff tests always defaults to the wrong evm version (usually Paris version). So we have to mention the evm version to shanghai which has the PUSH0 opcode.
- In order to compile a huff contract with bytecode displaying : `huffc src/horseStoreV1/HorseStore.huff -b = 60008060093d393df3`
- `huffc src/horseStoreV1/HorseStore.huff --bin-runtime` gives only runtime code
- By default, in huff contracts, the `CONSTRUCTOR` will add some bootstrap code that returns the compiled MAIN macro as the contract's runtime bytecode with the constructor arguments concatenated at the end.
- To install huff `forge install huff-language/foundry-huff` install huff library for foundry
- To test only the huff files `forge test --match-path *Huff* -vvvv`
- To compile a pure yul file .yul `solc --strict-assembly --optimize --optimize-runs 2000 ./yul/HorseStoreYul.yul --bin`
- Can also do `solc --strict-assembly --optimize --optimize-runs 2000 ./yul/HorseStoreYul.yul --bin |grep 60` to find the line that have the 60
