// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.20;

import {Base_TestV1, HorseStore} from "./Base_TestV1.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

// @note forge install huff-language/foundry-huff install huff library for foundry
// @note for testing only the huff files forge test --match-path *Huff* -vvvv
contract HorseStoreHuff is Base_TestV1 {
    string public constant HORSE_STORE_HUFF_LOCATION = "horseStoreV1/HorseStore"; // place of the huff contract
    function setUp() public override{
        horseStore = HorseStore(HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION)); // deploy using the huff contract
    }
}