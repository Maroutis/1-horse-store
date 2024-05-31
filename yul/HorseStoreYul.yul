// @note to compile the code solc --strict-assembly --optimize --optimize-runs 2000 ./yul/HorseStoreYul.yul --bin
// can do solc --strict-assembly --optimize --optimize-runs 2000 ./yul/HorseStoreYul.yul --bin |grep 60 to find the line that have the 60
object "HorseStoreYul" { // similar to contract
    code {
        // Contract deployment
        datacopy(0, dataoffset("runtime"), datasize("runtime")) // similar to codecopy with 3 arguments : offset in memory, offset in current code, size of code to copy
        return(0, datasize("runtime"))
    }
    object "runtime" {
        code {
            // function dispatcher
            switch selector()
            // updateHorseNumber(uint256)
            case 0xcdfead2e {
                storeNumber(decodeAsUint(0))
            }
            // readNumberOfHorses
            case 0xe026c017 {
                returnUint(readNumber())
            }

            default {
                revert(0,0)
            }

            /* -- decoding functions --*/
            function selector() -> s {
                s := div(calldataload(0), 0x100000000000000000000000000000000000000000000000000000000)
            }

            function storeNumber(newNumber){
                sstore(0, newNumber)
            }

            function readNumber() -> storedNumber{
                storedNumber := sload(0)
            }

            function decodeAsUint(offset) -> v {
                let positionInCalldata := add(4, mul(offset, 0x20))
                if lt(calldatasize(), add(positionInCalldata, 0x20)) {
                    revert(0, 0)
                }
                v := calldataload(positionInCalldata)
            }

            function returnUint(v) {
                mstore(0, v)
                return(0, 0x20)
            }
        }
    }
}

// @note bytecode result 603680600a5f395ff3fe5f803560e01c8063cdfead2e1460245763e026c01714601b5780fd5b80602091548152f35b50602436106033576004359055005b80fd -> Create this contract using create function in a test file