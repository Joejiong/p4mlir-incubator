// RUN: p4mlir-translate --typeinference-only %s | FileCheck %s

// NOTE: Assertions have been autogenerated by utils/generate-test-checks.py

action assign() {
    bit<10> res;

    bit<10> lhs = 1;
    bit<10> rhs = 2;

    res = lhs;
    res = lhs + rhs;
}

// CHECK-LABEL:   p4hir.func action @assign()
// CHECK:         %[[VAL_0:.*]] = p4hir.variable ["res"] : <!b10i>
// CHECK:         %[[VAL_1:.*]] = p4hir.const #int1_b10i
// CHECK:         %[[VAL_2:.*]] = p4hir.cast(%[[VAL_1]] : !b10i) : !b10i
// CHECK:         %[[VAL_3:.*]] = p4hir.variable ["lhs", init] : <!b10i>
// CHECK:         p4hir.assign %[[VAL_2]], %[[VAL_3]] : <!b10i>
// CHECK:         %[[VAL_4:.*]] = p4hir.const #int2_b10i
// CHECK:         %[[VAL_5:.*]] = p4hir.cast(%[[VAL_4]] : !b10i) : !b10i
// CHECK:         %[[VAL_6:.*]] = p4hir.variable ["rhs", init] : <!b10i>
// CHECK:         p4hir.assign %[[VAL_5]], %[[VAL_6]] : <!b10i>
// CHECK:         %[[VAL_7:.*]] = p4hir.read %[[VAL_3]] : <!b10i>
// CHECK:         p4hir.assign %[[VAL_7]], %[[VAL_0]] : <!b10i>
// CHECK:         %[[VAL_8:.*]] = p4hir.read %[[VAL_3]] : <!b10i>
// CHECK:         %[[VAL_9:.*]] = p4hir.read %[[VAL_6]] : <!b10i>
// CHECK:         %[[VAL_10:.*]] = p4hir.binop(add, %[[VAL_8]], %[[VAL_9]]) : !b10i
// CHECK:         p4hir.assign %[[VAL_10]], %[[VAL_0]] : <!b10i>
