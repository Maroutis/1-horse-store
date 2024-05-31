
// Contract creation code
// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe

// Runtime code 0x6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fe

// Metadata
// fea2646970667358221220dfb81406f4175d597c0510e67bc1f0d32c7151a364cb30c619ec3f765e4ff06164736f6c63430008140033

// 1. Contract creation code
// @note CREATE and CREATE2 do not appear here because of the following reason :
// An EOA creates a contarct by sending a transaction 'To' an empty address but with input data being the initialization code of the contract being created. In other words, this contract is created by sending 'nil' in the 'To' field of the transaction. Check Yellow paper section 7. for more details.
// CREATE and CREATE2 are how a contract can create another contract
PUSH1 0x80
PUSH1 0x40
MSTORE
// @note it would have been more gas efficient to not do anything with the free memory pointer

CALLVALUE
DUP1
ISZERO
PUSH1 0x0e
JUMPI
PUSH0
DUP1
REVERT
// @note it would have been more gas efficient to not do any check on callvalue. Which in solidity would have been possible by just adding constructor() payable {}

JUMPDEST
POP
PUSH1 0xa5
DUP1
PUSH2 0x001b
PUSH0
CODECOPY
PUSH0
RETURN
INVALID

// 2. Runtime code
PUSH1 0x80
PUSH1 0x40
MSTORE

CALLVALUE
DUP1
ISZERO
PUSH1 0x0e
JUMPI
PUSH0
DUP1
REVERT

JUMPDEST
POP
PUSH1 0x04
CALLDATASIZE // [calldatasize, 0x04]
LT           // [calldatasize < 0x04]   
PUSH1 0x30   // [0x30, calldatasize < 0x04]   
JUMPI

// Function dispatcher
PUSH0
CALLDATALOAD
PUSH1 0xe0
SHR
DUP1
PUSH4 0xcdfead2e // updateHorseNumber  [0xcdfead2e, func_selector, func_selector]
EQ               // 
PUSH1 0x34      
JUMPI           // [func_selector]

DUP1            // [func_selector, func_selector] //@note we removed the dup1 in our huff dispatcher
PUSH4 0xe026c017    // readNumberOfHorses
EQ
PUSH1 0x45
JUMPI           // [function_selector]

//0x30
JUMPDEST
PUSH0
DUP1
REVERT

// update
JUMPDEST            // [func_selector]
PUSH1 0x43          // [0x43, func_selector]
PUSH1 0x3f          // [0x3f, 0x43, func_selector]
CALLDATASIZE        // [calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x04
PUSH1 0x59          // [0x59, 0x04, calldatasize, 0x3f, 0x43, func_selector]
JUMP                // [0x04, calldatasize, 0x3f, 0x43, func_selector]

// destination 0x3f
JUMPDEST            
PUSH0               // [0x00, calldata_arguments, 0x43, func_selector]
SSTORE              // [0x43, func_selector]
JUMP                // [func_selector]

// destination 0x43
JUMPDEST            // [func_selector]
STOP                // [func_selector]

// jump destination 0x45 readNumberOfHorses
JUMPDEST            // [func_selector]
PUSH0               // [0, func_selector]
SLOAD               // [numHorses, func_selector]
PUSH1 0x40          // [0x40, numHorses, func_selector]
MLOAD               // [fmp: 0x80, numHorses, func_selector]
SWAP1               // [numHorses, 0x80, func_selector]
DUP2                // [0x80, numHorses, 0x80, func_selector]
MSTORE              // [0x80, func_selector]
PUSH1 0x20          // [0x20, 0x80, func_selector]
ADD                 // [0xa0, func_selector]
PUSH1 0x40          // [0x40, 0xa0, func_selector]
MLOAD               // [0x80, 0xa0, func_selector] // solidity knows that this is the end of the call so it doesn't store the new value of the free memory pointer
DUP1                // [0x80, 0x80, 0xa0, func_selector]
SWAP2               // [0xa0, 0x80, 0x80, func_selector]
SUB                 // [0xa0 - 0x80, 0x80, func_selector]
SWAP1               // [0x80, 0xa0 - 0x80, func_selector]
RETURN              // [func_selector]

// Jump of 0x59 of update
JUMPDEST        // [0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH0
PUSH1 0x20      // [0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP3            // [0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP5            // [calldatasize, 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
SUB             // [calldatasize - 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
SLT             // [calldatasize - 0x04 < 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
ISZERO          // [more_data_than_selector?, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1 0x68      // [0x68, calldatasize - 0x04 < 0x20 == true, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
JUMPI           // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]

// Revert if not enough arguments
PUSH0
DUP1
REVERT

// jump 0x68
JUMPDEST        // [0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
POP             // [ 0x04, calldatasize, 0x3f, 0x43, func_selector]
CALLDATALOAD    // [calldata_arguments, calldatasize, 0x3f, 0x43, func_selector]
SWAP2           // [0x3f, calldatasize, calldata_arguments, 0x43, func_selector]
SWAP1           // [calldatasize, 0x3f, calldata_arguments, 0x43, func_selector]
POP             // [0x3f, calldata_arguments, 0x43, func_selector]
JUMP            // jump to destination 0x3f

// 3. Metadata, @note unaccessible code that can never be reached by any tx. SOlidity puts this in place to make it easier to identify what version of the compiler is used, what optimisation, how was this compiled ...
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
INVALID
EQ
MOD
DELEGATECALL
OR
TSTORE
MSIZE
PUSH29 0x0510e67bc1f0d32c7151a364cb30c619ec3f765e4ff06164736f6c6343
STOP
ADDMOD
EQ
STOP
CALLER