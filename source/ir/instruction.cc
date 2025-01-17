//
// Created by SwiftGan on 2021/1/2.
//

#include "instruction.h"

namespace Svm::IR {

    Optional<u8> Instruction::GetIndex(Value &value) {
        for (u8 index = 0; index < MAX_OPERANDS; index++) {
            if (operands[index].IsValue()) {
                if (GetParam<Value>(index).GetId() == value.GetId()) {
                    return index;
                }
            }
        }
        return {};
    }

}
